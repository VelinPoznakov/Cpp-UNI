# C++ University Coursework

My C++20 work for the university course on object-oriented programming: the weekly laboratory exercises and the
course project. Every folder is a separate CLion / CMake project. Open the folder in CLion and run it.

| Folder | What it is | Topics |
|--------|------------|--------|
| [`1`](1) | Lab exercise 1 | Classes `Time`, `Employee` and `Line`: constructors and destructors, dynamic memory, validation with exceptions |
| [`2`](2) | Lab exercise 2 | `Rectangle`; `Car` and `Truck` with friend functions; extra tasks: a `Stack` and a printer status shared by two classes through a friend function (`Pr1`, `Pr2`) |
| [`3`](3) | Lab exercise 3 | `Point` and `Array`; extra tasks: `Stack`, `Queue` and a `Student` list. Classes that own dynamic memory get their own copy constructor and assignment operator |
| [`4`](4) | Lab exercise 4 | Inheritance: `Vehicle` → `Car`, `Truck`; extra task: a media collection (`Item` → `Movie`, `Game`, `Music`) with protected and static members |
| [`CourseProject`](CourseProject) | Course project | **Parking Lot Manager**: a console application with a PostgreSQL database (see below) |

## Lab exercises

All labs follow the same layout:

- every class has its own folder with a header and a source file (`Car/Car.h`, `Car/Car.cpp`);
- `main.cpp` runs the tasks one after another and prints `--- Task N: ... ---` for the worked examples and
  `--- Additional Task N: ... ---` for the self-study tasks;
- invalid values are rejected by the setters with exceptions, which `main` catches and prints as `Error: ...`.

They use only the standard library, so they build with CLion's default compiler without any setup.

## Course project: Parking Lot Manager

A console application for running a parking lot. Vehicles get the best-fitting free spot when they enter and pay for
every started hour when they leave. Everything is stored in PostgreSQL, so nothing is lost when the program closes.

The full documentation (requirements, class diagram, database design, algorithms, user guide and tests) is in
[`CourseProject/Documentation/Parking Lot Manager - Documentation.docx`](CourseProject/Documentation).

### Features

- **Parking map**: all spots with the vehicle on each one
- **Park a vehicle**: the smallest free spot that fits is chosen automatically, and returning vehicles are recognised by their plate
- **Vehicle leaves**: the fee is calculated and the ticket is closed
- **Find a vehicle** and **list parked vehicles**, with what each would pay right now
- **Ticket history** (last 20 visits) and a **revenue report** per vehicle type
- **Add parking spots** while the program is running

| Vehicle    | Spot it needs | Price                            |
|------------|---------------|----------------------------------|
| Motorcycle | SMALL         | 1.00 EUR / hour                  |
| Car        | MEDIUM        | 2.00 EUR / hour                  |
| Truck      | LARGE         | 4.00 EUR / hour + 5.00 EUR entry |

Every started hour is paid, with a minimum of 1 hour. A vehicle may use a bigger spot when all spots of its own size
are taken.

### Classes

```
Vehicle (abstract)     plate, owner; virtual type / spot size / price
 ├─ Car
 ├─ Motorcycle
 └─ Truck              overrides calculateFee() to add the entry fee
VehicleFactory         builds the right subclass from its name ("Car", ...)
ParkingSpot            numbered spot; owns the parked vehicle (unique_ptr)
Ticket                 one visit: entry/exit time, hours, fee
ParkingLot             the rules: park, leave, best-fitting spot, fees
PostgresStorage        saves and loads everything in PostgreSQL
Menu                   console user interface
ParkingException       error for broken parking rules
```

It shows encapsulation, inheritance, polymorphism and abstraction, plus a constructor/destructor pair that opens
and closes the database connection, smart pointers, operator overloading, a custom exception, STL containers and
parameterised SQL queries.

### Setup on Windows with CLion

1. **libpq** (PostgreSQL's client library). Install [MSYS2](https://www.msys2.org) and run this in its *UCRT64* shell:
   ```
   pacman -S mingw-w64-ucrt-x86_64-postgresql
   ```
   CLion's default compiler works, so nothing has to be changed in CLion. After every build, CMake copies `libpq.dll`
   and the DLLs it needs next to `CourseProject.exe`. If MSYS2 is not in `C:\msys64`, set the CMake option
   `-DLIBPQ_ROOT=<your MSYS2>/ucrt64`.
2. **PostgreSQL server** (version 13 or newer). With Docker, for example:
   ```
   docker run --name parking-db -e POSTGRES_PASSWORD=<admin password> -p 5431:5432 -d postgres:18
   docker exec -it parking-db psql -U postgres -c "CREATE ROLE parking LOGIN PASSWORD '<password>'" -c "CREATE DATABASE parking OWNER parking"
   ```
3. **Connection settings.** Copy `CourseProject/db.conf.example` to `CourseProject/db.conf` and put in the password.
   `db.conf` is in `.gitignore`, so the password never ends up in Git.
4. **Run it from CLion.** The first start creates the tables and 17 spots (4 small, 10 medium, 3 large).

To start over with an empty parking lot:
```
TRUNCATE tickets, vehicles, spots RESTART IDENTITY;
```
