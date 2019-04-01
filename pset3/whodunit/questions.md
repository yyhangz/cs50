# Questions

## What's `stdint.h`?

The stdint.h header defines sets of integer types with specific widths, corresponding sets of macros, and specifies the limit of integer types

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Using 'uint8_t', 'uint16_t' and 'uint32_t' defines an integer with a width of 8, 16 and 32 bits respectively, without a specified sign (values > 0), while 'int32_t' defines an integer with a width of 32 bits, using the first bit as the signing bit (to indicate >= 0 or < 0).

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM (file type)

## What's the difference between `bfSize` and `biSize`?

'bfSize' refers to the size of the bitmap file, in bytes, while 'biSize'refers to the size required by the structure, in bytes.

## What does it mean if `biHeight` is negative?

When 'biHeight' is negative, it means that the bitmap is top-down DIB with the origin at the upper-left.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

Either the 2nd or 3rd arguments (or both) are arguments to invalid files(files that are not named the same as the arguments) in the current directory, and hence fopen will not point to a valid address and return NULL instead.

## Why is the third argument to `fread` always `1` in our code?

The 3rd argument in 'fread' indicates the number of elements in the array, and the bmp file copied is simply an array with 1 element containing the contents of the file.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It sets the pointer location associated with stream to a new position specified by the 2nd and 3rd arguments.

## What is `SEEK_CUR`?

It indicates the current file pointer location in stream.
