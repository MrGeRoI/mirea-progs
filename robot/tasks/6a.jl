include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля, на котором  
	могут находиться также внутренние прямоугольные перегородки (все перегородки изолированы друг от друга, прямоугольники могут вырождаться в отрезки)
	РЕЗУЛЬТАТ: Робот - в исходном положении и по всему периметру внешней рамки стоят маркеры
=#

#отрисовать рамку (С ПРЕПЯТСВИЯМИ НА ПОЛЕ) и вернуться на место
function makeframe!(robot::Robot)
	path = HorizonSide[]
   
	while !isborder(robot,Sud) || !isborder(robot,Ost)
		if !isborder(robot,Ost)
			move!(robot,Ost)

			push!(path,West)
		end

		if !isborder(robot,Sud)
			move!(robot,Sud)

			push!(path,Nord)
		end
	end

	for side in (HorizonSide(i) for i in 0:3)
		putmarkers!(robot,side)
	end

	while !isempty(path)
		side = pop!(path)
		move!(robot,side)
	end
end

# Тест
robot = Robot("6a.sit",animate=true)

makeframe!(robot)