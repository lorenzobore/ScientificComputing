# Task 6

Codes are also available at: https://github.com/lorenzobore/ScientificComputing. For this task I chose to use `julia` instead of `C` to have some varation with respect to the past tasks.

### Task 6.0

I created a matrix A of size (1000,1000) filled with a gaussian random variable with mean one and standard deviation one, and I eventually made it of rank 2 by setting to zero the smalest singular values
```
using Random, Distributions, LinearAlgebra, FFTW

# Set the random seed
Random.seed!(3)

# Define the normal distribution with mean 1 and std dev 1
dist = Normal(1.0, 1.0)

# Create a 1000x1000 matrix filled with random values from the distribution
A = rand(dist, 1000, 1000)

# Reduce A to rank 2 using SVD
U, S, V = svd(A)
S[3:end] .= 0.0 
A = U * Diagonal(S) * V'
```


### Task 6.1
I performed a complex-to-complex Fourier Transform over A and called the result as C:
```
# 1) Perform c2c FFT
C = fft(A)
```

### Task 6.2
I reconstructed matrix A applying the inverse transformation and checked on the absolute and relative reconstruction errors:
```
# 2) Reconstruct A, take its real  part
A_reconstructed = ifft(C)
A_reconstructed = real.(A_reconstructed)
```

The output being:
```
(c2c) Reconstruction Error Stats:
  RMSE (absolute): 2.929509862391095e-16
  RMSE (relative): 2.926404212369386e-16
  Median RMSE (absolute): 2.220446049250313e-16
  Median RMSE (relative): 2.1445383615035936e-16
```

### Task 6.3
Then I performed a real-to-complex Fourier Transform over A and called the result as R:
```
#3) Now perform r2c FFT
R = rfft(A)
```

### Task 6.4
And again, I reconstructed matrix A applying the inverse transformation and checked on the absolute and relative reconstruction errors:
```
#4) Reconstruct A from R
A_real_reconstructed = irfft(R, 1000) 
```

The output being:
```
(r2c) Reconstruction Error Stats:
  RMSE (absolute): 2.866635905155763e-16
  RMSE (relative): 2.866125495655274e-16
  Median RMSE (absolute): 2.220446049250313e-16
  Median RMSE (relative): 2.1396890813817935e-16
```

### Task 6.5

```
Machine epsilon is: 2.220446049250313e-16
Machine precision is reached for c2c FFT!
Machine precision is reached for r2c FFT!
```


### Task 6.6

The values of `C[0,0]` and `R[0,0]` refer to the zero-frequency term of the Fourier Transform, therefore they both represent the mean of the original matrix A.

```
C[0, 0]: 1.000794923115816e6 + 0.0im
R[0, 0]: 1.000794923115816e6 + 0.0im
Mean of A: 1.000794923115816
```

### Task 6.7 (Bonus)

```
# Create new matrix A
dist = Normal(1.0, 1.0)
A = rand(dist, 6, 6)

# Perform r2c FFT
R = rfft(A, 1)

# actual c2c FFT
C_actual = fft(A,1)

# Create an empty array of the same size as fft output would be
C_reconstructed = Array{ComplexF64}(undef, 6, 6)
println("Size of C_reco: ", size(C_reconstructed))

# Copy the real part of R to C_reconstructed
C_reconstructed[1:4,:] .= R  

# Now, mirror the positive frequencies to create the full spectrum
for i in 2:3
    C_reconstructed[7 - i + 1, :] .= conj(R[i, :])
end

# Now compare with actual fft
println("C_reconstructed ≈ C_actual? ", isapprox(C_reconstructed, C_actual))
println("Max abs error: ", maximum(abs.(C_reconstructed .- C_actual)))

```


Output:


```
C_reconstructed ≈ C_actual? true
Max abs error: 0.0
```

