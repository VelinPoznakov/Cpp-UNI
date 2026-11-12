//
// Created by Velin Poznakov on 11/12/2026.
//

#include "PostgresStorage.h"
#include "../VehicleFactory/VehicleFactory.h"
#include <stdexcept>

// the columns readTicket() expects, in this order; times are read as Unix seconds
static const std::string SELECT_TICKETS =
    "SELECT t.id, t.plate, v.type, v.owner_name, t.spot_number, "
    "EXTRACT(EPOCH FROM t.entry_time)::BIGINT, EXTRACT(EPOCH FROM t.exit_time)::BIGINT, t.fee "
    "FROM tickets t JOIN vehicles v ON v.plate = t.plate ";

static Ticket readTicket(const Row &row) {
    Ticket ticket(std::stoi(row[0]), row[1], row[2], row[3], std::stoi(row[4]), std::stoll(row[5]));

    if (!row[6].empty()) // exit_time is NULL while the vehicle is still inside
        ticket.close(std::stoll(row[6]), std::stod(row[7]));

    return ticket;
}

PostgresStorage::PostgresStorage(const std::string &connectionSettings) {
    connection = PQconnectdb(connectionSettings.c_str());

    if (PQstatus(connection) != CONNECTION_OK) {
        std::string message = PQerrorMessage(connection);
        PQfinish(connection);
        throw std::runtime_error("Cannot connect to PostgreSQL: " + message);
    }

    query("SET client_min_messages TO WARNING"); // hide notices like "table already exists"
    createTables();
}

PostgresStorage::~PostgresStorage() {
    PQfinish(connection);
}

std::vector<Row> PostgresStorage::query(const std::string &sql, const std::vector<std::string> &params) {
    std::vector<const char *> values;
    for (const std::string &param : params)
        values.push_back(param.c_str());

    PGresult *result = PQexecParams(connection, sql.c_str(), static_cast<int>(values.size()),
                                    nullptr, values.data(), nullptr, nullptr, 0);

    ExecStatusType status = PQresultStatus(result);
    if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK) {
        std::string message = PQerrorMessage(connection);
        PQclear(result);
        throw std::runtime_error("Database error: " + message);
    }

    // copy the answer into normal C++ strings, then free the libpq result
    std::vector<Row> rows;
    for (int i = 0; i < PQntuples(result); i++) {
        Row row;
        for (int j = 0; j < PQnfields(result); j++)
            row.push_back(PQgetvalue(result, i, j));
        rows.push_back(row);
    }

    PQclear(result);
    return rows;
}

void PostgresStorage::createTables() {
    query(R"SQL(
        CREATE TABLE IF NOT EXISTS spots (
            number INTEGER PRIMARY KEY CHECK (number > 0),
            size   VARCHAR(10) NOT NULL CHECK (size IN ('SMALL', 'MEDIUM', 'LARGE'))
        )
    )SQL");

    query(R"SQL(
        CREATE TABLE IF NOT EXISTS vehicles (
            plate      VARCHAR(10) PRIMARY KEY,
            type       VARCHAR(20) NOT NULL CHECK (type IN ('Car', 'Motorcycle', 'Truck')),
            owner_name VARCHAR(100) NOT NULL
        )
    )SQL");

    query(R"SQL(
        CREATE TABLE IF NOT EXISTS tickets (
            id          INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
            plate       VARCHAR(10) NOT NULL REFERENCES vehicles (plate),
            spot_number INTEGER NOT NULL REFERENCES spots (number),
            entry_time  TIMESTAMPTZ NOT NULL,
            exit_time   TIMESTAMPTZ,
            fee         NUMERIC(10, 2) CHECK (fee >= 0),
            CHECK (exit_time IS NULL OR exit_time >= entry_time)
        )
    )SQL");

    // the database itself refuses a vehicle that is inside twice or two vehicles on one spot
    query("CREATE UNIQUE INDEX IF NOT EXISTS one_open_ticket_per_vehicle ON tickets (plate) WHERE exit_time IS NULL");
    query("CREATE UNIQUE INDEX IF NOT EXISTS one_open_ticket_per_spot ON tickets (spot_number) WHERE exit_time IS NULL");
}

std::vector<ParkingSpot> PostgresStorage::loadSpots() {
    std::vector<ParkingSpot> spots;
    for (const Row &row : query("SELECT number, size FROM spots ORDER BY number"))
        spots.emplace_back(std::stoi(row[0]), sizeFromName(row[1]));

    return spots;
}

void PostgresStorage::addSpot(int number, SpotSize size) {
    query("INSERT INTO spots (number, size) VALUES ($1, $2)", {std::to_string(number), sizeName(size)});
}

std::unique_ptr<Vehicle> PostgresStorage::loadVehicle(const std::string &licensePlate) {
    std::vector<Row> rows = query("SELECT type, owner_name FROM vehicles WHERE plate = $1", {licensePlate});
    if (rows.empty())
        return nullptr;

    return VehicleFactory::create(rows[0][0], licensePlate, rows[0][1]);
}

int PostgresStorage::openTicket(const Vehicle &vehicle, int spotNumber, std::time_t entryTime) {
    // a new vehicle is added, a returning one gets its details updated
    query("INSERT INTO vehicles (plate, type, owner_name) VALUES ($1, $2, $3) "
          "ON CONFLICT (plate) DO UPDATE SET type = EXCLUDED.type, owner_name = EXCLUDED.owner_name",
          {vehicle.getLicensePlate(), vehicle.getType(), vehicle.getOwnerName()});

    std::vector<Row> rows = query(
        "INSERT INTO tickets (plate, spot_number, entry_time) VALUES ($1, $2, to_timestamp($3)) RETURNING id",
        {vehicle.getLicensePlate(), std::to_string(spotNumber), std::to_string(entryTime)});

    return std::stoi(rows[0][0]);
}

void PostgresStorage::closeTicket(const Ticket &ticket) {
    query("UPDATE tickets SET exit_time = to_timestamp($2), fee = $3 WHERE id = $1",
          {std::to_string(ticket.getId()), std::to_string(ticket.getExitTime()), std::to_string(ticket.getFee())});
}

std::vector<Ticket> PostgresStorage::loadOpenTickets() {
    std::vector<Ticket> tickets;
    for (const Row &row : query(SELECT_TICKETS + "WHERE t.exit_time IS NULL ORDER BY t.entry_time"))
        tickets.push_back(readTicket(row));

    return tickets;
}

std::vector<Ticket> PostgresStorage::loadHistory(int count) {
    std::vector<Ticket> tickets;
    for (const Row &row : query(SELECT_TICKETS + "WHERE t.exit_time IS NOT NULL ORDER BY t.exit_time DESC LIMIT $1",
                                {std::to_string(count)}))
        tickets.push_back(readTicket(row));

    return tickets;
}

std::vector<RevenueRow> PostgresStorage::loadRevenue() {
    std::vector<RevenueRow> revenue;
    for (const Row &row : query("SELECT v.type, COUNT(*), SUM(t.fee) FROM tickets t "
                                "JOIN vehicles v ON v.plate = t.plate "
                                "WHERE t.exit_time IS NOT NULL GROUP BY v.type ORDER BY SUM(t.fee) DESC"))
        revenue.push_back({row[0], std::stoi(row[1]), std::stod(row[2])});

    return revenue;
}
