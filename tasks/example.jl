include("../lib/unirobot.jl")

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
println(get_native_robot(supermegarobot))