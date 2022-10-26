include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля, на поле расставлены горизонтальные перегородки различной длины (перегорки длиной в несколько клеток, считаются одной перегородкой), не касающиеся внешней рамки.
	РЕЗУЛЬТАТ: Робот — в исходном положении, подсчитано и возвращено число всех перегородок на поле.
=#

function numborders!(robot::Robot,side::HorizonSide)
    num_borders = 0
    border = false
    
    while !isborder(robot,side)
        move!(robot,side)
        bord = isborder(robot,Nord)

        if bord != border
            if !bord
                num_borders += 1
            end

            border = bord
        end
    end

    return num_borders
end

#посчитать границы
function numborders!(robot::Robot)
	while !isborder(robot,Sud) || !isborder(robot,West)
		if !isborder(robot,West)
			move!(robot,West)
		end

		if !isborder(robot,Sud)
			move!(robot,Sud)
		end
	end

    num_borders = 0
    side = Ost
    while !isborder(robot,side) || !isborder(robot,Nord)
        num_borders += numborders!(robot,side)

        if !isborder(robot,Nord)
            side = inverse(side)
            move!(robot,Nord)
        end
    end
    return num_borders
end

# Тест
robot = Robot("11.sit",animate=true)

print("Границы: ")
print(numborders!(robot))