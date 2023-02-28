include("arithmetics.jl")

#=
5. Для вычислений в кольце вычетов по модулю M определить специальный тип
=#

struct Residue{T,M}
    value::T
	module_::Any

    Residue{T,M}(a::T) where {T,M} = new(mod(a,M),M)
end

get_value(r::Residue) = r.value

get_module(r::Residue) = r.module_

#=

и определить для этого типа следующие операци и функции:
+, -, унарный минус, *, ^, inverse (обращает обратимые элементы), display (определяет, в каком виде значение будет выводиться в REPL)

=#

function Base. +(a::Residue{T,M},b::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(a.value + b.value)
end

function Base.:-(r::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}( -r )
end

function Base. -(a::Residue{T,M},b::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(a.value - b.value)
end

function inverse(r::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(invmod(r.value,M))
end

function Base. *(a::Residue{T,M},b::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(a.value ^ b.value)
end

function Base. ^(a::Residue{T,M},b::Residue{T,M})::Residue{T,M} where {T,M}
	return Residue{T,M}(a.value ^ b.value)
end

Base.display(r::Residue) = Base.display(r.value)
