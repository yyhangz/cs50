from cs50 import get_float


def calc(value, change, total_coins):
    coins = change // value
    change -= (value * coins)
    total_coins += coins
    return total_coins, change


while True:
    change = get_float("Change owed: ")
    if change > 0:
        change *= 100
        break

coins = 0

# Calculate quarters
coins, change = calc(25, change, coins)

# Calculate dimes
coins, change = calc(10, change, coins)

# Calculate nickels
coins, change = calc(5, change, coins)

# Calculate pennies
coins, change = calc(1, change, coins)

coins = int(coins)

print(f"{coins}")