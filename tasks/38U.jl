include("../lib/unirobot.jl")

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
checkinsidemaze!(edgecoord::EdgeRobot{CoordRobot})::Bool =
	countrotatesmaze!(edgecoord) > 0

# Тест

edgecoord = EdgeRobot{CoordRobot}(CoordRobot{SimpleRobot}(SimpleRobot(Robot("situations/38A.sit",animate=true))),West)
print("A: ")
println(checkinsidemaze!(edgecoord) ? "внутри" : "снаружи")
 
edgecoord = EdgeRobot{CoordRobot}(CoordRobot{SimpleRobot}(SimpleRobot(Robot("situations/38B.sit",animate=true))),Ost)
print("B: ")
println(checkinsidemaze!(edgecoord) ? "внутри" : "снаружи")

edgecoord = EdgeRobot{CoordRobot}(CoordRobot{SimpleRobot}(SimpleRobot(Robot("situations/38C.sit",animate=true))),Sud)
print("C: ")
println(checkinsidemaze!(edgecoord) ? "внутри" : "снаружи")
