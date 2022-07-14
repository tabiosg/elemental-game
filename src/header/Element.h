#ifndef ELEMENT_H
#define ELEMENT_H
/* Element.h
 *
 * Elements
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */

#include <iostream>
#include <string>

class Element
{
public:
  // element names
  static constexpr const char *const WATER = "Water";
  static constexpr const char *const WOOD = "Wood";
  static constexpr const char *const FIRE = "Fire";
  static constexpr const char *const EARTH = "Earth";
  static constexpr const char *const METAL = "Metal";

  // EFFECTS Initializes Element to Water
  Element();

  // REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
  // EFFECTS Initializes Element to specified element.
  Element(const std::string &element);

  // EFFECTS Returns the element
  std::string getElement() const;

  // EFFECTS Returns the best healing element
  std::string getBestHealingElement() const;

  // EFFECTS Returns the best opponent element
  std::string getBestOpponentElement() const;

  // REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
  // EFFECTS Changes element type to specified element.
  void changeElement(const std::string &element);

  // REQUIRES resource is valid element
  // EFFECTS Returns true if current element benefits other element. False if not.
  bool isBeneficialResourceTo(const Element &resource) const;

  // EFFECTS Returns true if current element is extremely effective
  // against defender element. False otherwise.
  bool isEffectiveAgainst(const Element &defender) const;

  // EFFECTS Returns true if current element is extremely weak
  // against attacker element. False otherwise.
  bool isWeakAgainst(const Element &attacker) const;

private:
  std::string element;
  std::string healsThisElementBest;  // element that current element heals the best
  std::string beatsThisElementBest; // element that current element beats the best
  std::string isWeakAgainstThisElement; // element that current element is weak against
};

// EFFECTS Returns the element that the current one benefits
std::string findElementThatThisBenefits(const std::string &element);

// EFFECTS Returns the element that current element would like to fight as opponent
std::string findElementThatThisBeats(const std::string &element);

// EFFECTS Returns the element that current element is weak against
std::string findElementThatThisIsWeakAgainst(const std::string &element);

// EFFECTS Returns true if lhs is same as rhs
bool operator==(const Element &lhs, const Element &rhs);

// EFFECTS Returns true if lhs is not same as rhs.
bool operator!=(const Element &lhs, const Element &rhs);

// EFFECTS Prints Element to stream, for example "Water"
std::ostream &operator<<(std::ostream &os, const Element &element);

#endif
