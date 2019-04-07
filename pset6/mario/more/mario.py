from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(height):
    for j in range(height - (i + 1)):
        print(f" ", end="")
    for k in range(i + 1):
        print(f"#", end="")
    print("  ", end="")
    for l in range(i + 1):
        print(f"#", end="")
    print("")