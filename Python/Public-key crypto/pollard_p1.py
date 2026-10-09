import math
from math import gcd


def lcm(a, b):
    return abs(a * b) // gcd(a, b)


def pollard_p_minus_1(n, B=None, max_a=100):

    if B is None:
        B = int(n ** 0.25) + 2

    # Calculate k = lcm(1, 2, 3, ..., B)
    k = 1
    for i in range(1, B + 1):
        k = lcm(k, i)

    # Try different values of a
    for a in range(2, min(max_a, n - 1)):
        # Calculate a^k mod n
        ak = pow(a, k, n)

        # Calculate gcd(a^k - 1, n)
        d = gcd(ak - 1, n)

        if d > 1 and d < n:
            # Found a factor!
            other = n // d
            return (min(d, other), max(d, other))

        if d == n:
            # Failure with this a, try next
            continue

    return None


# Main
if __name__ == "__main__":

    # (n, B)
    numbers = [
        (1241143, 13),
        (6721, None),
    ]

    for n, B in numbers:
        print(f"\nFactorizing n = {n} with B = {B}")
        result = pollard_p_minus_1(n, B)

        if result:
            a, b = result
            print(f"  Factors: {a} × {b}")
            print(f"  Verification: {a * b == n}")
        else:
            print("  No factor found")