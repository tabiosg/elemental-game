#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "header/Fighter.h"

#include "header/Weapon.h"
#include "header/Element.h"

class Human : public Fighter
{
public:
    Human()
        : name("Angel"),
          elementType(Element::WATER),
          numberOfWeapons(0),
          activeWeapon(-1),
          inCombat(false),
          maxHealth(200.0),
          currentHealth(maxHealth),
          attackStrength(25.0),
          healingStrength(25.0),
          type("Human") {}

    Human(const std::string &givenName, const Element &element) : Human()
    {
        name = givenName;
        elementType = element;
    }

    Human(
        const std::string &givenName,
        const Element &element,
        const std::string &weaponType) : Human()
    {
        name = givenName;
        elementType = element;
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

    Human(
        const std::string &givenName,
        const Element &givenElement,
        std::vector<Weapon *> givenWeapons,
        const int &givenNumberOfWeapons,
        const int &givenActiveWeapon,
        const bool &givenInCombat,
        const double &givenMaxHealth,
        const double &givenCurrentHealth,
        const double &givenAttackStrength,
        const double &givenHealingStrength,
        std::string &givenType)
        : name(givenName),
          elementType(givenElement),
          weapons(givenWeapons),
          numberOfWeapons(givenNumberOfWeapons),
          activeWeapon(givenActiveWeapon),
          inCombat(givenInCombat),
          maxHealth(givenMaxHealth),
          currentHealth(givenCurrentHealth),
          attackStrength(givenAttackStrength),
          healingStrength(givenHealingStrength),
          type(givenType)
    {
    }

    Human(const Human &other)
    {
        name = other.getName();
        elementType = other.getElement();
        numberOfWeapons = other.getNumberOfWeapons();
        activeWeapon = other.getActiveWeapon();
        inCombat = other.getCombatStatus();
        maxHealth = other.getMaxHealth();
        currentHealth = other.getCurrentHealth();
        attackStrength = other.getAttackStrength();
        healingStrength = other.getHealingStrength();
        type = other.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(other.getOfWeaponK(k));
            weapons.push_back(additionWeapon);
        }
    }

