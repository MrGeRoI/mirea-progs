#1. Написать обобщенную функцию, реализующую алгоритм быстрого возведения в степень
function FastPower(number::T,degree::Integer)::T where T <: Number
	power = oneunit(T)

	while degree > 0
		if degree % 2 == 0
			degree = degree / 2
			number = number * number
		else
			degree = degree - 1
			power = power * number
		end
	end

	return power
end

#2. На база этой функции написать другую функцию, возвращающую n-ый член последовательности Фибоначчи (сложность - O(log n))

phi = 0.5 + sqrt(1.25)	# Φ = ( 1 + √5 ) / 2
phi2 = phi - 1			# φ = ( 1 - √5 ) / 2

# F_n = ( Φ^n - φ^n ) / √5
function GetFibbonachi(n::Integer)::Real
	return ( FastPower( phi , n ) - FastPower( phi2 , n ) ) / sqrt(5)
end

#3. Написать функцию, вычисляющую с заданной точностью log_a(x)
# (при произвольном aa, не обязательно, что a > 1), методом рассмотренном на лекции
# (описание этого метода можно найти также в книке Борисенко "Основы программирования" - она выложена в нашей группе в телеграм).

function ApproximateLogarithm(number::Real,base::Real,epsilon::Real)::Real
	@assert base > 1
	@assert number > 0
	@assert epsilon > 0

	result = zero(Real)
	temp = oneunit(Real)

	while abs(temp) >= epsilon || number <= (1.0 / base) || number >= base
		if number >= base
			number = number / base
			result = result + temp
		elseif number <= (1.0 / base)
			number = number * base
			result = result - temp
		else
			number = number * number
			temp = temp / 2.0
		end
	end

	return result
end

#4. Написать функцию, реализующую приближенное решение уравнения вида f(x) = 0 методом деления отрезка пополам (описание метода см. ниже).

function SolveBisection(func::Function, a::Real, b::Real, epsilon::Real)::Real
    @assert func(a) * func(b) < 0 
    @assert a < b

    f_a = func(a)

    while (b - a) > epsilon

        t = ( a + b ) / 2.0

        f_t = func(t)

        if f_t == 0.0
            return t
        elseif f_a * f_t < 0
            b = t
        else
            a, f_a = t, f_t
        end

	end

    return ( a + b ) / 2.0
end

#5. Найти приближенное решение уравнения cos(x) = x методом деления отрезка пополам.
println("cos(x) = x\nx ~= ",
	SolveBisection(0.0,pi / 2.0,0.01) do x::Real
		return cos(x) - x
	end
)

#6. Написать обобщенную функцию, реализующую метод Ньютона приьлиженного решения уравнения вида f(x)=0 (описание метода см. ниже).
function NewtonMethod(func::Function, x::Real, epsilon::Real, num_max::Integer = 10)::Real
	dx = -func(x)

	k = 0

	while abs(dx) > epsilon && k <= num_max
		x += dx
		k += 1
	end

	k > num_max && @warn("Требуемая точность не достигнута")

	return x
end

#7. Методом Ньютона найти приближеннное решение уравнения cos(x) = x.
println("cos(x) = x\nx ~= ",
	NewtonMethod(pi / 4.0,0.01) do x::Real
		return cos(x) - x
	end
)

#8. Методом Ньютона найти приближеннное значение какого-либо вещественного корня многочлена, заданного своими коэффициенами.
println("(x-2) * (x^2 + 2*x + 5)\nx ~= ",
	NewtonMethod(4.0,0.01) do x::Real
		return (x - 2) * (x^2 + 2*x + 5)
	end
)