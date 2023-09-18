using HorizonSideRobots

left(side::HorizonSide)::HorizonSide = 
	HorizonSide( ( Int(side) + 1 ) % 4 )

abstract type AbstractRobot end

get_robot(robot::Robot)::Robot =
	robot

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

mutable struct PutMarkersRobot <: AbstractRobot
	robot::Robot

	PutMarkersRobot(robot::Robot) = new(robot)
end

mutable struct TemperatureRobot <: AbstractRobot
	robot::Robot
	temperature::Integer

	TemperatureRobot(robot::Robot,temp::Integer = 0) = new(robot,temp)
end

get_robot(temp::TemperatureRobot) =
	temp.robot

get_robot(put::PutMarkersRobot) =
	put.robot

get_tempterature(temp::TemperatureRobot) =
	temp.temperature

function HorizonSideRobots.move!(put::PutMarkersRobot,side::HorizonSide)
	putmarker!(put)
	move!(get_robot(put),side)
end

function HorizonSideRobots.move!(temp::TemperatureRobot,side::HorizonSide)
	temp.temperature += temperature(temp)
	move!(get_robot(temp),side)
end

function numsteps!(stop_condition::Function,robot::AbstractRobot,side::HorizonSide,num_steps::Integer)::Int
	steps = 0

	for _ in 1:num_steps
		if stop_condition(robot) return steps end
		
		move!(robot,side)

		steps += 1
	end

	return steps
end

function spiral!(stop_condition::Function,robot::AbstractRobot,side::HorizonSide = Ost)::Nothing
	dist = 1

	while true
		for _ in 1:2
			if numsteps!(stop_condition,robot,side,dist) <= 0 return end

			side = left(side)
		end

		dist += 1
	end
end

# ТЕСТ 1:

robot = Robot("situations/8.sit",animate=true)
put = PutMarkersRobot(robot)

spiral!(put,Nord) do r::AbstractRobot
	return ismarker(r)
end

# ТЕСТ 2:

robot = Robot("situations/8.sit",animate=true)
temp = TemperatureRobot(robot)

spiral!(temp,Nord) do r::AbstractRobot
	return ismarker(r)
end

print("Суммарная температура: ")
println(get_tempterature(temp))
