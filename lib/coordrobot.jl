using HorizonSideRobots

mutable struct CoordRobot
	robot::Robot

	x::Int
	y::Int

	#NOT USED
	#w::Int
	#h::Int
end

function HorizonSideRobots.move!(coord::CoordRobot,x::Int,y::Int)
	#TODO
end