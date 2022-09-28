include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

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