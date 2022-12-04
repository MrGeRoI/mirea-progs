include("simplerobot.jl")

mutable struct EdgeRobot{TypeRobot <: AbstractRobot} <: AbstractRobot
	robot::TypeRobot

    edge_side::HorizonSide
    is_left::Bool
 
	EdgeRobot{TypeRobot}(robot::TypeRobot,side::HorizonSide,left::Bool=true) where {TypeRobot <: AbstractRobot} = new(robot,side,left)

	EdgeRobot(side::HorizonSide) = EdgeRobot{Robot}(Robot(animate=true),side)
end

get_robot(edge::EdgeRobot)::AbstractRobot =
	edge.robot
	
get_edge_side(edge::EdgeRobot)::HorizonSide =
    edge.edge_side
 
get_forward_side(edge::EdgeRobot)::HorizonSide =
    edge.is_left ? right(edge.edge_side) : left(edge.edge_side)
 
function forward!(edge::EdgeRobot)::Tuple{HorizonSide,Int}
    if isborder(edge.robot,edge.edge_side) && !isborder(edge.robot,get_forward_side(edge))
        side = get_forward_side(edge)
        move!(edge.robot,side)
        return (side,0)
    end
 
    if !isborder(edge.robot,edge.edge_side)
        side = edge.edge_side
        move!(robot,side)
        edge.edge_side = edge.is_left ? left(edge.edge_side) : right(edge.edge_side)
        return (side,-1)
    elseif isborder(edge.robot,get_forward_side(edge))
        rotate = 0
        while isborder(edge.robot,get_forward_side(edge))
            edge.edge_side = edge.is_left ? right(edge.edge_side) : left(edge.edge_side)
            rotate = rotate + 1
        end
        side = get_forward_side(edge)
        move!(edge.robot,side)
        return (side,rotate)
    else
        side = get_forward_side(edge)
        move!(edge.robot,side)
        return (side,0)
    end
end

function backward!(edge::EdgeRobot)::Tuple{HorizonSide,Int}
    # TODO
end