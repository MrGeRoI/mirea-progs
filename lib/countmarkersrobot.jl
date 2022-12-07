include("simplerobot.jl")

mutable struct CountMarkersRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot
    count::Integer

	CountMarkersRobot{TypeRobot}(robot::TypeRobot) where {TypeRobot <: AbstractRobot} = new(robot)

	CountMarkersRobot() = CountMarkersRobot{SimpleRobot}(SimpleRobot())
end

get_robot(counter::CountMarkersRobot)::AbstractRobot =
	counter.robot

get_counter(counter::CountMarkersRobot)::Integer = counter.count

reset_counter(counter::CountMarkersRobot)::Nothing =
	counter.count = 0