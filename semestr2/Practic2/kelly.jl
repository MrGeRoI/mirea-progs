using Plots

include("start.jl")

#9. Построить фрактал Кэлли (описание алгоитма построения см. ниже)

x = range(0, 10, length=100)
y = sin.(x)
plot(x, y)