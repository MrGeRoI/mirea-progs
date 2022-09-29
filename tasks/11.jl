include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud


function numborders!(robot::Robot,side::HorizonSide)
    num_borders = 0
    border = false
    
    while !isborder(robot,side)
        move!(robot,side)
        bord = isborder(robot,Nord)

        if bord != border
            if !bord
                num_borders += 1
            end

            border = bord
        end
    end

    return num_borders
end
#закрасить поле в шахматном порядке
function numborders!(robot::Robot)
	while !isborder(robot,Sud) || !isborder(robot,West)
		if !isborder(robot,West)
			move!(robot,West)
		end

		if !isborder(robot,Sud)
			move!(robot,Sud)
		end
	end

    num_borders = 0
    b = false
    side = Ost
    while !isborder(robot,side) || !isborder(robot,Nord)
        num_borders += numborders!(robot,side)

        if !isborder(robot,Nord)
            side = inverse(side)
            move!(robot,Nord)
        end
    end
    return num_borders
end

# Тест
robot = Robot("11.sit",animate=true)

print("Границы: ")
print(numborders!(robot))