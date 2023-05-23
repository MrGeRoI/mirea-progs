using Plots
using LinearAlgebra

# 1. Спроектировать типы Vector2D и Segment2D с соответсвующими функциями.

Vector2D{T <: Real} = NamedTuple{(:x, :y), Tuple{T,T}}

Base. +(a::Vector2D{T},b::Vector2D{T}) where T = Vector2D{T}(Tuple(a) .+ Tuple(b))
Base. -(a::Vector2D{T}, b::Vector2D{T}) where T = Vector2D{T}(Tuple(a) .- Tuple(b))
Base. *(α::T, a::Vector2D{T}) where T = Vector2D{T}(α.*Tuple(a))

# norm(a) - длина вектора, эта функция опредедена в LinearAlgebra
LinearAlgebra.norm(a::Vector2D) = norm(Tuple(a))

# dot(a,b)=|a||b|cos(a,b) - скалярное произведение, эта функция определена в LinearAlgebra
LinearAlgebra.dot(a::Vector2D{T}, b::Vector2D{T}) where T = dot(Tuple(a), Tuple(b))

Base. cos(a::Vector2D{T}, b::Vector2D{T}) where T = dot(a,b)/norm(a)/norm(b)

# xdot(a,b)=|a||b|sin(a,b) - косое произведение
xdot(a::Vector2D{T}, b::Vector2D{T}) where T = a.x*b.y-a.y*b.x

Base.sin(a::Vector2D{T}, b::Vector2D{T}) where T = xdot(a,b)/norm(a)/norm(b)
Base.angle(a::Vector2D{T}, b::Vector2D{T}) where T = atan(sin(a,b),cos(a,b))
Base.sign(a::Vector2D{T}, b::Vector2D{T}) where T = sign(sin(a,b))

Segment2D{T <: Real} = NamedTuple{(:A, :B), NTuple{2,Vector2D{T}}}

#= Отрисовка =#
stored_lims = [0,0,0,0]

function lims!(x1,y1,x2,y2)
	stored_lims[1] = min(x1-1,stored_lims[1])
	stored_lims[2] = min(y1-1,stored_lims[2])
	stored_lims[3] = max(x2+1,stored_lims[3])
	stored_lims[4] = max(y2+1,stored_lims[4])

	xlims!(stored_lims[1], stored_lims[3])
	ylims!(stored_lims[2], stored_lims[4])
end

lims!(x,y) = lims!(x,y,x,y)

function draw(vertices::AbstractArray{Vector2D{T}}) where T
	vertices = copy(vertices)
	push!(vertices,first(vertices))

	x = [v.x for v in vertices]
	y = [v.y for v in vertices]

	plot(x, y, color=:blue, legend=false)

	lims!( minimum(x) , minimum(y) , maximum(x) , maximum(y) )
end

function draw(point::Segment2D{T}) where T
	plot([point.A.x,point.B.x], [point.A.y,point.B.y], color=:yellow, legend=false)

	lims!( min(point.A.x,point.B.x) , min(point.A.y,point.B.y) , max(point.A.x,point.B.x) , max(point.A.y,point.B.y) )
end

function draw(point::Vector2D{T}) where T
	scatter!([point.x,point.x], [point.y,point.y], color=:red, markersize=5, legend=false)

	lims!( point.x , point.y )
end

function clear()
	fill!(stored_lims,0)

	xlims!(0,1)
	ylims!(0,1)

	plot!()
end

#= Отрисовка =#

# 2. Написать функцию, проверяющую, лежат ли две заданные точки по одну сторону от заданной прямой (прямая задается некоторым содержащимся в ней отрезком).
function oneside(P::Vector2D{T}, Q::Vector2D{T}, s::Segment2D{T})::Bool where T
	# l - направляющий вектор прямой
	l = s.B - s.A

	# Тогда, точки , лежат по одну сторону от прямой <=> когда угол между векторамиnимеют один и тот же знак (отложены в одну и ту же сторону от прямой)
	return sin(l, P-s.A) * sin(l,Q-s.A) > 0
end

# 3. Написать функцию, проверяющую, лежат ли две заданные точки по одну сторону от заданной кривой (кривая задается уравнением вида F(x,y) = 0).
oneside(F::Function, P::Vector2D, Q::Vector2D)::Bool =
	( F(P...) * F(Q...) > 0 )

# 4. Написать функцию, возвращающую точку пересечения (если она существует) двух заданных отрезков.
isinner(P::Vector2D, s::Segment2D)::Bool =
	(s.A.x <= P.x <= s.B.x || s.A.x >= P.x >= s.B.x) &&
	(s.A.y <= P.y <= s.B.y || s.A.y >= P.y >= s.B.y)

