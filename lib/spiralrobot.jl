include("simplerobot.jl")

mutable struct SpiralRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot

	SpiralRobot{TypeRobot}(robot::TypeRobot) where {TypeRobot <: AbstractRobot} = new(robot)

	SpiralRobot() = SpiralRobot{SimpleRobot}(SimpleRobot())
end

get_robot(spiral::SpiralRobot)::AbstractRobot =
	spiral.robot
