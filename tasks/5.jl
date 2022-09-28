include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#отрисовать двойную рамку и вернуться на место
function makedoubleframe!(robot::Robot)
    n = numsteps!(robot,Ost)
    m = numsteps!(robot,Sud)

    for side in (HorizonSide(i) for i in 0:3)
        putmarkers!(robot,side)
    end

	side = West

	while !isborder(robot,Nord)
		move!(robot,side)

		if isborder(robot,side)
			side = inverse(side)
			move!(robot,Nord)
		end
	end

	#println("found!")
	
	f_rotate = (size == West) ? right : left

	#println(f_rotate)

	for i in 0:3
		while isborder(robot,f_rotate(side))
			putmarker!(robot)
			move!(robot,side)
		end
		
		putmarker!(robot)

		if i >= 3 break end
		
		side = f_rotate(side)
		move!(robot,side)
	end

    #along!(robot,West,n)
    #along!(robot,Nord,m)
end

# Тест
robot = Robot("5.sit",animate=true)

makedoubleframe!(robot)