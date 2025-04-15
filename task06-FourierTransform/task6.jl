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


# 1) Perform c2c FFT
C = fft(A)

# 2) Reconstruct A, take its real  part
A_reconstructed = ifft(C)
A_reconstructed = real.(A_reconstructed)

# Absolute error
abs_error = A_reconstructed .- A

# Relative error (element-wise)
relative_error = abs_error ./ A

# RMSE and Median RMSE
rmse_abs = sqrt(mean(abs_error .^ 2))
rmse_rel = sqrt(mean(relative_error .^ 2))

median_rmse_abs = sqrt(median(abs_error .^ 2))
median_rmse_rel = sqrt(median(relative_error .^ 2))


println("(c2c) Reconstruction Error Stats:")
println("  RMSE (absolute): $rmse_abs")
println("  RMSE (relative): $rmse_rel")
println("  Median RMSE (absolute): $median_rmse_abs")
println("  Median RMSE (relative): $median_rmse_rel")
println("\n")  
#3) Now perform r2c FFT
R = rfft(A)

#4) Reconstruct A from R
A_real_reconstructed = irfft(R, 1000) 

# Absolute error
abs_error_r2c = A_real_reconstructed .- A

# Relative error (element-wise)
relative_error_r2c = abs_error_r2c ./ A

# RMSE and median RMSE
rmse_abs_r2c = sqrt(mean(abs_error_r2c .^ 2))
rmse_rel_r2c = sqrt(mean(relative_error_r2c .^ 2))

median_rmse_abs_r2c = sqrt(median(abs_error_r2c .^ 2))
median_rmse_rel_r2c = sqrt(median(relative_error_r2c .^ 2))

println("(r2c) Reconstruction Error Stats:")
println("  RMSE (absolute): $rmse_abs_r2c")
println("  RMSE (relative): $rmse_rel_r2c")
println("  Median RMSE (absolute): $median_rmse_abs_r2c")
println("  Median RMSE (relative): $median_rmse_rel_r2c")
println("\n")  

#5) Is machine precision reached?
println("Machine epsilon is: ", eps())

if median_rmse_abs == eps() 
    println("Machine precision is reached for c2c FFT!")
end

if median_rmse_abs_r2c == eps()
    println("Machine precision is reached for r2c FFT!")
end

println("\n")  

#6) 
println("C[0, 0]: ", C[1, 1])  
println("R[0, 0]: ", R[1, 1])  
println("Mean of A: ", mean(A))  
println("\n")  


#7)

# Create new matrix A
dist = Normal(1.0, 1.0)
A = rand(dist, 6, 6)

# Perform r2c FFT
R = rfft(A, 1)

# actual c2c FFT
C_actual = fft(A,1)

println("Size of A: ", size(A))
println("Size of R: ", size(R))
println("Size of C_actual: ", size(C_actual))

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
