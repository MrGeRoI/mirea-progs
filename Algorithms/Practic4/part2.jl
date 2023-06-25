using LinearAlgebra

#4. Реализовать алгорим, реализующий обратный ход алгоритма Жордана-Гаусса
function ReverseGauss_first!(matrix::AbstractMatrix{T}, b::AbstractVector{T})::AbstractVector{T} where T
	x = similar(b)
	N = size(matrix, 1)

	for k in 0:N-1
		x[N-k] = (b[N-k] - sum(matrix[N-k,N-k+1:end] .* x[N-k+1:end])) / matrix[N-k,N-k]
	end

	return x
end

#5. Реализовать алгоритм, осуществляющий приведение матрицы матрицы к ступенчатому виду
function TransformToSteps!(matrix::AbstractMatrix, epsilon::Real = 1e-7)::AbstractMatrix
	@inbounds for k ∈ 1:size(matrix, 1)
		absval, Δk = findmax(abs, @view(matrix[k:end,k]))

		(absval <= epsilon) && throw("Вырожденая матрица")

		Δk > 1 && swap!(@view(matrix[k,k:end]), @view(matrix[k+Δk-1,k:end]))

		for i ∈ k+1:size(matrix,1)
			t = matrix[i,k]/matrix[k,k]
			@. @views matrix[i,k:end] = matrix[i,k:end] - t * matrix[k,k:end] # Макрос @. используется вместо того, чтобы в соответсвующей строчке каждую операцию записывать с точкой
		end
	end

	return matrix
end

#6. Реализовать алгоритм, реализующий метод Жордана-Гаусса решение СЛАУ для произвольной невырожденной матрицы (достаточно хорошо обусловленной).

#функцию sumprod можно оптимизировать, если две операции,
#выполняемые в цикле в теле этой функции на одну трехместную операцию,
#называемую fma :
@inline function sumprod(vec1::AbstractVector{T}, vec2::AbstractVector{T})::T where T
	s = zero(T)
	@inbounds for i in eachindex(vec1)
	s = fma(vec1[i], vec2[i], s) # fma(x, y, z) вычисляет выражение x*y+z
	end
	return s
end

function ReverseGauss!(matrix::AbstractMatrix{T}, vec::AbstractVector{T})::AbstractVector{T} where T
	#1. сначала расширенная матрица системы с помощью элементарных преобразований её строк приводится к ступенчатому виду
	
	x = similar(vec)
	N = size(matrix, 1)

	for k in 0:N-1
		#2. по очевидной простой формуле вычисляются значения элементов вектора решения, начиная с последнего элемента.
		x[N-k] = (vec[N-k] - sumprod(@view(matrix[N-k,N-k+1:end]), @view(x[N-k+1:end]))) / matrix[N-k,N-k]
	end

	return x
end

