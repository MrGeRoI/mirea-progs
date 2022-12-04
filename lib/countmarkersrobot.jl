include("simplerobot.jl")

mutable struct CountMarkersRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot
    count::Integer

	CountMarkersRobot{TypeRobot}(robot::TypeRobot) where {TypeRobot <: AbstractRobot} = new(robot)

	CountMarkersRobot() = CountMarkersRobot{Robot}(Robot(animate = true))
end

get_robot(counter::CountMarkesrRobot)::AbstractRobot =
	counter.robot

get_counter(counter::CountMarkersRobot)::Integer = counter.count

reset_counter(counter::CountMarkersRobot)::Nothing =
	counter.count = 0