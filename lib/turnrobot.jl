include("directrobot.jl")

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

mutable struct TurnRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	direct::DirectRobot{TypeRobot}
	turns::Int

	TurnRobot{TypeRobot}(robot::TypeRobot,dir::HorizonSide) where {TypeRobot <: AbstractRobot} = new(DirectRobot{TypeRobot}(robot,dir),0)

	TurnRobot(dir::HorizonSide) = TurnRobot{SimpleRobot}(SimpleRobot(),dir)
end

get_robot(turn::TurnRobot)::AbstractRobot =
	get_robot(turn.direct)

get_turns(turn::TurnRobot)::Int =
	turn.turns

reset_turns(turn::TurnRobot)::Nothing =
	turn.turns = 0

get_direction(turn::TurnRobot)::HorizonSide =
	turn.direct.direction

try_forward!(turn::TurnRobot)::Bool =
	try_forward!(turn.direct)

forward!(turn::TurnRobot)::Nothing = 
	forward!(turn.direct)

function turn!(turn::TurnRobot,rotate::Оrientation)::Nothing
	if rotate == Backward
		turn.direct.direction = inverse(turn.direct.direction)
	elseif rotate == Left
		turn.direct.direction = left(turn.direct.direction)

		turn.turns -= 1
	elseif rotate == Right
		turn.direct.direction = right(turn.direct.direction)

		turn.turns += 1
	end

	return nothing
end