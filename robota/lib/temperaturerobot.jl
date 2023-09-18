include("simplerobot.jl")

mutable struct TemperatureRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot
	temperature::Integer

	TemperatureRobot{TypeRobot}(robot::TypeRobot,temp::Integer = 0) where {TypeRobot <: AbstractRobot} = new(robot,temp)

	TemperatureRobot() = TemperatureRobot{SimpleRobot}(SimpleRobot())
end

get_robot(temp::TemperatureRobot)::AbstractRobot =
	temp.robot

get_temperature(temp::TemperatureRobot) =
	temp.temperature

reset_temperature(temp::TemperatureRobot) =
	temp.temperature = 0

HorizonSideRobots.move!(temp::TemperatureRobot,side::HorizonSide) =
	temp.temperature += temperature(temperature)