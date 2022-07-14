#include <cassert>
#include <iostream>
#include <string>

#include "header/Element.h"

// EFFECTS Initializes Element to Water
Element::Element() : element(WATER),
                     bestHealingElement(METAL),
                     bestOpponentElement(EARTH) {}

// REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
// EFFECTS Initializes Element to specified element.
Element::Element(const std::string &element_change) : Element()
{
    assert(element_change == "Water" || element_change == "Wood" || element_change == "Fire" || element_change == "Earth" || element_change == "Metal");
    element = element_change;
    bestHealingElement = findBestHealingElement(element_change);
    bestOpponentElement = findBestOpponentElement(element_change);
}

// EFFECTS Returns the element
std::string Element::getElement() const
{
    return element;
}

// EFFECTS Returns the best healing element
std::string Element::getBestHealingElement() const
{
    return bestHealingElement;
}

// EFFECTS Returns the best opponent element
std::string Element::getBestOpponentElement() const
{
    return bestOpponentElement;
}

// REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
// EFFECTS Changes element type to specified element.
void Element::change_element(const std::string &element_change)
{
    element = element_change;
    bestHealingElement = findBestHealingElement(element_change);
    bestOpponentElement = findBestOpponentElement(element_change);
}

// REQUIRES resource is a valid element
// EFFECTS Returns true if other resource element strengthens
// or harms current element. False otherwise.
bool Element::isSpecialResource(const Element &resource) const
{
    bool strengthener = resource == bestHealingElement;
    std::string resource_element = resource.getElement();
    bool harmer = element == findBestHealingElement(resource_element);
    return strengthener || harmer;
}

// REQUIRES resource either strengthens or harms current element
// EFFECTS Returns true if other resource element strengthens current element. False if harms.
bool Element::isStrengthening(const Element &resource) const
{
    return resource == bestHealingElement;
}

// REQUIRES defender is a valid element
// EFFECTS Returns true if current element is extremely effective or
// extremely ineffective against defender element. False otherwise.
bool Element::isSpecialStrength(const Element &defender) const
{
    bool effective = defender == bestOpponentElement;
    std::string defender_element = defender.getElement();
    bool harmer = element == findBestOpponentElement(defender_element);
    return effective || harmer;
}

// REQUIRES current element is extremely effective or extremely ineffective against defender element.
// EFFECTS Returns true if current element is extremely effective
// against defender element. False otherwise.
bool Element::is_effective_strength(const Element &defender) const
{
    return defender == bestOpponentElement;
}

// EFFECTS Returns the element that current element would like to receive healing from
std::string findBestHealingElement(const std::string &element)
{
    if (element == Element::WATER)
    {
        return Element::METAL;
    }
    else if (element == Element::METAL)
    {
        return Element::EARTH;
    }
    else if (element == Element::EARTH)
    {
        return Element::FIRE;
    }
    else if (element == Element::FIRE)
    {
        return Element::WOOD;
    }
    else if (element == Element::WOOD)
    {
        return Element::WATER;
    }
    else
    {
        assert(false);
    }
}

// EFFECTS Returns the element that current element would like to fight as opponent
std::string findBestOpponentElement(const std::string &element)
{
    if (element == Element::WATER)
    {
        return Element::FIRE;
    }
    else if (element == Element::METAL)
    {
        return Element::WOOD;
    }
    else if (element == Element::EARTH)
    {
        return Element::WATER;
    }
    else if (element == Element::FIRE)
    {
        return Element::METAL;
    }
    else if (element == Element::WOOD)
    {
        return Element::EARTH;
    }
    else
    {
        assert(false);
    }
}

// EFFECTS Returns true if lhs is same as rhs
bool operator==(const Element &lhs, const Element &rhs)
{
    bool sameElement = lhs.getElement() == rhs.getElement();
    bool sameBestHealer = lhs.getBestHealingElement() == rhs.getBestHealingElement();
    bool sameBestOpponent = lhs.getBestOpponentElement() == rhs.getBestOpponentElement();
    return sameElement && sameBestHealer && sameBestOpponent;
}

// EFFECTS Returns true if lhs is not same as rhs.
bool operator!=(const Element &lhs, const Element &rhs)
{
    return !(lhs == rhs);
}

// EFFECTS Prints Element to stream, for example "Water"
std::ostream &operator<<(std::ostream &os, const Element &element)
{
    os << element.getElement();
    return os;
}
