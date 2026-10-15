#include <iostream>
#include <stdexcept>

#include "Rectangle/Rectangle.h"
#include "Car/Car.h"
#include "Truck/Truck.h"
#include "Stack/Stack.h"
#include "Pr1/Pr1.h"
#include "Pr2/Pr2.h"

using namespace std;

void printComparison(int result)
{
    if (result < 0) std::cout << "Truck is faster.\n";
    else if (result == 0) std::cout << "Car and truck speed is the same.\n";
    else std::cout << "Car is faster.\n";
}

int main()
{
    std::cout << "--- Task 1: Rectangle ---\n";

    double width, height;
    std::cout << "Enter width and height of the rectangle: ";
    std::cin >> width >> height;

    try {
        Rectangle r1(width, height);
        r1.show("r1");
        std::cout << "The face of r1 is s=" << r1.face() << '\n';
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    {
        Rectangle r2(10, 5);
        double p;
        double s = r2.face(&p);

        r2.show("r2");
        std::cout << "The face of r2 is s=" << s << ", and the perimeter is p=" << p << '\n';
    }


    std::cout << "\n--- Task 2: Car and Truck ---\n";

    Car c1(6, 55), c2(2, 120);
    Truck t1(10000, 55), t2(20000, 72);

    std::cout << "Comparing c1 and t1:\n";
    printComparison(sp_greater(c1, t1));

    std::cout << "Comparing c2 and t2:\n";
    printComparison(c2.sp_greater(t2));

    double km;
    std::cout << "\nEnter distance in km: ";
    std::cin >> km;

    try {
        double timeC1 = travelTime(c1, km);
        double timeC2 = travelTime(c2, km);
        double timeT1 = travelTime(t1, km);
        double timeT2 = travelTime(t2, km);

        std::cout << "c1 needs " << timeC1 << " h\n";
        std::cout << "c2 needs " << timeC2 << " h\n";
        std::cout << "t1 needs " << timeT1 << " h\n";
        std::cout << "t2 needs " << timeT2 << " h\n";
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    std::cout << "\n--- Additional Task 1: Stack ---\n";

    Stack lower = loadstack();
    Stack upper = loadstack(1);

    std::cout << "Lowercase stack: ";
    while (!lower.isEmpty())
        std::cout << lower.pop();

    std::cout << "\nUppercase stack: ";
    while (!upper.isEmpty())
        std::cout << upper.pop();
    std::cout << '\n';


    std::cout << "\n--- Additional Task 2: Printer ---\n";

    Pr1 p1;
    Pr2 p2;
    std::cout << std::boolalpha;

    std::cout << "Nobody printing, in use: " << inuse(p1, p2) << '\n';

    p1.set_print(1);
    std::cout << "pr1 printing, in use: " << inuse(p1, p2) << '\n';

    p1.set_print(0);
    p2.set_print(1);
    std::cout << "pr2 printing, in use: " << inuse(p1, p2) << '\n';

    p2.set_print(0);
    std::cout << "Both done, in use: " << inuse(p1, p2) << '\n';

    return 0;
}
