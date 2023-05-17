# Пузырьковая сортировка O( n^2 )
function bubble_sort!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
    n = length(array)

    for k in 1:n-1
        istranspose = false

        for i in 1:n-k
            if array[i]>array[i+1]
                array[i], array[i+1] = array[i+1], array[i]
                istranspose = true
            end
        end

        if istranspose == false
            break
        end
    end

    return array
end

bubble_sort(array::AbstractVector)::AbstractVector = bubble_sort!(copy(array))

#1. Реализовать функции, аналогичные встроенным функциям sort, sort!, sortperm, sortperm! на основе алгоритма сортировки вставками.
# При этом, при проектировании функциий, аналогичных функциям sort и sort!, требуется избежать повторного кодирования алгоритма сортировки.
# То же относится и к проектированию пары функций, аналогичных функциям sortperm, sortperm!

# Сортировка вставками O( n^2 )
function insert_sort!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
    n = 1
    # Инвариант: срез array[1:n] - отсортирован

    while n < length(array) 
        n += 1
        i = n

        while i > 1 && array[i-1] > array[i]
            array[i], array[i-1] = array[i-1], array[i]
            i -= 1
        end

        # Утверждение: array[1] <= ... <= array[n]
    end

    return array
end

insert_sort(array::AbstractVector)::AbstractVector = insert_sort!(copy(array))

#2. Реализовать алгоритм сортировки "расчесыванием", который базируется на сортировке "пузырьком". Исследовать эффективность этого алгоритма в равнении с пузырьковой сортировкой (на больших массивах делать времннные замеры).

# Сортировка расчёской O( n^2 )
function comb_sort!(array::AbstractVector{T}, factor::Real=1.2473309) where T <: Number 
    step = length(array)

    while step >= 1
        for i in 1:length(array)-step
            if array[i] > array[i+step]
                array[i], array[i+step] = array[i+step], array[i]
            end
        end
        step = Int(floor(step/factor))
    end

    # Теперь массив почти упорядочен, осталось сделать всего несколько итераций внешнего цикла в bubble_sort!(array)
    bubble_sort!(array)
end

comb_sort(array::AbstractVector, factor::Real=1.2473309)::AbstractVector = comb_sort!(copy(array),factor)

#3. Реализовать алгоритм сортировки Шелла, который базируется на сортировке вставками.
# Исследовать эффективность этого алгоритма в равнении с сортировкой вставками (на больших массивах делать времннные замеры).

# Сортировка Шелла O( n^2 )
function shell_sort!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
    n = length(array)

	# Здесь последовательность шагов прореживания массива определяется генератором
    step_series = (n÷2^i for i in 1:Int(floor(log2(n)))) 

    for step in step_series
        for i in firstindex(array):step-1
            insert_sort!(@view array[i:step:end]) # - сортировка вставками выделенного (прореженного) подмассива
        end
    end
    return array
end

shell_sort(array::AbstractVector)::AbstractVector = shell_sort!(copy(array))

#4. Реализовать алгоритм сортировки слияниями. Исследовать эффективность этого алгоритма в сравнении с предыдущми алгоритмами.

# @inline - делает функцию "встраиваемой", т.е. во время компиляции ее тело будет встроено непосредственно в код вызывающей функции (за счет этого происходит экономия на времени, затрачиваемым на вызов функции; это время очень небольшое, но тем не менее)
@inline function Base.merge!(a1, a2, a3)::Nothing
    i1, i2, i3 = 1, 1, 1
    @inbounds while i1 <= length(a1) && i2 <= length(a2) # @inbounds - передотвращает проверки выхода за пределы массивов
        if a1[i1] < a2[i2]
            a3[i3] = a1[i1]
            i1 += 1
        else
            a3[i3] = a2[i2]
            i2 += 1
        end
        i3 += 1
    end
    @inbounds if i1 > length(a1)
        a3[i3:end] .= @view(a2[i2:end]) # Если бы тут было: a3[i3:end] = @view(a2[i2:end]), то это привело бы к лишним аллокациям (к созданию промежуточного массива)
    else
        a3[i3:end] .= @view(a1[i1:end])
    end
    nothing
end

# Сортировка слияниями O( n*log(n) )
function merge_sort!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
	b = similar(array) # - вспомогательный массив того же размера и типа, что и массив array
	N = length(array)
	n = 1 # n - текущая длина блоков

	@inbounds while n < N
		K = div(N,2n) # - число имеющихся пар блоков длины n
		for k in 0:K-1
			merge!(@view(array[(1:n).+k*2n]), @view(array[(n+1:2n).+k*2n]), @view(b[(1:2n).+k*2n]))
		end
		if N - K*2n > n # - осталось еще смержить блок длины n и более короткий остаток
			merge!(@view(array[(1:n).+K*2n]), @view(array[K*2n+n+1:end]), @view(b[K*2n+1:end]))
		elseif 0 < N - K*2n <= n # - оставшуюся короткую часть мержить не с чем
			b[K*2n+1:end] .= @view(array[K*2n+1:end])
		end
		array, b = b, array
		n *= 2
	end

	if isodd(log2(n)) # - если цикл был выполнен нечетное число раз, то b - это исходная ссылка на массив (на внешний массив), и array - это ссылка на вспомогательный массив (локальный)
		b .= array # b = copy(array) - это было бы не то же самое, т.к. при этом получилась бы ссылка на новый массив, который создает функция copy
		array = b
	end

	return array # - исходная ссылка на внешний массив (проверить, что это так, можно с помощью ===)
