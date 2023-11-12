from cs50 import get_int


def main():
    nmb = get_int("Number: ")
    p_nmb = nmb

    count = 0
    while p_nmb > 0:
        count += 1
        p_nmb //= 10

    p_nmb = nmb
    sum = 0
    scnd = False

    while nmb > 0:
        digit = nmb % 10
        if scnd:
            digit *= 2
            if digit > 9:
                digit -= 9

        sum += digit
        scnd = not scnd
        nmb //= 10

    while p_nmb >= 100:
        p_nmb //= 10

    if sum % 10 == 0:
        if (p_nmb // 10 == 4) and (count == 13 or count == 16):
            print("VISA")
        elif (p_nmb >= 51 and p_nmb <= 55) and count == 16:
            print("MASTERCARD")
        elif (p_nmb in [34, 37]) and count == 15:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
