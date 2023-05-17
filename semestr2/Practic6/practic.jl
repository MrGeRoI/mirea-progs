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
	#=
	function oreintation(p::Vector2D{T},q::Vector2D{T},r::Vector2D{T})::Bool where T
		return ( (q.y * p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y) ) > 2
	end

	#На нулевом шаге мы выбрали точку, точно лежащую в выпуклой оболочке
	@assert length(points) > 1

	if length(points) < 3
		return points
	end

	ydata = [points[i].y for i in eachindex(points)]
	i_start = findmin(ydata)
	i_cur = i_start[2]
	p = points[i_start[2]]
	q = nothing
	convex_shell = []

	while true
		push!(convex_shell,i_cur)
		q = (x=p.x + oneunit(T),y= p.y + zero(T))
		
		for i in firstindex(points):lastindex(points)
			if oreintation(p,points[i],q)
				q = points[i]
				i_cur = i
			end
		end

		p = q
		println(i_cur," ", i_start[2])
		if i_cur == i_start[2]
			break
		end
	end

	return points[convex_shell]=#
	p0 = points[0]
    sort!(@view(points[begin+1:end]), by=(point -> angle(point, (x=oneunit(T),y=zero(T)))))
    convex = [p0]
    while true
        t = p0 # кандидат на следующую точку
        for p in firstindex(points):lastindex(points)
            # лучше никакие полярные углы не считать
            if (dot((p - p0) , (t - p0)) > 0)
                t = p

        if t == p0
            continue
		end
		
        else {
            p0 = t;
            hull.push_back(t);
        }
	end

    return points[convex];
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
	ydata = [points[i].y for i in 1:length(points)]

	# Сначала надо найти базовую точку , и выбираеть базовое направление (точно так же, как это делалось в алгоритме Джарвиса).
	i_start = findmin(ydata)
	# Далее в выпуклую оболочку помещаютсяточки (они гарантированно в неё входят).
	points[begin], points[i_start[2]] = points[i_start[2]], points[begin]

	# Все остальные точки сортируются по возрастанию угла между вектором и вектором для k = 1,2,3,...,N.
	sort!(@view(points[begin+1:end]), by=(point -> angle(point, (x=oneunit(T),y=zero(T)))))
	push!(points, points[begin])

	convex = [firstindex(points), firstindex(points) + 1, firstindex(points) + 2]

	# Каждая сдедующая в отсортирванном порядке точка помещается в выпуклую оболочку, но пока временно. Т.е. эта точка помещается на вершину стека, в
	# который вконце-концов должна быть помещена вся выпуклая оболочка, но на следующих шагах алгоритма некоторые точки с вершины этого стека могут] быть сняты.
	for i in firstindex(points)+3:lastindex(points)
		while length(convex) > 1 && sign(points[i] - points[convex[end]], points[convex[end-1]] - points[convex[end]]) < 0
			pop!(convex)
		end

		push!(convex, i)
	end

	return points[convex]
end

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

draw( [
	(x=0,y=0),
	(x=5,y=1),
	(x=4,y=3),
	(x=1,y=9),
	(x=-3,y=8),
] )

draw((x=0,y=0))
draw((x=5,y=1))
draw((x=4,y=3))
draw((x=1,y=9))
draw((x=-3,y=8))
draw((x=-5,y=2))
draw((x=-2,y=3))

savefig("grekhom.png")

fig = Vector2D{Int}[]