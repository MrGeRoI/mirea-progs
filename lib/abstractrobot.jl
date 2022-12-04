include("stdrobot.jl")

abstract type AbstractRobot end

get_robot(robot::Robot)::Robot = robot

get_native_robot(robot::Robot)::Robot = robot

get_native_robot(abstract::AbstractRobot)::Robot =
	get_native_robot(get_robot(abstract))

HorizonSideRobots.move!(abstract::AbstractRobot,side::HorizonSide)::Nothing =
	move!(get_robot(abstract),side)

HorizonSideRobots.isborder(abstract::AbstractRobot,side::HorizonSide)::Bool =
	isborder(get_robot(abstract),side)

HorizonSideRobots.putmarker!(abstract::AbstractRobot)::Nothing =
	putmarker!(get_robot(abstract))

HorizonSideRobots.ismarker(abstract::AbstractRobot)::Bool =
	ismarker(get_robot(abstract))

HorizonSideRobots.temperature(abstract::AbstractRobot)::Int =
	temperature(get_robot(abstract))

HorizonSideRobots.show(abstract::AbstractRobot)::Nothing =
	show(get_robot(abstract))

HorizonSideRobots.show!(abstract::AbstractRobot)::Nothing =
	show!(get_robot(abstract))

HorizonSideRobots.save(abstract::AbstractRobot,file::AbstractString)::Nothing =
	save(get_robot(abstract),file)
