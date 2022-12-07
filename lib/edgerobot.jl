include("directrobot.jl")

mutable struct EdgeRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	direct::DirectRobot{TypeRobot}

    edge_side::HorizonSide

	EdgeRobot{TypeRobot}(robot::TypeRobot,side::HorizonSide) where {TypeRobot <: AbstractRobot} = new(DirectRobot{TypeRobot}(robot,right(side)),side)

	EdgeRobot(side::HorizonSide) = EdgeRobot{SimpleRobot}(SimpleRobot(),side)
end

get_robot(edge::EdgeRobot)::AbstractRobot =
	get_robot(edge.direct)
	
get_edge_side(edge::EdgeRobot)::HorizonSide =
    edge.edge_side
 
function forward!(edge::EdgeRobot)::Tuple{HorizonSide,Int}
	turn!(edge.direct,Left)
	
	rotate = -1

	while !try_forward!(edge.direct)
		turn!(edge.direct,Right)

		rotate = rotate + 1
	end

	return (get_direction(edge.direct),rotate)
end

function backward!(edge::EdgeRobot)::Tuple{HorizonSide,Int}
    # TODO
end