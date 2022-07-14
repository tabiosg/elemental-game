#ifndef FIGHTER_H
#define FIGHTER_H
/* Fighter.h
 *
 * Fighter
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */

#include "Element.h"

#include "Weapon.h"
#include <string>
#include <vector>

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

    // EFFECTS returns fighter's name
    virtual const std::string &getName() const = 0;

    // EFFECTS returns fighter's type
    virtual const std::string &getType() const = 0;

    // REQUIRES fighter has an element
    // EFFECTS  returns element of fighter
    virtual Element getElement() const = 0;

    // EFFECTS returns number of weapons on fighter
    virtual int getNumberOfWeapons() const = 0;

    // REQUIRES fighter has a weapon
    // EFFECTS  returns active weapon of fighter
    virtual int getActiveWeapon() const = 0;

    // EFFECTS returns kth weapons of fighter
    virtual Weapon *getOfWeaponK(const int &k) const = 0;

    // EFFECTS  returns combat status of fighter
    virtual bool getCombatStatus() const = 0;

    // EFFECTS  returns max health of fighter
    virtual double getMaxHealth() const = 0;

    // EFFECTS  returns current health of fighter
    virtual double getCurrentHealth() const = 0;

    // EFFECTS  returns attackStrength of fighter
    virtual double getAttackStrength() const = 0;

    // EFFECTS  returns healingStrength of fighter
    virtual double getHealingStrength() const = 0;

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    virtual void addWeapon(Weapon *weapon) = 0;

    // REQUIRES fighter wants to delete a weapon
    // EFFECTS deletes weapon
    virtual void deleteWeapon(const int &weaponIndex) = 0;

    // REQUIRES 0 < k <= numberOfWeapons
    // EFFECTS returns the kth weapon's name
    virtual const std::string &getNameOfWeaponK(const int &k) const = 0;

    // REQUIRES 0 < k <= numberOfWeapons
    // EFFECTS  returns element of the kth weapon
    virtual Element getElementOfWeaponK(const int &k) const = 0;

    /// REQUIRES 0 < k <= numberOfWeapons
    // EFFECTS  returns attack strength of the kth weapon
    virtual double getAttackStrengthOfWeaponK(const int &k) const = 0;

    // REQUIRES 0 < k <= numberOfWeapons
    // EFFECTS  returns healing strength of the kth weapon
    virtual double getHealingStrengthOfWeaponK(const int &k) const = 0;

    // REQUIRES 0 < k <= numberOfWeapons
    // EFFECTS returns the kth weapon's type
    virtual const std::string getTypeOfWeaponK(const int &k) const = 0;

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    virtual void changeName(const std::string &newName) = 0;

    // EFFECTS changes fighter max health
    virtual void changeMaxHealth(const int &newMaxHealth) = 0;

    // EFFECTS changes fighter current health
    virtual void changeCurrentHealth(const int &newMaxHealth) = 0;

    // EFFECTS changes fighter attack strength
    virtual void changeAttackStrength(const int &newAttackStrength) = 0;

    // EFFECTS changes fighter healing strength
    virtual void changeHealingStrength(const int &newHealingStrength) = 0;

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    virtual void enterCombat() = 0;

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    virtual void exitCombat() = 0;

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    virtual std::string requestAction(std::vector<Fighter *> allies, std::vector<Fighter *> opponents,
                                       const std::vector<Weapon *> droppedWeapons) = 0;

    // REQUIRES fighter wants to heal
    // MODIFIES allies
    // EFFECTS  make fighter heal allies or self
    virtual void goHeal(std::vector<Fighter *> allies) = 0;

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    virtual int goAttack(std::vector<Fighter *> opponents) = 0;

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    virtual int goGrabWeapon(std::vector<Fighter *> allies, std::vector<Fighter *> opponents,
                               const std::vector<Weapon *> droppedWeapons) = 0;

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    virtual void receiveHealing(const Weapon *healingWeapon, Fighter *healer) = 0;

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack
    // do not change combat status if below 0 hp here.
    virtual void receiveAttack(const Weapon *damagingWeapon, const Fighter *attacker) = 0;

    // EFFECTS: Prints weapons of fighter to os
    virtual std::ostream &printWeapons(std::ostream &os) const = 0;

    virtual std::ostream &printListOfWeapons(std::ostream &os, const std::vector<Weapon *> weapons) const = 0;

    // Needed to avoid some compiler errors
    virtual ~Fighter() {}

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
Fighter *FighterFactory(const std::string &name, const Element &element,
                         const std::string &type);

// EFFECTS: Returns a pointer to a fighter with the given name, element, weapon, and type
Fighter *FighterFactory(const std::string &name, const Element &element,
                         const std::string &weapon, const std::string &type);

// EFFECTS Returns a pointer to a fighter that is copy of copiedFighter
Fighter *FighterFactory(const Fighter *copiedFighter);

// EFFECTS Prints fighter's name to os
std::ostream &operator<<(std::ostream &os, const Fighter &f);

// EFFECTS Prints weapons of fighter to os as "Weapon 1: Excalibur"
// followed by newline and then "Weapon 2: Gate of Babylon"
std::ostream &printWeapons(std::ostream &os, const Fighter &f);

// EFFECTS Prints fighters to stream as "Fighter 1: Alex"
// followed by newline and then "Fighter 2: Harry"
std::ostream &printListOfFighters(std::ostream &os, std::vector<Fighter *> fighters);

#endif
