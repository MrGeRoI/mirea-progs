using Plots

include("../Practic2/practic.jl")

#1. Написать функцию, вычисляющую n-ю частичную сумму ряда Телора
# (Маклорена) функции для произвольно заданного значения аргумента x.
# Сложность алгоритма должна иметь оценку O(n).
function exp_taylor(x::T,n::Integer=10)::T where T
	value = oneunit(T)
	fact = oneunit(T)

	for i in 1:n
		value += x / fact
		x *= x
		fact *= fact + oneunit(T)
	end

	return value
end

println("exp(1) ~= ",exp_taylor(1.0))


#2. Написать функцию, вычиляющую значение exp(x) с машинной точностью (с
# максимально возможной в арифметике с плавающей точкой).
function exp_machine(x::T)::T where T
    value = oneunit(T)
	fact = oneunit(T)
    
	while abs(x/fact) > eps(T)
		value += x / fact
		x *= x
		fact *= fact + oneunit(T)
	end

	return value
end

function exp_ideal(x::T)::T where T
	return FastPower(Float64(ℯ),Int(trunc(x))) * exp_machine(x - trunc(x))
end

println("exp(1) = ",exp_ideal(1.0))

#3. Написать функцию, вычисляющую функцию Бесселя заданного целого
# неотрицательного порядка по ее ряду Тейлора с машинной точностью. Для
# этого сначала вывести соответствующую рекуррентную формулу,
# обеспечивающую возможность эффективного вычисления.
function bessel(M::Integer, x::Real)
    sqrx = x*x
    a = 1/factorial(M)
    m = 1
    s = 0 
    
    while s + a != s
        s += a
        a = -a * sqrx /(m*(M+m)*4)
        m += 1
    end
    
    return s*(x/2)^M
end

#3. Построить семейство графиков этих функций для нескольких порядков, начиная с нулевого порядка.
values = 0:0.1:20
myPlot = plot()
for m in 0:5
	plot!(myPlot, values, bessel.(m, values))
end
display(myPlot) #bessel.png
