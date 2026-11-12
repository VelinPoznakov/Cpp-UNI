cmake_minimum_required(VERSION 4.3)
project(CourseProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------- PostgreSQL client library (libpq) ----------
if (MINGW)
    # On Windows libpq comes from MSYS2. Install it once from the MSYS2 UCRT64 shell:
    #   pacman -S mingw-w64-ucrt-x86_64-postgresql
    # This works with CLion's bundled MinGW as well as with MSYS2's own compiler.
    set(LIBPQ_ROOT "C:/msys64/ucrt64" CACHE PATH "MSYS2 folder that contains libpq")

    set(LIBPQ_HEADERS libpq-fe.h postgres_ext.h pg_config_ext.h)
    # libpq.dll and the DLLs it needs; they are copied next to the .exe after every build
    set(LIBPQ_DLLS libpq.dll libssl-3-x64.dll libcrypto-3-x64.dll libintl-8.dll libiconv-2.dll)

    list(TRANSFORM LIBPQ_HEADERS PREPEND "${LIBPQ_ROOT}/include/" OUTPUT_VARIABLE LIBPQ_HEADER_PATHS)
    list(TRANSFORM LIBPQ_DLLS PREPEND "${LIBPQ_ROOT}/bin/" OUTPUT_VARIABLE LIBPQ_DLL_PATHS)

    foreach (file IN LISTS LIBPQ_HEADER_PATHS LIBPQ_DLL_PATHS ITEMS "${LIBPQ_ROOT}/lib/libpq.dll.a")
        if (NOT EXISTS "${file}")
            message(FATAL_ERROR "${file} not found.\n"
                    "Install libpq from the MSYS2 UCRT64 shell:  pacman -S mingw-w64-ucrt-x86_64-postgresql\n"
                    "If MSYS2 is not installed in C:/msys64, set LIBPQ_ROOT in the CMake options.")
        endif ()
    endforeach ()

    # Use a copy of just these three headers. The rest of ${LIBPQ_ROOT}/include belongs to the
    # MSYS2 compiler and would replace the standard headers (stdio.h, ...) of the compiler CLion uses.
    set(LIBPQ_INCLUDE_DIR "${CMAKE_BINARY_DIR}/libpq-include")
    file(COPY ${LIBPQ_HEADER_PATHS} DESTINATION "${LIBPQ_INCLUDE_DIR}")

    add_library(libpq SHARED IMPORTED)
    set_target_properties(libpq PROPERTIES
            IMPORTED_IMPLIB "${LIBPQ_ROOT}/lib/libpq.dll.a"
            IMPORTED_LOCATION "${LIBPQ_ROOT}/bin/libpq.dll"
            INTERFACE_INCLUDE_DIRECTORIES "${LIBPQ_INCLUDE_DIR}")
else ()
    # Linux / macOS, or Visual Studio with the official PostgreSQL installer
    find_package(PostgreSQL REQUIRED)
    add_library(libpq INTERFACE)
    target_link_libraries(libpq INTERFACE PostgreSQL::PostgreSQL)
endif ()

add_executable(CourseProject main.cpp
        SpotSize/SpotSize.cpp
        SpotSize/SpotSize.h
        Vehicle/Vehicle.cpp
        Vehicle/Vehicle.h
        Car/Car.cpp
        Car/Car.h
        Motorcycle/Motorcycle.cpp
        Motorcycle/Motorcycle.h
        Truck/Truck.cpp
        Truck/Truck.h
        VehicleFactory/VehicleFactory.cpp
        VehicleFactory/VehicleFactory.h
        ParkingSpot/ParkingSpot.cpp
        ParkingSpot/ParkingSpot.h
        Ticket/Ticket.cpp
        Ticket/Ticket.h
        ParkingException/ParkingException.h
        PostgresStorage/PostgresStorage.cpp
        PostgresStorage/PostgresStorage.h
        ParkingLot/ParkingLot.cpp
        ParkingLot/ParkingLot.h
        Menu/Menu.cpp
        Menu/Menu.h
)

target_link_libraries(CourseProject PRIVATE libpq)

# lets the program find db.conf no matter which folder CLion runs it from
target_compile_definitions(CourseProject PRIVATE "PROJECT_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(CourseProject PRIVATE -Wall -Wextra)
endif ()

if (MINGW)
    # The C++ runtime goes inside the .exe, and libpq's DLLs plus the compiler's thread library
    # are copied next to it, so the program starts from CLion, from a terminal or with a double-click.
    # (A fully -static link doesn't work with CLion's bundled MinGW.)
    target_link_options(CourseProject PRIVATE -static-libgcc -static-libstdc++)

    get_filename_component(COMPILER_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(RUNTIME_DLLS ${LIBPQ_DLL_PATHS})
    if (EXISTS "${COMPILER_BIN_DIR}/libwinpthread-1.dll")
        list(APPEND RUNTIME_DLLS "${COMPILER_BIN_DIR}/libwinpthread-1.dll")
    endif ()

    add_custom_command(TARGET CourseProject POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RUNTIME_DLLS} "$<TARGET_FILE_DIR:CourseProject>"
            COMMENT "Copying the PostgreSQL DLLs next to CourseProject.exe"
            VERBATIM)
endif ()
