from sys import argv
from sys import exit
from cs50 import get_string

if len(argv) != 2:
    print("usage: python caesar.py key")
    exit(1)

key = int(argv[1]) % 26
raw = get_string("plaintext: ")

# Print encrypted text
print("ciphertext: ", end="")
for c in raw:
    if c.islower():
        print(f"{chr(ord('a') + (ord(c) + key - ord('a')) % 26)}", end="")
    elif c.isupper():
        print(f"{chr(ord('A') + (ord(c) + key - ord('A')) % 26)}", end="")
    else:
        print(f"{c}", end="")
print("")