from sys import argv
from sys import exit
from cs50 import get_string

# Check validness of command line argument
if len(argv) != 2:
    print("usage: python vigenere.py keyword")
    exit(1)
if not argv[1].isalpha():
    print("keyword should be entirely alphabetical")
    exit(1)

# Generate keyword
keyword = []
argv[1] = argv[1].upper()
keylen = len(argv[1])
for i in range(keylen):
    keyword.append(int(ord(argv[1][i]) - ord('A')))

# Convert plain text to cipher text
raw = get_string("plaintext: ")
curkey = 0
print("ciphertext: ", end="")
for c in raw:
    if c.islower():
        print(f"{chr(ord('a') + (ord(c) + keyword[curkey] - ord('a')) % 26)}", end="")
        curkey = (curkey + 1) % keylen
    elif c.isupper():
        print(f"{chr(ord('A') + (ord(c) + keyword[curkey] - ord('A')) % 26)}", end="")
        curkey = (curkey + 1) % keylen
    else:
        print(f"{c}", end="")
print()