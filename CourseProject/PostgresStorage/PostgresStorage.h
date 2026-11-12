//
// Created by Velin Poznakov on 11/12/2026.
//

#ifndef COURSEPROJECT_POSTGRESSTORAGE_H
#define COURSEPROJECT_POSTGRESSTORAGE_H

#include "../ParkingSpot/ParkingSpot.h"
#include "../Ticket/Ticket.h"
#include "../Vehicle/Vehicle.h"
#include <libpq-fe.h>
#include <ctime>
#include <memory>
#include <string>
#include <vector>

// one row of a query result; every value comes as text, NULL comes as ""
using Row = std::vector<std::string>;

struct RevenueRow {
    std::string vehicleType;
    int visits;
    double total;
};

// Saves and loads all parking data in a PostgreSQL database with libpq, PostgreSQL's C library.
class PostgresStorage {
    PGconn *connection;

    // Runs one SQL command. The values in params replace $1, $2, ... in the SQL. They are sent
    // separately from the SQL text, so user input can never change the command (no SQL injection).
    std::vector<Row> query(const std::string &sql, const std::vector<std::string> &params = {});
    void createTables();

public:
    explicit PostgresStorage(const std::string &connectionSettings); // connects to the database
    ~PostgresStorage();                                               // closes the connection

    // one object = one connection, so the object must not be copied
    PostgresStorage(const PostgresStorage &other) = delete;
    PostgresStorage &operator=(const PostgresStorage &other) = delete;

    std::vector<ParkingSpot> loadSpots();
    void addSpot(int number, SpotSize size);

    std::unique_ptr<Vehicle> loadVehicle(const std::string &licensePlate); // nullptr if it was never here

    int openTicket(const Vehicle &vehicle, int spotNumber, std::time_t entryTime); // returns the ticket id
    void closeTicket(const Ticket &ticket);

    std::vector<Ticket> loadOpenTickets();
    std::vector<Ticket> loadHistory(int count);
    std::vector<RevenueRow> loadRevenue();
};


#endif //COURSEPROJECT_POSTGRESSTORAGE_H
