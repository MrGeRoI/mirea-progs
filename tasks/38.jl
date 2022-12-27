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

# Тест

edgecoord = EdgeRobot{CoordRobot}(CoordRobot{SimpleRobot}(SimpleRobot(Robot("situations/38A.sit",animate=true))),West)
around!(edgecoord)
print("A: ")
println(get_rotates(edgecoord) > 0 ? "внутри" : "снаружи")
 
edgecoord = EdgeRobot{CoordRobot}(CoordRobot{SimpleRobot}(SimpleRobot(Robot("situations/38B.sit",animate=true))),Ost)
around!(edgecoord)
print("B: ")
println(get_rotates(edgecoord) > 0 ? "внутри" : "снаружи")
 
edgecoord = EdgeRobot{CoordRobot}(CoordRobot{SimpleRobot}(SimpleRobot(Robot("situations/38C.sit",animate=true))),Sud)
around!(edgecoord)
print("C: ")
println(get_rotates(edgecoord) > 0 ? "внутри" : "снаружи")
 