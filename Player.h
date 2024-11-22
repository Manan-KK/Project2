// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class BaseC {
private:
    int age;
    int str;
    int sta;
    int wis;
    int PP;

    // Helper function to validate and reset statistics
    void validateStatistics();

public:
    // Constructor
    BaseC(int age, int str, int sta, int wis, int PP = 20000);

    // Getter functions
    int getAge() const;
    int getStrength() const;
    int getStamina() const;
    int getWisdom() const;
    int getPridePoints() const;

    // Setter functions
    void setAge(int newAge);
    void setStrength(int newStr);
    void setStamina(int newSta);
    void setWisdom(int newWis);
    void setPridePoints(int newPP);

    // Increment functions
    void increaseAge(int change);
    void increaseStrength(int change);
    void increaseStamina(int change);
    void increaseWisdom(int change);
    void increasePridePoints(int change);

    // Decrement functions
    void decreaseAge(int change);
    void decreaseStrength(int change);
    void decreaseStamina(int change);
    void decreaseWisdom(int change);
    void decreasePridePoints(int change);

    // Multiply functions
    void multiplyAge(int factor);
    void multiplyStrength(int factor);
    void multiplyStamina(int factor);
    void multiplyWisdom(int factor);
    void multiplyPridePoints(int factor);

    // Utility functions
    bool isEven(int num) const;
    void displayStats() const; // Display player's current stats
    void resetStats();         // Reset stats to default values

    // Additional functions for a board game player
    void moveToPosition(int position); // Move player to a new position
    void gainItem(const std::string& itemName); // Add item to inventory
    void useItem(const std::string& itemName);  // Use item from inventory
    void attack(BaseC& opponent);               // Attack another player
    void tradeItem(BaseC& otherPlayer, const std::string& yourItem, const std::string& theirItem); // Trade items
    bool hasWon() const;                        // Check if player has won

    // Inventory
    std::vector<std::string> inventory;
};

#endif // PLAYER_H
