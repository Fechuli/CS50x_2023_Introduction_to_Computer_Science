SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
JOIN stars AS bacon_stars ON movies.id = bacon_stars.movie_id
JOIN people AS bacon ON bacon_stars.person_id = bacon.id
WHERE bacon.name = 'Kevin Bacon' AND bacon.birth = 1958
AND people.name != 'Kevin Bacon';