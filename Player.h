
#ifndef PLAYER_H
#define PLAYER_H
class BaseC {
private:
    int age;
    int str;
    int sta;
    int wis;
    int PP;

    // Helper function to validate and reset statistics
    void validateStatistics()

public:
    // Constructor
    BaseC(int age, int str, int sta, int wis, int PP = 20000)
        : age(age), str(str), sta(sta), wis(wis), PP(PP) {
        validateStatistics(); // Ensure valid initial values
    }

    // Getter functions
    int getAge() const { return age; }
    int getStrength() const { return str; }
    int getStamina() const { return sta; }
    int getWisdom() const { return wis; }
    int getPridePoints() const { return PP; }

    // Setter functions
    void setAge(int newAge) { age = newAge; }
    void setStrength(int newStr) { str = newStr; validateStatistics(); }
    void setStamina(int newSta) { sta = newSta; validateStatistics(); }
    void setWisdom(int newWis) { wis = newWis; validateStatistics(); }
    void setPridePoints(int newPP) { PP = newPP; }

    // Increment functions
    void increaseAge(int change) { age += change; }
    void increaseStrength(int change) { str += change; validateStatistics(); }
    void increaseStamina(int change) { sta += change; validateStatistics(); }
    void increaseWisdom(int change) { wis += change; validateStatistics(); }
    void increasePridePoints(int change) { PP += change; }

    // Decrement functions
    void decreaseAge(int change) { age -= change; }
    void decreaseStrength(int change) { str -= change; validateStatistics(); }
    void decreaseStamina(int change) { sta -= change; validateStatistics(); }
    void decreaseWisdom(int change) { wis -= change; validateStatistics(); }
    void decreasePridePoints(int change) { PP -= change; }

    // Multiply functions
    void multiplyAge(int factor) { age *= factor; }
    void multiplyStrength(int factor) { str *= factor; validateStatistics(); }
    void multiplyStamina(int factor) { sta *= factor; validateStatistics(); }
    void multiplyWisdom(int factor) { wis *= factor; validateStatistics(); }
    void multiplyPridePoints(int factor) { PP *= factor; }

    // Check if a number is even
    bool isEven(int num) const { return num % 2 == 0; }

    
};
#endif
