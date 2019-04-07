from sys import argv
from sys import exit
import crypt

def click(char):
    is_end = False
    if not char:
        char = 'A'
    elif char == 'Z':
        char = 'a'
    elif char == 'z':
        char = 'A'
        is_end = True
    else:
        char = chr(ord(char) + 1)
    return char, is_end

def crack(pw, salt):
    s = ''.join(pw)
    if crypt.crypt(s, salt) == argv[1]:
        print(f"{s}")
        exit(42)
    print(f"{s}")
    pw[0], is_end = click(pw[0])
    cur = 1
    while is_end:
        pw[cur], is_end = click(pw[cur])
        cur += 1
    crack(pw, salt)


if len(argv) != 2:
    print("usage: python crack.py hash")
    exit(1)

# Get salt
salt = argv[1][:2]
print(f"salt is {salt}")
print(f"argv1 is {argv[1]}")

pw = ['A', '', '', '', '']
crack(pw, salt)