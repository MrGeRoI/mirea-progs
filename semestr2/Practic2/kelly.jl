using OffsetArrays

using Images # -> FileIO

Base.@kwdef struct NewtonFractal
    basin_colors::NTuple{n, RGB{N0f8}} where n  
        # - при создании объекта требуется задать цвета раскраски бассейнов притяжений
    order = length(basin_colors) # порядок уравнения
    roots = tuple((exp(im*2π/order*i) for i ∈ 0:order-1)...) # корни уравнения: z^order = 1
    cell_size = 1/1000
    N = 2000
    image = Matrix{RGB{N0f8}}(undef, 2N+1, 2N+1)
    ε = 0.3 # определяет окрестность "притяжения" корня
    iterations_number = 10 
        # - при построении фрактала после этого числа итераций определяется, в окрестность 
        # притяжения какого корня попала точка (или не попала ни в какую окрестность)
end 

function build!(fractal::NewtonFractal)
    @assert fractal.order > 1
    n = fractal.order
    
    r(z) = (z-1/z^(n-1))/n # r(z) = f(z)/f'(z), where f(z) = z^n-1
    
    diapason = -fractal.N:fractal.N
    image = OffsetArray(fractal.image, diapason, diapason)
    for j ∈ diapason, i ∈ diapason
        z = fractal.cell_size * complex(i,j)
        for _ in 1:fractal.iterations_number
            z -= r(z)
        end    
        root_index = findfirst(abs.(fractal.roots .- z) .<= fractal.ε)
        !isnothing(root_index) && (image[i,j] = fractal.basin_colors[root_index])
    end
end

using GLMakie
function draw(fractal::NewtonFractal) 
    f,a,_ = image(fractal.image)
    a.aspect = 1
    display(f)
end

Images.save(file, fractal::NewtonFractal) = save(file, rotl90(fractal.image))

fractal = NewtonFractal(
    basin_colors = (RGB(1,0,0),RGB(0,1,0),RGB(0,0,1)),
    iterations_number = 50,
    ε=0.5
)

build!(fractal)
#draw(fractal)
save("newton_fractal.png", fractal)
