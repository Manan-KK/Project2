#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class BaseC {
private:
    int age;
    int str;
    int sta;
    int wis;
    int PP;

    //number of items
    int itemCount;

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
    int getItemCount() const;

    // Setter functions
    void setAge(int newAge);
    void setStrength(int newStr);
    void setStamina(int newSta);
    void setWisdom(int newWis);
    void setPridePoints(int newPP);
    void setItemCount(int count);

    // Increment functions
    void increaseAge(int change);
    void increaseStrength(int change);
    void increaseStamina(int change);
    void increaseWisdom(int change);
    void increasePridePoints(int change);
    void increaseItemCount(int count);

    // Decrement functions
    void decreaseAge(int change);
    void decreaseStrength(int change);
    void decreaseStamina(int change);
    void decreaseWisdom(int change);
    void decreasePridePoints(int change);
    void decreaseItemCount(int count);

    //Multiply Functions
    void multiplyAge(int factor);
    void multiplyStrength(int factor);
    void multiplyStamina(int factor);
    void multiplyWisdom(int factor);
    void multiplyPridePoints(int factor);

    // Utility functions
    bool isEven(int num) const;
    void displayStats() const; // Display players current stats
    void resetStats();         // Reset stats to default values

    // Currently broken functions that need inter-class operability later on.
    void moveToPosition(int position); // Move player to a new position
    void useItem();                    // Use an item 
    void attack(BaseC& opponent);      // Attack another player
};

#endif 
