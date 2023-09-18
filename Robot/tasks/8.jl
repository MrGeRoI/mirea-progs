include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Где-то на неограниченном со всех сторон поле без внутренних перегородок 
	имеется единственный маркер. Робот - в произвольной клетке этого поля.
	РЕЗУЛЬТАТ: Робот - в клетке с маркером.
=#

#найти маркер на бесконечном поле
function findmarker!(robot::Robot)
	spiral!(robot,Nord) do r::Robot
		if ismarker(r)
			return true
		else
			putmarker!(r)
		end
	end
end

# Тест
robot = Robot("situations/8.sit",animate=true)

findmarker!(robot)