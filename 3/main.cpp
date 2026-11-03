#include <iostream>
#include <stdexcept>

#include "Point/Point.h"
#include "Array/Array.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "Student/Student.h"
#include "StudentList/StudentList.h"

int main()
{
    std::cout << "--- Task 1: Point ---\n";

    {
        Point a(3, 4), b(10, 4);

        std::cout << "Distance between ";
        a.print();
        std::cout << " and ";
        b.print();
        std::cout << " is " << a.dist(a, b) << '\n';
    }


    std::cout << "\n--- Task 2: Array ---\n";

    try {
        Array a(10);

        a.put(3) = 'X';
        a.put(2) = 'R';
        std::cout << a.get(3) << '\n' << a.get(2) << '\n';

        a.put(11) = '!';
    } catch (const std::out_of_range& ex) {
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


    std::cout << "\n--- Additional Task 2: Queue ---\n";

    Queue q1(3), q2(3), merged(6);

    for (int i = 1; i <= 3; i++) {
        q1.enqueue(i);
        q2.enqueue(i * 10);
    }

    int &added = merged.enqueue(0);
    added = 100;
    std::cout << "Changed through the returned reference, front: " << merged.front() << '\n';
    merged.dequeue();

    std::cout << "q1: ";
    q1.print();
    std::cout << "\nq2: ";
    q2.print();

    mergeQueues(q1, q2, merged);
    std::cout << "\nMerged: ";
    merged.print();
    std::cout << '\n';

    try {
        merged.enqueue(7);
    } catch (const std::overflow_error& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }


    std::cout << "\n--- Additional Task 3: Student list ---\n";

    StudentList list(2);

    list.add(Student("Ivan", 1001, 4.50));
    list.add(Student("Maria", 1002, 5.75));
    list.add(Student("Georgi", 1003, 3.25));
    list.add(Student("Elena", 1004, 5.20));
    list.add(Student("Petar", 1005, 4.00));

    list.print();

    Student &best = list.getBest();
    std::cout << "\nBest student: ";
    best.print();

    if (best.getGrade() < 6) {
        double newGrade = best.getGrade() + 0.5;
        best.setGrade(newGrade > 6 ? 6 : newGrade);
    }

    std::cout << "After the increase: ";
    list.getBest().print();

    list.swapStudents(0, 4);
    std::cout << "\nAfter swapping 0 and 4:\n";
    list.print();

    try {
        list.getByIndex(10).print();
    } catch (const std::out_of_range& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}
