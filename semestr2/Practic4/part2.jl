using LinearAlgebra

#4. Реализовать алгорим, реализующий обратный ход алгоритма Жордана-Гаусса
function ReverseGauss(matrix::AbstractMatrix{T}, b::AbstractVector{T}) where T
	x = similar(b)
	N = size(matrix, 1)

	for k in 0:N-1
		x[N-k] = (b[N-k] - sum(matrix[N-k,N-k+1:end] .* x[N-k+1:end])) / matrix[N-k,N-k]
	end

	return x
end

#5. Реализовать алгоритм, осуществляющий приведение матрицы матрицы к ступенчатому виду
function TransformToSteps!(matrix::AbstractMatrix, epsilon::Real = 1e-7)
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
@inline function sumprod(vec1::AbstractVector{T}, vec2::AbstractVector{T}) where T
	s = T(0)
	@inbounds for i in eachindex(vec1)
	s = fma(vec1[i], vec2[i], s) # fma(x, y, z) вычисляет выражение x*y+z
	end
	return s
end

function ReverseGauss(matrix::AbstractMatrix{T}, vec::AbstractVector{T}) where T
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
	@time ReverseGauss(randn(n,n),randn(n))
end

#8. Написать функцию, возвращающую ранг произвольной прямоугольной матрицы (реализуется на базе приведения матрицы к ступенчатому виду).
function GetRank(matrix::AbstractMatrix{T}) where T
    TransformToSteps!(Matrix)
    
	i = 1

    while matrix[i,i] != zero(T)
        i+=1
    end

    return i-1
end

#9. Написать функцию, возвращающую определитель произвольной квадратной матрицы (реализуется на основе приведения матрицы к ступенчатому виду).
function CalcDeterminant(matrix::AbstractMatrix{T}) where T
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