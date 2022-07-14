#include <string>
#include <vector>
#include <cassert>

#include "Element.h"
#include "Weapon.h"

class Staff : public Weapon
{
public:
    Staff()
        : name("A Magical Staff"),
          element(Element::WATER),
          attackStrength(40.0),
          healingStrength(20.0),
          weaponType(STAFF) {}

    Staff(const std::string &givenName, const Element &givenElement) : Staff()
    {
        name = givenName;
        element = givenElement;
    }

    Staff(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength) : Staff()
    {
        name = givenName;
        element = givenElement;
        attackStrength = givenAttackStrength;
        healingStrength = givenHealingStrength;
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
        return attackStrength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    double getHealingStrength() const override
    {
        return healingStrength;
    }

    // EFFECTS returns weapon's type
    const std::string getWeaponType() const override
    {
        std::string weaponType = Weapon::STAFF;
        return weaponType;
    }

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    void changeName(const std::string &newName) override
    {
        name = newName;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    void changeAttackStrength(const int &changedAttackStrength) override
    {
        attackStrength = changedAttackStrength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    void changeHealingStrength(const int &changedHealStrength) override
    {
        healingStrength = healingStrength;
    }

    // Needed to avoid some compiler errors
    ~Staff()
    {
    }

private:
    std::string name;
    Element element;
    double attackStrength;
    double healingStrength;
    std::string weaponType;
};

class Spear : public Weapon
{
public:
    Spear()
        : name("Super Strong Spear"),
          element(Element::WATER),
          attackStrength(50.0),
          healingStrength(10.0),
          weaponType("Spear") {}

    Spear(const std::string &givenName, const Element &givenElement) : Spear()
    {
        name = givenName;
        element = givenElement;
    }

    Spear(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength) : Spear()
    {
        name = givenName;
        element = givenElement;
        attackStrength = givenAttackStrength;
        healingStrength = givenHealingStrength;
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
        return attackStrength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    double getHealingStrength() const override
    {
        return healingStrength;
    }

    // EFFECTS returns weapon's type
    const std::string getWeaponType() const override
    {
        std::string weaponType = Weapon::SPEAR;
        return weaponType;
    }

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    void changeName(const std::string &newName) override
    {
        name = newName;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    void changeAttackStrength(const int &changedAttackStrength) override
    {
        attackStrength = changedAttackStrength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    void changeHealingStrength(const int &changedHealStrength) override
    {
        healingStrength = healingStrength;
    }

    // Needed to avoid some compiler errors
    ~Spear()
    {
    }

private:
    std::string name;
    Element element;
    double attackStrength;
    double healingStrength;
    std::string weaponType;
};

class Cross : public Weapon
{
public:
    Cross()
        : name("The Coolest Cross"),
          element(Element::WATER),
          attackStrength(30.0),
          healingStrength(50.0),
          weaponType("Cross") {}

    Cross(const std::string &givenName, const Element &givenElement) : Cross()
    {
        name = givenName;
        element = givenElement;
    }

    Cross(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength) : Cross()
    {
        name = givenName;
        element = givenElement;
        attackStrength = givenAttackStrength;
        healingStrength = givenHealingStrength;
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
        return attackStrength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    double getHealingStrength() const override
    {
        return healingStrength;
    }

    // EFFECTS returns weapon's type
    const std::string getWeaponType() const override
    {
        std::string weaponType = Weapon::CROSS;
        return weaponType;
    }

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    void changeName(const std::string &newName) override
    {
        name = newName;
    }

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    void changeAttackStrength(const int &changedAttackStrength) override
    {
        attackStrength = changedAttackStrength;
    }

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    void changeHealingStrength(const int &changedHealStrength) override
    {
        healingStrength = healingStrength;
    }

    // Needed to avoid some compiler errors
    ~Cross()
    {
    }

private:
    std::string name;
    Element element;
    double attackStrength;
    double healingStrength;
    std::string weaponType;
};

// EFFECTS Returns a pointer to a weapon with the given name, element, and type
Weapon *WeaponFactory(
    const std::string &name,
    const Element &element,
    const std::string &weaponType)
{

    if (weaponType == Weapon::STAFF)
    {
        return new Staff(name, element);
    }
    else if (weaponType == Weapon::SPEAR)
    {
        return new Spear(name, element);
    }
    else if (weaponType == Weapon::CROSS)
    {
        return new Cross(name, element);
    }
    assert(false);
    return nullptr;
}

// EFFECTS Returns a pointer to a weapon with the given weaponType
Weapon *WeaponFactory(const std::string &weaponType)
{
    if (weaponType == Weapon::STAFF)
    {
        return new Staff();
    }
    else if (weaponType == Weapon::SPEAR)
    {
        return new Spear();
    }
    else if (weaponType == Weapon::CROSS)
    {
        return new Cross();
    }
    assert(false);
    return nullptr;
}

// EFFECTS Returns a pointer to a weapon that is copy of copiedWeapon
Weapon *WeaponFactory(const Weapon *copiedWeapon)
{

    std::string name = copiedWeapon->getName();
    Element element = copiedWeapon->getElement();
    double attackStrength = copiedWeapon->getAttackStrength();
    double healingStrength = copiedWeapon->getHealingStrength();
    std::string weaponType = copiedWeapon->getWeaponType();

    if (weaponType == Weapon::STAFF)
    {
        return new Staff(name, element, attackStrength, healingStrength);
    }
    else if (weaponType == Weapon::SPEAR)
    {
        return new Spear(name, element, attackStrength, healingStrength);
    }
    else if (weaponType == Weapon::CROSS)
    {
        return new Cross(name, element, attackStrength, healingStrength);
    }
    assert(false);
    return nullptr;
}

// EFFECTS Prints weapon's name to os
std::ostream &operator<<(std::ostream &os, const Weapon &w)
{
    os << w.getName() << " (Type: " << w.getWeaponType() << ")";
    return os;
}
