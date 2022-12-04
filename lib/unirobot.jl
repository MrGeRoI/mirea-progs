include("coordrobot.jl")
include("countmarkersrobot.jl")
include("edgerobot.jl")
include("spiralrobot.jl")
include("temperaturerobot.jl")

function countrotatesmaze!(edgecoord::EdgeRobot{CoordRobot})::Int
	start_coord = get_coord(get_robot(edgecoord))

	now_coord = (0,0)

	rotate = 0

	while abs(rotate) < 4 || now_coord[1] != start_coord[1] || now_coord[2] != start_coord[2]
		result = forward!(edgecoord)

		rotate = rotate + result[2]
		now_coord = get_coord(get_robot(edgecoord))
	end

	return rotate
end