#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Fighter.h"

#include "Weapon.h"
#include "Element.h"

class Fighter
{
public:
    // fighter types
    static constexpr const char *const HUMAN = "Human";
    static constexpr const char *const WARRIOR = "Warrior";
    // list
    static constexpr const char *const FIGHTER_LIST[] = {
        Fighter::HUMAN,
        Fighter::WARRIOR};
    static constexpr const int NUM_FIGHTER_TYPES = 2;

    Fighter()
        : elementType(Element::WATER),
          activeWeapon(-1),
          inCombat(false),
          maxHealth(200.0),
          currentHealth(maxHealth),
          attackStrength(25.0),
          healingStrength(25.0)
    {
    }

    Fighter(const std::string &givenName, const Element &element) : Fighter()
    {
        name = givenName;
        elementType = element;
    }

    Fighter(
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

    Fighter(
        const std::string &givenName,
        const Element &givenElement,
        std::vector<Weapon *> givenWeapons,
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
          activeWeapon(givenActiveWeapon),
          inCombat(givenInCombat),
          maxHealth(givenMaxHealth),
          currentHealth(givenCurrentHealth),
          attackStrength(givenAttackStrength),
          healingStrength(givenHealingStrength),
          type(givenType)
    {
    }

    Fighter(const Fighter &other)
    {
        name = other.name;
        elementType = other.elementType;
        activeWeapon = other.activeWeapon;
        inCombat = other.inCombat;
        maxHealth = other.maxHealth;
        currentHealth = other.currentHealth;
        attackStrength = other.attackStrength;
        healingStrength = other.healingStrength;
        type = other.type;

        for (int k = 0; k < other.weapons.size(); ++k)
        {
            Weapon *additionWeapon = WeaponFactory(other.getOfWeaponK(k));
            weapons.push_back(additionWeapon);
        }
    }

    Fighter &operator=(const Fighter &rhs)
    {
        while (!weapons.empty())
        {
            deleteWeapon(0);
        }

        name = rhs.name;
        elementType = rhs.elementType;
        activeWeapon = rhs.activeWeapon;
        inCombat = rhs.inCombat;
        maxHealth = rhs.maxHealth;
        currentHealth = rhs.currentHealth;
        attackStrength = rhs.attackStrength;
        healingStrength = rhs.healingStrength;
        type = rhs.type;

        for (int k = 0; rhs.weapons.size(); ++k)
        {
            Weapon *additionWeapon = WeaponFactory(rhs.getOfWeaponK(k));
            weapons.push_back(additionWeapon);
        }

        return *this;
    }

    // EFFECTS returns fighter's name
    virtual const std::string &getName() const
    {
        return name;
    }

    // EFFECTS returns fighter's type
    virtual const std::string &getType() const
    {
        return type;
    };

    // REQUIRES fighter has an element
    // EFFECTS  returns element of fighter
    virtual Element getElement() const
    {
        return elementType;
    };

    // EFFECTS returns number of weapons on fighter
    virtual int getNumberOfWeapons() const
    {
        return weapons.size();
    };

    // REQUIRES fighter has a weapon
    // EFFECTS  returns active weapon of fighter
    virtual int getActiveWeapon() const
    {
        return activeWeapon;
    };

    // EFFECTS returns kth weapons of fighter
    virtual Weapon *getOfWeaponK(const int &k) const
    {
        return weapons[k];
    };

    // EFFECTS  returns combat status of fighter
    virtual bool getCombatStatus() const
    {
        return inCombat;
    };

    // EFFECTS  returns max health of fighter
    virtual double getMaxHealth() const
    {
        return maxHealth;
    };

    // EFFECTS  returns current health of fighter
    virtual double getCurrentHealth() const
    {
        return currentHealth;
    };

    // EFFECTS  returns attackStrength of fighter
    virtual double getAttackStrength() const
    {
        return attackStrength;
    };

    // EFFECTS  returns healingStrength of fighter
    virtual double getHealingStrength() const
    {
        return healingStrength;
    };

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    virtual void addWeapon(Weapon *weapon)
    {
        Weapon *addedWeapon = WeaponFactory(weapon);
        weapons.push_back(addedWeapon);
        if (activeWeapon == -1)
        {
            activeWeapon = 0;
        }
    };

    // REQUIRES fighter wants to delete a weapon and 0 <= weaponIndex < weapons.size()
    // EFFECTS deletes weapon
    virtual void deleteWeapon(const int &weaponIndex)
    {
        assert(0 <= weaponIndex && weaponIndex < weapons.size());
        delete weapons[weaponIndex];
        weapons.erase(weapons.begin() + weaponIndex);
        activeWeapon = min(activeWeapon, weapons.size() - 1)
    };

    // REQUIRES 0 <= k < weapons.size()
    // EFFECTS returns the kth weapon's name
    virtual const std::string &getNameOfWeaponK(const int &k) const
    {
        return weapons[k]->getName();
    };

    // REQUIRES 0 <= k < weapons.size()
    // EFFECTS  returns element of the kth weapon
    virtual Element getElementOfWeaponK(const int &k) const
    {
        return weapons[k]->getElement();
    };

    // EFFECTS  returns attack strength of active weapon
    virtual Element getElementOfActiveWeapon() const
    {
        return getElementOfWeaponK(activeWeapon);
    };

    /// REQUIRES 0 <= k < weapons.size()
    // EFFECTS  returns attack strength of the kth weapon
    virtual double getAttackStrengthOfWeaponK(const int &k) const
    {
        return weapons[k]->getAttackStrength();
    };

    // REQUIRES 0 <= k < weapons.size()
    // EFFECTS  returns healing strength of the kth weapon
    virtual double getHealingStrengthOfWeaponK(const int &k) const
    {
        return weapons[k]->getHealingStrength();
    };

    // REQUIRES 0 <= k < weapons.size()
    // EFFECTS returns the kth weapon's type
    virtual const std::string getTypeOfWeaponK(const int &k) const
    {
        return weapons[k]->getWeaponType();
    };

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    virtual void changeName(const std::string &newName)
    {
        name = newName;
    };

    // EFFECTS changes fighter max health
    virtual void changeMaxHealth(const int &newMaxHealth){
        maxHealth = newMaxHealth};

    // EFFECTS changes fighter current health
    virtual void changeCurrentHealth(const int &newMaxHealth)
    {
        currentHealth = newMaxHealth;
    };

    // EFFECTS changes fighter attack strength
    virtual void changeAttackStrength(const int &newAttackStrength)
    {
        attackStrength = newAttackStrength;
    };

    // EFFECTS changes fighter healing strength
    virtual void changeHealingStrength(const int &newHealingStrength)
    {
        healingStrength = newHealingStrength;
    };

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    virtual void enterCombat()
    {
        assert(!inCombat);
        inCombat = true;
    };

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    virtual void exitCombat()
    {
        assert(inCombat);
        inCombat = false;
    };

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    virtual std::string requestAction(
        std::vector<Fighter *> allies,
        std::vector<Fighter *> opponents,
        const std::vector<Weapon *> droppedWeapons) = 0;

    // REQUIRES fighter wants to heal
    // MODIFIES allies
    // EFFECTS  make fighter heal allies or self
    virtual void goHeal(std::vector<Fighter *> allies) = 0;

    // REQUIRES ally is in combat and weapon belongs to fighter
    // MODIFIES allies
    // EFFECTS make fighter heal allies or self
    virtual void goHealAllyWithWeapon(Fighter *ally, Weapon *weapon)
    {
        std::cout << *this << " used " << *weapon << " to heal " << *ally << std::endl;

        ally->receiveHealing(weapon, this);

        Element weaponElement = weapon->getElement();
        double lostHealthMultiplier = 0;
        if (
            weaponElement.isBeneficialResourceTo(ally->getElement()) ||
            elementType.isBeneficialResourceTo(ally->getElement()))
        {
            lostHealthMultiplier += 0.1;
        }
        if (elementType.isBeneficialResourceTo(weaponElement))
        {
            lostHealthMultiplier += 0.2;
        }
        if (lostHealthMultiplier)
        {
            double lostHealth = losthealthMultiplier * maxHealth;
            lostHealth = max(currentHealth, lostHealth);
            std::cout << *this << " lost " << lostHealth << " when healing!" << std::endl;
        }
    };

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    virtual int goAttack(std::vector<Fighter *> opponents) = 0;

    // REQUIRES fighter wants to fight
    // MODIFIES opponent
    // EFFECTS  make fighter attack opponent.
    virtual void goAttackTargetWithWeapon(Fighter *opponent, Weapon *weapon)
    {
        std::cout << *this << " used " << *weapon << " to attack " << *opponents[target] << std::endl;

        opponent->receiveAttack(weapon, this);

        Element weaponElement = weapon->getElement();
        if (elementType.isBeneficialResourceTo(weaponElement))
        {
            lostHealthMultiplier += 0.4;
        }
        if (lostHealthMultiplier)
        {
            double lostHealth = losthealthMultiplier * maxHealth;
            lostHealth = max(currentHealth, lostHealth);
            std::cout << *this << " lost " << lostHealth << " when attacking!" << std::endl;
        }
    };

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    virtual int goGrabWeapon(
        std::vector<Fighter *> allies,
        std::vector<Fighter *> opponents,
        const std::vector<Weapon *> droppedWeapons) = 0;

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    virtual void goGrabThisWeapon(Weapon *droppedWeapon)
    {
        addWeapon(wantedWeapon);
        std::cout << *this << " has picked up " << *wantedWeapon << "." << std::endl
                  << std::endl;
    };

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    virtual void receiveHealing(const Weapon *healingWeapon, Fighter *healer)
    {
        assert(getCombatStatus());
        double multiplier = 1.0;
        Element healerElement = healer->getElement();
        Element weaponElement = healingWeapon->getElement();
        if (healerElement.isBeneficialResourceTo(weaponElement))
        {
            lostHealthMultiplier += 0.4;
            std::cout << *healer << "'s action was significantly more effective because of " << *healer << "'s and " << *healingWeapon << "'s element!" << std::endl;
        }
        if (weaponElement.isBeneficialResourceTo(elementType))
        {
            multiplier = multiplier + 0.2;
            std::cout << *healer << "'s action was more effective because of " << *healingWeapon << "'s and " << *this << "'s element!" << std::endl;
        }
        if (healerElement.isBeneficialResourceTo(elementType))
        {
            multiplier = multiplier + 0.2;
            std::cout << *healer << "'s action more effective because of " << *healingWeapon << "'s and " << *this << "'s element!" << std::endl;
        }

        double healingStrength = healingWeapon->getHealingStrength();
        double totalHealing = healingStrength * multiplier;

        totalHealing = min(maxHealth - currentHealth, totalHealing);
        currentHealth += totalHealing;

        std::cout << *this << " received " << totalHealing << " healing from " << *healer << "." << std::endl
                  << *this << " now has " << currentHealth << " health." << std::endl
                  << std::endl;
    };

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack
    // do not change combat status if below 0 hp here.
    virtual void receiveAttack(const Weapon *damagingWeapon, const Fighter *attacker)
    {
        assert(getCombatStatus());
        double multiplier = 1.0;
        Element damagingElement = attacker->getElement();
        Element weaponElement = damagingWeapon->getElement();
        if (damagingElement.isEffectiveAgainst(weaponElement))
        {
            lostHealthMultiplier += 0.4;
            std::cout << *attacker << "'s action was significantly more effective because of " << *attacker << "'s and " << *damagingWeapon << "'s element!" << std::endl;
        }
        if (weaponElement.isEffectiveAgainst(elementType))
        {
            multiplier = multiplier + 0.2;
            std::cout << *attacker << "'s action was more effective because of " << *damagingWeapon << "'s and " << *this << "'s element!" << std::endl;
        }
        else if (weaponElement.isWeakAgainst(weaponElement))
        {
            multiplier = multiplier - 0.4;
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
        totalDamage = min(currentHealth, totalDamage);
        currentHealth -= totalDamage;

        std::cout << *this << " received " << totalDamage << " damage from " << *attacker << "." << std::endl
                  << *this << " now has " << currentHealth << " health." << std::endl
                  << std::endl;
    };

    // EFFECTS: Prints weapons of fighter to os
    virtual std::ostream &printWeapons(std::ostream &os) const
    {
        for (int i = 0; i < weapons.size(); ++i)
        {
            os << "Weapon " << i << ": " << *weapons[i] << std::endl;
        }
        return os;
    };

    virtual std::ostream &printListOfWeapons(
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
    virtual ~Fighter()
    {
        while (!weapons.empty())
        {
            deleteWeapon(0);
        }
    }

private:
    std::string name;
    Element elementType;
    std::vector<Weapon *> weapons;
    int activeWeapon;
    bool inCombat;
    double maxHealth;
    double currentHealth;
    double attackStrength;
    double healingStrength;
    std::string type;
};

class Human : public Fighter
{
public:
    Human()
        : Fighter(),
          name("Angel"),
          type("Human") {}

    Human(const std::string &givenName, const Element &element) : Human()
    {
        name = givenName;
        elementType = element;
    }

    Warrior(const std::string &givenName, const Element &element)
        : Warrior(givenName, element)
    {
    }

    Warrior(
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
        const int &givenActiveWeapon,
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
              givenActiveWeapon,
              givenInCombat,
              givenMaxHealth,
              givenCurrentHealth,
              givenAttackStrength,
              givenHealingStrength,
              givenType)
    {
    }

    Human(const Human &other) : Fighter(other) {}

    Human &operator=(const Human &rhs) : Fighter(rhs) {}

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
        activeWeapon = requestActiveWeaponK();
        Weapon *currentWeapon = getOfWeaponK(activeWeapon);
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
        activeWeapon = requestActiveWeaponK();
        Weapon *currentWeapon = getOfWeaponK(activeWeapon);
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
    int requestActiveWeaponK()
    {
        std::cout << "These are your weapons: " << std::endl;
        printWeapons(std::cout);
        std::cout << std::endl;
        std::cout << name << ", choose which weapon to equip by entering a number (-1 for same): " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(-1 <= target && target < weapons.size()))
        {
            std::cout << std::endl
                      << "\033[2J"
                      << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return requestActiveWeaponK();
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        return target == -1 ? activeWeapon : target;
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
        : Warrior(givenName, element)
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
        const int &givenActiveWeapon,
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
              givenActiveWeapon,
              givenInCombat,
              givenMaxHealth,
              givenCurrentHealth,
              givenAttackStrength,
              givenHealingStrength,
              givenType)
    {
    }

    Warrior(const Warrior &other) : Fighter(other) {}

    Warrior &operator=(const Warrior &rhs) : Fighter(rhs) {}

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

        int activeWeapon = getHighestDamageWeapon();

        Element activeweaponElement = weapons[activeWeapon]->getElement();

        int target = 0;
        int bestAdvantage = INT_MIN;
        for (size_t i = 0; i < opponents.size(); ++i)
        {
            Fighter *potentialDefender = opponents[i];
            Element opponentElement = potentialDefender->getElement();
            int potentialAdvantage = 0;

            if (activeweaponElement.isEffectiveAgainst(opponentElement))
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
            Element opponentWeaponElement = potentialDefender->getElementOfActiveWeapon();
            if (opponentWeaponElement.isEffectiveAgainst(elementType))
            {
                potentialAdvantage -= 4;
            }

            if (potentialAdvantage > bestAdvantage)
            {
                bestAdvantage = potentialAdvantage;
                target = i;
            }
        }

        Weapon *currentWeapon = getOfWeaponK(activeWeapon);
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
    int activeWeapon;
    bool inCombat;
    double maxHealth;
    double currentHealth;

    double attackStrength;
    double healingStrength;
    std::string type;

    // REQUIRES fighter has at least 1 weapon
    // EFFECTS returns highest damage weapon
    int getHighestDamageWeapon()
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

        return highestDamageWeapon;
    }
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

    std::string name = copiedFighter->name;
    Element element = copiedFighter->element);

    std::vector<Weapon *> weapons;
    for (int i = 0; i < copiedFighter->weapons.size(); ++i)
    {
        Weapon *weaponI = copiedFighter->weapons[i];
        Weapon *addedWeapon = WeaponFactory(weaponI);
        weapons.push_back(addedWeapon);
    }

    int activeWeapon = copiedFighter->activeWeapon];
    bool inCombat = copiedFighter->inCombat;
    double maxHealth = copiedFighter->maxHealth;
    double currentHealth = copiedFighter->currentHealth;

    double attackStrength = copiedFighter->attackStrength;
    double healingStrength = copiedFighter->healingStrength;
    std::string type = copiedFighter->type;

    if (type == "Human")
    {
        return new Human(
            name, element, weapons, activeWeapon,
            inCombat, maxHealth, currentHealth, attackStrength, healingStrength, type);
    }
    else if (type == "Warrior")
    {
        return new Warrior(
            name, element, weapons, activeWeapon,
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
        os << "Fighter " << i << ": " << *fighterI << std::endl;
    }
    return os;
}
