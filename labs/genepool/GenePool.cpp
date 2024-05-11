#include "GenePool.h"

#include <sstream>
#include <iostream>

// GenePool Member Functions
GenePool::GenePool(std::istream &stream)
{
    std::string line;
    size_t i = 0;
    while (std::getline(stream, line))
    {
        std::istringstream stringstream(line);
        std::string currName;
        if (stringstream >> currName && currName != "#")
        {
            std::string currString;
            stringstream >> currString;
            while (currString != "male" && currString != "female")
            {
                currName += " " + currString;
                stringstream >> currString;
            }
            Gender currGender = (currString == "male") ? Gender::MALE : Gender::FEMALE;
            stringstream >> currString;
            Person *currFather = (currString == "???") ? nullptr : find(currString);
            stringstream >> currString;
            Person *currMother = (currString == "???") ? nullptr : find(currString);
            everyoneSet.insert(new Person(currName, currGender, currFather, currMother));
        }
    }
}
GenePool::~GenePool()
{
    for (Person *p : everyoneSet)
    {
        delete p;
    }
    // everyoneSet.clear();
}
std::set<Person *> GenePool::everyone() const { return everyoneSet; }
Person *GenePool::find(const std::string &name) const
{
    for (Person *p : everyoneSet)
    {
        if (p->name() == name)
        {
            return p;
        }
    }
    return nullptr;
}