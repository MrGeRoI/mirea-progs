include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#=
	ДАНО: Робот - в произвольной клетке поля (без внутренних перегородок и маркеров)
	РЕЗУЛЬТАТ: Робот - в исходном положении, и все клетки по периметру внешней рамки промакированы
=#

#отрисовать рамку и вернуться на место
function makeframe!(robot::Robot)
    n = numsteps!(robot,Ost)
    m = numsteps!(robot,Sud)

	# Nord -> West -> Sud -> Ost
    for side in (HorizonSide(i) for i in 0:3)
        putmarkers!(robot,side)
    end

    along!(robot,West,n)
    along!(robot,Nord,m)
end

# Тест
robot = Robot("2.sit",animate=true)

makeframe!(robot)