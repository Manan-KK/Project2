#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
private:
    string name;
    int age;
    int might;
    int endurance;
    int cunning;
    int honor;
    int pathType;
    int advisor;
    void validateStats();

public:
    Player();
    Player(string n, int a, int m, int e, int c, int h=20000);

    string getName() const;
    int getAge() const;
    int getMight() const;
    int getEndurance() const;
    int getCunning() const;
    int getHonor() const;
    int getPathType() const;
    int getAdvisor() const;

    void setName(string n);
    void setAge(int a);
    void setMight(int m);
    void setEndurance(int d);
    void setCunning(int c);
    void setHonor(int h);
    void setPathType(int p);
    void setAdvisor(int adv);

    void incMight(int x);
    void incEndurance(int x);
    void incCunning(int x);
    void incHonor(int x);

    void decMight(int x);
    void decEndurance(int x);
    void decCunning(int x);
    void decHonor(int x);

    void displayStats() const;
    void resetStats();
    void convertTraitsToHonor();
};

#endif
