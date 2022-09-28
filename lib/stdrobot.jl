using HorizonSideRobots

#		ебаный компас
#
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#обратное направление
inverse(side::HorizonSide) =
    HorizonSide( ( Int(side) + 2 ) % 4 )

#повернуть налево
left(side::HorizonSide) = 
	HorizonSide( ( Int(side) + 1 ) % 4 )

#повернуть направо
right(side::HorizonSide) = 
	HorizonSide( ( Int(side) - 1 ) % 4 )

#пройти до упора в направлении
along!(robot::Robot,side::HorizonSide) =
    while !isborder(robot,side)
        move!(robot,side)
    end

#пройти в направлении с указаным количеством шагов
along!(robot::Robot,side::HorizonSide,num_steps::Integer) =
    for _ in 1:num_steps move!(robot,side) end
	
#идти до упора и считать шаги
function numsteps!(robot::Robot,side::HorizonSide)
    num_steps = 0
    while !isborder(robot,side)
        move!(robot,side)
        num_steps += 1
    end
    num_steps
end

#идти до упора и расставить маркеры
# 1. Делаем шаг
# 2. Ставим маркер
function putmarkers!(robot::Robot,side::HorizonSide)
    while !isborder(robot,side)
        move!(robot,side)
        putmarker!(robot)
    end
end

#идти до упора и расставить маркеры с указаным количеством шагов
# 1. Делаем шаг
# 2. Ставим маркер
function putmarkers!(robot::Robot,side::HorizonSide,num_steps::Integer)
	for _ in 1:num_steps
		move!(robot,side)
		putmarker!(robot)
	end
end

#идти до упора, расставить маркеры и посчитать шаги
function numsteps_putmarkers!(robot::Robot,side::HorizonSide)
    num_steps = 0
    while !isborder(robot,side)
        move!(robot,side)
        num_steps += 1
        putmarker!(robot)
    end
    num_steps
end

#расставить маркеры вдоль границы и сделать шаг дальше
function putmarkers_border!(robot::Robot,borderSide::HorizonSide,moveSide::HorizonSide)
	while isborder(robot,borderSide)
		putmarker!(robot)
		move!(robot,moveSide)
	end
end
