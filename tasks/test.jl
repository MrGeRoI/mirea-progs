include("../lib/coordrobot.jl")
include("../lib/edgerobot.jl")
include("../lib/spiralrobot.jl")
include("../lib/simplerobot.jl")

supermegarobot =
	CoordRobot{EdgeRobot{SpiralRobot{SimpleRobot}}}(
		EdgeRobot{SpiralRobot{SimpleRobot}}(
			SpiralRobot{SimpleRobot}(
				SimpleRobot(
					Robot(animate = true)
				)
			),Sud
		)
	)

println(supermegarobot)
println(get_robot(supermegarobot))
