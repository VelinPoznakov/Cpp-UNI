#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Car/Car.h"
#include "Truck/Truck.h"
#include "Movie/Movie.h"
#include "Game/Game.h"
#include "Music/Music.h"

int main()
{
    std::cout << "--- Task 1: Vehicle, Car and Truck ---\n";

    Car c(5, 4, 500);
    Truck t(30000, 12, 1200);

    std::cout << "Car:\n";
    c.show();
    std::cout << "\nTruck:\n";
    t.show();

    // getRange() is not written in Car - it is inherited from Vehicle
    std::cout << "\nThe truck can go " << t.getRange() - c.getRange() << " km further than the car\n";

    try {
        Car broken(5, 0, 500);
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }


    std::cout << "\n--- Additional Task: Media Collection Tool ---\n";

    Movie inception("Inception", 19.99, 1, "DVD", "12.03.2024", 8.8);
    Movie matrix("The Matrix", 7.50, 2, "Video", "05.11.2001", 8.7);
    Game zelda("The Legend of Zelda", 59.90, 3, "CD", "20.06.2023", 7, "Nintendo Switch");
    Music queen("A Night at the Opera", 14.99, 4, "01.02.2020", "Queen");

    std::cout << inception.toString() << '\n';
    std::cout << matrix.toString() << '\n';
    std::cout << zelda.toString() << '\n';
    std::cout << queen.toString() << '\n';

    std::cout << "\nItems in the collection: " << Item::getNumberOfItems() << '\n';

    // A Movie, a Game and a Music are all Items, so they can be pointed to by an Item*
    const Item *collection[] = {&inception, &matrix, &zelda, &queen};
    double total = 0;

    std::cout << std::fixed << std::setprecision(2);
    for (const Item *item : collection) {
        std::cout << '#' << item->getItemId() << ' ' << item->getContentType() << " (" << item->getMediaFormat()
                  << "): " << item->getTitle() << " - " << item->getPrice() << '\n';
        total += item->getPrice();
    }
    std::cout << "Total value: " << total << '\n';
    std::cout.unsetf(std::ios::fixed);

    std::cout << '\n';
    inception.playOnDVD();
    matrix.playOnVideo();
    zelda.playOnCD();
    queen.playOnCD();

    try {
        inception.playOnVideo();
    } catch (const std::logic_error& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    std::cout << '\n' << inception.getTitle() << " has rating " << inception.getRating() << '\n';
    std::cout << zelda.getTitle() << " has difficulty " << zelda.getDifficultyLevel()
              << " and runs on " << zelda.getEquipment() << '\n';
    std::cout << queen.getTitle() << " is by " << queen.getBandOrArtist() << '\n';

    std::cout << "\nChanging the ID of \"" << queen.getTitle() << "\" to 10\n";
    queen.setItemId(10);
    std::cout << queen.getTitle() << " now has ID " << queen.getItemId() << '\n';

    try {
        matrix.setItemId(1);
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    // Item's constructor runs first, so the Movie part fails only after the Item part is built.
    // ~Item() still runs and the number of items doesn't change.
    try {
        Movie wrong("Avatar", 12.00, 5, "CD", "18.12.2009", 7.9);
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    try {
        Game hard("Dark Souls", 39.99, 6, "Video", "22.09.2011", 15, "Sony PlayStation");
    } catch (const std::invalid_argument& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    std::cout << "Items in the collection: " << Item::getNumberOfItems() << '\n';

    {
        Music temporary("Thriller", 9.99, 5, "30.11.1982", "Michael Jackson");
        std::cout << "\nInside the block: " << temporary.toString() << '\n';
        std::cout << "Items in the collection: " << Item::getNumberOfItems() << '\n';
    }
    std::cout << "After the block (destructor called): " << Item::getNumberOfItems() << '\n';

    return 0;
}
