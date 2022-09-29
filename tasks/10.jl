include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

#закрасить поле в шахматном порядке
function makechess!(robot::Robot)
    side = Ost
    b = true
    while !isborder(robot,Nord) || !isborder(robot,side)
        if b putmarker!(robot) end

        if isborder(robot,side)
            move!(robot,Nord)
            side = inverse(side)
        else
            move!(robot,side)
        end

        b = !b
    end

    if b putmarker!(robot) end
end

# Тест
robot = Robot("10.sit",animate=true)

makechess!(robot)