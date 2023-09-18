include("coordrobot.jl")
include("countmarkersrobot.jl")
#include("turnrobot.jl")
#include("directrobot.jl")
include("edgerobot.jl")
include("spiralrobot.jl")
include("temperaturerobot.jl")
 
# Стена всегда СЛЕВА от робота!
# side - текущее направление стены от робота
function around!(edgecoord::EdgeRobot{CoordRobot})::Nothing
	start_coord = get_coord(get_robot(edgecoord))

	now_coord = (0,0)

	while abs(get_rotates(edgecoord)) < 4 || now_coord != start_coord
		forward!(edgecoord)

		now_coord = get_coord(get_robot(edgecoord))
	end
end