end

merge_sort(array::AbstractVector)::AbstractVector = merge_sort!(copy(array))

#5. Реализовать алгоритм сортировки Хоара. Исследовать эффективность этого алгоритма в сравнении с предыдущми алгоритмами.
function part_sort!(array::AbstractVector{T}, base::T) where T <: Number
	N = length(array)
	K=0
	L=0
	M=N

	# Инвариант: array[1:K] < base && array[K+1:L] == base && array[M+1:N] > base
	while L < M 
		if array[L+1] == base
			L += 1
		elseif array[L+1] > base
			array[L+1], array[M] = array[M], array[L+1]
			M -= 1
		else # if array[L+1] < base
			L += 1; K += 1
			array[L], array[K] = array[K], array[L]
		end
	end

	# Замечание: 1:K и M+1:N - эти диапазоны индексов определяют ещё не отсортированные части массива array

	return K, M+1 
end

# Быстрая сортировка O( n*log(n) )
function quick_sort!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
	if isempty(array) return array end

	N = length(array)

	K, M = part_sort!(array, array[rand(1:N)]) # - "базовый" элемент массива выбирается случайнам образом

	quick_sort!(@view array[1:K])
	quick_sort!(@view array[M:N])

	return array
end

quick_sort(array::AbstractVector)::AbstractVector = quick_sort!(copy(array))

#6. Реализовать вычисление медианы массива на основе процедуры Хоара.
function median(array::AbstractVector{T})::T where T <: Number
	quick_sort!(array)

    if len(array) % 2 == 1
        return array[len(array) / 2]
    else
        return 0.5 * (array[len(array) / 2 - 1] + l[len(array) / 2])
	end
end

#7. Реализовать алгоритм сортировки за линейное время.

# Эффективная сортировка O(n)
function calc_sort!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
    min_val, max_val = extrema(array)
    num_val = zeros(T, max_val - min_val + 1) # - число всех возможных значений

    for val in array
        num_val[val-min_val+1] += 1
    end  
    k = 0

    for (i, num) in enumerate(num_val)
        array[k+1:k+num] .= min_val+i-1
        k += num
    end

    return array
end

calc_sort(array::AbstractVector)::AbstractVector = calc_sort!(copy(array))

# Порядковые статистики, алгоритм быстрого вычисления порядковых статистик
function order_statistics!(array::AbstractVector{T}, index::Integer)::T where T
	function part_sort!(indexes_range::AbstractUnitRange, b)
		K, L, M = indexes_range[1]-1, indexes_range[begin]-1, indexes_range[end] # 0, 0, N
		#ИНВАРИАНТ: array[indexes_range[begin]:K] < b && array[K+1:L] == b && array[M+1:indexes_range[end]] > b
		while L < M 
			if array[L+1] == b
				L += 1
			elseif array[L+1] > b
				array[L+1], array[M] = array[M], array[L+1]
				M -= 1
			else # if array[L+1] < b
				L += 1; K += 1
				array[L], array[K] = array[K], array[L]
			end
		end    
		return indexes_range[begin]:K, M+1:indexes_range[end] 
		# - эти диапазоны индексов определяют ещё не отсортированные части массива array
	end

	function find(indexes_range)
		left_range, right_range = part_sort!(indexes_range, array[rand(indexes_range)]) 
		# - здесь "базовый" элемент массива выбирается случайным образом
		if index in left_range
			return find(left_range) 
		elseif index in right_range
			return find(right_range)
		else
			return array[index]
		end
	end

	find(firstindex(array):lastindex(array))
end

order_statistics(array::AbstractVector, index::Integer) = order_statistics!(copy(array), index)

# Реализация кучи на базе массива O(n)
function heap!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
    N = length(array)

    for i in 1:N÷2
        if array[i] < array[2i]
            array[i], array[2i] = array[2i], array[i]
        end
        
        if 2i+1 <= N && array[i] < array[2i+1]
            array[i], array[2i+1] = array[2i+1], array[i]
        end
    end

    return array
end

heap(array::AbstractVector)::AbstractVector = heap!(copy(array))

# Использую модуль Random для генерации случайного массива
using Random

A = randperm(100000)[1:100000]

@showtime bubble_sort(A)
@showtime insert_sort(A)
@showtime comb_sort(A)
@showtime shell_sort(A)
@showtime merge_sort(A)
@showtime quick_sort(A)

#= Топ сортировок 
bubble_sort(A): 26.440701 seconds
insert_sort(A): 4.235230 seconds
comb_sort(A): 0.132195 seconds
shell_sort(A): 0.375892 seconds
merge_sort(A): 1.152994 seconds
quick_sort(A): 0.255517 seconds
=#

@showtime sort(A,alg=InsertionSort)
@showtime sort(A,alg=QuickSort)
@showtime sort(A,alg=MergeSort)

#= Библиотечные сортировки
sort(A, alg = InsertionSort): 1.881611 seconds
sort(A, alg = QuickSort): 0.190779 seconds
sort(A, alg = MergeSort): 0.246879 seconds
=#