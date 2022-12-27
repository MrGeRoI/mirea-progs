include("turnrobot.jl")

mutable struct EdgeRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	turn::TurnRobot{TypeRobot}

    edge_side::HorizonSide

	EdgeRobot{TypeRobot}(robot::TypeRobot,side::HorizonSide) where {TypeRobot <: AbstractRobot} = new(TurnRobot{TypeRobot}(robot,right(side)),side)

	EdgeRobot(side::HorizonSide) = EdgeRobot{SimpleRobot}(SimpleRobot(),side)
end

get_robot(edge::EdgeRobot)::AbstractRobot =
	get_robot(edge.turn)

get_rotates(edge::EdgeRobot)::Int =
	get_turns(edge.turn)
	
get_edge_side(edge::EdgeRobot)::HorizonSide =
    edge.edge_side
 
function forward!(edge::EdgeRobot)::Nothing
	turn!(edge.turn,Left)
	
	while !try_forward!(edge.turn)
		turn!(edge.turn,Right)
	end
end

function backward!(edge::EdgeRobot)::Nothing
    # TODO
end