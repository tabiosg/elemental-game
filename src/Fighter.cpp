#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Fighter.h"

#include "Weapon.h"
#include "Element.h"

Fighter::Fighter()
    : name("Defualt Fighter"),
      elementType(Element::WATER),
      weapons(std::vector<Weapon*>()),
      inCombat(false),
      maxHealth(20.0),
      currentHealth(maxHealth),
      attackStrength(2.5),
      healingStrength(2.5),
      type(Fighter::WARRIOR)
{
}

Fighter::Fighter(const std::string &givenName, const Element &element) : Fighter()
{
    name = givenName;
    elementType = element;
}

Fighter::Fighter(
    const std::string &givenName,
    const Element &element,
    const std::string &weaponType) : Fighter(givenName, element)
{
    Weapon *defaultWeapon;
    if (weaponType == Weapon::STAFF)
    {
        defaultWeapon = WeaponFactory(Weapon::STAFF);
    }
    else if (weaponType == Weapon::SPEAR)
    {
        defaultWeapon = WeaponFactory(Weapon::STAFF);
    }
    else if (weaponType == Weapon::CROSS)
    {
        defaultWeapon = WeaponFactory(Weapon::CROSS);
    }
    else
    {
        assert(false);
    }
    addWeapon(defaultWeapon);
}

Fighter::Fighter(
    const std::string &givenName,
    const Element &givenElement,
    std::vector<Weapon *> givenWeapons,
    const bool &givenInCombat,
    const double &givenMaxHealth,
    const double &givenCurrentHealth,
    const double &givenAttackStrength,
    const double &givenHealingStrength,
    std::string &givenType)
    : name(givenName),
      elementType(givenElement),
      weapons(givenWeapons),
      inCombat(givenInCombat),
      maxHealth(givenMaxHealth),
      currentHealth(givenCurrentHealth),
      attackStrength(givenAttackStrength),
      healingStrength(givenHealingStrength),
      type(givenType)
{
}

Fighter::Fighter(const Fighter &other)
{
    name = other.name;
    elementType = other.elementType;
    inCombat = other.inCombat;
    maxHealth = other.maxHealth;
    currentHealth = other.currentHealth;
    attackStrength = other.attackStrength;
    healingStrength = other.healingStrength;
    type = other.type;

    for (int k = 0; k < other.weapons.size(); ++k)
    {
        Weapon *additionWeapon = WeaponFactory(other.weapons[k]);
        weapons.push_back(additionWeapon);
    }
}

Fighter &Fighter::operator=(const Fighter &rhs)
{
    while (!weapons.empty())
    {
        deleteWeapon(0);
    }

    name = rhs.name;
    elementType = rhs.elementType;
    inCombat = rhs.inCombat;
    maxHealth = rhs.maxHealth;
    currentHealth = rhs.currentHealth;
    attackStrength = rhs.attackStrength;
    healingStrength = rhs.healingStrength;
    type = rhs.type;

    for (int k = 0; rhs.weapons.size(); ++k)
    {
        Weapon *additionWeapon = WeaponFactory(rhs.weapons[k]);
        weapons.push_back(additionWeapon);
    }

    return *this;
}

// EFFECTS returns fighter's name
const std::string &Fighter::getName() const
{
    return name;
}

// EFFECTS returns fighter's type
const std::string &Fighter::getType() const
{
    return type;
};

// REQUIRES fighter has an element
// EFFECTS  returns element of fighter
Element Fighter::getElement() const
{
    return elementType;
};

// EFFECTS returns number of weapons on fighter
int Fighter::getNumberOfWeapons() const
{
    return weapons.size();
};

// EFFECTS returns kth weapons of fighter
Weapon *Fighter::getWeaponK(const int &k) const
{
    return weapons[k];
};

// EFFECTS  returns combat status of fighter
bool Fighter::getCombatStatus() const
{
    return inCombat;
};

// EFFECTS  returns max health of fighter
double Fighter::getMaxHealth() const
{
    return maxHealth;
};

// EFFECTS  returns current health of fighter
double Fighter::getCurrentHealth() const
{
    return currentHealth;
};

// EFFECTS  returns attackStrength of fighter
double Fighter::getAttackStrength() const
{
    return attackStrength;
};

