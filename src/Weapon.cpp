#include <string>
#include <vector>
#include <cassert>

#include "Element.h"
#include "Weapon.h"

class Weapon
{
public:
    // weapon names
    static constexpr const char *const STAFF = "Staff";
    static constexpr const char *const SPEAR = "Spear";
    static constexpr const char *const CROSS = "Cross";
    // list
    static constexpr const char *const WEAPON_LIST[] = {
        Weapon::STAFF,
        Weapon::SPEAR,
        Weapon::CROSS};
    static constexpr const int NUM_weaponTypeS = 3;

    Weapon() {}

    Weapon(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength)
        : Weapon(givenName, givenElement),
          attackStrength(givenAttackStrength),
          healingStrength(givenHealingStrength) {}

    Weapon(
        const std::string &givenName,
        const Element &givenElement)
        : name(givenName), element(givenElement) {}

    // EFFECTS returns weapon's name
    virtual const std::string &getName() const
    {
        return name;
    };

    // REQUIRES weapon has an element
    // EFFECTS  returns element of weapon
    virtual Element getElement() const
    {
        return element;
    };

    // REQUIRES weapon has an attack strength
    // EFFECTS  returns attack strength of weapon
    virtual double getAttackStrength() const
    {
        return attackStrength;
    };

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    virtual double getHealingStrength() const
    {
        return healingStrength;
    }

    // EFFECTS returns weapon's type
    virtual const std::string getWeaponType() const
    {
        return weaponType;
    };

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    virtual void changeName(const std::string &newName)
    {
        name = newName;
    };

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    virtual void changeAttackStrength(
        const int &changedAttackStrength){
        attackStrength = changedAttackStrength};

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    virtual void changeHealingStrength(
        const int &changedHealStrength)
    {
        healingStrength = changedHealStrength;
    };

    // Needed to avoid some compiler errors
    virtual ~Weapon() {}

private:
    std::string name;
    Element element;
    double attackStrength;
    double healingStrength;
    std::string weaponType;
};

class Staff : public Weapon
{
public:
    Staff(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength)
        : Weapon(
              givenName,
              givenElement,
              givenAttackStrength,
              givenHealingStrength) {}

    Staff(
        const std::string &givenName,
        const Element &givenElement)
        : Weapon(
              givenName,
              givenElement,
              4.0,
              2.0) {}

    Staff()
        : Staff(
              "A Magical Staff",
              Element::WATER) {}

    // Needed to avoid some compiler errors
    ~Staff() {}

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
    Spear(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength)
        : Weapon(
              givenName,
              givenElement,
              givenAttackStrength,
              givenHealingStrength) {}

    Spear(
        const std::string &givenName,
        const Element &givenElement)
        : Weapon(
              givenName,
              givenElement,
              5.0,
              1.0) {}

    Spear()
        : Spear(
              "Super Strong Spear",
              Element::WATER) {}

    // Needed to avoid some compiler errors
    ~Spear() {}

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
    Cross(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength)
        : Weapon(
              givenName,
              givenElement,
              givenAttackStrength,
              givenHealingStrength) {}

    Cross(const std::string &givenName, const Element &givenElement)
        : Weapon(
              givenName,
              givenElement,
              3.0,
              5.0) {}

    Cross()
        : Cross(
              "The Coolest Cross",
              Element::WATER) {}

    // Needed to avoid some compiler errors
    ~Cross() {}

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
