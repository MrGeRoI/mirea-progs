include("../lib/morerobot.jl")

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
checkinsidemaze!(edge::EdgeRobot,coord::CoordRobot) =
	countrotatesmaze!(edge,coord) > 0

# Тест
 
robot = Robot("38A.sit",animate=true)
edge = EdgeRobot(robot,West)
coord = CoordRobot{Robot}(robot,0,0)
print("A: ")
println(checkinsidemaze!(edge,coord) ? "внутри" : "снаружи")
 
robot = Robot("38B.sit",animate=true)
edge = EdgeRobot(robot,Ost)
coord = CoordRobot{Robot}(robot,0,0)
print("B: ")
println(checkinsidemaze!(edge,coord) ? "внутри" : "снаружи")
#=
robot = Robot("38C.sit",animate=true)
edge = EdgeRobot(robot,Sud)
print("C: ")
println(checkinsidemaze!(edge) ? "внутри" : "снаружи")
=#