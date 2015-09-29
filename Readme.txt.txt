Author: Jason Bromfield
Purpose: To encode/decode input
Files: a1.c, encode.txt, decode.txt

Also a version written in java and python

Compile using command “gcc a1.c -lm -std=c99 -o a1”
Run using “./a1”, ”./a1 < decode.txt” or “./a1 < encode.txt”


Note: This program checks for out of bounds errors but not type errors so if you enter a non-numeric key value the character at the first position gets turned into its ASCII value and that is used.