#7. Постараться обеспечить максимально возможную производительность алгорима решения СЛАУ;
# провести временные замеры с помощью макроса @time для систем большого размера (порядка 1000)
for n in 50:50:1000
	println("Матрица порядка ",n,"×",n,":")
	@time ReverseGauss_first!(randn(n,n),randn(n))
	@time ReverseGauss!(randn(n,n),randn(n))
	#= Выигрыш по времени от 2 до 3 раз
	Матрица порядка 50×50:
	0.000044 seconds (154 allocations: 58.641 KiB)
	0.000017 seconds (4 allocations: 20.578 KiB)
	Матрица порядка 100×100:
	0.000153 seconds (304 allocations: 217.453 KiB)
	0.000041 seconds (4 allocations: 79.922 KiB)
	Матрица порядка 150×150:
	0.000291 seconds (454 allocations: 475.797 KiB)
	0.000164 seconds (4 allocations: 178.516 KiB)
	Матрица порядка 200×200:
	0.000437 seconds (604 allocations: 835.547 KiB)
	0.000271 seconds (4 allocations: 316.078 KiB)
	Матрица порядка 250×250:
	0.000766 seconds (754 allocations: 1.267 MiB)
	0.000562 seconds (4 allocations: 492.484 KiB)
	Матрица порядка 300×300:
	0.002630 seconds (904 allocations: 1.814 MiB)
	0.001499 seconds (4 allocations: 708.172 KiB)
	Матрица порядка 350×350:
	0.001796 seconds (1.05 k allocations: 2.456 MiB)
	0.000717 seconds (4 allocations: 962.859 KiB)
	Матрица порядка 400×400:
	0.002315 seconds (1.20 k allocations: 3.194 MiB)
	0.001202 seconds (4 allocations: 1.227 MiB)
	Матрица порядка 450×450:
	0.005530 seconds (1.35 k allocations: 4.027 MiB)
	0.000977 seconds (4 allocations: 1.552 MiB)
	Матрица порядка 500×500:
	0.002824 seconds (1.50 k allocations: 4.955 MiB)
	0.015324 seconds (4 allocations: 1.915 MiB, 86.49% gc time)
	Матрица порядка 550×550:
	0.003108 seconds (1.65 k allocations: 5.979 MiB)
	0.004743 seconds (4 allocations: 2.317 MiB)
	Матрица порядка 600×600:
	0.004049 seconds (1.80 k allocations: 7.098 MiB)
	0.002966 seconds (4 allocations: 2.756 MiB)
	Матрица порядка 650×650:
	0.007465 seconds (1.95 k allocations: 8.313 MiB)
	0.002635 seconds (4 allocations: 3.234 MiB)
	Матрица порядка 700×700:
	0.004771 seconds (2.10 k allocations: 9.623 MiB)
	0.005154 seconds (4 allocations: 3.749 MiB)
	Матрица порядка 750×750:
	0.015398 seconds (2.25 k allocations: 11.028 MiB, 53.80% gc time)
	0.002690 seconds (4 allocations: 4.303 MiB)
	Матрица порядка 800×800:
	0.006438 seconds (2.40 k allocations: 12.529 MiB)
	0.005629 seconds (4 allocations: 4.895 MiB)
	Матрица порядка 850×850:
	0.008032 seconds (2.55 k allocations: 14.125 MiB)
	0.011510 seconds (4 allocations: 5.526 MiB, 64.66% gc time)
	Матрица порядка 900×900:
	0.009919 seconds (2.70 k allocations: 15.817 MiB)
	0.004069 seconds (4 allocations: 6.194 MiB)
	Матрица порядка 950×950:
	0.011421 seconds (2.85 k allocations: 17.603 MiB)
	0.008368 seconds (4 allocations: 6.900 MiB, 55.12% gc time)
	Матрица порядка 1000×1000:
	0.012442 seconds (3.00 k allocations: 19.485 MiB)
	0.004354 seconds (4 allocations: 7.645 MiB)
	=#
end

#8. Написать функцию, возвращающую ранг произвольной прямоугольной матрицы (реализуется на базе приведения матрицы к ступенчатому виду).
function rank!(matrix::AbstractMatrix{T}) where T
    TransformToSteps!(Matrix)
    
	i = 1

    while matrix[i,i] != zero(T)
        i+=1
    end

    return i-1
end

#9. Написать функцию, возвращающую определитель произвольной квадратной матрицы (реализуется на основе приведения матрицы к ступенчатому виду).
function determinant!(matrix::AbstractMatrix{T}) where T
    TransformToSteps!(matrix)

    det = oneunit(T)
    i = 1

    while i <= size(matrix, 1)
		if matrix[i, i] == zero(T)
			break
		end
	
		det *= matrix[i, i]
		
		i += 1
    end

    return det
end

#Проверка:
matrix = [1.0 2.0 3.0;1.0 6.0 9.0;-1.0 2.0 4.0]
values = [-1.0, 2.0, 2.0]
println("--Матрица--")
display(matrix)
println("--Свободные члены--")
display(values)
println("--Обратный ход Гаусса--")
display(ReverseGauss!(matrix,values))
