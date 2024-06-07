#include "VoxMap.h"
#include "Errors.h"

#include <fstream>
#include <iostream>

int main()
{
    std::string filepath = "data/labrat.vox";
    std::ifstream stream(filepath);
    if (stream.fail())
    {
        std::cerr << "ERROR: Could not open file: " << filepath << '\n';
        return 1;
    }

    VoxMap map(stream);
    stream.close();

    Point src(37, 10, 1), dst(6, 38, 1);
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
