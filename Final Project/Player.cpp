#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() {
    name="Unknown";
    age=0;
    might=500;
    endurance=500;
    cunning=500;
    honor=20000;
    pathType=0;
    advisor=0;
    validateStats();
}

Player::Player(string n, int a, int m, int e, int c, int h) {
    name=n;
    age=a;
    might=m;
    endurance=e;
    cunning=c;
    honor=h;
    pathType=0;
    advisor=0;
    validateStats();
}

void Player::validateStats(){
    if(might<100) might=100;
    if(endurance<100) endurance=100;
    if(cunning<100) cunning=100;
}

string Player::getName() const{return name;}
int Player::getAge() const{return age;}
int Player::getMight() const{return might;}
int Player::getEndurance() const{return endurance;}
int Player::getCunning() const{return cunning;}
int Player::getHonor() const{return honor;}
int Player::getPathType() const{return pathType;}
int Player::getAdvisor() const{return advisor;}

void Player::setName(string n){name=n;}
void Player::setAge(int a){age=a;}
void Player::setMight(int m){might=m;validateStats();}
void Player::setEndurance(int d){endurance=d;validateStats();}
void Player::setCunning(int c){cunning=c;validateStats();}
void Player::setHonor(int h){honor=h;}
void Player::setPathType(int p){pathType=p;}
void Player::setAdvisor(int adv){advisor=adv;}

void Player::incMight(int x){might+=x;validateStats();}
void Player::incEndurance(int x){endurance+=x;validateStats();}
void Player::incCunning(int x){cunning+=x;validateStats();}
void Player::incHonor(int x){honor+=x;}

void Player::decMight(int x){might-=x;validateStats();}
void Player::decEndurance(int x){endurance-=x;validateStats();}
void Player::decCunning(int x){cunning-=x;validateStats();}
void Player::decHonor(int x){honor-=x;}

void Player::displayStats() const {
    cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Might: "<<might<<endl;
    cout<<"Endurance: "<<endurance<<endl;
    cout<<"Cunning: "<<cunning<<endl;
    cout<<"Honor: "<<honor<<endl;
    cout<<"Path: "<<(pathType==0?"Chapter Training Grounds":"Frontline Deployment")<<endl;
    cout<<"Advisor: ";
    switch(advisor){
        case 1: cout<<"Chapter Master";break;
        case 2: cout<<"Ethereal";break;
        case 3: cout<<"Ork Mek";break;
        case 4: cout<<"Eldar Farseer";break;
        case 5: cout<<"Necron Cryptek";break;
        default: cout<<"None";break;
    }
    cout<<endl;
}

void Player::resetStats(){
    might=100;endurance=100;cunning=100;honor=20000;
    validateStats();
}

void Player::convertTraitsToHonor(){
    int total=might+endurance+cunning;
    int chunks=total/100;
    incHonor(chunks*1000);
}
