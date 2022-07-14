#include <cassert>
#include <iostream>
#include <string>

#include "Element.h"

// EFFECTS Initializes Element to Water
Element::Element()
{
    changeElement(WATER);
}

// REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
// EFFECTS Initializes Element to specified element.
Element::Element(const std::string &elementChange) : Element()
{
    changeElement(elementChange);
}

// EFFECTS Returns the element
std::string Element::getElement() const
{
    return element;
}

// EFFECTS Returns the best healing element
std::string Element::getBestHealingElement() const
{
    return healsThisElementBest;
}

// EFFECTS Returns the best opponent element
std::string Element::getBestOpponentElement() const
{
    return beatsThisElementBest;
}

// REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
// EFFECTS Changes element type to specified element.
void Element::changeElement(const std::string &elementChange)
{
    assert(
        elementChange == WATER || elementChange == WOOD ||
        elementChange == FIRE || elementChange == EARTH ||
        elementChange == METAL);
    element = elementChange;
    healsThisElementBest = findElementThatThisBenefits(elementChange);
    beatsThisElementBest = findElementThatThisBeats(elementChange);
    isWeakAgainstThisElement = findElementThatThisIsWeakAgainst(elementChange);
}

// REQUIRES resource is valid element
// EFFECTS Returns true if current element benefits other element. False if not.
bool Element::isBeneficialResourceTo(const Element &resource) const
{
    return resource == healsThisElementBest;
}

// EFFECTS Returns true if current element is extremely effective
// against defender element. False otherwise.
bool Element::isEffectiveAgainst(const Element &defender) const
{
    return defender == beatsThisElementBest;
}

// EFFECTS Returns true if current element is extremely weak
// against attacker element. False otherwise.
bool Element::isWeakAgainst(const Element &attacker) const
{
    return attacker == isWeakAgainstThisElement;
}

// EFFECTS Returns the element that the current one benefits
std::string findElementThatThisBenefits(const std::string &element)
{
    if (element == Element::METAL)
    {
        return Element::WATER;
    }
    else if (element == Element::EARTH)
    {
        return Element::METAL;
    }
    else if (element == Element::FIRE)
    {
        return Element::EARTH;
    }
    else if (element == Element::WOOD)
    {
        return Element::FIRE;
    }
    else if (element == Element::WATER)
    {
        return Element::WOOD;
    }
    else
    {
        assert(false);
    }
}

// EFFECTS Returns the element that current element would like to fight as opponent
std::string findElementThatThisBeats(const std::string &element)
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

// EFFECTS Returns the element that current element is weak against
std::string findElementThatThisIsWeakAgainst(const std::string &element)
{
    if (element == Element::FIRE)
    {
        return Element::WATER;
    }
    else if (element == Element::WOOD)
    {
        return Element::METAL;
    }
    else if (element == Element::WATER)
    {
        return Element::EARTH;
    }
    else if (element == Element::METAL)
    {
        return Element::FIRE;
    }
    else if (element == Element::EARTH)
    {
        return Element::WOOD;
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
