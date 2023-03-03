include("polynomial.jl")

println("====================")

print("НОД (5,3) = ")
println(gcd_(5,3))

println("====================")

print("НОД (12,4) = ")
println(gcd_(12,4))

println("====================")

print("Алгоритм евклида (6,3): ")
println(gcdx_(6,3))

println("====================")

print("Обратный к 2 по модулю 7: ")
println(invmod_(2,7))

println("====================")

print("Обратный к 4 по модулю 8: ")
println(invmod_(4,8))

println("====================")

print("Диофантово 2*n + 3*m = 5:\n")
result = diaphant_solve(2,3,5)
print("\tn = ",result[1],"\n\tm = ",result[2],"\n")

println("====================")

print("Остаток -25 (mod 5):\n")
display(Residue{Integer,5}(-25))

println("====================")

print("Остаток 12 (mod 9):\n")
display(Residue{Integer,9}(12))

println("====================")

print("-7 (mod 10) = ")
display( Residue{Integer,10}(-7) )

println("====================")

print("2 + 3 (mod 7) = ")
display( Residue{Integer,7}(2) + Residue{Integer,7}(3) )

println("====================")

print("6 * 3 (mod 15) = ")
display( Residue{Integer,15}(6) + Residue{Integer,15}(3) )

println("====================")

print("2 - 4 (mod 5) = ")
display( Residue{Integer,5}(2) - Residue{Integer,5}(4) )

println("====================")

print("Обратный к 5 (mod 6) = ")
display( inverse( Residue{Integer,6}(5) ) )

println("====================")

poly = Polynom{Real}([13.0,9.0,2.0])
qoly = Polynom{Real}([1.0,-9.0])

print("p(t) := ")
display(poly)

print("q(t) := ")
display(qoly)

println("====================")

print("-p(t) = ")
display(-poly)

println("====================")

print("p(t) + q(t) = ")
display(poly + qoly)

println("====================")

print("p(t) - q(t) = ")
display(poly - qoly)

println("====================")

print("p(t) * q(t) = ")
display(poly * qoly)

println("====================")

println("p(t) (mod 5) = ")

display(Residue{Polynom{Real},5}(poly))

println("====================")

println("p(t) (mod 10,5,4) = ")

display(Residue{Polynom{Real},(10,5,4)}(poly))
