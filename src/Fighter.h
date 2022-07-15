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
    virtual const std::string &getName() const;

    // EFFECTS returns fighter's type
    virtual const std::string &getType() const;

    // REQUIRES fighter has an element
    // EFFECTS  returns element of fighter
    virtual Element getElement() const;

    // EFFECTS returns number of weapons on fighter
    virtual int getNumberOfWeapons() const;

    // REQUIRES fighter has a weapon
    // EFFECTS  returns active weapon of fighter
    virtual int getActiveWeapon() const;

    // EFFECTS returns kth weapons of fighter
    virtual Weapon *getOfWeaponK(const int &k) const;

    // EFFECTS  returns combat status of fighter
    virtual bool getCombatStatus() const;

    // EFFECTS  returns max health of fighter
    virtual double getMaxHealth() const;

    // EFFECTS  returns current health of fighter
    virtual double getCurrentHealth() const;

    // EFFECTS  returns attackStrength of fighter
    virtual double getAttackStrength() const;

    // EFFECTS  returns healingStrength of fighter
    virtual double getHealingStrength() const;

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    virtual void addWeapon(Weapon *weapon);

    // REQUIRES fighter wants to delete a weapon
    // EFFECTS deletes weapon
    virtual void deleteWeapon(const int &weaponIndex);

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's name
    virtual const std::string &getNameOfWeaponK(const int &k) const;

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns element of the kth weapon
    virtual Element getElementOfWeaponK(const int &k) const;

    // EFFECTS  returns attack strength of active weapon
    virtual Element getElementOfActiveWeapon() const;

    /// REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns attack strength of the kth weapon
    virtual double getAttackStrengthOfWeaponK(const int &k) const;

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS  returns healing strength of the kth weapon
    virtual double getHealingStrengthOfWeaponK(const int &k) const;

    // REQUIRES 0 <= k < numberOfWeapons
    // EFFECTS returns the kth weapon's type
    virtual const std::string getTypeOfWeaponK(const int &k) const;

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    virtual void changeName(const std::string &newName);

    // EFFECTS changes fighter max health
    virtual void changeMaxHealth(const int &newMaxHealth);

    // EFFECTS changes fighter current health
    virtual void changeCurrentHealth(const int &newMaxHealth);

    // EFFECTS changes fighter attack strength
    virtual void changeAttackStrength(const int &newAttackStrength);

    // EFFECTS changes fighter healing strength
    virtual void changeHealingStrength(const int &newHealingStrength);

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    virtual void enterCombat();

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    virtual void exitCombat();

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
    virtual void goHealAllyWithWeapon(Fighter *ally, Weapon *weapon);

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    virtual int goAttack(std::vector<Fighter *> opponents) = 0;

    // REQUIRES fighter wants to fight
    // MODIFIES opponent
    // EFFECTS  make fighter attack opponent.
    virtual void goAttackTargetWithWeapon(Fighter *opponent, Weapon *weapon);

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    virtual int goGrabWeapon(const std::vector<Weapon *> droppedWeapons) = 0;

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    virtual void goGrabThisWeapon(Weapon *droppedWeapon);

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    virtual void receiveHealing(const Weapon *healingWeapon, Fighter *healer);

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack
    // do not change combat status if below 0 hp here.
    virtual void receiveAttack(const Weapon *damagingWeapon, const Fighter *attacker);

    // EFFECTS: Prints weapons of fighter to os
    virtual std::ostream &printWeapons(std::ostream &os) const;

    virtual std::ostream &printListOfWeapons(
        std::ostream &os,
        const std::vector<Weapon *> weapons) const;

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
Fighter *FighterFactory(
    const std::string &name,
    const Element &element,
    const std::string &type);

// EFFECTS: Returns a pointer to a fighter with the given name, element, weapon, and type
Fighter *FighterFactory(
    const std::string &name,
    const Element &element,
    const std::string &weapon,
    const std::string &type);

// EFFECTS Returns a pointer to a fighter that is copy of copiedFighter
Fighter *FighterFactory(const Fighter *copiedFighter);

// EFFECTS Prints fighter's name to os
std::ostream &operator<<(std::ostream &os, const Fighter &f);

// EFFECTS Prints weapons of fighter to os as "Weapon 1: Excalibur"
// followed by newline and then "Weapon 2: Gate of Babylon"
std::ostream &printWeapons(std::ostream &os, const Fighter &f);

// EFFECTS Prints fighters to stream as "Fighter 1: Alex"
// followed by newline and then "Fighter 2: Harry"
std::ostream &printListOfFighters(
    std::ostream &os,
    std::vector<Fighter *> fighters);

#endif
