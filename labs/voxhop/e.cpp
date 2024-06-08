#include "VoxMap.h"
#include "Errors.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

static const std::string world[] = {
    "flatland",
    "labrat",
    "pyramid",
    "stairs",
    "stairs2",
    "bouncy-castle",
    "goo-ball",
    "tower-block",
    "no-route"};

static const Point source[] = {
    Point(11, 0, 1),
    Point(37, 27, 1),
    Point(7, 7, 4),
    Point(7, 5, 6),
    Point(11, 6, 1),
    Point(7, 11, 1),
    Point(37, 44, 67),
    Point(71, 4, 22),
    Point(9, 3, 1)};

static const Point destination[] = {
    Point(0, 11, 1),
    Point(21, 35, 1),
    Point(1, 1, 1),
    Point(0, 0, 1),
    Point(0, 0, 6),
    Point(5, 5, 3),
    Point(36, 54, 19),
    Point(32, 23, 51),
    Point(7, 10, 3)};

int main()
{
    std::chrono::steady_clock::time_point start, end;
    std::chrono::duration<double> elapsed_seconds;
    for (unsigned char i = 0; i < 9; i++)
    {
        std::ifstream stream("data/" + world[i] + ".vox");
        std::cout << "\n"
                  << std::setw(15) << std::left << world[i] << source[i] << "->" << destination[i] << "\n";
        if (stream.fail())
            return 1;

        VoxMap map(stream);
        stream.close();

        Route route;
        try
        {
            start = std::chrono::steady_clock::now();
            route = map.route(source[i], destination[i]);
            end = std::chrono::steady_clock::now();
            elapsed_seconds = end - start;
            std::cout << elapsed_seconds.count() * 1000000 << " microseconds\n"
                      << route << "\n";
        }
        catch (const InvalidPoint &err)
        {
            std::cout << "Invalid point: " << err.point() << '\n';
        }
        catch (const NoRoute &err)
        {
            std::cout << "No route from " << err.src() << " to " << err.dst() << ".\n";
        }
        // map.printMap(source[i], destination[i]);
    }

    return 0;
}
