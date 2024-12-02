// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class BaseC {
private:
    string name;
    int age;
    int attack;
    int defense;
    int intellect;
    int VP; // Victory Points

    int pathType; // 0 for Specialized Training, 1 for Straight to Battlefront

    // Helper function to validate and reset statistics
    void validateStatistics();

public:
    // Constructor
    BaseC(string name, int age, int attack, int defense, int intellect, int VP = 20000);

    // Getter functions
    string getName() const;
    int getAge() const;
    int getAttack() const;
    int getDefense() const;
    int getIntellect() const;
    int getVictoryPoints() const;
    int getPathType() const;

    // Setter functions
    void setName(string newName);
    void setAge(int newAge);
    void setAttack(int newAttack);
    void setDefense(int newDefense);
    void setIntellect(int newIntellect);
    void setVictoryPoints(int newVP);
    void setPathType(int path);

    // Increment functions
    void increaseAge(int change);
    void increaseAttack(int change);
    void increaseDefense(int change);
    void increaseIntellect(int change);
    void increaseVictoryPoints(int change);

    // Decrement functions
    void decreaseAge(int change);
    void decreaseAttack(int change);
    void decreaseDefense(int change);
    void decreaseIntellect(int change);
    void decreaseVictoryPoints(int change);

    // Multiply Functions
    void multiplyAge(int factor);
    void multiplyAttack(int factor);
    void multiplyDefense(int factor);
    void multiplyIntellect(int factor);
    void multiplyVictoryPoints(int factor);

    // Utility functions
    bool isEven(int num) const;
    void displayStats() const; // Display player's current stats
    void resetStats();         // Reset stats to default values

    // Placeholder for future functions
    void moveToPosition(int position); // Move player to a new position
    void useItem();                    // Use an item
    void attackPlayer(BaseC opponent); // Attack another player
};

#endif
