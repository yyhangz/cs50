from sys import argv
from sys import exit
import crypt

def click(char):
    if not char:
        char = 'A'
    elif char == 'Z':
        char = 'a'
    elif char == 'z':
        char = 'A'
    else:
        char = chr(ord(char) + 1)
    return char


if len(argv) != 2:
    print("usage: python crack.py hash")
    exit(1)

# Get salt
salt = argv[1][:2]

# Crack password
pw = ['', '', '', '', '']
for i in range(53):
    for j in range(53):
        for k in range(53):
            for l in range(53):
                for m in range(52):
                    pw[0] = click(pw[0])
                    s = ''.join(pw)
                    if crypt.crypt(s, salt) == argv[1]:
                        print(f"{s}")
                        exit(42)
                pw[1] = click(pw[1])
                m = 0
            pw[2] = click(pw[2])
            l = 0
        pw[3] = click(pw[3])
        k = 0
    pw[4] = click(pw[4])
    j = 0