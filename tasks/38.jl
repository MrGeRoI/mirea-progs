include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	Робот находится рядом с границей лабиринта произвольной формы.
	Требуется определить где он находится, внутри лабиринта или снаружи.
=#

# Стена всегда СПРАВА от робота!
# side - текущее направление стены от робота
function checkinsidemaze!(robot::Robot,side::HorizonSide)
	rotate_number = 0

	move_x = 0
	move_y = 0

	while true
		while isborder(robot,side) && !isborder(robot,right(side))
			move!(robot,right(side))

			move_x = move_x + tox(right(side))
			move_y = move_y + toy(right(side))

			if abs(rotate_number) >= 4 && move_x == 0 && move_y == 0 return rotate_number > 0 end
		end

		while !isborder(robot,side) || isborder(robot,right(side))
			if !isborder(robot,side)
				move!(robot,side)

				move_x = move_x + tox(side)
				move_y = move_y + toy(side)

				side = left(side)

				rotate_number = rotate_number - 1
			elseif isborder(robot,right(side))
				side = right(side)

				rotate_number = rotate_number + 1
			end

			if abs(rotate_number) >= 4 && move_x == 0 && move_y == 0 return rotate_number > 0 end
		end
	end

	rotate_number > 0
end

# Тест
robot = Robot("tasks/38A.sit",animate=true)

print("A: ")
println(checkinsidemaze!(robot,West) ? "внутри" : "снаружи")

robot = Robot("tasks/38B.sit",animate=true)

print("B: ")
println(checkinsidemaze!(robot,Ost) ? "внутри" : "снаружи")