// REQUIRES fighter has at least 1 weapon
// EFFECTS returns highest damage weapon
Weapon *Fighter::getHighestDamageWeapon() const
{
    assert(!weapons.empty());
    int highestDamageWeapon = 0;

    double highestDamageAmount = DBL_MIN;

    for (int i = 0; i < weapons.size(); ++i)
    {
        if (weapons[i]->getAttackStrength() > highestDamageAmount)
        {
            highestDamageAmount = weapons[i]->getAttackStrength();
            highestDamageWeapon = i;
        }
    }

    return weapons[highestDamageWeapon];
}

// EFFECTS  returns healingStrength of fighter
double Fighter::getHealingStrength() const
{
    return healingStrength;
};

// REQUIRES fighter wants to add weapon
// EFFECTS gives fighter the extra weapon
void Fighter::addWeapon(Weapon *weapon)
{
    Weapon *addedWeapon = WeaponFactory(weapon);
    weapons.push_back(addedWeapon);
};

// REQUIRES fighter wants to delete a weapon and 0 <= weaponIndex < weapons.size()
// EFFECTS deletes weapon
void Fighter::deleteWeapon(const int &weaponIndex)
{
    assert(0 <= weaponIndex && weaponIndex < weapons.size());
    delete weapons[weaponIndex];
    weapons.erase(weapons.begin() + weaponIndex);
};

// REQUIRES 0 <= k < weapons.size()
// EFFECTS returns the kth weapon's name
const std::string &Fighter::getNameOfWeaponK(const int &k) const
{
    return weapons[k]->getName();
};

// REQUIRES 0 <= k < weapons.size()
// EFFECTS  returns element of the kth weapon
Element Fighter::getElementOfWeaponK(const int &k) const
{
    return weapons[k]->getElement();
};

/// REQUIRES 0 <= k < weapons.size()
// EFFECTS  returns attack strength of the kth weapon
double Fighter::getAttackStrengthOfWeaponK(const int &k) const
{
    return weapons[k]->getAttackStrength();
};

// REQUIRES 0 <= k < weapons.size()
// EFFECTS  returns healing strength of the kth weapon
double Fighter::getHealingStrengthOfWeaponK(const int &k) const
{
    return weapons[k]->getHealingStrength();
};

// REQUIRES 0 <= k < weapons.size()
// EFFECTS returns the kth weapon's type
const std::string Fighter::getTypeOfWeaponK(const int &k) const
{
    return weapons[k]->getWeaponType();
};

// REQUIRES fighter wants to change name
// EFFECTS changes fighter name
void Fighter::changeName(const std::string &newName)
{
    name = newName;
};

// EFFECTS changes fighter max health
void Fighter::changeMaxHealth(const int &newMaxHealth)
{
    maxHealth = newMaxHealth;
}

// EFFECTS changes fighter current health
void Fighter::changeCurrentHealth(const int &newMaxHealth)
{
    currentHealth = newMaxHealth;
}

// EFFECTS changes fighter attack strength
void Fighter::changeAttackStrength(const int &newAttackStrength)
{
    attackStrength = newAttackStrength;
};

// EFFECTS changes fighter healing strength
void Fighter::changeHealingStrength(const int &newHealingStrength)
{
    healingStrength = newHealingStrength;
};

// REQUIRES fighter is currently not in combat
// EFFECTS make fighter enter combat
void Fighter::enterCombat()
{
    assert(!inCombat);
    inCombat = true;
};

// REQUIRES fighter is currently in combat
// EFFECTS make fighter exit combat
void Fighter::exitCombat()
{
    assert(inCombat);
    inCombat = false;
};

// REQUIRES ally is in combat and weapon belongs to fighter
// MODIFIES allies
// EFFECTS make fighter heal allies or self
void Fighter::goHealAllyWithWeapon(Fighter *ally, Weapon *weapon)
{
    std::cout << *this << " used " << *weapon << " to heal " << *ally << std::endl;

    ally->receiveHealing(weapon, this);

    Element weaponElement = weapon->getElement();
    double lostHealthMultiplier = 0;
    if (
        weaponElement.isBeneficialResourceTo(ally->elementType) ||
        elementType.isBeneficialResourceTo(ally->elementType))
    {
        lostHealthMultiplier += 0.1;
    }
    if (elementType.isBeneficialResourceTo(weaponElement))
    {
        lostHealthMultiplier += 0.2;
    }
    if (lostHealthMultiplier)
    {
        double lostHealth = lostHealthMultiplier * maxHealth;
        lostHealth = std::max(currentHealth, lostHealth);
        std::cout << *this << " lost " << lostHealth << " when healing!" << std::endl;
    }
};

