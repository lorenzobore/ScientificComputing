using Test

function multiplication(a, x)
    return a * x
end

function sum(a, b)
    return a + b
end

function single_daxpy(a,x,y)
    return sum(multiplication(a,x),y)
end

function vector_daxpy(a,x,y)
    return sum(multiplication(a,x),y)
end

@testset "Multiplication Tests" begin
    @test multiplication(2, 3) == 6
    @test multiplication(0, 0) == 0
    @test multiplication(0, 1) == 0
    @test multiplication(1,0) == 0
    @test isapprox(multiplication(3, 0.1), 0.3)
    @test isapprox(multiplication(3, -0.1),-0.3)
end


@testset "Sum Tests" begin
    @test sum(2, 3) == 5
    @test sum(0, 0) == 0
    @test sum(2, -3) == -1
    @test sum(1,-1) == 0
    @test isapprox(sum(0.3,7.1),7.4)
    @test isapprox(sum(-0.3,7.1),6.8)
    @test isapprox(sum(-0.3,-7.1),-7.4)
end


@testset "Single Daxpy Tests" begin
    @test single_daxpy(1,0,1) == 1
    @test single_daxpy(0,0,0) == 0
    @test single_daxpy(-1,1,1) == 0
    @test single_daxpy(-1,1,0) == -1
    @test isapprox(single_daxpy(3,0.1,7.1),7.4)
    @test isapprox(single_daxpy(-3,0.1,7.1),6.8)
    @test isapprox(single_daxpy(-3,0.1,-7.1),-7.4)
end


@testset "Vector Daxpy Tests" begin
    a=3; N=10;
    x=fill(0.1,N); y=fill(7.1,N);
    
    @test isapprox(vector_daxpy(a,x,y),fill(7.4,N))
    @test isapprox(vector_daxpy(-a,x,y),fill(6.8,N))
    @test isapprox(vector_daxpy(-a,x,-y),fill(-7.4,N))
end