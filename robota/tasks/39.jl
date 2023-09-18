include("../lib/stdrobot.jl")
#	      Nord	
#
#	West    O	  Ost
#	
#	       Sud

# Стена всегда СЛЕВА от робота!
# side - текущее направление стены от робота
function getmazearea!(robot::Robot,maze_side::HorizonSide)
    borders = Dict{Int,Vector{Int}}()

    println("1")

	result = maze(robot,maze_side) do r::Robot,side::HorizonSide,x::Int,y::Int,rotate::Int
        if borders[x] == Nothing
            borders[x] = Vector{Int}()
        end

        if (side == Nord || side == Sud)
            push!(borders[x],y)
        end

		return abs(rotate) >= 4 && x == 0 && y == 0
	end
    
    for array in borders
        sort!(array)
    end

    print(borders)

	return result[3] > 0
end

# Тест

robot = Robot("39.sit",animate=true)

println(getmazearea!(robot,Ost))
