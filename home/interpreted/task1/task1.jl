a = 3
N = 20
x = ones(N)  # Vector of ones with dimension N
y = fill(4, N)  # Vector of fours with dimension N

# Compute the scalar product
z = a * x + y

# Write result to a text file
open("result.txt", "w") do file
    write(file, "z = " * string(z))
end

println("Computation complete. Result saved to result.txt")