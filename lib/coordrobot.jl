include("simplerobot.jl")

mutable struct CoordRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot

	x::Int
	y::Int

	CoordRobot{TypeRobot}(robot::TypeRobot,x::Int = 0,y::Int = 0) where {TypeRobot <: AbstractRobot} = new(robot,x,y)

	CoordRobot() = CoordRobot{SimpleRobot}(SimpleRobot())
end

get_robot(coord::CoordRobot)::AbstractRobot =
	coord.robot

get_coord(coord::CoordRobot)::Tuple{Int,Int} =
	(coord.x,coord.y)

get_x(coord::CoordRobot)::Int =
	coord.x

get_y(coord::CoordRobot)::Int =
	coord.y

HorizonSideRobots.move!(coord::CoordRobot,side::HorizonSide)::Nothing = begin
	move!(coord.robot,side)

	coord.x = coord.x + tox(side)
	coord.y = coord.y + toy(side)

	return nothing
end

shift!(coord::CoordRobot,x::Int,y::Int)::Nothing = begin
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

goto!(coord::CoordRobot,x::Int,y::Int)::Nothing = begin
	shift!(coord,(x > coord.x ? 1 : -1) * abs(x - coord.x),(y > coord.y ? 1 : -1) * abs(y - coord.y))
end
