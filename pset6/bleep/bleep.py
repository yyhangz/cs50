from cs50 import get_string
from sys import argv
from sys import exit


def main():
    # Check if there is only 1 command line argument
    if len(argv) != 2:
        print("usage: python bleep.py banned.txt")
        exit(1)

    # Add banned words from banned.txt to set
    banned = set()
    file = open(argv[1], "r")
    for line in file:
        banned.add(line.rstrip("\n"))
    file.close()

    # Prompts user for sentence to be censored
    raw = get_string("What message would you like to censor?\n")
    words = raw.split(" ")

    # Return sentence with censor
    for word in words:
        fword = word.lower()
        if fword in banned:
            for i in range(len(word)):
                print("*", end="")
            print(" ", end="")
        else:
            print(f"{word} ", end="")
    print()


if __name__ == "__main__":
    main()