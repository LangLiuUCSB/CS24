#include "VoxMap.h"
#include "Errors.h"

#include <fstream>
#include <iostream>
#include <bitset>

int main()
{
    std::string filepath = "data/tower-block.vox";
    std::ifstream stream(filepath);
    if (stream.fail())
    {
        std::cerr << "ERROR: Could not open file: " << filepath << '\n';
        return 1;
    }

    VoxMap map(stream);
    stream.close();

    Point src(7, 29, 36), dst(67, 42, 15);
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

    std::cout << 21 << " in bitset is " << std::bitset<8>(21) << "\n";

    return 0;
}
