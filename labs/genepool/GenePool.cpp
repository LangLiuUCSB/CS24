#include "GenePool.h"

#include <sstream>

// GenePool Member Functions
GenePool::GenePool(std::istream &stream)
{
    std::string line;
    while (std::getline(stream, line))
    {
        if (line == "" || line[0] == '#')
        {
            continue;
        }

        std::istringstream stringstream(line);
        std::string currName;
        if (stringstream >> currName)
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
            Person *currMother = (currString == "???") ? nullptr : find(currString);
            stringstream >> currString;
            Person *currFather = (currString == "???") ? nullptr : find(currString);
            Person *currPerson = new Person(currName, currGender, currFather, currMother);
            everyoneSet.insert(currPerson);
            if (currMother != nullptr)
            {
                currMother->addChild(currPerson);
            }
            if (currFather != nullptr)
            {
                currFather->addChild(currPerson);
            }
        }
    }
}
GenePool::~GenePool()
{
    for (Person *p : everyoneSet)
    {
        delete p;
    }
    everyoneSet.clear();
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