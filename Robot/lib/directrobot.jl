include("simplerobot.jl")

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
