#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Enemy.h"

const int LOW = 25;
const int MED = 50;
const int HIGH = 75;

class Enemy;
class Hero
{
public:
	Hero();
	~Hero();
	std::string getName();
	int getHitPoints();
	int getSkillPoints();
	int getStrength();
	int getIntelligence();
	int getDefense();
	int getSpeed();
	int getAttack();
	void setHitPoints(int);
	void setSkillPoints(int);
	void setName(std::string);
	void setStrength(int);
	void setIntelligence(int);
	void setDefense(int);
	void setSpeed(int);
	void setAttack(int, int);
	void damage(Enemy&);
	void magicDamage(Enemy&);
	void takeDamage(int);
	void physicalAttack(std::vector<Enemy>&);
	int getType();
	void setType(int);
	void printStats();
	int chooseActionCleric();
	void clericHeal(std::vector<Hero>&);
	void heal(Hero&);
	void magicAttack(std::vector<Enemy>&);
	bool blocked(int);

private:
	std::string name;
	int hitPoints;
	int skillPoints;
	int strength;
	int intelligence;
	int defence;
	int speed;
	int attack;
	int type;
};

