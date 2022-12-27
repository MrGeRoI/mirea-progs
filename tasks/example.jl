include("../lib/unirobot.jl")

supermegarobot =
	CoordRobot{EdgeRobot}(
		EdgeRobot{SpiralRobot}(
			SpiralRobot{TemperatureRobot}(
				TemperatureRobot{SimpleRobot}(
					SimpleRobot(
						Robot(animate = true)
					)
				)
			),Sud
		)
	)

println(supermegarobot)
println(get_native_robot(supermegarobot))