﻿# Arithmetic Encoding

Arithmetic encoding is a type of entropy-encoding used in lossless data compression. It is essentially a generalization of the well-known huffman encoding and allows symbols to have fractional bit representation(when the number of bits per symbol are averaged).

This implementation is heavily inspired by BillBird's implementation of AC: https://youtu.be/xt3uNibQWlQ?si=9uoEKW_WJ8i42cj-

Symbols: 8-bit/ASCII Representation.

Precision: 32 bits.  

It is recommended to have 32 extra bits to account for overflow.

## Details about implementation

- The character 256 is used as the EOS character
- When the MSB matches between the lower and upper range, it is sent to the output bit stream
- An Underflow counter is used to keep track of the 'underflow' problem while implementing arithmetic coding

![screenshot](ArithmeticCoding.png)'

Use this implementation with

```
./arith_compress < some_input_file > encoded_output
./arith_decompress < encoded_output > reconstructed_input_file
```

## Future improvements

- Write the implementation in python since python natively supports bigint arithmetic
- Have the python implementation work with LLM data compression i.e the input is an array of ranks with rank 0 being the most likely token