// REQUIRES fighter wants to fight
// MODIFIES opponent
// EFFECTS  make fighter attack opponent.
void Fighter::goAttackTargetWithWeapon(Fighter *opponent, Weapon *weapon)
{
    std::cout << *this << " used " << *weapon << " to attack " << *opponent << std::endl;

    opponent->receiveAttack(weapon, this);

    double lostHealthMultiplier = 0;

    Element weaponElement = weapon->getElement();
    if (elementType.isBeneficialResourceTo(weaponElement))
    {
        lostHealthMultiplier += 0.4;
    }
    if (lostHealthMultiplier)
    {
        double lostHealth = lostHealthMultiplier * maxHealth;
        lostHealth = std::max(currentHealth, lostHealth);
        std::cout << *this << " lost " << lostHealth << " when attacking!" << std::endl;
    }
};

// REQUIRES fighter wants to fight
// EFFECTS  make fighter grab weapon
void Fighter::goGrabThisWeapon(Weapon *wantedWeapon)
{
    addWeapon(wantedWeapon);
    std::cout << *this << " has picked up " << *wantedWeapon << "." << std::endl
              << std::endl;
};

// REQUIRES fighter must be in combat
// EFFECTS  change health based on amount healed
void Fighter::receiveHealing(const Weapon *healingWeapon, Fighter *healer)
{
    assert(getCombatStatus());
    double multiplier = 1.0;
    Element healerElement = healer->elementType;
    Element weaponElement = healingWeapon->getElement();
    if (healerElement.isBeneficialResourceTo(weaponElement))
    {
        multiplier += 0.4;
        std::cout << *healer << "'s action was significantly more effective because of " << *healer << "'s and " << *healingWeapon << "'s element!" << std::endl;
    }
    if (weaponElement.isBeneficialResourceTo(elementType))
    {
        multiplier += 0.2;
        std::cout << *healer << "'s action was more effective because of " << *healingWeapon << "'s and " << *this << "'s element!" << std::endl;
    }
    if (healerElement.isBeneficialResourceTo(elementType))
    {
        multiplier -= 0.2;
        std::cout << *healer << "'s action more effective because of " << *healingWeapon << "'s and " << *this << "'s element!" << std::endl;
    }

    double healingStrength = healingWeapon->getHealingStrength();
    double totalHealing = healingStrength * multiplier;

    totalHealing = std::min(maxHealth - currentHealth, totalHealing);
    currentHealth += totalHealing;

    std::cout << *this << " received " << totalHealing << " healing from " << *healer << "." << std::endl
              << *this << " now has " << currentHealth << " health." << std::endl
              << std::endl;
};

// REQUIRES fighter is focused by enemy
// EFFECTS  change health based on attack
// do not change combat status if below 0 hp here.
void Fighter::receiveAttack(const Weapon *damagingWeapon, const Fighter *attacker)
{
    assert(getCombatStatus());
    double multiplier = 1.0;
    Element damagingElement = attacker->elementType;
    Element weaponElement = damagingWeapon->getElement();
    if (damagingElement.isEffectiveAgainst(weaponElement))
    {
        multiplier += 0.4;
        std::cout << *attacker << "'s action was significantly more effective because of " << *attacker << "'s and " << *damagingWeapon << "'s element!" << std::endl;
    }
    if (weaponElement.isEffectiveAgainst(elementType))
    {
        multiplier += 0.2;
        std::cout << *attacker << "'s action was more effective because of " << *damagingWeapon << "'s and " << *this << "'s element!" << std::endl;
    }
    else if (weaponElement.isWeakAgainst(weaponElement))
    {
        multiplier -= 0.4;
        std::cout << *attacker << "'s action was significantly weaker because of " << *this << "'s and " << *damagingWeapon << "'s element!" << std::endl;
    }
    if (damagingElement.isEffectiveAgainst(elementType))
    {
        multiplier = multiplier + 0.2;
        std::cout << *damagingWeapon << " was more effective because of " << *damagingWeapon << "'s and " << *this << "'s element!" << std::endl;
    }
    else if (damagingElement.isWeakAgainst(elementType))
    {
        multiplier = multiplier - 0.4;
        std::cout << *attacker << "'s action was significantly weaker because of " << *this << "'s and " << *attacker << "'s element!" << std::endl;
    }

    double attackStrength = damagingWeapon->getAttackStrength();
    double totalDamage = attackStrength * multiplier;
    totalDamage = std::min(currentHealth, totalDamage);
    currentHealth -= totalDamage;

    std::cout << *this << " received " << totalDamage << " damage from " << *attacker << "." << std::endl
              << *this << " now has " << currentHealth << " health." << std::endl
              << std::endl;
};

