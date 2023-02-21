include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля
	РЕЗУЛЬТАТ: Робот - в исходном положении, и все клетки поля промакированы
=#

#заполнить всё и вернуться на место
function makefill!(robot::Robot)
    n = numsteps!(robot,Ost)
    m = numsteps!(robot,Sud)

	putmarker!(robot)

    side = West
	
	while true
		n += (side == Ost ? 1 : -1) * numsteps_putmarkers!(robot,side)

		if isborder(robot,Nord) break end

		move!(robot,Nord)
		putmarker!(robot)
		
		side = inverse(side)

		m -= 1
	end

	along!(robot, n > 0 ? West : Ost , abs(n) )
    along!(robot,Sud,abs(m))
end

# Тест
robot = Robot("3.sit",animate=true)

makefill!(robot)