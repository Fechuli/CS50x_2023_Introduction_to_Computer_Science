-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Let us first analyze what happened at the crime scene.

SELECT description FROM crime_scene_reports WHERE year = 2021 AND day = 28 AND month = 7;

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- It's time to take a look at the interviews

SELECT transcript, name, year FROM interviews;
SELECT transcript, name, day FROM interviews WHERE month = 7;

-- Digging through the interviews I managed to retrieve three interesting ones which I transcribe below.

-- Barbara says: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--               If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- Ruth says:    I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--               I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Eugene says:  As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--               In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--               The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Ruth talks about ATM on Legget Street. Maybe i can check the operations.
-- Barbara talks about bakery parking and security footage.
-- Eugene talks about the fact that the thief would take the first flight out of Fiftyville 29/07.

-- Let's start with Ruth.

SELECT account_number, amount
FROM atm_transactions
WHERE atm_location = "Legget Street"
AND year = 2021
AND day = 28
AND month = 7
AND transaction_type = "withdraw";

-- This operation gave me access to 8 operations that occurred that day.

-- +----------------+--------+
-- | account_number | amount |
-- +----------------+--------+
-- | 28500762       | 48     |
-- | 28296815       | 20     |
-- | 76054385       | 60     |
-- | 49610011       | 50     |
-- | 16153065       | 80     |
-- | 25506511       | 20     |
-- | 81061156       | 30     |
-- | 26013199       | 35     |
-- +----------------+--------+

-- It is time to verify who performed those operations.

SELECT people.name, atm_transactions.amount
FROM people, bank_accounts, atm_transactions
WHERE people.id = bank_accounts.person_id
  AND bank_accounts.account_number = atm_transactions.account_number
  AND atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';

-- Through this research we receive this data

-- +---------+--------+
-- |  name   | amount |
-- +---------+--------+
-- | Bruce   | 50     |
-- | Diana   | 35     |
-- | Brooke  | 80     |
-- | Kenny   | 20     |
-- | Iman    | 20     |
-- | Luca    | 48     |
-- | Taylor  | 60     |
-- | Benista | 30     |
-- +---------+--------+

-- We now all know the names of the people who performed operations on the day of the theft.
-- Our culprit is among these eight people.

-- Now is the time to retrieve the information that Barbara gave us.

SELECT people.name, bakery_security_logs.hour, bakery_security_logs.minute
FROM people
INNER JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.activity = 'exit'
  AND (bakery_security_logs.hour = 10 AND bakery_security_logs.minute BETWEEN 15 AND 25)
ORDER BY bakery_security_logs.minute;

-- +---------+------+--------+
-- |  name   | hour | minute |
-- +---------+------+--------+
-- | Vanessa | 10   | 16     |
-- | Bruce   | 10   | 18     |
-- | Barry   | 10   | 18     |
-- | Luca    | 10   | 19     |
-- | Sofia   | 10   | 20     |
-- | Iman    | 10   | 21     |
-- | Diana   | 10   | 23     |
-- | Kelsey  | 10   | 23     |
-- +---------+------+--------+

-- The people who match so far are Bruce, Luca, Iman, and Diana.

-- We return from Eugene and go to analyze the first flight of the day on the 29th.

SELECT airports.full_name, airports.city, flights.hour, flights.minute
FROM flights
JOIN airports ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id IN (SELECT id FROM airports WHERE city = 'Fiftyville')
  AND flights.year = 2021
  AND flights.month = 7
  AND flights.day = 29
ORDER BY flights.hour;

-- Now we have all the flights that started from Fiftyville's airport.

-- +-------------------------------------+---------------+------+--------+
-- |              full_name              |     city      | hour | minute |
-- +-------------------------------------+---------------+------+--------+
-- | LaGuardia Airport                   | New York City | 8    | 20     |
-- | O'Hare International Airport        | Chicago       | 9    | 30     |
-- | San Francisco International Airport | San Francisco | 12   | 15     |
-- | Tokyo International Airport         | Tokyo         | 15   | 20     |
-- | Logan International Airport         | Boston        | 16   | 0      |
-- +-------------------------------------+---------------+------+--------+

-- The first flight leaves at 8:20 a.m. and heads to LaGuardia Airport so let's focus on that.
-- We need to know who got on that plane.

SELECT people.name
FROM passengers
JOIN people
  ON passengers.passport_number = people.passport_number
JOIN flights
  ON passengers.flight_id = flights.id
WHERE flights.month = 7
  AND flights.day = 29
  AND flights.hour = 8
  AND flights.minute = 20
ORDER BY passengers.passport_number;

-- Now we have all the passengers.

-- +--------+
-- |  name  |
-- +--------+
-- | Edward |
-- | Sofia  |
-- | Taylor |
-- | Bruce  |
-- | Doris  |
-- | Kelsey |
-- | Luca   |
-- | Kenny  |
-- +--------+

-- Going by exclusion, my suspects now are Luke and Bruce who appear respectively
-- on the list of people who picked up at the ATM and left the bakery parking lot.

-- Eugene also said that the thief called someone.
-- I have to figure out who was the accomplice who helped him.
-- From the phone records I can trace this information and conclude the mystery.

SELECT people.name, phone_calls.duration
FROM phone_calls
JOIN people
  ON people.phone_number = phone_calls.caller
WHERE phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;

-- We have all the phone calls that occurred that day that lasted less than a minute.

-- +---------+----------+
-- |  name   | duration |
-- +---------+----------+
-- | Kelsey  | 36       |
-- | Carina  | 38       |
-- | Taylor  | 43       |
-- | Bruce   | 45       |
-- | Diana   | 49       |
-- | Kelsey  | 50       |
-- | Sofia   | 51       |
-- | Benista | 54       |
-- | Kenny   | 55       |
-- | Kathryn | 60       |
-- +---------+----------+

SELECT people.name, phone_calls.duration
FROM phone_calls
JOIN people
  ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;

-- Let us now check who received the call and compare the durations.

-- +------------+----------+
-- |    name    | duration |
-- +------------+----------+
-- | Larry      | 36       |
-- | Jacqueline | 38       |
-- | James      | 43       |
-- | Robin      | 45       |
-- | Philip     | 49       |
-- | Melissa    | 50       |
-- | Jack       | 51       |
-- | Anna       | 54       |
-- | Doris      | 55       |
-- | Luca       | 60       |
-- +------------+----------+

-- We finally have a square of the situation.
-- Bruce is clearly the thief as he is present in all 4 lists I analyzed.
-- Robin was the accomplice who bought the ticket for Bruce.
-- His intent was to fly to New York and get away with it.
-- Unfortunately for him, we are here to foil his plans.