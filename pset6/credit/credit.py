from cs50 import get_int
import sys

# Get users card number info
while True:
    card = get_int("Number: ")
    if card > 0:
        break
card_copy = str(card)
cardlen = len(card_copy)

# Calculate sum of digits of product of every other digit and 2
curdig = cardlen - 2
totalsum = 0
while True:
    i = int(card_copy[curdig]) * 2
    if i > 9:
        i = 1 + (i % 10)
    totalsum += i

    if (curdig - 2) < 0:
        break
    curdig -= 2

# Add to sum the digits that weren't multiplied by 2
curdig = cardlen - 1
while True:
    i = int(card_copy[curdig])
    totalsum += i

    if (curdig - 2) < 0:
        if (totalsum % 10) != 0:
            print("INVALID")
            exit()
        else:
            break

    curdig -= 2

# Check card type
if cardlen == 15 and card_copy[0] == "3" and (card_copy[1] == "4" or card_copy[1] == "7"):
    print("AMEX")
elif cardlen == 13 and card_copy[0] == "4":
    print("VISA")
elif cardlen == 16:
    if card_copy[0] == "4":
        print("VISA")
    elif card_copy[0] == "5" and int(card_copy[1]) > 0 and int(card_copy[1]) < 6:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")