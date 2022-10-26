include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля (без внутренних 
	перегородок)
	РЕЗУЛЬТАТ: Робот - в исходном положении, на всем поле расставлены маркеры в шахматном порядке, причем так, чтобы в клетке с роботом находился маркер
=#

#закрасить поле в шахматном порядке (маркер на месте робота)
function makechess!(robot::Robot)
	n = numsteps!(robot,Ost)
    m = numsteps!(robot,Sud)

    b = (n+m) % 2 == 0

    side = West
    while !isborder(robot,Nord) || !isborder(robot,side)
        if b putmarker!(robot) end

        if isborder(robot,side)
            move!(robot,Nord)
            side = inverse(side)
            m -= 1
        else
            move!(robot,side)

            n += (side == West) ? -1 : 1
        end

        b = !b
    end

    if b putmarker!(robot) end

	along!(robot, n > 0 ? West : Ost , abs(n) )
	along!(robot, m > 0 ? Nord : Sud , abs(m) )
end

# Тест
robot = Robot("9.sit",animate=true)

makechess!(robot)