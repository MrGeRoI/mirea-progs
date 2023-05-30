# 1. Генерация всех размещений с повторениями из n элементов {1,2,...,n} по k

function showplacements(k::T,n::T) where T<:Integer
	for i in 0:n^k-1
		digits(i; base=n, pad=k) |> println
	end
end

showplacements(3,5)