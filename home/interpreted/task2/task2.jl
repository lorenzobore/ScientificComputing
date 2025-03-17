
N = [10,10^6,10^8]
a = 3

for n in N 

    elapsed_time = @elapsed begin

        #initialize vectors
        x = fill(0.1,n)  
        y = fill(7.1,n)  

        #check
        @assert length(x)==n "ERROR: wrong initialization of x!"
        @assert length(y)==n "ERROR: wrong initialization of y!"

        #compute vector x scalar
        temp = a * x

        @assert length(temp)==n "ERROR: wrong dimension in vector-scalar multiplication"
        @assert all(abs.(temp .- 0.3) .== eps(0.3)) "ERROR: wrong computation of a * x"

        #compute final result 
        d = temp + y
        @assert length(d)==n "ERROR: wrong dimension in vector-vector sum"
        @assert all(abs.(d .- 7.4) .== eps(7.4)) "ERROR: wrong computation of a * x + y"

    end
    println("Correct computation of d=a*x+y for N=$n ($elapsed_time sec)")
end

println("\n")


N=[10, 100, 10000]


for n in N

    elapsed_time = @elapsed begin
        #initialize matrices
        A = fill(3.0, (n,n))
        B = fill(7.1, (n,n))

        #compute matrix-amtrix multiplication 
        C = A * B 

        @assert size(C)==(n,n) "ERROR: wrong size after multiplicaiton"
        @assert all(abs.(C .- n*21.3) .<= n*eps(n*21.3)) "ERROR: wrong matrix matrix multiplicaiton"
    end 

    println("Correct computation of C = AB, for N=$n ($elapsed_time sec)")
end


