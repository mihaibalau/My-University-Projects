# Public-key crypto

Implementations from the public-key cryptography course. The number-theory pieces in C (big-integer GCD, primes, Carmichael numbers) are in `C/Number theory`. This folder is the part that actually encrypts text.

`rsa.py` is RSA without a library: extended Euclid for the modular inverse, choice of `e`, block size from the modulus, and encrypt/decrypt of text turned into integer blocks. `rsa_server.py` and `rsa_client.py` use that for a small multi-client chat. The server picks two primes, generates the key pair and sends it to each client. Clients check that a message is only letters and spaces before encrypting, and they check the ciphertext shape before decrypting. Sockets and one thread per client.

`pollard_p1.py` is Pollard's p-1 factorization: LCM of `1..B`, then `gcd(a^k - 1, n)`.

`mceliece.py` is the McEliece cryptosystem on binary Goppa codes, with a 27-letter alphabet (space and A-Z, 5 bits each). The public key is the generator matrix hidden by a scrambling matrix and a permutation. Encryption adds an error vector. The server and client next to it repeat the chat idea with those keys, including checks that a received block has the right length and only bits.

Technologies: Python, sockets, threading, NumPy.
