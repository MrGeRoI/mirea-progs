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

# Стена всегда СЛЕВА от робота!
# side - текущее направление стены от робота
function checkinsidemaze!(robot::Robot,maze_side::HorizonSide)
	result = maze!(robot,maze_side)

	return result[3] > 0
end

# Тест
robot = Robot("38A.sit",animate=true)

print("A: ")
println(checkinsidemaze!(robot,West) ? "внутри" : "снаружи")

robot = Robot("38B.sit",animate=true)

print("B: ")
println(checkinsidemaze!(robot,Ost) ? "внутри" : "снаружи")
