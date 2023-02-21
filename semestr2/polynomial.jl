#=

6. Реализовать тип Plolynom{T} (T- тип коэффициентов многочлена)

=#

struct Polynom{T <: Number}
    Coefficient::Array{T}
	Power::Integer

	Polynom{T}(power::Integer) where T = new(T[power],power)

	Polynom{T}(coef::Array) where T = new( convert(Array{T},coef),length(coef))
end

# единица
oneunit(::Type{Polynom{T}})::Polynom{T} where T <: Number = Polynom([oneunit(T)])

# ноль
zero(::Type{Polynom{T}})::Polynom{T} where T <: Number = Polynom([zero(T)])

get_power(poly::Polynom) = length(poly.Coefficient)

function print_poly(poly::Polynom{T}) where T
	print("poly.Coefficient ")

	for i in poly.Power:-1:1
		print( poly.Coefficient[i] )

		if i > 2
			print( " * t^")
			print( i )
			print( " + " )
		elseif i > 1
			print( " * t + ")
		end
	end
end
#=

7. Обеспечить взаимодействие типов Residue{M} и Polynom{T}, т.е. добиться, чтобы можно было бы создавать кольцо вычетов многочленов (по заданному модулю) и чтобы можно было создавить многочлены с коэффициентами из кольца вычетов.

При создании кольца вычетов многочленов параеметр M должен принимать значение кортежа коэффициентов соответсвующего многочлена.

=#

function Base. +(a::Polynom{T},b::Polynom{T})::Polynom{T} where T
    result = Polynom{T}(max(a.Power,b.Power))

	for i in 1:min(a.Power,b.Power)
		result.Coefficient[i] = a.Coefficient[i] + b.Coefficient[i]
	end

	for i in ( min(a.Power,b.Power) + 1 ):a.Power
		result.Coefficient[i] = a.Coefficient[i]
	end

	for i in ( min(a.Power,b.Power) + 1 ):b.Power
		result.Coefficient[i] = b.Coefficient[i]
	end

	return result
end

function Base. -(poly::Polynom{T})::Polynom{T} where T
    result = Polynom{T}(poly.Power)

	for i in 1:length(poly.Coefficient)
		result.Coefficient[i] = -poly.Coefficient[i]
	end

	return result
end

print_poly(-Polynom{Real}([3.0,2.0,2.0]))