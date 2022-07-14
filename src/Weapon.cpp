#include <string>
#include <vector>
#include <cassert>

#include "header/Element.h"
#include "header/Weapon.h"

class Staff : public Weapon
{
public:
    Staff() : name("A Magical Staff"), element(Element::WATER),
              attack_strength(40.0), healing_strength(20.0),
              weaponType(WEAPON_STAFF) {}

    Staff(const std::string &givenName, const Element &givenElement) : Staff()
    {
        name = givenName;
        element = givenElement;
    }

    Staff(const std::string &givenName, const Element &givenElement,
          const double &givenAttackStrength,
          const double &givenHealingStrength) : Staff()
    {
        name = givenName;
        element = givenElement;
        attack_strength = givenAttackStrength;
        healing_strength = givenHealingStrength;
    }

    // EFFECTS returns weapon's name
    const std::string &getName() const override
    {
        return name;
    }

    // REQUIRES weapon has an element
    // EFFECTS  returns element of weapon
    Element getElement() const override
    {
        return element;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  returns attack strength of weapon
    double getAttackStrength() const override
    {
        return attack_strength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    double getHealingStrength() const override
    {
        return healing_strength;
    }

    // EFFECTS returns weapon's type
    const std::string get_weaponType() const override
    {
        std::string weaponType = Weapon::WEAPON_STAFF;
        return weaponType;
    }

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    void change_name(const std::string &name_change) override
    {
        name = name_change;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    void change_attack_strength(const int &changed_attack_strength) override
    {
        attack_strength = changed_attack_strength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    void change_healing_strength(const int &changed_heal_strength) override
    {
        healing_strength = healing_strength;
    }

    // Needed to avoid some compiler errors
    ~Staff()
    {
    }

private:
    std::string name;
    Element element;
    double attack_strength;
    double healing_strength;
    std::string weaponType;
};

class Spear : public Weapon
{
public:
    Spear() : name("Super Strong Spear"), element(Element::WATER),
              attack_strength(50.0), healing_strength(10.0),
              weaponType("Spear") {}

    Spear(const std::string &givenName, const Element &givenElement) : Spear()
    {
        name = givenName;
        element = givenElement;
    }

    Spear(const std::string &givenName, const Element &givenElement,
          const double &givenAttackStrength,
          const double &givenHealingStrength) : Spear()
    {
        name = givenName;
        element = givenElement;
        attack_strength = givenAttackStrength;
        healing_strength = givenHealingStrength;
    }

    // EFFECTS returns weapon's name
    const std::string &getName() const override
    {
        return name;
    }

    // REQUIRES weapon has an element
    // EFFECTS  returns element of weapon
    Element getElement() const override
    {
        return element;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  returns attack strength of weapon
    double getAttackStrength() const override
    {
        return attack_strength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    double getHealingStrength() const override
    {
        return healing_strength;
    }

    // EFFECTS returns weapon's type
    const std::string get_weaponType() const override
    {
        std::string weaponType = Weapon::WEAPON_SPEAR;
        return weaponType;
    }

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    void change_name(const std::string &name_change) override
    {
        name = name_change;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    void change_attack_strength(const int &changed_attack_strength) override
    {
        attack_strength = changed_attack_strength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    void change_healing_strength(const int &changed_heal_strength) override
    {
        healing_strength = healing_strength;
    }

    // Needed to avoid some compiler errors
    ~Spear()
    {
    }

private:
    std::string name;
    Element element;
    double attack_strength;
    double healing_strength;
    std::string weaponType;
};

class Cross : public Weapon
{
public:
    Cross() : name("The Coolest Cross"), element(Element::WATER),
              attack_strength(30.0), healing_strength(50.0),
              weaponType("Cross") {}

    Cross(const std::string &givenName, const Element &givenElement) : Cross()
    {
        name = givenName;
        element = givenElement;
    }

    Cross(const std::string &givenName, const Element &givenElement,
          const double &givenAttackStrength,
          const double &givenHealingStrength) : Cross()
    {
        name = givenName;
        element = givenElement;
        attack_strength = givenAttackStrength;
        healing_strength = givenHealingStrength;
    }

    // EFFECTS returns weapon's name
    const std::string &getName() const override
    {
        return name;
    }

    // REQUIRES weapon has an element
    // EFFECTS  returns element of weapon
    Element getElement() const override
    {
        return element;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  returns attack strength of weapon
    double getAttackStrength() const override
    {
        return attack_strength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    double getHealingStrength() const override
    {
        return healing_strength;
    }

    // EFFECTS returns weapon's type
    const std::string get_weaponType() const override
    {
        std::string weaponType = Weapon::WEAPON_CROSS;
        return weaponType;
    }

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    void change_name(const std::string &name_change) override
    {
        name = name_change;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    void change_attack_strength(const int &changed_attack_strength) override
    {
        attack_strength = changed_attack_strength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    void change_healing_strength(const int &changed_heal_strength) override
    {
        healing_strength = healing_strength;
    }

    // Needed to avoid some compiler errors
    ~Cross()
    {
    }

private:
    std::string name;
    Element element;
    double attack_strength;
    double healing_strength;
    std::string weaponType;
};

// EFFECTS Returns a pointer to a weapon with the given name, element, and type
Weapon *WeaponFactory(const std::string &name, const Element &element,
                       const std::string &weaponType)
{

    if (weaponType == Weapon::WEAPON_STAFF)
    {
        return new Staff(name, element);
    }
    else if (weaponType == Weapon::WEAPON_SPEAR)
    {
        return new Spear(name, element);
    }
    else if (weaponType == Weapon::WEAPON_CROSS)
    {
        return new Cross(name, element);
    }
    assert(false);
    return nullptr;
}

// EFFECTS Returns a pointer to a weapon with the given weaponType
Weapon *WeaponFactory(const std::string &weaponType)
{
    if (weaponType == Weapon::WEAPON_STAFF)
    {
        return new Staff();
    }
    else if (weaponType == Weapon::WEAPON_SPEAR)
    {
        return new Spear();
    }
    else if (weaponType == Weapon::WEAPON_CROSS)
    {
        return new Cross();
    }
    assert(false);
    return nullptr;
}

// EFFECTS Returns a pointer to a weapon that is copy of copied_weapon
Weapon *WeaponFactory(const Weapon *copied_weapon)
{

    std::string name = copied_weapon->getName();
    Element element = copied_weapon->getElement();
    double attack_strength = copied_weapon->getAttackStrength();
    double healing_strength = copied_weapon->getHealingStrength();
    std::string weaponType = copied_weapon->get_weaponType();

    if (weaponType == Weapon::WEAPON_STAFF)
    {
        return new Staff(name, element, attack_strength, healing_strength);
    }
    else if (weaponType == Weapon::WEAPON_SPEAR)
    {
        return new Spear(name, element, attack_strength, healing_strength);
    }
    else if (weaponType == Weapon::WEAPON_CROSS)
    {
        return new Cross(name, element, attack_strength, healing_strength);
    }
    assert(false);
    return nullptr;
}

// EFFECTS Prints weapon's name to os
std::ostream &operator<<(std::ostream &os, const Weapon &w)
{
    os << w.getName() << " (Type: " << w.get_weaponType() << ")";
    return os;
}
