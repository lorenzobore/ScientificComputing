# Aprire il file e leggere i dati
function leggi_file(filename)
    x = Float64[]
    y = Float64[]

    open(filename, "r") do file
        for line in eachline(file)
            valori = split(line)
            if length(valori) == 2
                push!(x, parse(Float64, valori[1]))
                push!(y, parse(Float64, valori[2]))
            end
        end
    end

    return x, y
end

# Funzione per calcolare l'integrale con la regola del trapezio
function integral(x, y)
    n = length(x)
    integral = 0.0

    for i in 1:n-1
        dx = x[i+1] - x[i]
        integral += (y[i] + y[i+1]) * dx / 2  # Regola del trapezio
    end

    return integral
end

# Esempio di utilizzo
x, y = leggi_file("../../compiled/task4/data.txt")

I4 = integral(x, y)
integrale_true = (exp(pi/2) - 1) / 2; 
abs_err = abs(integrale_true-I4)
rel_err = I4/integrale_true - 1

# Stampare il risultato
println("L'integrale calcoato con N=100 è: ", I4)
println("L'integrale analitico è: ", integrale_true)
println("L'errore assoluto: ",abs_err)
println("L'errore relativo: ",rel_err)

