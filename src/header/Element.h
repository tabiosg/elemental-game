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

  // REQUIRES resource is a valid element
  // EFFECTS Returns true if other resource element strengthens
  // or harms current element. False otherwise.
  bool isSpecialResource(const Element &resource) const;

  // REQUIRES resource either strengthens or harms current element
  // EFFECTS Returns true if other resource element strengthens current element. False if harms.
  bool isStrengthening(const Element &resource) const;

  // REQUIRES defender is a valid element
  // EFFECTS Returns true if current element is extremely effective or
  // extremely ineffective against defender element. False otherwise.
  bool isSpecialStrength(const Element &defender) const;

  // REQUIRES current element is extremely effective or extremely ineffective against defender element.
  // EFFECTS Returns true if current element is extremely effective
  // against defender element. False otherwise.
  bool isEffectiveStrength(const Element &defender) const;

private:
  std::string element;
  std::string bestHealingElement;  // element that current element would like to receive healing from
  std::string bestOpponentElement; // element that current element would like to have as opponent
};

// EFFECTS Returns the element that current element would like to receive healing from
std::string findBestHealingElement(const std::string &element);

// EFFECTS Returns the element that current element would like to fight as opponent
std::string findBestOpponentElement(const std::string &element);

// EFFECTS Returns true if lhs is same as rhs
bool operator==(const Element &lhs, const Element &rhs);

// EFFECTS Returns true if lhs is not same as rhs.
bool operator!=(const Element &lhs, const Element &rhs);

// EFFECTS Prints Element to stream, for example "Water"
std::ostream &operator<<(std::ostream &os, const Element &element);

#endif
