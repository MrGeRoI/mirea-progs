include("arithmetics.jl")

#=
5. Для вычислений в кольце вычетов по модулю M определить специальный тип
=#

struct Residue{T,M}
    value::T

    Residue{T,M}(a::T) where {T,M} = new(mod(a,M))
end

get_value(r::Residue) = r.value

#=

и определить для этого типа следующие операци и функции:
+, -, унарный минус, *, ^, inverse (обращает обратимые элементы), display (определяет, в каком виде значение будет выводиться в REPL)

=#

function Base. +(a::Residue{T,M},b::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(a.value + b.value)
end

function Base. -(r::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}( r + M * ( r > 0 ? -1 : 1 ) )
end

function Base. -(a::Residue{T,M},b::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(a.value + b.value)
end

function inverse(r::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(invmod_(r.value,M))
end

# display(r::Residue) = display(r.value) # Говно, которое не делает ничего

println( Residue{Integer,3}(-25) )

println( Residue{Integer,9}(12) )

println( Residue{Integer,7}(2) + Residue{Integer,7}(3) )
