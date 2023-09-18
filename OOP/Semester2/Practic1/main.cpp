#include <iostream>

#include "Circle.hpp"

int main()
{
    Circle c1(3.0,4.0);
    Circle c2(2.0);

    std::cout << "Circle1: (" << c1.GetX() << ',' << c1.GetY() << ") R = " << c1.GetRadius() << std::endl;
    std::cout << "Circle2: (" << c2.GetX() << ',' << c2.GetY() << ") R = " << c2.GetRadius() << std::endl;

    std::cout << (c1 < c2 ? "R1 < R2" : "R1 !< R2") << std::endl;

    if(+c1)
        std::cout << "Circle1 in quarter: " << -c1 << std::endl;
    else
        std::cout << "Circle1 not in any quarter" << std::endl;

    if (+c2)
        std::cout << "Circle2 in quarter: " << -c1 << std::endl;
    else
        std::cout << "Circle2 not in any quarter" << std::endl;

    return 0;
}
