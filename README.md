
## Intuition behind mandelbrot and julia sets

### Julia set

If by iterating a formula
```py
Zn = (Zn-1)^2 + C
```
the distance of the point Z to the center is < than 2, then the point is in the Julia set thus colored in black.

To generate it, the Z complex number will represent a pixel on the screen, with x the real part of the complex and y the imaginary part. Then we'll cherry pick a C, a different C would generate a different set of Julia. So basically, a 
```py
Z + C
```
combo would be in the set of Julia, if after iterating x number of time the suite, the point Z would stay in a distance of 2 of the center.


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

## How to compute mandelbrot

[naive vs optimized approach](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set)

## Further optimizations

At this point, using the optimized escape algorithm made the thing usable in low resolution / low iterations on my computer. Since I will probably not make it go faster using mathematics, so lets just ask the computer to compute faster.

### Threads

Threads pool implementation, each threads multiple of n line.
So with 600 pixel height image and 10 threads, each threads would compute 60 lines.
But how to do it without the need of mutex? We should just pop the threads at start, they wait until we start rendering, then they compute, set the pixel
in images to the computed values and go back to waiting.


### SIMD instructions

SIMD, for Single Instruction Multiple Data, is a set of instructions that don't
execute on scalar values (like numbers), but rather on vectors, using less cycle to compute results proportionally to the number of scalar values. [YoutubeVideo](https://www.youtube.com/watch?v=o_n4AKwdfiA) is a short introduction to SIMD.

For examples, where you would put a single multiplication in your code, you could rewrite it so that the multiplication actually multiple 4 8 or more numbers at the same time(instruction).

In the case you were wondering why not using GPU instead of CPU for rendering, its just that I prefer to learn SIMD beforehand, since this repository just is a school project. If its not your case, go with GPU.

#### Can my computer run SIMD instructions?

linux
```bash
cat /proc/cpuinfo
```

macos
```
sysctl -a | grep machdep.cpu.features
```

and look forward for `avx`, `sse` and `mmx`.

#### Applying SIMD on Mandlebrot computing

Ok, so how will it help in our quest to speed?
Well, let's take the `mandlebrot` function that's job is to estimate if a complex number(coordinate of a pixel) actually is in the Mandelbrot set:

```c
int	mandelbrot(t_state *state, t_complex *c, int iteration)
{
	t_complex	z;
	double		x2;
	double		y2;
	double		w;
	int 		i;

	i = 0;
	z.r = 0;
	z.i = 0;
	x2 = 0;
	y2 = 0;
	w = 0;
	while ((x2 + y2 <= 4.0) && (i < iteration))
	{
		z.r = x2 - y2 + c->r;
		z.i = w - x2 - y2 + c->i;
		x2 = z.r * z.r;
		y2 = z.i * z.i;
		w = (z.r + z.i) * (z.r + z.i);
		++i;
	}
	return (i);
}
```

We use a lot of arithmetic to compute each pixel, since the result of one doesn't depend on the result of another, this code is **parallelizable**.

Note that you should always check that your compiler hasn't already optimized your code using SIMD instructions by disassembling your binary.


## COLOR 
color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));