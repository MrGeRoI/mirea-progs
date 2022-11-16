using HorizonSideRobots

# ЗАИНКЛЮДЬ МЕНЯ 🥵

#		ебаный компас
#
#	         Nord (0)
#
#	West (1)   X   Ost (3)
#	
#	          Sud (2)

# Сторона света в координату X
tox(side::HorizonSide) =
	Int(side) % 2 == 0 ? 0 : Int(side) - 2

# Сторона света в координату Y
toy(side::HorizonSide) =
	Int(side) % 2 == 0 ? Int(side) - 1 : 0

#обратное направление
inverse(side::HorizonSide) =
    HorizonSide( ( Int(side) + 2 ) % 4 )

#повернуть налево
left(side::HorizonSide) = 
	HorizonSide( ( Int(side) + 1 ) % 4 )

#повернуть направо
right(side::HorizonSide) =
	Int(side) < 1 ? HorizonSide(3) : HorizonSide( Int(side) - 1 )

#пройти до упора в направлении
along!(robot::Robot,side::HorizonSide) =
    while !isborder(robot,side)
        move!(robot,side)
    end

#пройти в направлении с указаным количеством шагов
along!(robot::Robot,side::HorizonSide,num_steps::Integer) =
    for _ in 1:num_steps move!(robot,side) end
	
#пройти в направлении пока функция не вернёт true 
along!(stop_condition::Function,robot::Robot,side::HorizonSide) =
	while stop_condition(robot) move!(robot,side) end

#пройти в направлении пока функция не вернёт true или не кончатся шаги
function along!(stop_condition::Function,robot::Robot,side::HorizonSide,num_steps::Integer)
	for _ in 1:num_steps
		if stop_condition(robot) return end
		move!(robot,side)
	end
end

#идти до упора и считать шаги
function numsteps!(robot::Robot,side::HorizonSide)
    num_steps = 0
    while !isborder(robot,side)
        move!(robot,side)
        num_steps += 1
    end
    num_steps
end

#идти до функции и считать шаги
function numsteps!(stop_condition::Function,robot::Robot,side::HorizonSide)
    num_steps = 0
    while !isborder(robot,side) && !stop_condition(robot)
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
function putmarkers_border!(robot::Robot,borderSide::HorizonSide,move_side::HorizonSide)
	while isborder(robot,borderSide)
		putmarker!(robot)
		move!(robot,move_side)
	end
end

function snake!(robot::Robot,move_side::HorizonSide,next_row_side::HorizonSide)
	while !isborder(robot,move_side)
		along!(robot,move_side)

		if isborder(robot,next_row_side) return end

		move_side = inverse(move_side)
		move!(robot,next_row_side)
	end
end

#двигаться по спирали
function spiral!(stop_condition::Function,robot::Robot,side::HorizonSide = Ost)
	dist = 1

	while true
		for _ in 1:2
			if stop_condition(robot) return end

			along!(stop_condition,robot,side,dist)
			side = left(side)
		end

		dist += 1
	end
end

function shatl!(stop_condition::Function, robot::Robot)
	while !stop_condition(robot)
		#move!(robot,) куда?
	end
end
