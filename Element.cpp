#include <cassert>
#include <iostream>
#include <string>
#include "Element.h"

// rank and suit names -- do not remove these
constexpr const char* const Element::ELE_WATER;
constexpr const char* const Element::ELE_WOOD;
constexpr const char* const Element::ELE_FIRE;
constexpr const char* const Element::ELE_EARTH;
constexpr const char* const Element::ELE_METAL;

//EFFECTS Initializes Element to Water
Element::Element() {

}

//REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
//EFFECTS Initializes Element to specified element.
Element::Element(const std::string& element) {

}

//EFFECTS Returns the element that current element would like to receive healing from
std::string Element::get_best_healing_element() const {

}

//EFFECTS Returns the element that current element would like to fight as opponent
std::string Element::get_best_opponent_element() const {

}

//REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
//EFFECTS Changes element type to specified element.
void Element::change_element(const std::string& element) {

}

//REQUIRES resource is a valid element
//EFFECTS Returns true if other resource element strengthens 
//or harms current element. False otherwise.
bool Element::is_special_resource(const Element& resource) const {

}

//REQUIRES resource either strengthens or harms current element
//EFFECTS Returns true if other resource element strengthens current element. False if harms.
bool Element::is_strengthening(const Element& resource) const {

}

//REQUIRES defender is a valid element
//EFFECTS Returns true if current element is extremely effective or 
//extremely ineffective against defender element. False otherwise.
bool Element::is_special_strength(const Element& defender) const {

}

//REQUIRES current element is extremely effective or extremely ineffective against defender element.
//EFFECTS Returns true if current element is extremely effective
//against defender element. False otherwise.
bool Element::is_effective_strength(const Element& defender) const {

}

//EFFECTS Returns true if lhs is weak against rhs.
bool operator<(const Element& lhs, const Element& rhs) {

}

//EFFECTS Returns true if lhs is weak oe neutral against rhs.
bool operator<=(const Element& lhs, const Element& rhs) {

}

//EFFECTS Returns true if lhs is strong against rhs.
bool operator>(const Element& lhs, const Element& rhs) {

}

//EFFECTS Returns true if lhs is strong or neutral against rhs.
bool operator>=(const Element& lhs, const Element& rhs) {

}

//EFFECTS Returns true if lhs is neutral against rhs.
bool operator==(const Element& lhs, const Element& rhs) {

}

//EFFECTS Returns true if lhs is not neutral against rhs.
bool operator!=(const Element& lhs, const Element& rhs) {

}

//EFFECTS Prints Element to stream, for example "Water"
std::ostream& operator<<(std::ostream& os, const Element& element) {

}