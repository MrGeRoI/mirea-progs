include("directrobot.jl")

mutable struct EdgeRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	direct::DirectRobot{TypeRobot}

    edge_side::HorizonSide

	EdgeRobot{TypeRobot}(robot::TypeRobot,side::HorizonSide) where {TypeRobot <: AbstractRobot} = new(DirectRobot{TypeRobot}(robot,right(side)),side)

	EdgeRobot(side::HorizonSide) = EdgeRobot{Robot}(Robot(animate=true),side)
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

	#=
    if isborder(edge.direct,edge.edge_side) && !isborder(edge.direct,get_forward_side(edge))
        side = get_forward_side(edge)
        move!(edge.direct,side)
        return (side,0)
    end
 
    if !isborder(edge.direct,edge.edge_side)
        side = edge.edge_side
        move!(robot,side)
        edge.edge_side = edge.is_left ? left(edge.edge_side) : right(edge.edge_side)
        return (side,-1)
    elseif isborder(edge.direct,get_forward_side(edge))
        rotate = 0
        while isborder(edge.direct,get_forward_side(edge))
            edge.edge_side = edge.is_left ? right(edge.edge_side) : left(edge.edge_side)
            rotate = rotate + 1
        end
        side = get_forward_side(edge)
        move!(edge.direct,side)
        return (side,rotate)
    else
        side = get_forward_side(edge)
        move!(edge.direct,side)
        return (side,0)
    end
	=#
end

function backward!(edge::EdgeRobot)::Tuple{HorizonSide,Int}
    # TODO
end