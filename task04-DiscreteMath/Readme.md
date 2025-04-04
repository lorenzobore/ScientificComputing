# Task 4

The codes are available also at : https://github.com/lorenzobore/ScientificComputing

In the folder `task4` you can find:

* The `Makefile` to compile the C codes.
* The `task4.c` and `task4.exe` that contain the solutions of questions 1 to 3.
* The `data.txt` file generated by the C code and read by the code in `julia`.
* The `task4.jl` taht answers question 4.


### Question 1
This is the output of `task4.c` relative to Question 1. 

The number of sampling points N are inserted from command line. $I_{true} = 1.9052386904826757$, $I = 1.9051192179747309$, $epsrel = |\frac{I}{I_{true}}-1| = 0.000063$.

```
--------------------
Insert number of sampling points N:
100
Integrate from:
0
To: x_sup=1.570796 by default
--------------------

N = 100 points generated in the range [0.000000,1.570796] with step dx=0.015708.
I = 1.9051192179747309
I=1.905119, I_true=1.905239, |eps|=0.000063 considering N=100 sampling points
```

### Question 2
In order to make a better evaluation of the integral, I can increase the number of sampling points, for example from 100 to 10000.

```
N = 10000 points generated in the range [0.000000,1.570796] with step dx=0.000157.
I_2 = 1.9052386785353614
I_2 = 1.9052386785353614, I_true = 1.9052386904826757, |eps| = 0.0000000062707703 considering N=10000 sampling points
```

### Question 3
The absolute error scales as $O(\frac{1}{N^2})$.


### Question 4
The same values of point 1 are read by the `julia` program, obtaining these results, showing slightly worse performances:

```
L'integrale calcolato con N=100 è: 1.9045350981134992
L'integrale analitico è: 1.9052386904826757
L'errore assoluto: 0.0007035923691764978
L'errore relativo: -0.0003692935550234644
```

In `julia` the default type used is Float64, while in C I decided to use the `double` type. Both codes use the trapezoidal method to compute the integral.