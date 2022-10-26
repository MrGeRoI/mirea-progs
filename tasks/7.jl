include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - рядом с горизонтальной бесконечно продолжающейся 
	в обе стороны перегородкой (под ней), в которой имеется проход шириной в одну клетку.
	РЕЗУЛЬТАТ: Робот - в клетке под проходом
=#

#найти дырку в бесконечной перегородке с отверстием
function findhole!(robot::Robot)
	along!(robot,Nord)
	
	side = Ost
	num = 1

	while isborder(robot,Nord)
		along!(robot,side,num) do r::Robot
			return !isborder(r,Nord)
		end

		side = inverse(side)
		num += 1
	end

	move!(robot,Nord)
end

# Тест
robot = Robot("tasks/7.sit",animate=true)

findhole!(robot)