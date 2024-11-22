// player.cpp
#include "Player.h"
#include <iostream>
#include <algorithm> // For std::find

// Constructor
BaseC::BaseC(int age, int str, int sta, int wis, int PP)
    : age(age), str(str), sta(sta), wis(wis), PP(PP) {
    validateStatistics(); // Ensure valid initial values
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
    std::cout << "Age: " << age << "\n"
              << "Strength: " << str << "\n"
              << "Stamina: " << sta << "\n"
              << "Wisdom: " << wis << "\n"
              << "Pride Points: " << PP << "\n";
}

void BaseC::resetStats() {
    str = 100;
    sta = 100;
    wis = 100;
    PP = 20000;
    validateStatistics();
    std::cout << "Stats have been reset to default values.\n";
}

// Additional functions for a board game player

// Move the player to a new position
void BaseC::moveToPosition(int position) {
    // Implement movement logic
    std::cout << "Player moves to position " << position << ".\n";
}

// Add an item to the player's inventory
void BaseC::gainItem(const std::string& itemName) {
    inventory.push_back(itemName);
    std::cout << "Player gains item: " << itemName << ".\n";
}

// Use an item from the player's inventory
void BaseC::useItem(const std::string& itemName) {
    auto it = std::find(inventory.begin(), inventory.end(), itemName);
    if (it != inventory.end()) {
        // Implement item usage logic
        std::cout << "Player uses item: " << itemName << ".\n";
        inventory.erase(it); // Remove item after use
    } else {
        std::cout << "Item not found in inventory.\n";
    }
}

// Attack another player
void BaseC::attack(BaseC& opponent) {
    // Simple attack logic based on Strength attribute
    std::cout << "Attacking opponent...\n";
    if (this->str > opponent.str) {
        std::cout << "You win the attack!\n";
        this->increasePridePoints(100);
        opponent.decreasePridePoints(100);
    } else if (this->str < opponent.str) {
        std::cout << "You lose the attack!\n";
        this->decreasePridePoints(100);
        opponent.increasePridePoints(100);
    } else {
        std::cout << "It's a tie! No one gains or loses Pride Points.\n";
    }
}

// Trade items with another player
void BaseC::tradeItem(BaseC& otherPlayer, const std::string& yourItem, const std::string& theirItem) {
    auto yourIt = std::find(inventory.begin(), inventory.end(), yourItem);
    auto theirIt = std::find(otherPlayer.inventory.begin(), otherPlayer.inventory.end(), theirItem);

    if (yourIt != inventory.end() && theirIt != otherPlayer.inventory.end()) {
        inventory.erase(yourIt);
        otherPlayer.inventory.erase(theirIt);

        inventory.push_back(theirItem);
        otherPlayer.inventory.push_back(yourItem);

        std::cout << "Trade successful! You traded " << yourItem << " for " << theirItem << ".\n";
    } else {
        std::cout << "Trade failed. Item not found.\n";
    }
}

// Check if player has won (example condition)
bool BaseC::hasWon() const {
    // Example win condition: Pride Points exceed a certain threshold
    return PP >= 50000;
}