# Number theory

Two small C programs from the public-key cryptography course, written before the RSA and McEliece work in Python.

`bigint-gcd.c` computes the greatest common divisor of large integers kept as decimal strings, so the size is not limited by a machine word. The same pairs are run through the Euclidean algorithm, the binary GCD and a subtraction version, and each run is timed with a monotonic clock.

`primes-and-carmichael.c` covers the checks those cryptosystems rely on: trial division, the sieve of Eratosthenes, a square-free test, and a search for Carmichael numbers (composite numbers that pass the Fermat test for bases coprime to them).

Technologies: C.
