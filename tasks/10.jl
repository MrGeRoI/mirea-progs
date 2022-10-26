include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля (без внутренних 
	перегородок)
	РЕЗУЛЬТАТ: Робот - в исходном положении, и на всем поле расставлены маркеры в шахматном порядке клетками размера N*N (N-параметр функции), начиная с юго-западного угла
=#

#закрасить поле в шахматном порядке
function makechess!(robot::Robot)
    side = Ost
    b = true
    while !isborder(robot,Nord) || !isborder(robot,side)
        if b putmarker!(robot) end

        if isborder(robot,side)
            move!(robot,Nord)
            side = inverse(side)
        else
            move!(robot,side)
        end

        b = !b
    end

    if b putmarker!(robot) end
end

# Тест
robot = Robot("10.sit",animate=true)

makechess!(robot)