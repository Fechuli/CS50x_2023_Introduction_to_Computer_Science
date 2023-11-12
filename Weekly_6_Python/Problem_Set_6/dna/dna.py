import csv
import sys


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    db = read_db(sys.argv[1])

    dna_seq = read_dna_sqc(sys.argv[2])

    str_counts = {}
    for key in db[0].keys():
        if key != "name":
            str_counts[key] = longest_match(dna_seq, key)

    matchingProfiles = []
    for person in db:
        isMatch = all(int(person[key]) == str_counts[key] for key in str_counts)
        if isMatch:
            matchingProfiles.append(person["name"])

    if matchingProfiles:
        print("".join(matchingProfiles))
    else:
        print("No match")

    return


def read_db(fileName):
    with open(fileName) as file:
        reader = csv.DictReader(file)
        db = [row for row in reader]
    return db


def read_dna_sqc(fileName):
    with open(fileName) as file:
        dna_sqc = file.read().strip()
    return dna_sqc


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
