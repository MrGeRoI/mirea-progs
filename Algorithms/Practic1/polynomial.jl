include("residue.jl")
 
#=

6. Реализовать тип Plolynom{T} (T- тип коэффициентов многочлена)

=#

struct Polynom{T <: Number}
    Coefficient::Array{T}
	Power::Integer

	Polynom{T}(power::Integer) where T = new(Vector{T}(undef,power + 1),power)

	Polynom{T}(coef::Array) where T = new(convert(Array{T},coef),length(coef) - 1)
end

# единица
Base.oneunit(::Type{Polynom{T}}) where T = Polynom([oneunit(T)])

# ноль
Base.zero(::Type{Polynom{T}}) where T = Polynom([zero(T)])

function get_power(poly::Polynom{T}) where T 
	for i in poly.Power:-1:0
		if get_coefficient(poly,i) != Base.zero(T)
			return i
		end
	end

	return 0
end

get_coefficient(poly::Polynom{T},n::Integer) where T = poly.Coefficient[n + 1]

set_coefficient(poly::Polynom{T},n::Integer,coef::T) where T = ( poly.Coefficient[n + 1] = coef )

function Base.display(poly::Polynom{T}) where T
	for i in poly.Power:-1:0
		if get_coefficient(poly,i) == Base.zero(T)
			continue
		end

		print( get_coefficient(poly,i) )

		if i > 1
			print(" * t^",i," + ")
		elseif i > 0
			print( " * t + ")
		end
	end

	println("")

	return nothing
end
#=

7. Обеспечить взаимодействие типов Residue{M} и Polynom{T}, т.е. добиться, чтобы можно было бы создавать кольцо вычетов многочленов (по заданному модулю) и чтобы можно было создавить многочлены с коэффициентами из кольца вычетов.

При создании кольца вычетов многочленов параеметр M должен принимать значение кортежа коэффициентов соответсвующего многочлена.

=#

function Base.:+(a::Polynom{T},b::Polynom{T})::Polynom{T} where T
    result = Polynom{T}(max(a.Power,b.Power))

	for i in 0:min(a.Power,b.Power)
		set_coefficient(result,i,get_coefficient(a,i) + get_coefficient(b,i))
	end

	for i in ( min(a.Power,b.Power) + 1 ):a.Power
		set_coefficient(result,i,get_coefficient(a,i))
	end

	for i in ( min(a.Power,b.Power) + 1 ):b.Power
		set_coefficient(result,i,get_coefficient(b,i))
	end

	return result
end

function Base.:-(a::Polynom{T},b::Polynom{T})::Polynom{T} where T
    result = Polynom{T}(max(a.Power,b.Power))

	for i in 0:min(a.Power,b.Power)
		set_coefficient(result,i,get_coefficient(a,i) - get_coefficient(b,i))
	end

	for i in ( min(a.Power,b.Power) + 1 ):a.Power
		set_coefficient(result,i,get_coefficient(a,i))
	end

	for i in ( min(a.Power,b.Power) + 1 ):b.Power
		set_coefficient(result,i,-get_coefficient(b,i))
	end

	return result
end

function Base.:*(poly::Polynom{T},mul::T)::Polynom{T} where T
	result = Polynom{T}(poly.Power)

	for i in 0:poly.Power
		set_coefficient(result,i,get_coefficient(poly,i) * mul)
	end

	return result
end

function Base.:*(a::Polynom{T},b::Polynom{T})::Polynom{T} where T
	result = Polynom{T}(a.Power + b.Power)

	for i in 0:a.Power
		for j in 0:b.Power
			set_coefficient(result,i + j,Base.zero(T))
		end
	end

	for i in 0:a.Power
		for j in 0:b.Power
			#println(i + j,": = ",get_coefficient(a,i) * get_coefficient(b,j))
			set_coefficient(result,i + j,get_coefficient(result,i + j) + get_coefficient(a,i) * get_coefficient(b,j))
		end
	end

	return result
end

function Base.:/(poly::Polynom{T},mul::T)::Polynom{T} where T
	result = Polynom{T}(poly.Power)

	for i in 0:poly.Power
		set_coefficient(result,i,get_coefficient(poly,i) / mul)
	end

	return result
end

function Base.:+(poly::Polynom{T},coef::T)::Polynom{T} where T
	result = Polynom{T}(poly.Power)

	set_coefficient(result,1,get_coefficient(result,1) + coef)

	return result
end

function Base.:-(poly::Polynom{T},coef::T)::Polynom{T} where T
	result = Polynom{T}(poly.Power)

	set_coefficient(result,1,get_coefficient(result,1) - coef)

	return result
end

function Base.:-(poly::Polynom{T})::Polynom{T} where T
    result = Polynom{T}(poly.Power)

	for i in 0:poly.Power
		set_coefficient(result,i,-get_coefficient(poly,i))
	end

	return result
end

function Base.mod(poly::Polynom{T},m::T)::Polynom{T} where T
	result = Polynom{T}(poly.Power)

	for i in 0:poly.Power
		set_coefficient(result,i,mod(get_coefficient(poly,i),m))
	end

	return result
end

function Base.mod(poly::Polynom{T},m::Tuple)::Polynom{T} where T
	result = Polynom{T}(poly.Power)

	for i in 0:poly.Power
		set_coefficient(result,i,mod(get_coefficient(poly,i),m[i + 1]))
	end

	return result
end