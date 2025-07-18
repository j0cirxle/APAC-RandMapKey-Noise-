# APAC (RandMapKey-Noise) Encryption Method

**APAC (RandMapKey-Noise)** is a cipher that combines ASCII code prime factorization with randomized offsets and noise to enhance security and obfuscation.

## Overview

- Each character's ASCII code is incremented by a random offset (`random`).
- For every even-indexed character (1-based), an additional noise value (`noise`) is added.
- The modified ASCII values are factorized into prime factors.
- Each prime factor is mapped to a letter according to a predefined key map.
- Repeated prime factors are compressed using run-length encoding.
- The cipher text starts with the two random values (`random` and `noise`) necessary for decryption.

## Decryption Process

- The cipher text is parsed to extract `random` and `noise`.
- Each encoded block is converted back to prime factors and multiplied to recover the modified ASCII code.
- For odd-indexed characters, only `random` is subtracted.
- For even-indexed characters, both `random` and `noise` are subtracted.
- The resulting ASCII codes are converted back to the original characters.

## Advantages

- Adds randomness and noise to prevent frequency and pattern analysis.
- Same characters are encrypted differently depending on position, increasing complexity.
- Run-length encoding reduces cipher length for repeated factors, improving efficiency.

## Use Cases

This method is suitable for lightweight encryption where obfuscation and simple randomness help resist basic cryptanalysis without heavy computational overhead.

---
