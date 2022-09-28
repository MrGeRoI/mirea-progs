include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#найти дырку в бесконечной перегородке с отверстием
function findhole!(robot::Robot)
	along!(robot,Nord)
	
	side = Ost
	num = 1

	while isborder(robot,Nord)
		for _ in 1:num
			if !isborder(robot,Nord) break end

			move!(robot,side)
		end
		
		side = inverse(side)
		num += 1
	end

	move!(robot,Nord)
end

# Тест
robot = Robot("7.sit",animate=true)

findhole!(robot)