include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#отрисовать крест и вернуться на место
function makecross!(robot::Robot)
	for side in (HorizonSide(i) for i in 0:3)
		n = numsteps_putmarkers!(robot,side)
		along!(robot,inverse(side),n)#lib.jl
	end

	putmarker!(robot)
end

# Тест
robot = Robot("1.sit",animate=true)

makecross!(robot)