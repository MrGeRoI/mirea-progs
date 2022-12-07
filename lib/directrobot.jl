include("simplerobot.jl")

#	     Forward	
#
#	Left    O	  Right
#	
#	     Backward
 
@enum Оrientation begin
	Forward = 0
	Left = 1
	Backward = 2
	Right = 3
end

#повернуть налево
left(side::Оrientation)::Оrientation = 
	Оrientation( ( Int(side) + 1 ) % 4 )

#повернуть направо
right(side::Оrientation)::Оrientation =
	Оrientation( mod( Int(side) - 1 , 4 ) )

#обратное направление
inverse(side::Оrientation)::Оrientation =
	Оrientation( ( Int(side) + 2 ) % 4 )

mutable struct DirectRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot
	direction::HorizonSide

	DirectRobot{TypeRobot}(robot::TypeRobot,dir::HorizonSide) where {TypeRobot <: AbstractRobot} = new(robot,dir)

	DirectRobot(dir::HorizonSide) = DirectRobot{SimpleRobot}(SimpleRobot(),dir)
end

get_robot(direct::DirectRobot)::AbstractRobot =
	direct.robot

get_direction(direct::DirectRobot)::HorizonSide =
	direct.direction

set_direction(direct::DirectRobot,dir::HorizonSide)::HorizonSide =
	direct.direction = dir

function try_forward!(direct::DirectRobot)::Bool
	if isborder(direct,direct.direction)
		return false
	end

	move!(direct,direct.direction)

	return true
end

forward!(direct::DirectRobot)::Nothing = 
	move!(direct,direct.direction)

function turn!(direct::DirectRobot,rotate::Оrientation)::Nothing
	if rotate == Backward
		direct.direction = inverse(direct.direction)
	elseif rotate == Left
		direct.direction = left(direct.direction)
	elseif rotate == Right
		direct.direction = right(direct.direction)
	end

	return nothing
end