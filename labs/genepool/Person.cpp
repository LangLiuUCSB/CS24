#include "Person.h"

#include <iostream>

// Person Member Functions
// Constructor
Person::Person(const std::string &n, const Gender &g, Person *f, Person *m)
    : personName(n), personGender(g), fatherPtr(f), motherPtr(m) {}

// Required Getter Functions
const std::string &Person::name() const { return personName; }
Gender Person::gender() const { return personGender; }
Person *Person::father() { return fatherPtr; }
Person *Person::mother() { return motherPtr; }

// Required Relationship Functions
std::set<Person *> Person::ancestors(PMod pmod)
{
    std::set<Person *> ancestorsSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr)
    {
        ancestorsSet.insert(fatherPtr);
        std::set<Person *> fatherAncestorsSet = fatherPtr->ancestors();
        ancestorsSet.insert(fatherAncestorsSet.begin(), fatherAncestorsSet.end());
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr)
    {
        ancestorsSet.insert(motherPtr);
        std::set<Person *> motherAncestorsSet = motherPtr->ancestors();
        ancestorsSet.insert(motherAncestorsSet.begin(), motherAncestorsSet.end());
    }
    return ancestorsSet;
}
std::set<Person *> Person::grandparents(PMod pmod)
{
    std::set<Person *> grandparentsSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr)
    {
        std::set<Person *> fatherParentsSet = fatherPtr->parents();
        grandparentsSet.insert(fatherParentsSet.begin(), fatherParentsSet.end());
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr)
    {
        std::set<Person *> motherParentsSet = motherPtr->parents();
        grandparentsSet.insert(motherParentsSet.begin(), motherParentsSet.end());
    }
    return grandparentsSet;
}
std::set<Person *> Person::grandfathers(PMod pmod)
{
    std::set<Person *> grandfathersSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr && fatherPtr->father() != nullptr)
    {
        grandfathersSet.insert(fatherPtr->father());
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr && motherPtr->father() != nullptr)
    {
        grandfathersSet.insert(motherPtr->father());
    }
    return grandfathersSet;
}
std::set<Person *> Person::grandmothers(PMod pmod)
{
    std::set<Person *> grandmothersSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr && fatherPtr->mother() != nullptr)
    {
        grandmothersSet.insert(fatherPtr->mother());
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr && motherPtr->mother() != nullptr)
    {
        grandmothersSet.insert(motherPtr->mother());
    }
    return grandmothersSet;
}
std::set<Person *> Person::parents(PMod pmod)
{
    std::set<Person *> parentsSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr)
    {
        parentsSet.insert(fatherPtr);
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr)
    {
        parentsSet.insert(motherPtr);
    }
    return parentsSet;
}
std::set<Person *> Person::uncles(PMod pmod, SMod smod)
{
    std::set<Person *> unclesSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr)
    {
        std::set<Person *> fatherBrothersSet = fatherPtr->brothers(PMod::ANY, smod);
        unclesSet.insert(fatherBrothersSet.begin(), fatherBrothersSet.end());
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr)
    {
        std::set<Person *> motherBrothersSet = motherPtr->brothers(PMod::ANY, smod);
        unclesSet.insert(motherBrothersSet.begin(), motherBrothersSet.end());
    }
    return unclesSet;
}
std::set<Person *> Person::aunts(PMod pmod, SMod smod)
{
    std::set<Person *> auntsSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr)
    {
        std::set<Person *> fatherSistersSet = fatherPtr->sisters(PMod::ANY, smod);
        auntsSet.insert(fatherSistersSet.begin(), fatherSistersSet.end());
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr)
    {
        std::set<Person *> motherSistersSet = motherPtr->sisters(PMod::ANY, smod);
        auntsSet.insert(motherSistersSet.begin(), motherSistersSet.end());
    }
    return auntsSet;
}
std::set<Person *> Person::siblings(PMod pmod, SMod smod)
{
    std::set<Person *> siblingsSet;
    if (smod == SMod::FULL)
    {
        std::set<Person *> motherChildrenSet = motherPtr->children();
        for (Person *childPtr : motherChildrenSet)
        {
            if (fatherPtr != nullptr && childPtr->father() == fatherPtr)
            {
                siblingsSet.insert(childPtr);
            }
        }
        siblingsSet.erase(this);
    }
    else
    {
        if (pmod != PMod::PATERNAL && fatherPtr != nullptr)
        {
            std::set<Person *> fatherChildrenSet = fatherPtr->children();
            if (smod == SMod::HALF)
            {
                for (Person *childPtr : fatherChildrenSet)
                {
                    if (childPtr->mother() != motherPtr)
                    {
                        siblingsSet.insert(childPtr);
                    }
                }
            }
            else
            {
                siblingsSet.insert(fatherChildrenSet.begin(), fatherChildrenSet.end());
                siblingsSet.erase(this);
            }
        }
        if (pmod != PMod::MATERNAL && motherPtr != nullptr)
        {
            std::set<Person *> motherChildrenSet = motherPtr->children();
            if (smod == SMod::HALF)
            {
                for (Person *childPtr : motherChildrenSet)
                {
                    if (childPtr->father() != fatherPtr)
                    {
                        siblingsSet.insert(childPtr);
                    }
                }
            }
            else
            {
                siblingsSet.insert(motherChildrenSet.begin(), motherChildrenSet.end());
                siblingsSet.erase(this);
            }
        }
    }
    return siblingsSet;
}
std::set<Person *> Person::brothers(PMod pmod, SMod smod)
{
    std::set<Person *> brothersSet = siblings(pmod, smod);
    for (Person *childPtr : brothersSet)
    {
        if (childPtr->gender() != Gender::MALE)
        {
            brothersSet.erase(childPtr);
        }
    }
    return brothersSet;
}
std::set<Person *> Person::sisters(PMod pmod, SMod smod)
{
    std::set<Person *> sistersSet = siblings(pmod, smod);
    for (Person *childPtr : sistersSet)
    {
        if (childPtr->gender() != Gender::FEMALE)
        {
            sistersSet.erase(childPtr);
        }
    }
    return sistersSet;
}
std::set<Person *> Person::cousins(PMod pmod, SMod smod)
{
    std::set<Person *> cousinsSet;
    if (pmod != PMod::PATERNAL && fatherPtr != nullptr)
    {
        std::set<Person *> fatherSiblingSet = fatherPtr->siblings(PMod::ANY, smod);
        for (Person *sibling : fatherSiblingSet)
        {
            std::set<Person *> fatherSiblingChildrenSet = sibling->children();
            cousinsSet.insert(fatherSiblingChildrenSet.begin(), fatherSiblingChildrenSet.end());
        }
    }
    if (pmod != PMod::MATERNAL && motherPtr != nullptr)
    {
        std::set<Person *> motherSiblingSet = motherPtr->siblings(PMod::ANY, smod);
        for (Person *sibling : motherSiblingSet)
        {
            std::set<Person *> motherSiblingChildrenSet = sibling->children();
            cousinsSet.insert(motherSiblingChildrenSet.begin(), motherSiblingChildrenSet.end());
        }
    }
    return cousinsSet;
}
std::set<Person *> Person::descendants()
{
    std::set<Person *> descendantsSet;
    for (Person *childPtr : childrenSet)
    {
        descendantsSet.insert(childPtr);
        std::set<Person *> childDescendantsSet = childPtr->descendants();
        descendantsSet.insert(childDescendantsSet.begin(), childDescendantsSet.end());
    }
    return descendantsSet;
}
std::set<Person *> Person::children() { return childrenSet; }
std::set<Person *> Person::sons()
{
    std::set<Person *> sonsSet;
    for (Person *childPtr : childrenSet)
    {
        if (childPtr->gender() == Gender::MALE)
        {
            sonsSet.insert(childPtr);
        }
    }
    return sonsSet;
}
std::set<Person *> Person::daughters()
{
    std::set<Person *> daughtersSet;
    for (Person *childPtr : childrenSet)
    {
        if (childPtr->gender() == Gender::FEMALE)
        {
            daughtersSet.insert(childPtr);
        }
    }
    return daughtersSet;
}
std::set<Person *> Person::nephews(PMod pmod, SMod smod)
{
    std::set<Person *> nephewsSet;
    std::set<Person *> siblingsSet = siblings(pmod, smod);
    for (Person *sibling : siblingsSet)
    {
        std::set<Person *> siblingSonsSet = sibling->sons();
        nephewsSet.insert(siblingSonsSet.begin(), siblingSonsSet.end());
    }
    return nephewsSet;
}
std::set<Person *> Person::nieces(PMod pmod, SMod smod)
{
    std::set<Person *> niecesSet;
    std::set<Person *> siblingsSet = siblings(pmod, smod);
    for (Person *sibling : siblingsSet)
    {
        std::set<Person *> siblingDaughtersSet = sibling->daughters();
        niecesSet.insert(siblingDaughtersSet.begin(), siblingDaughtersSet.end());
    }
    return niecesSet;
}
std::set<Person *> Person::grandchildren()
{
    std::set<Person *> grandchildrenSet;
    for (Person *childPtr : childrenSet)
    {
        std::set<Person *> childChildrenSet = childPtr->children();
        grandchildrenSet.insert(childChildrenSet.begin(), childChildrenSet.end());
    }
    return grandchildrenSet;
}
std::set<Person *> Person::grandsons()
{
    std::set<Person *> grandsonsSet;
    for (Person *childPtr : childrenSet)
    {
        std::set<Person *> childSonsSet = childPtr->sons();
        grandsonsSet.insert(childSonsSet.begin(), childSonsSet.end());
    }
    return grandsonsSet;
}
std::set<Person *> Person::granddaughters()
{
    std::set<Person *> granddaughtersSet;
    for (Person *childPtr : childrenSet)
    {
        std::set<Person *> childDaughtersSet = childPtr->daughters();
        granddaughtersSet.insert(childDaughtersSet.begin(), childDaughtersSet.end());
    }
    return granddaughtersSet;
}

// Other Member Functions
void Person::addChild(Person *c)
{
    childrenSet.insert(c);
}
