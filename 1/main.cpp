#include <iostream>
#include <string>
#include <thread>

#include "Time/Time.h"
#include "Employee/Employee.h"
#include "Line/Line.h"

using namespace std;

int main()
{
    // Time *time = new Time(20, 20, 20);
    // std::cout << time->getTime() << std::endl;
    // delete time;


    Employee *employee = new Employee(
        "Velin",
        20,
        "Software Engineer",
        new double[3]{1000, 2000, 3000},
        3
    );

    employee->setYearsOfExperience(5);

    std::string position;

    std::cin >> position;

    employee->setCurrentPosition(position);

    employee->setSalary(4000.50);

    double avg = employee->getAverageSalary();
    double min = employee->getMinimalSalary();

    std::cout << "Average salary: " << avg << std::endl;
    std::cout << "Minimal salary: " << min << std::endl;

    delete employee;

    std::cout << "Drawing a line of length 20:\n";
    {
        Line line(20);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "Line erased.\n";

    Line* p = new Line(10);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    delete p;
    std::cout << "Second line erased.\n";

    try {
        Line bad(-5);
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }
    return 0;
}