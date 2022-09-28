include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#найти маркер на бесконечном поле
function findmarker!(robot::Robot)
	side = Nord
	radius = 1

	while !ismarker(robot)
		move!(robot,Ost)

		# Nord -> West -> Sud -> Ost -> Nord
		for side in (HorizonSide(i % 4) for i in 0:4)
			if ismarker(robot) break end
		
			along!(robot,side, radius * ( 2 - Int(side == Nord) ) )
		end

		radius += 1
	end
end

# Тест
robot = Robot("8.sit",animate=true)

findmarker!(robot)