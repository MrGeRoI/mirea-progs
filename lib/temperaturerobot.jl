include("simplerobot.jl")

mutable struct TemperatureRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot
	temperature::Integer

	TemperatureRobot{TypeRobot}(robot::TypeRobot,temp::Integer = 0) where {TypeRobot <: AbstractRobot} = new(robot,temp)

	TemperatureRobot() = TemperatureRobot{Robot}(Robot(animate = true))
end

get_robot(temperature::TemperatureRobot)::AbstractRobot =
	temperature.robot

get_temperature(temperature::TemperatureRobot) =
	temperature.temperature

reset_temperature(temperature::TemperatureRobot) =
	temperature.temperature = 0