// EFFECTS: Prints weapons of fighter to os
std::ostream &Fighter::printWeapons(std::ostream &os) const
{
    for (int i = 0; i < weapons.size(); ++i)
    {
        os << "Weapon " << i << ": " << *weapons[i] << std::endl;
    }
    return os;
};

std::ostream &Fighter::printListOfWeapons(
    std::ostream &os,
    const std::vector<Weapon *> weapons) const
{
    for (size_t i = 0; i < weapons.size(); ++i)
    {
        Weapon *ithweapon = weapons[i];
        os << "Weapon " << i << ": " << *ithweapon << std::endl;
    }
    return os;
};

// Needed to avoid some compiler errors
Fighter::~Fighter()
{
    while (!weapons.empty())
    {
        deleteWeapon(0);
    }
}

class Human : public Fighter
{
public:
    Human()
        : Fighter(),
          name("Angel"),
          type("Human")
    {
    }

    Human(const std::string &givenName, const Element &element)
        : Fighter(givenName, element)
    {
    }

    Human(
        const std::string &givenName,
        const Element &element,
        const std::string &weaponType)
        : Fighter(givenName, element, weaponType)
    {
    }

    Human(
        const std::string &givenName,
        const Element &givenElement,
        std::vector<Weapon *> givenWeapons,
        const bool &givenInCombat,
        const double &givenMaxHealth,
        const double &givenCurrentHealth,
        const double &givenAttackStrength,
        const double &givenHealingStrength,
        std::string &givenType)
        : Fighter(
              givenName,
              givenElement,
              givenWeapons,
              givenInCombat,
              givenMaxHealth,
              givenCurrentHealth,
              givenAttackStrength,
              givenHealingStrength,
              givenType)
    {
    }

