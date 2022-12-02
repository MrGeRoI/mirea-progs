using HorizonSideRobots

left(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)-1, 4))
right(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+1, 4))

print(right(Nord))