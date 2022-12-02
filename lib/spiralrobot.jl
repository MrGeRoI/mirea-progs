include("simplerobot.jl")

mutable struct SpiralRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot

	SpiralRobot{TypeRobot}(robot::TypeRobot) where {TypeRobot <: AbstractRobot} = new(robot)

	SpiralRobot() = SpiralRobot{Robot}(Robot(animate = true))
end

get_robot(spiral::SpiralRobot)::Robot =
	get_robot(spiral.robot)
