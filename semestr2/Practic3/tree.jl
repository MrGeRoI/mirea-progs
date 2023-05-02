#5. Написать функции, позволяющие взаимное преобразование различных
# способов представления корневых деревьев.
# Рассмотреть следующие способы представления корневого дерева

# с помощью связанных структур.
struct Node
    index::Int
    children::Vector{Union{Node,Nothing}}

	function Node(idx::Int)
		new(idx,Union{Node,Nothing}[])
	end

	# с помощью вложенных векторов;
	function Node(vec::Vector)
		child = Union{Node,Nothing}[]

		for sub in vec[1:end-1]
			push!(child,isempty(sub) ? nothing : Node(sub))
		end

		new(vec[end],child)
	end

	# с помощью списка смежностей, представленного словарём (Dict{Int, Vector{Union{Int, Nothing}})
	function Node(dict::Dict{Int,Vector{Union{Int, Nothing}}},rootIdx::Int)
		nodes = Dict{Int,Node}()

		rootVec = Union{Node,Nothing}[]
		
		for (parent,vec) in dict
			if parent != rootIdx && !haskey(nodes,parent)
				nodes[parent] = Node(parent)
			end
			
			for child in vec
				if isnothing(child)
					push!((parent == rootIdx) ? rootVec : nodes[parent].children,nothing)
				else
					if child != rootIdx && !haskey(nodes,child)
						nodes[child] = Node(child)
					end

					push!((parent == rootIdx) ? rootVec : nodes[parent].children,nodes[child])
				end
			end
		end

		new(rootIdx,rootVec)
	end
end

add!(root::Node,node::Node)::Nothing = push!(root.children,node)

function trace(root::Node,inhert::Int = 0)::Nothing
	print('\t'^inhert)
	display(root.index)
	println('\t'^inhert,'[')
	if length(root.children) == 0
		println('\t'^(inhert + 1),"(no nodes)")
	else
		for node in root.children
			if isnothing(node)
				println('\t'^(inhert + 1),"[]")
			else
				trace(node,inhert + 1)
			end
		end
	end
	println('\t'^inhert,']')
	if inhert > 0
		println("")
	end
end

function to_vec(root::Node)::Vector
	vec = Vector()

	for node in root.children
		if isnothing(node)
			push!(vec,[])
		else
			push!(vec,to_vec(node))
		end
	end

	push!(vec,root.index)

	return vec
end

function to_dict!(root::Node,dict::Dict{Int,Vector{Union{Int, Nothing}}})::Nothing
	if !haskey(dict,root.index)
		dict[root.index] = Int[]
	end

	for node in root.children
		if isnothing(node)
			push!(dict[root.index],nothing)
		else
			to_dict!(node,dict)

			push!(dict[root.index],node.index)
		end
	end

	return nothing
end

#6. Для дерева, представленного вложенными векторами, реализовать следующие функции:

#6.1. функцию, возвращающую высоту дерева
function get_height(root::Node)::Integer
	height = 0

	for node in root.children
		if !isnothing(node)
			height = max(height,get_height(node))
		end
	end

	return height + 1
end

#6.2 функцию, возвращающую, число листьв дерева
function get_leaves(root::Node)::Integer
	if length(root.children) == 0
		return 1
	end

	leaves = 0 

	for node in root.children
		if !isnothing(node)
			leaves += get_leaves(node)
		end
	end

	return leaves
end

#6.3 функцию, возвращающую число всех вершин дерева
function get_nodes(root::Node)::Integer
	nodes = 1 

	for node in root.children
		if !isnothing(node)
			nodes += get_nodes(node)
		end
	end

	return nodes
end

#6.4 функцию, возвращающую наибольшую валентность по выходу вершин дерева
function get_valence(root::Node)::Integer
	val = length(root.children) 

	for node in root.children
		if !isnothing(node)
			val = max(val,get_valence(node))
		end
	end

	return val
end

#6.5 функцию, возвращающую среднюю длину пути к вершинам дерева
function get_average_path(root::Node)::Integer
	average = 0

	for node in root.children
		if !isnothing(node)
			average += get_height(node)
		end
	end

	average /= length(root.children)

	return average
end

vecTree1 = [
    [
        [
            [],
            [],
            6
        ],

        [],

        2
    ],

    [
        [
            [],
            [],
            4
        ],

        [
            [],
            [],
            5
        ],

        3
    ],

    1
]

dictTree2 = Dict{Int, Vector{Union{Int, Nothing}}}([
    (1,
        [
            2,
            3,
			nothing,
        ]
    ),

    (3,
        [
            4,
			nothing,
        ]
    ),

    (5,
        [
            6
        ]
    ),
])

dictTree1 = Dict{Int, Vector{Union{Int, Nothing}}}()
to_dict!(Node(vecTree1),dictTree1)
vecTree2 = to_vec(Node(dictTree2,1))

println(dictTree1)
println(vecTree2)

trace(Node(dictTree2,1))

println("Height: ",get_height(Node(dictTree2,1)))
println("Leaves: ",get_leaves(Node(dictTree2,1)))
println("Nodes: ",get_nodes(Node(dictTree2,1)))
println("Valence: ",get_valence(Node(dictTree2,1)))
println("Average Path: ",get_average_path(Node(dictTree2,1)))
