include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля, на котором  
	могут находиться также внутренние прямоугольные перегородки (все перегородки изолированы друг от друга, прямоугольники могут вырождаться в отрезки)
	РЕЗУЛЬТАТ: Робот - в исходном положении и маркеры не во всех клетках периметра, а только в 4-х позициях - напротив исходного положения робота
=#

# Тест
robot = Robot("6b.sit",animate=true)