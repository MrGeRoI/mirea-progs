include("abstractrobot.jl")

mutable struct SimpleRobot <: AbstractRobot
	robot::Robot

	SimpleRobot(robot::Robot) = new(robot)
	SimpleRobot() = new(Robot(animate = true))
end

get_robot(simple::SimpleRobot)::Robot =
	simple.robot
