// Player.cpp
#include "Player.h"
#include <iostream>

using namespace std;

// Constructor
BaseC::BaseC(string name, int age, int attack, int defense, int intellect, int VP)
    : name(name), age(age), attack(attack), defense(defense), intellect(intellect), VP(VP) {
    validateStatistics();
}

// Helper function to validate and reset statistics
void BaseC::validateStatistics() {
    if (attack < 100) attack = 100;
    if (defense < 100) defense = 100;
    if (intellect < 100) intellect = 100;
}

// Getter functions
string BaseC::getName() const { return name; }
int BaseC::getAge() const { return age; }
int BaseC::getAttack() const { return attack; }
int BaseC::getDefense() const { return defense; }
int BaseC::getIntellect() const { return intellect; }
int BaseC::getVictoryPoints() const { return VP; }
int BaseC::getPathType() const { return pathType; }

// Setter functions
void BaseC::setName(string newName) { name = newName; }
void BaseC::setAge(int newAge) { age = newAge; }
void BaseC::setAttack(int newAttack) { attack = newAttack; validateStatistics(); }
void BaseC::setDefense(int newDefense) { defense = newDefense; validateStatistics(); }
void BaseC::setIntellect(int newIntellect) { intellect = newIntellect; validateStatistics(); }
void BaseC::setVictoryPoints(int newVP) { VP = newVP; }
void BaseC::setPathType(int path) { pathType = path; }

// Increment functions
void BaseC::increaseAge(int change) { age += change; }
void BaseC::increaseAttack(int change) { attack += change; validateStatistics(); }
void BaseC::increaseDefense(int change) { defense += change; validateStatistics(); }
void BaseC::increaseIntellect(int change) { intellect += change; validateStatistics(); }
void BaseC::increaseVictoryPoints(int change) { VP += change; }

// Decrement functions
void BaseC::decreaseAge(int change) { age -= change; }
void BaseC::decreaseAttack(int change) { attack -= change; validateStatistics(); }
void BaseC::decreaseDefense(int change) { defense -= change; validateStatistics(); }
void BaseC::decreaseIntellect(int change) { intellect -= change; validateStatistics(); }
void BaseC::decreaseVictoryPoints(int change) { VP -= change; }

// Multiply functions
void BaseC::multiplyAge(int factor) { age *= factor; }
void BaseC::multiplyAttack(int factor) { attack *= factor; validateStatistics(); }
void BaseC::multiplyDefense(int factor) { defense *= factor; validateStatistics(); }
void BaseC::multiplyIntellect(int factor) { intellect *= factor; validateStatistics(); }
void BaseC::multiplyVictoryPoints(int factor) { VP *= factor; }

// Utility functions
bool BaseC::isEven(int num) const {
    return num % 2 == 0;
}

void BaseC::displayStats() const {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << "\n";
    cout << "Attack: " << attack << "\n";
    cout << "Defense: " << defense << "\n";
    cout << "Intellect: " << intellect << "\n";
    cout << "Victory Points: " << VP << "\n";
}

void BaseC::resetStats() {
    attack = 100;
    defense = 100;
    intellect = 100;
    VP = 20000;
    validateStatistics();
    cout << "Stats have been reset to base values.\n";
}

// Placeholder functions
void BaseC::moveToPosition(int position) {
    cout << "Player moves to position " << position << ".\n";
}

void BaseC::useItem() {
    cout << "Use item functionality (to be implemented).\n";
}

void BaseC::attackPlayer(BaseC opponent) {
    cout << "Attack player functionality (to be implemented).\n";
}
