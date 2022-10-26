include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud


#=
	ДАНО: Робот находится в произвольной клетке ограниченного прямоугольного поля без 
	внутренних перегородок и маркеров.
	РЕЗУЛЬТАТ: Робот — в исходном положении в центре косого креста из маркеров, расставленных вплоть до внешней рамки.
=#

#отрисовать крест и вернуться на место
function makediagonalcross!(robot::Robot)
	n = -numsteps!(robot,West)
	m = -numsteps!(robot,Nord)

	putmarker!(robot)

	while !isborder(robot,Sud) && !isborder(robot,Ost)
		if !isborder(robot,Sud)
			move!(robot,Sud)
			m += 1
		end
		
		if !isborder(robot,Ost)
			move!(robot,Ost)
		end

		putmarker!(robot)
	end
	
	along!(robot,Nord)

	putmarker!(robot)

	while !isborder(robot,Sud) && !isborder(robot,West)
		if !isborder(robot,Sud)
			move!(robot,Sud)
		end
		
		if !isborder(robot,West)
			move!(robot,West)
		end

		putmarker!(robot)
	end
	
	along!(robot, n > 0 ? West : Ost , abs(n) )
	along!(robot, m > 0 ? Nord : Sud , abs(m) )
end

# Тест
robot = Robot("4.sit",animate=true)

makediagonalcross!(robot)