    Human &operator=(const Human &rhs)
    {
        while (numberOfWeapons != 0)
        {
            deleteWeapon(0);
        }

        name = rhs.getName();
        elementType = rhs.getElement();
        numberOfWeapons = rhs.getNumberOfWeapons();
        activeWeapon = rhs.getActiveWeapon();
        inCombat = rhs.getCombatStatus();
        maxHealth = rhs.getMaxHealth();
        currentHealth = rhs.getCurrentHealth();
        attackStrength = rhs.getAttackStrength();
        healingStrength = rhs.getHealingStrength();
        type = rhs.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(rhs.getOfWeaponK(k));
            weapons.push_back(additionWeapon);
        }
        return *this;
    }

    // EFFECTS returns fighter's name
    const std::string &getName() const override
    {
        return name;
    }

    // EFFECTS returns fighter's type
    const std::string &getType() const override
    {
        return type;
    }

    // REQUIRES fighter has an element
    // EFFECTS  returns element of fighter
    Element getElement() const override
    {
        return elementType;
    }

    // EFFECTS returns number of weapons on fighter
    int getNumberOfWeapons() const override
    {
        return numberOfWeapons;
    }

    // REQUIRES fighter has a weapon
    // EFFECTS  returns active weapon of fighter
    int getActiveWeapon() const override
    {
        return activeWeapon;
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns kth weapons of fighter
    Weapon *getOfWeaponK(const int &k) const override
    {
        assert(getNumberOfWeapons() != 0);
        return weapons[k];
    }

    // EFFECTS  returns combat status of fighter
    bool getCombatStatus() const override
    {
        return inCombat;
    }

    // EFFECTS  returns max health of fighter
    double getMaxHealth() const override
    {
        return maxHealth;
    }

    // EFFECTS  returns current health of fighter
    double getCurrentHealth() const override
    {
        return currentHealth;
    }

    // EFFECTS  returns attackStrength of fighter
    double getAttackStrength() const override
    {
        return attackStrength;
    }

    // EFFECTS  returns healingStrength of fighter
    double getHealingStrength() const override
    {
        return healingStrength;
    }

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    void addWeapon(Weapon *weapon) override
    {
        ++numberOfWeapons;
        Weapon *addedWeapon = WeaponFactory(weapon);
        weapons.push_back(addedWeapon);
        if (activeWeapon == -1)
        {
            activeWeapon = 0;
        }
    }

    // REQUIRES fighter wants to delete a weapon
    // EFFECTS deletes weapon
    void deleteWeapon(const int &weaponIndex)
    {
        --numberOfWeapons;
        delete weapons[weaponIndex];
        weapons.erase(weapons.begin() + weaponIndex);
        if (activeWeapon >= numberOfWeapons)
        {
            activeWeapon = numberOfWeapons - 1;
        }
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's name
    const std::string &getNameOfWeaponK(const int &k) const override
    {
        return weapons[k]->getName();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns element of the kth weapon
    Element getElementOfWeaponK(const int &k) const override
    {
        return weapons[k]->getElement();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns attack strength of the kth weapon
    double getAttackStrengthOfWeaponK(const int &k) const override
    {
        return weapons[k]->getAttackStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns healing strength of the kth weapon
    double getHealingStrengthOfWeaponK(const int &k) const override
    {
        return weapons[k]->getHealingStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's type
    const std::string getTypeOfWeaponK(const int &k) const override
    {
        return weapons[k]->getWeaponType();
    }

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    void changeName(const std::string &newName) override
    {
        name = newName;
    }

    // EFFECTS changes fighter max health
    void changeMaxHealth(const int &newMaxHealth) override
    {
        maxHealth = newMaxHealth;
    }

    // EFFECTS changes fighter current health
    void changeCurrentHealth(const int &newMaxHealth) override
    {
        currentHealth = newMaxHealth;
    }

    // EFFECTS changes fighter attack strength
    void changeAttackStrength(const int &newAttackStrength) override
    {
        attackStrength = newAttackStrength;
    }

    // EFFECTS changes fighter healing strength
    void changeHealingStrength(const int &newHealingStrength) override
    {
        healingStrength = newHealingStrength;
    }

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    void enterCombat() override
    {
        assert(!inCombat);
        inCombat = true;
    }

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    void exitCombat() override
    {
        assert(inCombat);
        inCombat = false;
    }

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
        activeWeapon = requestActiveWeapon();
        Weapon *currentWeapon = getOfWeaponK(activeWeapon);

        std::cout << *this << " used " << *currentWeapon << " to heal " << *allies[target] << std::endl;

        allies[target]->receiveHealing(currentWeapon, this);

        Element weaponElement = currentWeapon->getElement();
        double lostHealthMultiplier = 0;
        if (
            weaponElement.isStrengthening(allies[target]->getElement()) ||
            elementType.isStrengthening(allies[target]->getElement())
        )
        {
            lostHealthMultiplier += 0.1;
        }
        if (elementType.isStrengthening(weaponElement))
        {
            lostHealthMultiplier += 0.2;
        }
        if (lostHealthMultiplier) {
            double lostHealth = losthealthMultiplier * maxHealth;
            lostHealth = max(currentHealth, lostHealth);
            std::cout << *this << " lost " <<
            lostHealth << " when healing!" << std::endl;
        }
        
    }

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    int goAttack(std::vector<Fighter *> opponents) override
    {
        assert(getCombatStatus());
        int target = requestAttackTarget(opponents);
        activeWeapon = requestActiveWeapon();
        Weapon *currentWeapon = getOfWeaponK(activeWeapon);

        std::cout << *this << " used " << *currentWeapon << " to attack " << *opponents[target] << std::endl;

        opponents[target]->receiveAttack(currentWeapon, this);

        Element weaponElement = currentWeapon->getElement();
        if (elementType.isStrengthening(weaponElement))
        {
            lostHealthMultiplier += 0.4;
        }
        if (lostHealthMultiplier) {
            double lostHealth = losthealthMultiplier * maxHealth;
            lostHealth = max(currentHealth, lostHealth);
            std::cout << *this << " lost " <<
            lostHealth << " when attacking!" << std::endl;
        }

        return target;
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int goGrabWeapon(
        std::vector<Fighter *> allies,
        std::vector<Fighter *> opponents,
        const std::vector<Weapon *> droppedWeapons) override
    {
        assert(getCombatStatus());
        int target = requestGrabTarget(droppedWeapons);
        Weapon *wantedWeapon = droppedWeapons[target];
        addWeapon(wantedWeapon);

        std::cout << *this << " has picked up " << *wantedWeapon << "." << std::endl
                  << std::endl;
        return target;
    }

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    void receiveHealing(const Weapon *healingWeapon, Fighter *healer) override
    {
        assert(getCombatStatus());
        double multiplier = 1.0;
        Element healerElement = healer->getElement();
        Element weaponElement = healingWeapon->getElement();
        if (healerElement.isStrengthening(weaponElement))
        {
            lostHealthMultiplier += 0.4;
            std::cout << *healer << "'s action was significantly more effective because of " << 
            *healer << "'s and " << *healingWeapon << "'s element!" << std::endl;
        }
        if (weaponElement.isStrengthening(elementType))
        {
            multiplier = multiplier + 0.2;
            std::cout << *healer << "'s action was more effective because of " << 
            *healingWeapon << "'s and " << *this << "'s element!" << std::endl;
        }
        if (healerElement.isStrengthening(elementType))
        {
            multiplier = multiplier + 0.2;
            std::cout << *healer << "'s action more effective because of " << 
            *healingWeapon << "'s and " << *this << "'s element!" << std::endl;
        }

        double healingStrength = healingWeapon->getHealingStrength();
        double totalHealing = healingStrength * multiplier;

        totalHealing = min(maxHealth - currentHealth, totalHealing);
        currentHealth += totalHealing;

        std::cout << *this << " received " << totalHealing << " healing from " << *healer << "." << std::endl
                  << *this << " now has " << currentHealth << " health." << std::endl
                  << std::endl;
    }

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack.
    // do not change combat status if below 0 hp here.
    void receiveAttack(const Weapon *damagingWeapon, const Fighter *attacker) override
    {
        assert(getCombatStatus());
        double multiplier = 1.0;
        Element damagingElement = attacker->getElement();
        Element weaponElement = damagingWeapon->getElement();
        if (damagingElement.isEffectiveStrength(weaponElement))
        {
            lostHealthMultiplier += 0.4;
            std::cout << *attacker << "'s action was significantly more effective because of " << 
            *attacker << "'s and " << *damagingWeapon << "'s element!" << std::endl;
        }
        if (weaponElement.isEffectiveStrength(elementType))
        {
            multiplier = multiplier + 0.2;
            std::cout << *attacker << "'s action was more effective because of " << 
            *damagingWeapon << "'s and " << *this << "'s element!" << std::endl;
        }
        else if (elementType.isEffectiveStrength(weaponElement))
        {
            multiplier = multiplier - 0.4;
            std::cout << *attacker << "'s action was significantly weaker because of " << 
            *this << "'s and " << *damagingWeapon << "'s element!" << std::endl;
        }
        if (damagingElement.isEffectiveStrength(elementType))
        {
            multiplier = multiplier + 0.2;
            std::cout << *damagingWeapon << " was more effective because of " << 
            *damagingWeapon << "'s and " << *this << "'s element!" << std::endl;
        }
        else if (elementType.isEffectiveStrength(damagingElement))
        {
            multiplier = multiplier - 0.4;
            std::cout << *attacker << "'s action was significantly weaker because of " << 
            *this << "'s and " << *attacker << "'s element!" << std::endl;
        }

        double attackStrength = damagingWeapon->getAttackStrength();
        double totalDamage = attackStrength * multiplier;
        totalDamage = min(currentHealth, totalDamage);
        currentHealth -= totalDamage;

        std::cout << *this << " received " << totalDamage << " damage from " << *attacker << "." << std::endl
                  << *this << " now has " << currentHealth << " health." << std::endl
                  << std::endl;
    }

    // EFFECTS: Prints weapons of fighter to os
    std::ostream &printWeapons(std::ostream &os) const override
    {
        for (int i = 0; i < numberOfWeapons; ++i)
        {
            os << "Weapon " << i + 1 << ": " << *weapons[i] << std::endl;
        }
        return os;
    }

    // EFFECTS Prints droppedWeapons to stream as "Weapon 1: Excalibur"
    // followed by newline and then "Weapon 2: Gate of Babylon"
    std::ostream &printListOfWeapons(std::ostream &os, const std::vector<Weapon *> weapons) const override
    {
        for (size_t i = 0; i < weapons.size(); ++i)
        {
            Weapon *ithweapon = weapons[i];
            os << "Weapon " << i + 1 << ": " << *ithweapon << std::endl;
        }
        return os;
    }

    // Needed to avoid some compiler errors
    ~Human()
    {
        while (numberOfWeapons != 0)
        {
            deleteWeapon(0);
        }
    }

private:
    std::string name;
    Element elementType;
    std::vector<Weapon *> weapons;
    int numberOfWeapons;
    int activeWeapon;
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
        if (!((size_t)target <= opponents.size() && target > 0))
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
        return target - 1;
    }

    // REQUIRES fighter wants to heal
    // EFFECTS see who fighter wants to heal
    int requestHealTarget(std::vector<Fighter *> allies) const
    {
        std::cout << "These are your allies: " << std::endl;
        printListOfFighters(std::cout, allies);
        std::cout << std::endl;
        std::cout << name << ", choose who to heal (0 for self)" << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(target <= allies.size() && target > 0))
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
        return target - 1;
    }

    // REQUIRES fighter wants to heal or attack
    // EFFECTS see which weapon the fighter wants to use
    int requestActiveWeapon()
    {
        std::cout << "These are your weapons: " << std::endl;
        printWeapons(std::cout);
        std::cout << std::endl;
        std::cout << name << ", choose which weapon to equip by entering a number (0 for same): " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(0 <= target && target <= numberOfWeapons))
        {
            std::cout << std::endl
                      << "\033[2J"
                      << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return requestActiveWeapon();
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        if (target == 0)
        {
            return activeWeapon;
        }
        return target - 1;
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
        if (!(0 <= target && target <= droppedWeapons.size()))
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
        return target - 1;
    }
};

class Warrior : public Fighter
{
public:
    Warrior()
        : name("Default Name"),
          elementType(Element::WATER),
          numberOfWeapons(0),
          activeWeapon(0),
          inCombat(false),
          maxHealth(200.0),
          currentHealth(maxHealth),
          attackStrength(25.0),
          healingStrength(25.0),
          type("Warrior") {}

    Warrior(const std::string &givenName, const Element &element) : Warrior()
    {
        name = givenName;
        elementType = element;
    }

    Warrior(
        const std::string &givenName,
        const Element &element,
        const std::string &weaponType) : Warrior()
    {
        name = givenName;
        elementType = element;
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

    Warrior(
        const std::string &givenName,
        const Element &givenElement,
        std::vector<Weapon *> givenWeapons,
        const int &givenNumberOfWeapons,
        const int &givenActiveWeapon,
        const bool &givenInCombat,
        const double &givenMaxHealth,
        const double &givenCurrentHealth,
        const double &givenAttackStrength,
        const double &givenHealingStrength,
        std::string &givenType)
        : name(givenName),
          elementType(givenElement),
          weapons(givenWeapons),
          numberOfWeapons(givenNumberOfWeapons),
          activeWeapon(givenActiveWeapon),
          inCombat(givenInCombat),
          maxHealth(givenMaxHealth),
          currentHealth(givenCurrentHealth),
          attackStrength(givenAttackStrength),
          healingStrength(givenHealingStrength),
          type(givenType)
    {
    }

    Warrior(const Warrior &other)
    {
        name = other.getName();
        elementType = other.getElement();
        numberOfWeapons = other.getNumberOfWeapons();
        activeWeapon = other.getActiveWeapon();
        inCombat = other.getCombatStatus();
        maxHealth = other.getMaxHealth();
        currentHealth = other.getCurrentHealth();
        attackStrength = other.getAttackStrength();
        healingStrength = other.getHealingStrength();
        type = other.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(other.getOfWeaponK(k));
            weapons.push_back(additionWeapon);
        }
    }

    Warrior &operator=(const Warrior &rhs)
    {
        while (numberOfWeapons != 0)
        {
            deleteWeapon(0);
        }

        name = rhs.getName();
        elementType = rhs.getElement();
        numberOfWeapons = rhs.getNumberOfWeapons();
        activeWeapon = rhs.getActiveWeapon();
        inCombat = rhs.getCombatStatus();
        maxHealth = rhs.getMaxHealth();
        currentHealth = rhs.getCurrentHealth();
        attackStrength = rhs.getAttackStrength();
        healingStrength = rhs.getHealingStrength();
        type = rhs.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(rhs.getOfWeaponK(k));
            weapons.push_back(additionWeapon);
        }

        return *this;
    }

    // EFFECTS returns fighter's name
    const std::string &getName() const override
    {
        return name;
    }

    // EFFECTS returns fighter's type
    const std::string &getType() const override
    {
        return type;
    }

    // REQUIRES fighter has an element
    // EFFECTS  returns element of fighter
    Element getElement() const override
    {
        return elementType;
    }

    // EFFECTS returns number of weapons on fighter
    int getNumberOfWeapons() const override
    {
        return numberOfWeapons;
    }

    // REQUIRES fighter has a weapon
    // EFFECTS  returns active weapon of fighter
    int getActiveWeapon() const override
    {
        return activeWeapon;
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns kth weapons of fighter
    Weapon *getOfWeaponK(const int &k) const override
    {
        assert(getNumberOfWeapons() != 0);
        return weapons[k];
    }

    // EFFECTS  returns combat status of fighter
    bool getCombatStatus() const override
    {
        return inCombat;
    }

    // EFFECTS  returns max health of fighter
    double getMaxHealth() const override
    {
        return maxHealth;
    }

    // EFFECTS  returns current health of fighter
    double getCurrentHealth() const override
    {
        return currentHealth;
    }

    // EFFECTS  returns attackStrength of fighter
    double getAttackStrength() const override
    {
        return attackStrength;
    }

    // EFFECTS  returns healingStrength of fighter
    double getHealingStrength() const override
    {
        return healingStrength;
    }

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    void addWeapon(Weapon *weapon) override
    {
        ++numberOfWeapons;
        Weapon *addedWeapon = WeaponFactory(weapon);
        weapons.push_back(addedWeapon);
        if (activeWeapon == -1)
        {
            activeWeapon = 0;
        }
    }

    // REQUIRES fighter wants to delete a weapon
    // EFFECTS deletes weapon
    void deleteWeapon(const int &weaponIndex)
    {
        --numberOfWeapons;
        delete weapons[weaponIndex];
        weapons.erase(weapons.begin() + weaponIndex);
        if (activeWeapon >= numberOfWeapons)
        {
            activeWeapon = numberOfWeapons - 1;
        }
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's name
    const std::string &getNameOfWeaponK(const int &k) const override
    {
        return weapons[k]->getName();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns element of the kth weapon
    Element getElementOfWeaponK(const int &k) const override
    {
        return weapons[k]->getElement();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns attack strength of the kth weapon
    double getAttackStrengthOfWeaponK(const int &k) const override
    {
        return weapons[k]->getAttackStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns healing strength of the kth weapon
    double getHealingStrengthOfWeaponK(const int &k) const override
    {
        return weapons[k]->getHealingStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's type
    const std::string getTypeOfWeaponK(const int &k) const override
    {
        return weapons[k]->getWeaponType();
    }

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    void changeName(const std::string &newName) override
    {
        name = newName;
    }

    // EFFECTS changes fighter max health
    void changeMaxHealth(const int &newMaxHealth) override
    {
        maxHealth = newMaxHealth;
    }

    // EFFECTS changes fighter current health
    void changeCurrentHealth(const int &newMaxHealth) override
    {
        currentHealth = newMaxHealth;
    }

    // EFFECTS changes fighter attack strength
    void changeAttackStrength(const int &newAttackStrength) override
    {
        attackStrength = newAttackStrength;
    }

    // EFFECTS changes fighter healing strength
    void changeHealingStrength(const int &newHealingStrength) override
    {
        healingStrength = newHealingStrength;
    }

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    void enterCombat() override
    {
        assert(!inCombat);
        inCombat = true;
    }

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    void exitCombat() override
    {
        assert(inCombat);
        inCombat = false;
    }

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

        int highestDamageWeapon = 0;
        int highestDamageAmount = weapons[0]->getAttackStrength();

        for (int i = 0; i < numberOfWeapons; ++i)
        {
            if (weapons[i]->getAttackStrength() > highestDamageAmount)
            {
                highestDamageAmount = weapons[i]->getAttackStrength();
                highestDamageWeapon = i;
            }
        }

        activeWeapon = highestDamageWeapon;

        Element activeweaponElement = weapons[activeWeapon]->getElement();

        int target = 0;
        bool worstTarget = true;
        for (size_t i = 0; i < opponents.size(); ++i)
        {
            Fighter *potentialDefender = opponents[i];
            Element opponentElement = potentialDefender->getElement();

            if (activeweaponElement.isSpecialStrength(opponentElement))
            {
                if (activeweaponElement.isEffectiveStrength(opponentElement))
                {
                    if (worstTarget)
                    {
                        worstTarget = false;
                    }
                    target = i;
                }
            }
            else
            {
                if (worstTarget)
                {
                    worstTarget = false;
                    target = i;
                }
            }
        }

        Weapon *currentWeapon = getOfWeaponK(activeWeapon);

        std::cout << *this << " used " << *currentWeapon << " to attack " << *opponents[target] << std::endl;

        opponents[target]->receiveAttack(currentWeapon, this);

        return target;
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int goGrabWeapon(
        std::vector<Fighter *> allies,
        std::vector<Fighter *> opponents,
        const std::vector<Weapon *> droppedWeapons) override
    {
        assert(getCombatStatus());
        assert(false);
    }

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    void receiveHealing(const Weapon *healingWeapon, Fighter *healer) override
    {
        assert(getCombatStatus());
        double multiplier = 1.0;
        Element healerElement = healer->getElement();
        Element weaponElement = healingWeapon->getElement();
        if (weaponElement.isSpecialResource(healerElement))
        {
            if (weaponElement.isStrengthening(healerElement))
            {
                multiplier = multiplier + 0.2;
            }
            else if (!weaponElement.isStrengthening(healerElement))
            {
                multiplier = multiplier - 0.2;
            }
        }
        if (elementType.isSpecialResource(weaponElement))
        {
            if (elementType.isStrengthening(weaponElement))
            {
                multiplier = multiplier + 0.2;
            }
            else if (!elementType.isStrengthening(weaponElement))
            {
                multiplier = multiplier - 0.2;
            }
        }

        double healingStrength = healingWeapon->getHealingStrength();
        double totalHealing = (healingStrength)*multiplier;

        currentHealth += totalHealing;
        if (currentHealth > maxHealth)
        {
            currentHealth = maxHealth;
        }
        std::cout << *this << " received " << totalHealing << " healing from " << *healer << "." << std::endl
                  << *this << " now has " << currentHealth << " health." << std::endl
                  << std::endl;
    }

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack.
    // do not change combat status if below 0 hp here.
    void receiveAttack(const Weapon *damagingWeapon, const Fighter *attacker) override
    {
        assert(getCombatStatus());
        double multiplier = 1.0;
        Element damagingElement = attacker->getElement();
        Element weaponElement = damagingWeapon->getElement();
        if (weaponElement.isSpecialStrength(damagingElement))
        {
            if (weaponElement.isEffectiveStrength(damagingElement))
            {
                multiplier = multiplier + 0.2;
                std::cout << *damagingWeapon << " was more effective because of " << *attacker << "'s element!" << std::endl;
            }
            else if (!weaponElement.isSpecialStrength(damagingElement))
            {
                multiplier = multiplier - 0.2;
                std::cout << *damagingWeapon << " was less effective because of " << *attacker << "'s element!" << std::endl;
            }
        }
        if (elementType.isSpecialStrength(weaponElement))
        {
            if (elementType.isEffectiveStrength(weaponElement))
            {
                multiplier = multiplier + 0.2;
                std::cout << *damagingWeapon << " was more effective because of " << *this << "'s element!" << std::endl;
            }
            else if (!elementType.isEffectiveStrength(weaponElement))
            {
                multiplier = multiplier - 0.2;
                std::cout << *damagingWeapon << " was less effective because of " << *this << "'s element!" << std::endl;
            }
        }

        double healingStrength = healingWeapon->getHealingStrength();
        double totalDamage = (healingStrength)*multiplier;

        currentHealth += totalDamage;
        if (currentHealth > maxHealth)
        {
            currentHealth = maxHealth;
        }
        std::cout << *this << " received " << totalDamage << " damage from " << *attacker << "." << std::endl
                  << *this << " now has " << currentHealth << " health." << std::endl
                  << std::endl;
    }

    // EFFECTS: Prints weapons of fighter to os
    std::ostream &printWeapons(std::ostream &os) const override
    {
        for (int i = 0; i < numberOfWeapons; ++i)
        {
            os << "Weapon " << i + 1 << ": " << *weapons[i] << std::endl;
        }
        return os;
    }

    // EFFECTS Prints droppedWeapons to stream as "Weapon 1: Excalibur"
    // followed by newline and then "Weapon 2: Gate of Babylon"
    std::ostream &printListOfWeapons(std::ostream &os, const std::vector<Weapon *> weapons) const override
    {
        for (size_t i = 0; i < weapons.size(); ++i)
        {
            Weapon *ithweapon = weapons[i];
            os << "Weapon " << i + 1 << ": " << *ithweapon << std::endl;
        }
        return os;
    }

    // Needed to avoid some compiler errors
    ~Warrior()
    {
        while (numberOfWeapons != 0)
        {
            deleteWeapon(0);
        }
    }

private:
    std::string name;
    Element elementType;
    std::vector<Weapon *> weapons;
    int numberOfWeapons;
    int activeWeapon;
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

    std::string name = copiedFighter->getName();
    Element element = copiedFighter->getElement();

    int numberOfWeapons = copiedFighter->getNumberOfWeapons();

    std::vector<Weapon *> weapons;
    for (int i = 0; i < numberOfWeapons; ++i)
    {
        Weapon *weaponI = copiedFighter->getOfWeaponK(i);
        Weapon *addedWeapon = WeaponFactory(weaponI);
        weapons.push_back(addedWeapon);
    }

    int activeWeapon = copiedFighter->getActiveWeapon();
    bool inCombat = copiedFighter->getCombatStatus();
    double maxHealth = copiedFighter->getMaxHealth();
    double currentHealth = copiedFighter->getCurrentHealth();

    double attackStrength = copiedFighter->getAttackStrength();
    double healingStrength = copiedFighter->getHealingStrength();
    std::string type = copiedFighter->getType();

    if (type == "Human")
    {
        return new Human(
            name, element, weapons, numberOfWeapons, activeWeapon,
            inCombat, maxHealth, currentHealth, attackStrength, healingStrength, type);
    }
    else if (type == "Warrior")
    {
        return new Warrior(
            name, element, weapons, numberOfWeapons, activeWeapon,
            inCombat, maxHealth, currentHealth, attackStrength, healingStrength, type);
    }
    assert(false);
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
        os << "Fighter " << i + 1 << ": " << *fighterI << std::endl;
    }
    return os;
}
