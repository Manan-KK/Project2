
#include "Player.h"
#include <iostream>
using namespace std;

// Constructor
BaseC::BaseC(int age, int str, int sta, int wis, int PP)
    : age(age), str(str), sta(sta), wis(wis), PP(PP) {
    validateStatistics(); 
}

// Helper function to validate and reset statistics
void BaseC::validateStatistics() {
    if (str < 100) str = 100;
    if (sta < 100) sta = 100;
    if (wis < 100) wis = 100;
}

// Getter functions
int BaseC::getAge() const { return age; }
int BaseC::getStrength() const { return str; }
int BaseC::getStamina() const { return sta; }
int BaseC::getWisdom() const { return wis; }
int BaseC::getPridePoints() const { return PP; }

// Setter functions
void BaseC::setAge(int newAge) { age = newAge; }
void BaseC::setStrength(int newStr) { str = newStr; validateStatistics(); }
void BaseC::setStamina(int newSta) { sta = newSta; validateStatistics(); }
void BaseC::setWisdom(int newWis) { wis = newWis; validateStatistics(); }
void BaseC::setPridePoints(int newPP) { PP = newPP; }

// Increment functions
void BaseC::increaseAge(int change) { age += change; }
void BaseC::increaseStrength(int change) { str += change; validateStatistics(); }
void BaseC::increaseStamina(int change) { sta += change; validateStatistics(); }
void BaseC::increaseWisdom(int change) { wis += change; validateStatistics(); }
void BaseC::increasePridePoints(int change) { PP += change; }

// Decrement functions
void BaseC::decreaseAge(int change) { age -= change; }
void BaseC::decreaseStrength(int change) { str -= change; validateStatistics(); }
void BaseC::decreaseStamina(int change) { sta -= change; validateStatistics(); }
void BaseC::decreaseWisdom(int change) { wis -= change; validateStatistics(); }
void BaseC::decreasePridePoints(int change) { PP -= change; }

// Multiply functions
void BaseC::multiplyAge(int factor) { age *= factor; }
void BaseC::multiplyStrength(int factor) { str *= factor; validateStatistics(); }
void BaseC::multiplyStamina(int factor) { sta *= factor; validateStatistics(); }
void BaseC::multiplyWisdom(int factor) { wis *= factor; validateStatistics(); }
void BaseC::multiplyPridePoints(int factor) { PP *= factor; }

// Utility functions
bool BaseC::isEven(int num) const {
    return num % 2 == 0;
}

void BaseC::displayStats() const {
    cout << "Age: " << age << "\n";
    cout << "Strength: " << str << "\n";
    cout  << "Stamina: " << sta << "\n";
    cout  << "Wisdom: " << wis << "\n";
    cout  << "Pride Points: " << PP << "\n";
}

void BaseC::resetStats() {
    str = 100;
    sta = 100;
    wis = 100;
    PP = 20000;
    validateStatistics();
    cout << "Stats have been reset to Base values.\n";
}

// Move the player to a new position
void BaseC::moveToPosition(int position) {
    // Implement movement logic with board later
    cout << "Player moves to position " << position << ".\n";
}

// Use an item
void BaseC::useItem() {
    if (itemCount > 0) {
        cout << "Player uses an item.\n";
        // Example item usage code, will likely implement picker menu and individual class that will work with tile. 
        increaseStrength(50);
        decreaseItemCount(1);
    } else {
        cout << "No items to use.\n";
    }
}
//Random attack method, will also again likely be modified to be used with board.
void BaseC::attack(BaseC& opponent) {
    std::cout << "Attacking opponent...\n";

    //random  
    srand((time(0))); // Seed random number generator
    int outcome = rand() % 2; // Generates 0 or 1

    if (outcome == 0) {
        std::cout << "You win the attack!\n";
        this->increasePridePoints(100);
        opponent.decreasePridePoints(100);
    } else {
        std::cout << "You lose the attack!\n";
        this->decreasePridePoints(100);
        opponent.increasePridePoints(100);
    }
}