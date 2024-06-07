#include "VoxMap.h"
#include "Errors.h"

#include <fstream>
#include <iostream>

int main()
{
    std::string filepath = "data/bouncy-castle.vox";
    std::ifstream stream(filepath);
    if (stream.fail())
    {
        std::cerr << "ERROR: Could not open file: " << filepath << '\n';
        return 1;
    }

    VoxMap map(stream);
    stream.close();

    // Point src(7, 5, 2);
    // Point dst(8, 5, 1);

    Point src(6, 6, 2);
    Point dst(0, 5, 1);

    std::cout << "src: (" << src.x << "," << src.y << "," << src.z << ")\n";
    std::cout << "dst: (" << dst.x << "," << dst.y << "," << dst.z << ")\n\n";
    try
    {
        Route route = map.route(src, dst);
        std::cout << route << '\n';
    }
    catch (const InvalidPoint &err)
    {
        std::cout << "Invalid point: " << err.point() << '\n';
    }
    catch (const NoRoute &err)
    {
        std::cout << "No route from " << err.src() << " to " << err.dst() << ".\n";
    }

    return 0;
}
