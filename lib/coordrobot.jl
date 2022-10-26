include("simplerobot.jl")

mutable struct CoordRobot <: SimpleRobot
	robot::Robot

	x::Int
	y::Int

	w::UInt
	h::UInt

	CoordRobot(robot::Robot) = begin
		set_w = robot.situation.frame_size[1]
		set_h = robot.situation.frame_size[2]

		set_x = robot.situation.robot_position[1]
		set_y = robot.situation.robot_position[2]

		new(robot,set_x,set_y,set_w,set_h)
	end

	CoordRobot()=CoordRobot(Robot(animate=true))
end

get_robot(coord::CoordRobot) =
	coord.robot

HorizonSideRobots.move!(coord::CoordRobot,side::HorizonSide) = 
	move!(coord.robot,side)

function HorizonSideRobots.move!(coord::CoordRobot,x::Int,y::Int)
	horizontal = x > 0 ? West : Ost
	vertical = y > 0 ? Sud : Nord

	x = abs(x)
	y = abs(y)

	while x > 0 && y > 0
		if !isborder(coord.robot,vertical) && y > 0
			move!(coord.robot,vertical)

			y-=1
		end

		if !isborder(coord.robot,horizontal)
			move!(coord.robot,horizontal) && x > 0

			x-=1
		end
	end
end

function HorizonSideRobots.goto!(coord::CoordRobot,x::Int,y::Int)
	move!(coord,(x > coord.x ? 1 : -1) * abs(x - coord.x),(y > coord.y ? 1 : -1)*abs(y - coord.y))
end