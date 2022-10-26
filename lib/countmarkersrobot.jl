include("simplerobot.jl")

struct CountMarkersRobot <: SimpleRobot
    robot::Robot
    count::Integer

	CoordRobot(robot::Robot) = begin
		new(robot,0)
	end

	CoordRobot()=CoordRobot(Robot(animate=true))
end

get_robot(counter::CountMarkesrRobot) = counter.robot
get_value(counter::CountMarkersRobot) = counter.count
reset_value(counter::CountMarkersRobot) =
	counter.count = 0