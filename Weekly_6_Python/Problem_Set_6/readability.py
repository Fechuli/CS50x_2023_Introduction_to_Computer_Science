from cs50 import get_string
import math


def count_letters(txt):
    count_l = 0
    for char in txt:
        if char.isalpha():
            count_l += 1
    return count_l


def count_words(txt):
    words = txt.split()
    return len(words)


def count_sentences(txt):
    count_s = 0
    for char in txt:
        if char in [".", "!", "?"]:
            count_s += 1
    return count_s


def manual_round(nmb):
    return int(nmb + 0.5) if nmb >= 0 else int(nmb - 0.5)


def main():
    txt = get_string("Text: ")

    count_l = count_letters(txt)
    count_w = count_words(txt)
    count_s = count_sentences(txt)

    L = (count_l / count_w) * 100
    S = (count_s / count_w) * 100
    index = manual_round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
