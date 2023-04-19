using Plots

#Быстрое возведение в степень
function FastPower(a, deg)
    k, t, p = deg, 1, a

    while k>0
        if k % 2 == 0
            k ÷= 2
            p *= p
        else
            k -= 1
            t *= p 
        end   
    end
    return t
end

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

#2. Написать функцию, вычиляющую значение с машинной точностью (с
# максимально возможной в арифметике с плавающей точкой).
function exp_ideal(x::T)::T where T
	return FastPower(Float64(ℯ),Int(trunc(x))) * exp(x - trunc(x))
end

println("exp(1) = ",exp_ideal(1.0))

#3. Написать функцию, вычисляющую функцию Бесселя заданного целого
#неотрицательного порядка по ее ряду Тейлора с машинной точностью. Для
#этого сначала вывести соответствующую рекуррентную формулу,
#обеспечивающую возможность эффективного вычисления. Построить
#семейство графиков этих функций для нескольких порядков, начиная с нулевого
#порядка.

function besselj(M::Integer, x::Real)
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

println("besselj = ",besselj(3,52.1))

function draw_besselj()
    #=
    x = 1:0.1:10
    p = plot()
    for n in 2:2:16
        plot!(p, x, part_sum.(n, x))
    end
    display(p)
    =#
    x1 = 0:0.1:20
    p1 = plot()
    for m in 1:5
        plot!(p1, x1, besselj.(m, x1))
    end
    display(p1)
end

draw_besselj()

#4. Реализовать алгорим, реализующий обратный ход алгоритма Жордана-Гаусса
function reversedGauss(Matrix, b)
    x = similar(b)
    n = size(Matrix, 1)

    for k in 0:n-1
        x[n - k] = (b[n - k] - sum(@view(Matrix[n-k, n-k+1 : n]) .* @view(x[n-k+1:n]))) / Matrix[n-k, n-k]
    end
    return x
end

#5. Реализовать алгоритм, осуществляющий приведение матрицы матрицы к ступенчатому виду
function toUpperTriangle!(Matrix)
    coef(a, b) = b / a
    
    n, m = size(Matrix)
    for t in 1:m-1
        for i in t+1:n
            c = coef(Matrix[t, t], Matrix[i, t])
            Matrix[i, t] = 0
            for j in t+1:m
                Matrix[i, j] -= c * Matrix[t, j]
            end
        end
    end

    return Matrix
end

#6. Реализовать алгоритм, реализующий метод Жордана-Гаусса решение СЛАУ для
#произвольной невырожденной матрицы (достаточно хорошо обусловленной).

#7. Постараться обеспечить максимально возможную производительность
#алгорима решения СЛАУ; провести временные замеры с помощью макроса
#@time для систем большого размера (порядка 1000)

#8. Написать функцию, возвращающую ранг произвольной прямоугольной матрицы
#(реализуется на базе приведения матрицы к ступенчатому виду).
function rank(Matrix)
    toUpperTriangle!(Matrix)
    i = 1
    while(Matrix[i, i] != 0)
        i+=1
    end
    return i-1
end

#9. Написать функцию, возвращающую определитель произвольной квадратной
#матрицы (реализуется на основе приведения матрицы к ступенчатому виду)
function det(Matrix)
    toUpperTriangle!(Matrix)
    det = 1
    i = 1
    while (i <= size(Matrix, 1))
        if (Matrix[i, i] != 0)
            det *= Matrix[i, i]
            i+=1
        else break end
    end
    return det
end