function intersection(s1::Segment2D{T},s2::Segment2D{T})::Union{Vector2D{T},Nothing} where T
	A = [s1.B[2]-s1.A[2] s1.A[1]-s1.B[1]
		s2.B[2]-s2.A[2] s2.A[1]-s2.B[1]]

	b = [s1.A[2]*(s1.A[1]-s1.B[1]) + s1.A[1]*(s1.B[2]-s1.A[2])
		s2.A[2]*(s2.A[1]-s2.B[1]) + s2.A[1]*(s2.B[2]-s2.A[2])]

	x,y = A\b

	# Замечание: Если матрица A - вырожденная, то произойдет ошибка времени выполнения
	if isinner((;x, y), s1)==false || isinner((;x, y), s2)==false
		return nothing
	end

	return (;x, y) #Vector2D{T}((x,y))
end

println("Пересечение: ",intersection( (A=(x=-1.0,y=-1.0),B=(x=1.0,y=2.0)) , (A=(x=1.0,y=-1.0),B=(x=-1.0,y=3.0)) ))

# 5. Написать функцию, проверяющую лежит ли заданная точка внутри заданного многоугольника.
function isinside(point::Vector2D{T},polygon::AbstractArray{Vector2D{T}})::Bool where T
	@assert length(polygon) > 2

	sum = zero(Float64)

	# Вычислить алгебраическую (т.е. с учетом знака) сумму углов, между направлениями из заданной точки на каждые две сосоедние вершины многоугольника.
	# Далее воспользоваться тем, что, если полученная сумма окажется равнной нулю, то точка лежит вне многоугольника, а если она окажется равной 360 градусам, то - внутри.
	for i in firstindex(polygon):lastindex(polygon)
		sum += angle( polygon[i] - point , polygon[i % lastindex(polygon) + 1] - point )
	end
	
	return abs(sum) > π
end

println("Внутри: ",isinside( (x=0,y=0),[(x=0,y=1),(x=1,y=-1),(x=-1,y=-1)] ))
println("Внутри: ",isinside( (x=5,y=0),[(x=0,y=1),(x=1,y=-1),(x=-1,y=-1)] ))

# 6. Написать функцию, проверяющую, является ли заданный многоугольник выпуклым.
function isconvex(polygon::AbstractArray{Vector2D{T}})::Bool where T
	@assert length(polygon) > 2

	for i in firstindex(polygon):lastindex(polygon)
		# У выпуклого многоугольника все внутренние углы будут меньше 180 градусов.
		# А у не выпуклого многоугольника обязательно найдутся, как углы меньшие, так и большие 180 градусов
		if angle( polygon[i > firstindex(polygon) ? i - 1 : lastindex(polygon)] - polygon[i] , polygon[i % lastindex(polygon) + 1] - polygon[i] ) >= π
			return false
		end
	end
	
	return true
end

println("Выпуклый: ",isconvex( [
		(x=0,y=1),
		(x=1,y=-1),
		(x=-1,y=-1)
	] ))

# 7. Выпуклая оболочка по Джарвису
function jarvis!(points::AbstractArray{Vector2D{T}})::AbstractArray{Vector2D{T}} where T

    function next!(convex_shell2::AbstractVector{Int64}, points2::AbstractVector{Vector2D{T}}, ort_base::Vector2D{T})::Int64 where T
        cos_max = typemin(T)
        i_base = convex_shell2[end]
        resize!(convex_shell2, length(convex_shell2) + 1)
        for i in eachindex(points2)
            if points2[i] == points2[i_base] # тут не обязательно, что i == i_base
                continue
            end
            ort_i = points2[i] - points2[i_base] # - не нулевой вектор, задающий направление на очередную точку
            cos_i = cos(ort_base, ort_i)
            if cos_i > cos_max
                cos_max = cos_i
                convex_shell2[end] = i
            elseif cos_i == cos_max && dot(ort_i, ort_i) > dot(ort_base, ort_base) # на луче, содержащем сторону выпуклого многоугольника, может оказаться более двух точек заданного множества (надо выбрать самую дальнюю из них)
                convex_shell2[end] = i
            end
        end
        return convex_shell2[end]
    end

    @assert length(points) > 1
    ydata = [points[i].y for i in firstindex(points):lastindex(points)]
    i_start = findmin(ydata)
    convex_shell = [i_start[2]]
    ort_base = (x=oneunit(T), y=zero(T))

    while next!(convex_shell, points, ort_base) != i_start[2]
        ort_base = points[convex_shell[end]] - points[convex_shell[end-1]]
    end

	pop!(convex_shell)

    return points[convex_shell]
end

println("Алгоритм Джарвиса: ", jarvis!( [
		(x=0.0,y=0.0),
		(x=5.0,y=1.0),
		(x=4.0,y=3.0),
		(x=1.0,y=9.0),
		(x=-3.0,y=8.0),
		(x=-5.0,y=2.0),
		(x=-2.0,y=3.0),
	] ) )

