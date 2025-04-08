# Task 5

Codes are also available at: https://github.com/lorenzobore/ScientificComputing

### Task 5.a - Floating point

Due to the numeric precision required by the calculation, the sum returns the wrong result -0.5 for the three methods, even with Kahan Algorithm.

```
Vector instantiated as: [1,10000000000000000,-10000000000000000,-0.5]
Result from for loop = -0.5
Somma degli elementi con GSL = -0.5
Result with KahanSum = -0.5

```

To make this effect disappear it is sufficient to reduce the highest values by a factor 10:

```
Vector instantiated as: [1,1000000000000000,-1000000000000000,-0.5]
Result from for loop = 0.5
Somma degli elementi con GSL = 0.5
Result with KahanSum = 0.5
--------------------
```


### Task 5.6 - Random

I filled the two variables x and y with 10000 values sampled froma Gaussian with mean=0 and std=1, using `double xi = gsl_ran_gaussian(rng, 1.0);` function from GSL.

Then, I performed the Daxpy Algorithm witth A=1.0:
```
// Compute D = A * x
gsl_vector_memcpy(D, x);           // D = x
gsl_vector_scale(D, A);           // D = A * x
gsl_vector_add(D, y);             // D = A * x + y
```

Eventually, I printed the mean and std of the new distribution D and checked that were compatible with $\mu=0$ and $\sigma=\sqrt{1^2+1^2}=\sqrt{2}$.


```
Stats for vector D:
Mean: -0.00699
Standard Deviation: 1.41282
```