    Human(const Human &other) : Fighter(other) {}

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    std::string requestAction(
        std::vector<Fighter *> allies,
        std::vector<Fighter *> opponents,
        const std::vector<Weapon *> droppedWeapons) override
    {
        std::cout << name << ", would you like to attack, heal, grab a weapon, or skip your turn?" << std::endl
                  << "Answer with \"Attack\", \"Heal\", \"Grab\", or \"Skip\": " << std::endl;
        std::string response;
        std::cin >> response;
        std::cout << std::endl;
        if (response != "Attack" && response != "Heal" && response != "Grab" && response != "Skip")
        {
            std::cout << std::endl
                      << "\033[2J"
                      << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return requestAction(allies, opponents, droppedWeapons);
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        return response;
    }

    // REQUIRES fighter wants to heal
    // MODIFIES allies
    // EFFECTS  make fighter heal allies or self
    void goHeal(std::vector<Fighter *> allies) override
    {
        assert(getCombatStatus());
        int target = requestHealTarget(allies);
        Weapon *currentWeapon = weapons[requestAttackWeaponK()];
        Fighter *ally = allies[target];
        goHealAllyWithWeapon(ally, currentWeapon);
    }

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    int goAttack(std::vector<Fighter *> opponents) override
    {
        assert(getCombatStatus());
        int target = requestAttackTarget(opponents);
        Weapon *currentWeapon = weapons[requestAttackWeaponK()];
        Fighter *opponent = opponents[target];
        goAttackTargetWithWeapon(opponent, currentWeapon);
        return target;
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int goGrabWeapon(const std::vector<Weapon *> droppedWeapons) override
    {
        assert(getCombatStatus());
        int target = requestGrabTarget(droppedWeapons);
        Weapon *wantedWeapon = droppedWeapons[target];
        goGrabThisWeapon(wantedWeapon);
        return target;
    }

private:
    std::string name;
    Element elementType;
    std::vector<Weapon *> weapons;
    bool inCombat;
    double maxHealth;
    double currentHealth;

    double attackStrength;
    double healingStrength;
    std::string type;

    // REQUIRES fighter wants to attack
    // EFFECTS see who fighter wants to attack
    int requestAttackTarget(std::vector<Fighter *> opponents) const
    {
        std::cout << "These are your opponents: " << std::endl;
        printListOfFighters(std::cout, opponents);
        std::cout << std::endl;
        std::cout << name << ", choose who to attack: " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(0 <= target && target < opponents.size()))
        {
            std::cout << std::endl
                      << "\033[2J"
                      << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return requestAttackTarget(opponents);
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        return target;
    }

    // REQUIRES fighter wants to heal
    // EFFECTS see who fighter wants to heal
    int requestHealTarget(std::vector<Fighter *> allies) const
    {
        std::cout << "These are your allies: " << std::endl;
        printListOfFighters(std::cout, allies);
        std::cout << std::endl;
        std::cout << name << ", choose who to heal (-1 for self): " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(-1 <= target && target < allies.size()))
        {
            std::cout << std::endl
                      << "\033[2J"
                      << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return requestHealTarget(allies);
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";

        if (target == -1)
        {
            for (auto ally : allies)
            {
                if (ally == this)
                {
                    return target;
                }
            }
        }

        return target;
    }

    // REQUIRES fighter wants to heal or attack
    // EFFECTS see which weapon the fighter wants to use
    int requestAttackWeaponK()
    {
        std::cout << "These are your weapons: " << std::endl;
        printWeapons(std::cout);
        std::cout << std::endl;
        std::cout << name << ", choose which weapon to equip by entering a number: " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(0 <= target && target < weapons.size()))
        {
            std::cout << std::endl
                      << "\033[2J"
                      << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return requestAttackWeaponK();
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        return target;
    }

    // REQUIRES fighter wants to grab and there are dropped weapons
    // EFFECTS see what weapon the fighter wants to grab
    int requestGrabTarget(const std::vector<Weapon *> droppedWeapons) const
    {
        std::cout << "These are the dropped weapons: " << std::endl;
        printListOfWeapons(std::cout, droppedWeapons);
        std::cout << std::endl;
        std::cout << name << ", choose which weapon to equip by entering a number: " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(0 <= target && target < droppedWeapons.size()))
        {
            std::cout << std::endl
                      << "\033[2J"
                      << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return requestGrabTarget(droppedWeapons);
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        return target;
    }
};

class Warrior : public Fighter
{
public:
    Warrior()
        : Fighter(),
          name("Default AI Bob"),
          type("Warrior") {}

    Warrior(const std::string &givenName, const Element &element)
        : Fighter(givenName, element)
    {
    }

    Warrior(
        const std::string &givenName,
        const Element &element,
        const std::string &weaponType)
        : Fighter(givenName, element, weaponType)
    {
    }

    Warrior(
        const std::string &givenName,
        const Element &givenElement,
        std::vector<Weapon *> givenWeapons,
        const bool &givenInCombat,
        const double &givenMaxHealth,
        const double &givenCurrentHealth,
        const double &givenAttackStrength,
        const double &givenHealingStrength,
        std::string &givenType)
        : Fighter(
              givenName,
              givenElement,
              givenWeapons,
              givenInCombat,
              givenMaxHealth,
              givenCurrentHealth,
              givenAttackStrength,
              givenHealingStrength,
              givenType)
    {
    }

    Warrior(const Warrior &other) : Fighter(other) {}

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    std::string requestAction(
        std::vector<Fighter *> allies,
        std::vector<Fighter *> opponents,
        const std::vector<Weapon *> droppedWeapons) override
    {
        std::string response = "Attack";
        return response;
    }

    // REQUIRES fighter wants to heal
    // MODIFIES allies
    // EFFECTS  make fighter heal allies or self
    void goHeal(std::vector<Fighter *> allies) override
    {
        assert(getCombatStatus());
        assert(false);
    }

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    int goAttack(std::vector<Fighter *> opponents) override
    {
        assert(getCombatStatus());

        Weapon *currentWeapon = getHighestDamageWeapon();

        Element selectedWeaponElement = currentWeapon->getElement();

        int target = 0;
        int bestAdvantage = INT_MIN;
        for (size_t i = 0; i < opponents.size(); ++i)
        {
            Fighter *potentialDefender = opponents[i];
            Element opponentElement = potentialDefender->getElement();
            int potentialAdvantage = 0;

            if (selectedWeaponElement.isEffectiveAgainst(opponentElement))
            {
                potentialAdvantage += 2;
            }
            if (elementType.isEffectiveAgainst(opponentElement))
            {
                potentialAdvantage += 2;
            }
            if (opponentElement.isEffectiveAgainst(elementType))
            {
                potentialAdvantage -= 4;
            }
            if (opponentElement.isEffectiveAgainst(selectedWeaponElement))
            {
                potentialAdvantage -= 4;
            }

            if (potentialAdvantage > bestAdvantage)
            {
                bestAdvantage = potentialAdvantage;
                target = i;
            }
        }

        Fighter *opponent = opponents[target];
        goAttackTargetWithWeapon(opponent, currentWeapon);

        return target;
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int goGrabWeapon(const std::vector<Weapon *> droppedWeapons) override
    {
        assert(getCombatStatus());
        assert(false);
    }

private:
    std::string name;
    Element elementType;
    std::vector<Weapon *> weapons;
    bool inCombat;
    double maxHealth;
    double currentHealth;

    double attackStrength;
    double healingStrength;
    std::string type;
};

// EFFECTS Returns a pointer to a fighter with the given name, element, and type
Fighter *FighterFactory(
    const std::string &name,
    const Element &element,
    const std::string &type)
{
    if (type == "Human")
    {
        return new Human(name, element);
    }
    else if (type == "Warrior")
    {
        return new Warrior(name, element);
    }
    assert(false);
    return nullptr;
}

// EFFECTS: Returns a pointer to a fighter with the given name, element, weapon, and type
Fighter *FighterFactory(
    const std::string &name,
    const Element &element,
    const std::string &weapon,
    const std::string &type)
{
    if (type == "Human")
    {
        return new Human(name, element, weapon);
    }
    else if (type == "Warrior")
    {
        return new Warrior(name, element, weapon);
    }
    assert(false);
    return nullptr;
}

// EFFECTS Returns a pointer to a fighter that is copy of copiedFighter
Fighter *FighterFactory(const Fighter *copiedFighter)
{
    std::cout << "TODO - test" << std::endl;
    std::string name = copiedFighter->getName();
    std::cout << "TODO - test name" << std::endl;
    Element element = copiedFighter->getElement();
    std::cout << "TODO - test element" << std::endl;

    std::vector<Weapon *> weapons;
    for (int i = 0; i < copiedFighter->getNumberOfWeapons(); ++i)
    {
        Weapon *weaponI = copiedFighter->getWeaponK(i);
        Weapon *addedWeapon = WeaponFactory(weaponI);
        weapons.push_back(addedWeapon);
    }
    bool inCombat = copiedFighter->getCombatStatus();
    double maxHealth = copiedFighter->getMaxHealth();
    double currentHealth = copiedFighter->getCurrentHealth();

    double attackStrength = copiedFighter->getAttackStrength();
    double healingStrength = copiedFighter->getHealingStrength();
    std::string type = copiedFighter->getType();

    if (type == "Human")
    {
        return new Human(
            name, element, weapons, inCombat, maxHealth,
            currentHealth, attackStrength, healingStrength, type);
    }
    else if (type == "Warrior")
    {
        return new Warrior(
            name, element, weapons, inCombat, maxHealth,
            currentHealth, attackStrength, healingStrength, type);
    }
    return nullptr;
}

// EFFECTS: Prints fighter's name to os
std::ostream &operator<<(std::ostream &os, const Fighter &f)
{
    os << f.getName();
    return os;
}

// EFFECTS: Prints weapons of fighter to os
std::ostream &printWeapons(std::ostream &os, const Fighter &f)
{
    f.printWeapons(os);
    return os;
}

// EFFECTS Prints fighters to stream as "Fighter 1: Alex"
// followed by newline and then "Fighter 2: Harry"
std::ostream &printListOfFighters(std::ostream &os, std::vector<Fighter *> fighters)
{
    for (size_t i = 0; i < fighters.size(); ++i)
    {
        Fighter *fighterI = fighters[i];
        os << "Fighter " << i << ": " << *fighterI << std::endl;
    }
    return os;
}