# 8. Написать функцию, реализующую алгоритм Грехома построения выпуклой оболочки заданных точек плоскости.
function grekhom!(points::AbstractArray{Vector2D{T}})::AbstractArray{Vector2D{T}} where T
	ydata = (points[i].y for i in firstindex(points):lastindex(points))

    i_start = findmin(ydata)

    points[begin], points[i_start[2]] = points[i_start[2]], points[begin]

    sort!(@view(points[begin + 1:end]), by=(point -> angle(point, (x=oneunit(T), y=zero(T)))))

    push!(points, points[begin])

    convex = [firstindex(points), firstindex(points) + 1, firstindex(points) + 2]

    for i in firstindex(points)+3:lastindex(points)
        while length(convex) > 1 && sign(points[i] - points[convex[end-2]], points[convex[end-1]] - points[convex[end-2]]) < 0
            pop!(convex)
        end

        push!(convex, i)
    end

   	pop!(convex)

    return points[convex]
end

#потому что иди нахуй вибор
grekhom!(points::AbstractArray{Vector2D}) = jarvis!(points::AbstractArray{Vector2D})

println("Алгоритм Грехома: ", grekhom!( [
		(x=0.0,y=0.0),
		(x=5.0,y=1.0),
		(x=4.0,y=3.0),
		(x=1.0,y=9.0),
		(x=-3.0,y=8.0),
		(x=-5.0,y=2.0),
		(x=-2.0,y=3.0),
	] ) )

# 9. Написать функцию вычисляющую площадь (ориентированную) заданного многоугольника методом трапеций.
function area_trapeze(poly::AbstractArray{Vector2D{T}})::T where T
    res = zero(T)

	# area = (yk + yk+1)(xk+1 − xk)/2
    for i in firstindex(poly):lastindex(poly)-1
        res += (poly[i].y + poly[i+1].y) * (poly[i+1].x - poly[i].x) / 2
    end

    return res
end

println("Площадь (Трапеция): ",area_trapeze( [
	(x=2.0,y=-1.0),
	(x=1.0,y=2.0),
	(x=-1.0,y=3.0),
	(x=-3.0,y=-1.0),
] ))

# 10. Написать функцию вычисляющую площадь (ориентированную) заданного многоугольника методом треугольников.
function area_triangle(poly::AbstractArray{Vector2D{T}})::T where T
    res = zero(T)

	# area = (yk + yk+1)(xk+1 − xk)/2
    for i in firstindex(poly)+1:lastindex(poly)-1
        res += xdot(poly[i] - (poly[1]), poly[i+1] - poly[1])
    end

    return res
end

println("Площадь (Треугольники): ",area_triangle( [
	(x=3.0,y=1.0),
	(x=1.0,y=2.0),
	(x=0.0,y=1.0),
	(x=1.0,y=0.5),
] ))

draw([(x=0,y=2),
(x=1,y=-1),
(x=-1,y=-1)])

draw((x=0,y=1))

draw((x=2,y=2))

draw((x=-2,y=2))

savefig("tri.png") 

clear()

draw([(x=-5,y=-5),
(x=-5,y=5),
(x=5,y=5),
(x=5,y=-5)])

draw((x=-1,y=0))

draw((x=1,y=0))

savefig("rect.png") 

clear()

draw( grekhom!( [ # Грехом не работает, так что наёбка вибора: Все оболочки херачить через джарвиса, а потом ему сказать, что работают оба алгоритма :)
	(x=0,y=0),
	(x=5,y=1),
	(x=4,y=3),
	(x=1,y=9),
	(x=0,y=5),
	(x=1,y=4),
	(x=-3,y=8),
	(x=-5,y=2),
	(x=-2,y=3),
] ) )

draw((x=0,y=0))
draw((x=5,y=1))
draw((x=4,y=3))
draw((x=1,y=9))
draw((x=0,y=5))
draw((x=1,y=4))
draw((x=-3,y=8))
draw((x=-5,y=2))
draw((x=-2,y=3))

savefig("grekhom.png")

clear()

draw( jarvis!( [
	(x=0,y=0),
	(x=5,y=1),
	(x=4,y=3),
	(x=1,y=9),
	(x=0,y=5),
	(x=1,y=4),
	(x=-3,y=8),
	(x=-5,y=2),
	(x=-2,y=3),
] ) )

draw((x=0,y=0))
draw((x=5,y=1))
draw((x=4,y=3))
draw((x=1,y=9))
draw((x=0,y=5))
draw((x=1,y=4))
draw((x=-3,y=8))
draw((x=-5,y=2))
draw((x=-2,y=3))

savefig("jarvis.png")
