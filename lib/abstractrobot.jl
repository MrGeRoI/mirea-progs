include("stdrobot.jl")

abstract type AbstractRobot end

get_robot(robot::Robot)::Robot = robot

HorizonSideRobots.move!(simple::AbstractRobot,side::HorizonSide)::Nothing =
	move!(get_robot(simple),side)

HorizonSideRobots.isborder(simple::AbstractRobot,side::HorizonSide)::Bool =
	isborder(get_robot(simple),side)

HorizonSideRobots.putmarker!(simple::AbstractRobot)::Nothing =
	putmarker!(get_robot(simple))

HorizonSideRobots.ismarker(simple::AbstractRobot)::Bool =
	ismarker(get_robot(simple))

HorizonSideRobots.temperature(simple::AbstractRobot)::Int =
	temperature(get_robot(simple))

HorizonSideRobots.show(simple::AbstractRobot)::Nothing =
	show(get_robot(simple))

HorizonSideRobots.show!(simple::AbstractRobot)::Nothing =
	show!(get_robot(simple))

HorizonSideRobots.save(simple::AbstractRobot,file::AbstractString)::Nothing =
	save(get_robot(simple),file)
