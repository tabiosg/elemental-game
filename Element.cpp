#include <cassert>
#include <iostream>
#include <string>
#include "Element.h"

class Element {
public:
   // element names
    static constexpr const char* const ELE_WATER = "Water";
    static constexpr const char* const ELE_WOOD = "Wood";
    static constexpr const char* const ELE_FIRE = "Fire";
    static constexpr const char* const ELE_EARTH = "Earth";
    static constexpr const char* const ELE_METAL = "Metal";

    //EFFECTS Initializes Element to Water
    Element() : element(ELE_WATER), 
        best_healing_element(ELE_METAL), 
        best_opponent_element(ELE_EARTH) {
    }

    //REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
    //EFFECTS Initializes Element to specified element.
    Element(const std::string& element_change) : Element() {
        assert(element_change != "Water" || element_change == "Wood"
            || element_change == "Fire" || element_change == "Earth"
            || element_change == "Metal");
        element = element_change;
        best_healing_element = find_best_healing_element(element_change);
        best_opponent_element = find_best_opponent_element(element_change);
    }

    //EFFECTS Returns the element
    std::string get_element() const {
        return element;
    }

    //EFFECTS Returns the best healing element
    std::string get_best_healing_element() const {
        return best_healing_element;
    }

    //EFFECTS Returns the best opponent element
    std::string get_best_opponent_element() const {
        return best_opponent_element;
    }

    //REQUIRES element is "Water", "Wood", "Fire", "Earth", or "Metal"
    //EFFECTS Changes element type to specified element.
    void change_element(const std::string& element_change) {
        element = element_change;
        best_healing_element = find_best_healing_element(element_change);
        best_opponent_element = find_best_opponent_element(element_change);
    }

    //REQUIRES resource is a valid element
    //EFFECTS Returns true if other resource element strengthens 
    //or harms current element. False otherwise.
    bool is_special_resource(const Element& resource) const {
        bool strengthener = resource == best_healing_element;
        std::string resource_element = resource.get_element();
        bool harmer = element == find_best_healing_element(resource_element);
        return strengthener || harmer;
    }

    //REQUIRES resource either strengthens or harms current element
    //EFFECTS Returns true if other resource element strengthens current element. False if harms.
    bool is_strengthening(const Element& resource) const {
        assert(is_special_resource(resource));
        return resource == best_healing_element;
    }

    //REQUIRES defender is a valid element
    //EFFECTS Returns true if current element is extremely effective or 
    //extremely ineffective against defender element. False otherwise.
    bool is_special_strength(const Element& defender) const {
        bool effective = defender == best_opponent_element;
        std::string defender_element = defender.get_element();
        bool harmer = element == find_best_opponent_element(defender_element);
        return effective || harmer;
    }

    //REQUIRES current element is extremely effective or extremely ineffective against defender element.
    //EFFECTS Returns true if current element is extremely effective
    //against defender element. False otherwise.
    bool is_effective_strength(const Element& defender) const {
        assert(is_special_strength(defender));
        return defender == best_opponent_element;
    }

private:
    std::string element;
    std::string best_healing_element; // element that current element would like to receive healing from
    std::string best_opponent_element; // element that current element would like to have as opponent
};

//EFFECTS Returns the element that current element would like to receive healing from
std::string find_best_healing_element(const std::string& element) {
    if (element == Element::ELE_WATER) {
        return Element::ELE_METAL;
    }
    else if (element == Element::ELE_METAL) {
        return Element::ELE_EARTH;
    }
    else if (element == Element::ELE_EARTH) {
        return Element::ELE_FIRE;
    }
    else if (element == Element::ELE_FIRE) {
        return Element::ELE_WOOD;
    }
    else if (element == Element::ELE_WOOD) {
        return Element::ELE_WATER;
    }
    else {
        assert(false);
    }
}

//EFFECTS Returns the element that current element would like to fight as opponent
std::string find_best_opponent_element(const std::string& element) {
    if (element == Element::ELE_WATER) {
        return Element::ELE_FIRE;
    }
    else if (element == Element::ELE_METAL) {
        return Element::ELE_WOOD;
    }
    else if (element == Element::ELE_EARTH) {
        return Element::ELE_WATER;
    }
    else if (element == Element::ELE_FIRE) {
        return Element::ELE_METAL;
    }
    else if (element == Element::ELE_WOOD) {
        return Element::ELE_EARTH;
    }
    else {
        assert(false);
    }
}

//EFFECTS Returns true if lhs is same as rhs
bool operator==(const Element& lhs, const Element& rhs) {
    bool same_element = lhs.get_element() == rhs.get_element();
    bool same_best_healer = lhs.get_best_healing_element() == rhs.get_best_healing_element();
    bool same_best_opponent = lhs.get_best_opponent_element() == rhs.get_best_opponent_element();
    return same_element && same_best_healer && same_best_opponent;
}

//EFFECTS Returns true if lhs is not same as rhs.
bool operator!=(const Element& lhs, const Element& rhs) {
    return !(lhs == rhs);
}

//EFFECTS Prints Element to stream, for example "Water"
std::ostream& operator<<(std::ostream& os, const Element& element) {
    os << element.get_element();
    return os;
}