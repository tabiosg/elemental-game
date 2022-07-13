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
  static constexpr const char *const ELE_WATER = "Water";
  static constexpr const char *const ELE_WOOD = "Wood";
  static constexpr const char *const ELE_FIRE = "Fire";
  static constexpr const char *const ELE_EARTH = "Earth";
  static constexpr const char *const ELE_METAL = "Metal";

  // EFFECTS Initializes Element to Water
  Element();

  // REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
  // EFFECTS Initializes Element to specified element.
  Element(const std::string &element);

  // EFFECTS Returns the element
  std::string get_element() const;

  // EFFECTS Returns the best healing element
  std::string get_best_healing_element() const;

  // EFFECTS Returns the best opponent element
  std::string get_best_opponent_element() const;

  // REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
  // EFFECTS Changes element type to specified element.
  void change_element(const std::string &element);

  // REQUIRES resource is a valid element
  // EFFECTS Returns true if other resource element strengthens
  // or harms current element. False otherwise.
  bool is_special_resource(const Element &resource) const;

  // REQUIRES resource either strengthens or harms current element
  // EFFECTS Returns true if other resource element strengthens current element. False if harms.
  bool is_strengthening(const Element &resource) const;

  // REQUIRES defender is a valid element
  // EFFECTS Returns true if current element is extremely effective or
  // extremely ineffective against defender element. False otherwise.
  bool is_special_strength(const Element &defender) const;

  // REQUIRES current element is extremely effective or extremely ineffective against defender element.
  // EFFECTS Returns true if current element is extremely effective
  // against defender element. False otherwise.
  bool is_effective_strength(const Element &defender) const;

private:
  std::string element;
  std::string best_healing_element;  // element that current element would like to receive healing from
  std::string best_opponent_element; // element that current element would like to have as opponent
};

// EFFECTS Returns the element that current element would like to receive healing from
std::string find_best_healing_element(const std::string &element);

// EFFECTS Returns the element that current element would like to fight as opponent
std::string find_best_opponent_element(const std::string &element);

// EFFECTS Returns true if lhs is same as rhs
bool operator==(const Element &lhs, const Element &rhs);

// EFFECTS Returns true if lhs is not same as rhs.
bool operator!=(const Element &lhs, const Element &rhs);

// EFFECTS Prints Element to stream, for example "Water"
std::ostream &operator<<(std::ostream &os, const Element &element);

#endif
