include("abstractrobot.jl")

mutable struct SimpleRobot <: AbstractRobot
	robot::Robot

	SimpleRobot(r::Robot) = new(r)
	SimpleRobot() = new(Robot(animate = true))
end

get_robot(simple::SimpleRobot)::Robot = robot.robot
