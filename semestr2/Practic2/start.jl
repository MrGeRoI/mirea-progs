#1. Написать обобщенную функцию, реализующую алгоритм быстрого возведения в степень
function FastPower(number::T,degree::Integer)::T where T <: Number
	power = oneunit(T)

	# инвариант: number ^ degree * power == number ^ degree

	while degree > 0
		# инвариант: number ^ degree * power == number ^ degree

		if degree % 2 == 0
			degree = degree / 2
			number = number * number
		else
			degree = degree - 1
			power = power * number
		end
	end

	# утверждение: degree == 0 и number ^ degree * power == number ^ degree
	
	return power
end

#2. На база этой функции написать другую функцию, возвращающую n-ый член последовательности Фибоначчи (сложность - O(log n))

function GetFibonachi(n::Integer)::Real
	return 0 #= Нужно юзать какие-то матрицы =#
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

	# утверждение: base ^ result * number ^ temp == number

	while abs(temp) >= epsilon || number <= (1.0 / base) || number >= base

		# инвариант: base ^ result * number ^ temp == number

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

	# утверждение: |temp| < epsilon и
	#	number > 1.0 / base и number < base
	#	и
	#	base ^ result * number ^ temp == number
		
	return result
end

#4. Написать функцию, реализующую приближенное решение уравнения вида f(x) = 0 методом деления отрезка пополам (описание метода см. ниже).
function SolveBisection(func::Function, left::Real, right::Real, epsilon::Real)::Real
    @assert func(left) * func(right) < 0 
    @assert left < right

	# ИНВАРИАНТ: func(left) * f(right) < 0
    while (right - left) > epsilon

        mid = ( left + right ) / 2.0

        if func(mid) == 0.0
            return mid
        elseif func(left) * func(mid) < 0
            right = mid
        else
            left = mid
        end

	end

    return ( left + right ) / 2.0
end

#5. Найти приближенное решение уравнения cos(x) = x методом деления отрезка пополам.
println("===\nДеление отрезка пополам:\ncos(x) = x\nx ~= ",
	SolveBisection(0.0,pi / 2.0,0.01) do x::Real
		return cos(x) - x
	end
)

#6. Написать обобщенную функцию, реализующую метод Ньютона приьлиженного решения уравнения вида f(x) = 0 .
# ratio: f(x) / f'(x)
function NewtonMethod(ratio::Function, x::Real, epsilon::Real, num_max::Integer = 10)::Real
	dx = -ratio(x)

	for _ in 0:num_max
		if abs(dx) <= epsilon
			return x
		end

		x += dx
		dx = -ratio(x)
	end

	return x
end

#7. Методом Ньютона найти приближеннное решение уравнения cos(x) = x.
# f(x) = cos(x) - x
# f'(x) = - sin(x) - 1
println("===\nМетод Ньютона:\ncos(x) = x\nx ~= ",
	NewtonMethod(pi / 4.0,0.01) do x::Real
		return ( cos(x) - x ) /
			( -sin(x) - 1 )
	end
)

#8. Методом Ньютона найти приближеннное значение какого-либо вещественного корня многочлена, заданного своими коэффициенами.
# f(x) = (x - 2) * (x^2 + 2*x + 5)
# f(x) = x^3 + x - 10
# f'(x) = 3 * x ^ 2 + 1
println("===\nМетод Ньютона:\n(x - 2) * (x^2 + 2*x + 5)\nx ~= ",
	NewtonMethod(4.0,0.01) do x::Real
		return ( x^3 + x - 10 ) /
			( 3*x^2 + 1 )
	end
)
