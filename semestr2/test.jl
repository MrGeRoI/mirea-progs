include("arithmetics.jl")

print("НОД (5,3) ")
println(gcd_(5,3))

print("Алгоритм евклида (6,3): ")
println(gcdx_(6,3))

print("Обратный к 2 по модулю 7: ")
println(invmod_(2,7))

print("Обратный к 4 по модулю 8: ")
println(invmod_(4,8))

print("Диофантово 2*n + 3*m = 5: ")
println(diaphant_solve(2,3,5))