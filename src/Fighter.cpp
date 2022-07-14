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
    Human() : name("Angel"), elementType(Element::WATER),
              numberOfWeapons(0), activeWeapon(-1), inCombat(false), maxHealth(200.0),
              current_health(maxHealth), attack_strength(25.0),
              healing_strength(25.0), type("Human") {}

    Human(const std::string &givenName, const Element &element) : Human()
    {
        name = givenName;
        elementType = element;
    }

    Human(const std::string &givenName, const Element &element,
          const std::string &weaponType) : Human()
    {
        name = givenName;
        elementType = element;
        Weapon *defaultWeapon;
        if (weaponType == Weapon::WEAPON_STAFF)
        {
            defaultWeapon = WeaponFactory(Weapon::WEAPON_STAFF);
        }
        else if (weaponType == Weapon::WEAPON_SPEAR)
        {
            defaultWeapon = WeaponFactory(Weapon::WEAPON_STAFF);
        }
        else if (weaponType == Weapon::WEAPON_CROSS)
        {
            defaultWeapon = WeaponFactory(Weapon::WEAPON_CROSS);
        }
        else
        {
            assert(false);
        }
        add_weapon(defaultWeapon);
    }

    Human(const std::string &givenName, const Element &givenElement,
          std::vector<Weapon *> givenWeapons, const int &givenNumberOfWeapons,
          const int &givenActiveWeapon, const bool &givenInCombat,
          const double &givenMaxHealth, const double &givenCurrentHealth,
          const double &givenAttackStrength, const double &givenHealingStrength,
          std::string &givenType) : name(givenName), elementType(givenElement),
                                     weapons(givenWeapons), numberOfWeapons(givenNumberOfWeapons),
                                     activeWeapon(givenActiveWeapon), inCombat(givenInCombat),
                                     maxHealth(givenMaxHealth), current_health(givenCurrentHealth),
                                     attack_strength(givenAttackStrength), healing_strength(givenHealingStrength),
                                     type(givenType)
    {
    }

    Human(const Human &other)
    {
        name = other.getName();
        elementType = other.getElement();
        numberOfWeapons = other.getNumberOfWeapons();
        activeWeapon = other.getActiveWeapon();
        inCombat = other.get_combat_status();
        maxHealth = other.get_maxHealth();
        current_health = other.getCurrentHealth();
        attack_strength = other.getAttackStrength();
        healing_strength = other.getHealingStrength();
        type = other.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(other.getWeaponK(k));
            weapons.push_back(additionWeapon);
        }
    }

    Human &operator=(const Human &rhs)
    {
        while (numberOfWeapons != 0)
        {
            delete_weapon(0);
        }

        name = rhs.getName();
        elementType = rhs.getElement();
        numberOfWeapons = rhs.getNumberOfWeapons();
        activeWeapon = rhs.getActiveWeapon();
        inCombat = rhs.get_combat_status();
        maxHealth = rhs.get_maxHealth();
        current_health = rhs.getCurrentHealth();
        attack_strength = rhs.getAttackStrength();
        healing_strength = rhs.getHealingStrength();
        type = rhs.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(rhs.getWeaponK(k));
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
    Weapon *getWeaponK(const int &k) const override
    {
        assert(getNumberOfWeapons() != 0);
        return weapons[k];
    }

    // EFFECTS  returns combat status of fighter
    bool get_combat_status() const override
    {
        return inCombat;
    }

    // EFFECTS  returns max health of fighter
    double get_maxHealth() const override
    {
        return maxHealth;
    }

    // EFFECTS  returns current health of fighter
    double getCurrentHealth() const override
    {
        return current_health;
    }

    // EFFECTS  returns attack_strength of fighter
    double getAttackStrength() const override
    {
        return attack_strength;
    }

    // EFFECTS  returns healing_strength of fighter
    double getHealingStrength() const override
    {
        return healing_strength;
    }

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    void add_weapon(Weapon *weapon) override
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
    void delete_weapon(const int &weapon_index)
    {
        --numberOfWeapons;
        delete weapons[weapon_index];
        weapons.erase(weapons.begin() + weapon_index);
        if (activeWeapon >= numberOfWeapons)
        {
            activeWeapon = numberOfWeapons - 1;
        }
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's name
    const std::string &get_k_name(const int &k) const override
    {
        return weapons[k]->getName();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns element of the kth weapon
    Element get_k_element(const int &k) const override
    {
        return weapons[k]->getElement();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns attack strength of the kth weapon
    double get_k_attack_strength(const int &k) const override
    {
        return weapons[k]->getAttackStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns healing strength of the kth weapon
    double get_k_healing_strength(const int &k) const override
    {
        return weapons[k]->getHealingStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's type
    const std::string getWeaponK_type(const int &k) const override
    {
        return weapons[k]->get_weaponType();
    }

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    void change_name(const std::string &name_change) override
    {
        name = name_change;
    }

    // EFFECTS changes fighter max health
    void change_maxHealth(const int &health_change) override
    {
        maxHealth = health_change;
    }

    // EFFECTS changes fighter current health
    void change_current_health(const int &health_change) override
    {
        current_health = health_change;
    }

    // EFFECTS changes fighter attack strength
    void change_attack_strength(const int &strength_change) override
    {
        attack_strength = strength_change;
    }

    // EFFECTS changes fighter healing strength
    void change_healing_strength(const int &healing_change) override
    {
        healing_strength = healing_change;
    }

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    void enter_combat() override
    {
        assert(!inCombat);
        inCombat = true;
    }

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    void exit_combat() override
    {
        assert(inCombat);
        inCombat = false;
    }

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    std::string requestAction(std::vector<Fighter *> allies, std::vector<Fighter *> opponents,
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
    void go_heal(std::vector<Fighter *> allies) override
    {
        assert(get_combat_status());
        int target = request_heal_target(allies);
        activeWeapon = request_activeWeapon();
        Weapon *current_weapon = getWeaponK(activeWeapon);

        std::cout << *this << " used " << *current_weapon << " to heal " << *allies[target] << std::endl;

        allies[target]->receive_healing(current_weapon, this);

        Element weapon_element = current_weapon->getElement();
        if (weapon_element.isStrengthening(elementType))
        {
            if (current_health >= 0.2 * maxHealth)
            {
                current_health -= 0.1 * maxHealth;
            }
        }
    }

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    int goAttack(std::vector<Fighter *> opponents) override
    {
        assert(get_combat_status());
        int target = request_attack_target(opponents);
        activeWeapon = request_activeWeapon();
        Weapon *current_weapon = getWeaponK(activeWeapon);

        std::cout << *this << " used " << *current_weapon << " to attack " << *opponents[target] << std::endl;

        opponents[target]->receive_attack(current_weapon, this);

        return target;
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int go_grab_weapon(std::vector<Fighter *> allies, std::vector<Fighter *> opponents,
                       const std::vector<Weapon *> droppedWeapons) override
    {
        assert(get_combat_status());
        int target = request_grab_target(droppedWeapons);
        Weapon *wanted_weapon = droppedWeapons[target];
        add_weapon(wanted_weapon);

        std::cout << *this << " has picked up " << *wanted_weapon << "." << std::endl
                  << std::endl;
        return target;
    }

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    void receive_healing(const Weapon *healing_weapon, Fighter *healer) override
    {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element healer_element = healer->getElement();
        Element weapon_element = healing_weapon->getElement();
        if (weapon_element.isSpecialResource(healer_element))
        {
            if (weapon_element.isStrengthening(healer_element))
            {
                multiplier = multiplier + 0.2;
                std::cout << *healing_weapon << " was more effective because of " << *healer << "'s element!" << std::endl;
                std::cout << *healer << " lost " << 0.1 * maxHealth << " when healing!" << std::endl;
            }
            else if (!weapon_element.isStrengthening(healer_element))
            {
                multiplier = multiplier - 0.2;
                std::cout << *healing_weapon << " was less effective because of " << *healer << "'s element!" << std::endl;
            }
        }
        if (elementType.isSpecialResource(weapon_element))
        {
            if (elementType.isStrengthening(weapon_element))
            {
                multiplier = multiplier + 0.2;
                std::cout << *healing_weapon << " was more effective because of " << *this << "'s element!" << std::endl;
            }
            else if (!elementType.isStrengthening(weapon_element))
            {
                multiplier = multiplier - 0.2;
                std::cout << *healing_weapon << " was less effective because of " << *this << "'s element!" << std::endl;
            }
        }

        double healing_strength = healing_weapon->getHealingStrength();
        double total_healing = (healing_strength)*multiplier;

        current_health += total_healing;
        if (current_health > maxHealth)
        {
            current_health = maxHealth;
        }

        std::cout << *this << " received " << total_healing << " healing from " << *healer << "." << std::endl
                  << *this << " now has " << current_health << " health." << std::endl
                  << std::endl;
    }

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack.
    // do not change combat status if below 0 hp here.
    void receive_attack(const Weapon *damaging_weapon, const Fighter *attacker) override
    {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element damaging_element = attacker->getElement();
        Element weapon_element = damaging_weapon->getElement();
        if (weapon_element.isSpecialStrength(damaging_element))
        {
            if (weapon_element.is_effective_strength(damaging_element))
            {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *attacker << "'s element!" << std::endl;
            }
            else if (!weapon_element.isSpecialStrength(damaging_element))
            {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *attacker << "'s element!" << std::endl;
            }
        }
        if (elementType.isSpecialStrength(weapon_element))
        {
            if (elementType.is_effective_strength(weapon_element))
            {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *this << "'s element!" << std::endl;
            }
            else if (!elementType.is_effective_strength(weapon_element))
            {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *this << "'s element!" << std::endl;
            }
        }

        double healing_strength = damaging_weapon->getAttackStrength();
        double total_damage = (healing_strength)*multiplier;

        current_health -= total_damage;
        if (current_health <= 0)
        {
            current_health = 0;
        }

        std::cout << *this << " received " << total_damage << " damage from " << *attacker << "." << std::endl
                  << *this << " now has " << current_health << " health." << std::endl
                  << std::endl;
    }

    // EFFECTS: Prints weapons of fighter to os
    std::ostream &print_weapons(std::ostream &os) const override
    {
        for (int i = 0; i < numberOfWeapons; ++i)
        {
            os << "Weapon " << i + 1 << ": " << *weapons[i] << std::endl;
        }
        return os;
    }

    // EFFECTS Prints droppedWeapons to stream as "Weapon 1: Excalibur"
    // followed by newline and then "Weapon 2: Gate of Babylon"
    std::ostream &print_list_of_weapons(std::ostream &os, const std::vector<Weapon *> weapons) const override
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
            delete_weapon(0);
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
    double current_health;

    double attack_strength;
    double healing_strength;
    std::string type;

    // REQUIRES fighter wants to attack
    // EFFECTS see who fighter wants to attack
    int request_attack_target(std::vector<Fighter *> opponents) const
    {
        std::cout << "These are your opponents: " << std::endl;
        print_list_of_fighters(std::cout, opponents);
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
            return request_attack_target(opponents);
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        return target - 1;
    }

    // REQUIRES fighter wants to heal
    // EFFECTS see who fighter wants to heal
    int request_heal_target(std::vector<Fighter *> allies) const
    {
        std::cout << "These are your allies: " << std::endl;
        print_list_of_fighters(std::cout, allies);
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
            return request_heal_target(allies);
        }
        std::cout << std::endl
                  << "\033[2J"
                  << "\033[1;1H";
        return target - 1;
    }

    // REQUIRES fighter wants to heal or attack
    // EFFECTS see which weapon the fighter wants to use
    int request_activeWeapon()
    {
        std::cout << "These are your weapons: " << std::endl;
        print_weapons(std::cout);
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
            return request_activeWeapon();
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
    int request_grab_target(const std::vector<Weapon *> droppedWeapons) const
    {
        std::cout << "These are the dropped weapons: " << std::endl;
        print_list_of_weapons(std::cout, droppedWeapons);
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
            return request_grab_target(droppedWeapons);
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
    Warrior() : name("Default Name"), elementType(Element::WATER),
                numberOfWeapons(0), activeWeapon(0), inCombat(false), maxHealth(200.0),
                current_health(maxHealth), attack_strength(25.0),
                healing_strength(25.0), type("Warrior") {}

    Warrior(const std::string &givenName, const Element &element) : Warrior()
    {
        name = givenName;
        elementType = element;
    }

    Warrior(const std::string &givenName, const Element &element,
            const std::string &weaponType) : Warrior()
    {
        name = givenName;
        elementType = element;
        Weapon *defaultWeapon;
        if (weaponType == Weapon::WEAPON_STAFF)
        {
            defaultWeapon = WeaponFactory(Weapon::WEAPON_STAFF);
        }
        else if (weaponType == Weapon::WEAPON_SPEAR)
        {
            defaultWeapon = WeaponFactory(Weapon::WEAPON_STAFF);
        }
        else if (weaponType == Weapon::WEAPON_CROSS)
        {
            defaultWeapon = WeaponFactory(Weapon::WEAPON_CROSS);
        }
        else
        {
            assert(false);
        }
        add_weapon(defaultWeapon);
    }

    Warrior(const std::string &givenName, const Element &givenElement,
            std::vector<Weapon *> givenWeapons, const int &givenNumberOfWeapons,
            const int &givenActiveWeapon, const bool &givenInCombat,
            const double &givenMaxHealth, const double &givenCurrentHealth,
            const double &givenAttackStrength, const double &givenHealingStrength,
            std::string &givenType) : name(givenName), elementType(givenElement),
                                       weapons(givenWeapons), numberOfWeapons(givenNumberOfWeapons),
                                       activeWeapon(givenActiveWeapon), inCombat(givenInCombat),
                                       maxHealth(givenMaxHealth), current_health(givenCurrentHealth),
                                       attack_strength(givenAttackStrength), healing_strength(givenHealingStrength),
                                       type(givenType)
    {
    }

    Warrior(const Warrior &other)
    {
        name = other.getName();
        elementType = other.getElement();
        numberOfWeapons = other.getNumberOfWeapons();
        activeWeapon = other.getActiveWeapon();
        inCombat = other.get_combat_status();
        maxHealth = other.get_maxHealth();
        current_health = other.getCurrentHealth();
        attack_strength = other.getAttackStrength();
        healing_strength = other.getHealingStrength();
        type = other.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(other.getWeaponK(k));
            weapons.push_back(additionWeapon);
        }
    }

    Warrior &operator=(const Warrior &rhs)
    {
        while (numberOfWeapons != 0)
        {
            delete_weapon(0);
        }

        name = rhs.getName();
        elementType = rhs.getElement();
        numberOfWeapons = rhs.getNumberOfWeapons();
        activeWeapon = rhs.getActiveWeapon();
        inCombat = rhs.get_combat_status();
        maxHealth = rhs.get_maxHealth();
        current_health = rhs.getCurrentHealth();
        attack_strength = rhs.getAttackStrength();
        healing_strength = rhs.getHealingStrength();
        type = rhs.getType();

        for (int k = 0; numberOfWeapons; ++k)
        {
            Weapon *additionWeapon = WeaponFactory(rhs.getWeaponK(k));
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
    Weapon *getWeaponK(const int &k) const override
    {
        assert(getNumberOfWeapons() != 0);
        return weapons[k];
    }

    // EFFECTS  returns combat status of fighter
    bool get_combat_status() const override
    {
        return inCombat;
    }

    // EFFECTS  returns max health of fighter
    double get_maxHealth() const override
    {
        return maxHealth;
    }

    // EFFECTS  returns current health of fighter
    double getCurrentHealth() const override
    {
        return current_health;
    }

    // EFFECTS  returns attack_strength of fighter
    double getAttackStrength() const override
    {
        return attack_strength;
    }

    // EFFECTS  returns healing_strength of fighter
    double getHealingStrength() const override
    {
        return healing_strength;
    }

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    void add_weapon(Weapon *weapon) override
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
    void delete_weapon(const int &weapon_index)
    {
        --numberOfWeapons;
        delete weapons[weapon_index];
        weapons.erase(weapons.begin() + weapon_index);
        if (activeWeapon >= numberOfWeapons)
        {
            activeWeapon = numberOfWeapons - 1;
        }
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's name
    const std::string &get_k_name(const int &k) const override
    {
        return weapons[k]->getName();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns element of the kth weapon
    Element get_k_element(const int &k) const override
    {
        return weapons[k]->getElement();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns attack strength of the kth weapon
    double get_k_attack_strength(const int &k) const override
    {
        return weapons[k]->getAttackStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns healing strength of the kth weapon
    double get_k_healing_strength(const int &k) const override
    {
        return weapons[k]->getHealingStrength();
    }

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's type
    const std::string getWeaponK_type(const int &k) const override
    {
        return weapons[k]->get_weaponType();
    }

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    void change_name(const std::string &name_change) override
    {
        name = name_change;
    }

    // EFFECTS changes fighter max health
    void change_maxHealth(const int &health_change) override
    {
        maxHealth = health_change;
    }

    // EFFECTS changes fighter current health
    void change_current_health(const int &health_change) override
    {
        current_health = health_change;
    }

    // EFFECTS changes fighter attack strength
    void change_attack_strength(const int &strength_change) override
    {
        attack_strength = strength_change;
    }

    // EFFECTS changes fighter healing strength
    void change_healing_strength(const int &healing_change) override
    {
        healing_strength = healing_change;
    }

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    void enter_combat() override
    {
        assert(!inCombat);
        inCombat = true;
    }

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    void exit_combat() override
    {
        assert(inCombat);
        inCombat = false;
    }

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    std::string requestAction(std::vector<Fighter *> allies, std::vector<Fighter *> opponents,
                               const std::vector<Weapon *> droppedWeapons) override
    {
        std::string response = "Attack";
        return response;
    }

    // REQUIRES fighter wants to heal
    // MODIFIES allies
    // EFFECTS  make fighter heal allies or self
    void go_heal(std::vector<Fighter *> allies) override
    {
        assert(get_combat_status());
        assert(false);
    }

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    int goAttack(std::vector<Fighter *> opponents) override
    {
        assert(get_combat_status());

        int highest_damage_weapon = 0;
        int highest_damage_amount = weapons[0]->getAttackStrength();

        for (int i = 0; i < numberOfWeapons; ++i)
        {
            if (weapons[i]->getAttackStrength() > highest_damage_amount)
            {
                highest_damage_amount = weapons[i]->getAttackStrength();
                highest_damage_weapon = i;
            }
        }

        activeWeapon = highest_damage_weapon;

        Element activeWeapon_element = weapons[activeWeapon]->getElement();

        int target = 0;
        bool worst_target = true;
        for (size_t i = 0; i < opponents.size(); ++i)
        {
            Fighter *potential_defender = opponents[i];
            Element opponent_element = potential_defender->getElement();

            if (activeWeapon_element.isSpecialStrength(opponent_element))
            {
                if (activeWeapon_element.is_effective_strength(opponent_element))
                {
                    if (worst_target)
                    {
                        worst_target = false;
                    }
                    target = i;
                }
            }
            else
            {
                if (worst_target)
                {
                    worst_target = false;
                    target = i;
                }
            }
        }

        Weapon *current_weapon = getWeaponK(activeWeapon);

        std::cout << *this << " used " << *current_weapon << " to attack " << *opponents[target] << std::endl;

        opponents[target]->receive_attack(current_weapon, this);

        return target;
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int go_grab_weapon(std::vector<Fighter *> allies, std::vector<Fighter *> opponents,
                       const std::vector<Weapon *> droppedWeapons) override
    {
        assert(get_combat_status());
        assert(false);
    }

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    void receive_healing(const Weapon *healing_weapon, Fighter *healer) override
    {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element healer_element = healer->getElement();
        Element weapon_element = healing_weapon->getElement();
        if (weapon_element.isSpecialResource(healer_element))
        {
            if (weapon_element.isStrengthening(healer_element))
            {
                multiplier = multiplier + 0.2;
            }
            else if (!weapon_element.isStrengthening(healer_element))
            {
                multiplier = multiplier - 0.2;
            }
        }
        if (elementType.isSpecialResource(weapon_element))
        {
            if (elementType.isStrengthening(weapon_element))
            {
                multiplier = multiplier + 0.2;
            }
            else if (!elementType.isStrengthening(weapon_element))
            {
                multiplier = multiplier - 0.2;
            }
        }

        double healing_strength = healing_weapon->getHealingStrength();
        double total_healing = (healing_strength)*multiplier;

        current_health += total_healing;
        if (current_health > maxHealth)
        {
            current_health = maxHealth;
        }
        std::cout << *this << " received " << total_healing << " healing from " << *healer << "." << std::endl
                  << *this << " now has " << current_health << " health." << std::endl
                  << std::endl;
    }

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack.
    // do not change combat status if below 0 hp here.
    void receive_attack(const Weapon *damaging_weapon, const Fighter *attacker) override
    {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element damaging_element = attacker->getElement();
        Element weapon_element = damaging_weapon->getElement();
        if (weapon_element.isSpecialStrength(damaging_element))
        {
            if (weapon_element.is_effective_strength(damaging_element))
            {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *attacker << "'s element!" << std::endl;
            }
            else if (!weapon_element.isSpecialStrength(damaging_element))
            {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *attacker << "'s element!" << std::endl;
            }
        }
        if (elementType.isSpecialStrength(weapon_element))
        {
            if (elementType.is_effective_strength(weapon_element))
            {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *this << "'s element!" << std::endl;
            }
            else if (!elementType.is_effective_strength(weapon_element))
            {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *this << "'s element!" << std::endl;
            }
        }

        double healing_strength = damaging_weapon->getAttackStrength();
        double total_damage = (healing_strength)*multiplier;

        current_health -= total_damage;
        if (current_health <= 0)
        {
            current_health = 0;
        }
        std::cout << *this << " received " << total_damage << " damage from " << *attacker << "." << std::endl
                  << *this << " now has " << current_health << " health." << std::endl
                  << std::endl;
    }

    // EFFECTS: Prints weapons of fighter to os
    std::ostream &print_weapons(std::ostream &os) const override
    {
        for (int i = 0; i < numberOfWeapons; ++i)
        {
            os << "Weapon " << i + 1 << ": " << *weapons[i] << std::endl;
        }
        return os;
    }

    // EFFECTS Prints droppedWeapons to stream as "Weapon 1: Excalibur"
    // followed by newline and then "Weapon 2: Gate of Babylon"
    std::ostream &print_list_of_weapons(std::ostream &os, const std::vector<Weapon *> weapons) const override
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
            delete_weapon(0);
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
    double current_health;

    double attack_strength;
    double healing_strength;
    std::string type;
};

// EFFECTS Returns a pointer to a fighter with the given name, element, and type
Fighter *Fighter_factory(const std::string &name, const Element &element,
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
Fighter *Fighter_factory(const std::string &name, const Element &element,
                         const std::string &weapon, const std::string &type)
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

// EFFECTS Returns a pointer to a fighter that is copy of copied_fighter
Fighter *Fighter_factory(const Fighter *copied_fighter)
{

    std::string name = copied_fighter->getName();
    Element element = copied_fighter->getElement();

    int numberOfWeapons = copied_fighter->getNumberOfWeapons();

    std::vector<Weapon *> weapons;
    for (int i = 0; i < numberOfWeapons; ++i)
    {
        Weapon *ith_weapon = copied_fighter->getWeaponK(i);
        Weapon *addedWeapon = WeaponFactory(ith_weapon);
        weapons.push_back(addedWeapon);
    }

    int activeWeapon = copied_fighter->getActiveWeapon();
    bool inCombat = copied_fighter->get_combat_status();
    double maxHealth = copied_fighter->get_maxHealth();
    double current_health = copied_fighter->getCurrentHealth();

    double attack_strength = copied_fighter->getAttackStrength();
    double healing_strength = copied_fighter->getHealingStrength();
    std::string type = copied_fighter->getType();

    if (type == "Human")
    {
        return new Human(name, element, weapons, numberOfWeapons, activeWeapon,
                         inCombat, maxHealth, current_health, attack_strength, healing_strength, type);
    }
    else if (type == "Warrior")
    {
        return new Warrior(name, element, weapons, numberOfWeapons, activeWeapon,
                           inCombat, maxHealth, current_health, attack_strength, healing_strength, type);
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
std::ostream &print_weapons(std::ostream &os, const Fighter &f)
{
    f.print_weapons(os);
    return os;
}

// EFFECTS Prints fighters to stream as "Fighter 1: Alex"
// followed by newline and then "Fighter 2: Harry"
std::ostream &print_list_of_fighters(std::ostream &os, std::vector<Fighter *> fighters)
{
    for (size_t i = 0; i < fighters.size(); ++i)
    {
        Fighter *ithfighter = fighters[i];
        os << "Fighter " << i + 1 << ": " << *ithfighter << std::endl;
    }
    return os;
}
