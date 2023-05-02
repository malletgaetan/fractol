## How to use

**tested on Debian:11.6 and Ubuntu:22.10 only.**

Clone the repository
```bash
git clone https://github.com/malletgaetan/fractol.git
```

Build the binary
```bash
cd fractol
make
```

Execute the binary
```bash
./fractol "mandelbrot"
```

## How to compute mandelbrot

[naive vs optimized approach](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set)

If you don't have enough, better solutions would be:

- use SIMD instructions
- use threads
- use your graphics card

[here](https://github.com/bisqwit/cpp_parallelization_examples) is a nice repository that compare these solutions.

## Intuition

If by iterating a formula
```py
Zn = (Zn-1)^2 + C # Z and C being complex numbers
```
if the distance of the point Z to the center is closer than 2, the point is considered in the Julia set, thus colored in black.

To generate it, the Z complex number will represent a pixel on the screen, with x the real part of the complex and y the imaginary part. Then we'll cherry pick a C, a different C would generate a different set of Julia. So basically, a 
```py
Z + C
```
combo would be in the set of Julia, if after iterating a certain number of time the suite, the point Z would remain at the maximum distance of 2 from the center `(0,0)`.


## Complex numbers arithmetic

In our case, we'll only square and add complex numbers so:

addition
```py
Z + W = Z.r + Z.r + Z.i + W.i
```

multiplicaton
```py
Z * Z = Z.r^2 + 2 * Z.r * Z.i + Z.i^2

example:
Z = 2 - 5i

Z * Z = 2^2 + (2 * 2 * 5) + (5^2 - i^2)
since i^2 == -1 we have:
Z * Z = 2^2 + (2 * 2 * 5) - 25
Z^2 = -21 -20i
```
