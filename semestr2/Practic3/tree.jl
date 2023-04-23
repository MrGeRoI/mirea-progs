struct Node
    index::Int
    children::Vector{Union{Node,Nothing}}

	function Node(idx::Int)
		new(idx,Union{Node,Nothing}[])
	end

	function Node(vec::Vector)
		child = Union{Node,Nothing}[]

		for sub in vec[1:end-1]
			push!(child,isempty(sub) ? nothing : Node(sub))
		end

		new(vec[end],child)
	end

	function Node(dict::Dict{Int,Vector{Int}},rootIdx::Int)
		nodes = Dict{Int,Node}()

		rootVec = Union{Node,Nothing}[]
		
		for (parent,vec) in dict
			if parent != rootIdx && !haskey(nodes,parent)
				nodes[parent] = Node(parent)
			end
			
			for child in vec
				if child != rootIdx && !haskey(nodes,child)
					nodes[child] = Node(child)
				end

				push!((parent == rootIdx) ? rootVec : nodes[parent].children,nodes[child])
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
	for node in root.children
		if isnothing(node)
			println('\t'^(inhert + 1),"[]")
		else
			trace(node,inhert + 1)
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

function to_dict!(root::Node,dict::Dict{Int,Vector{Int}})::Nothing
	if !haskey(dict,root.index)
		dict[root.index] = Int[]
	end

	for node in root.children
		if !isnothing(node)
			to_dict!(node,dict)

			push!(dict[root.index],node.index)
		end
	end

	return nothing
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

dictTree2 = Dict{Int, Vector{Int}}([
    (1,
        [
            2,
            3
        ]
    ),

    (3,
        [
            4
        ]
    ),

    (5,
        [
            6
        ]
    ),
])

dictTree1 = Dict{Int, Vector{Int}}()
to_dict!(Node(vecTree1),dictTree1)
vecTree2 = to_vec(Node(dictTree2,1))

println(dictTree1)
println(vecTree2)