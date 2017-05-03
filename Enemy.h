#pragma once
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include "Hero.h"
class Hero;
class Enemy
{
public:
	Enemy();
	~Enemy();
	std::string getName();
	void setName(std::string);
	int getHitPoints();
	int getStrength();
	int getIntelligence();
	int getDefense();
	int getAttack();
	int getType();
	void setHitPoints(int);
	void setStrength(int);
	void setIntelligence(int);
	void setDefense(int);
	void setAttack(int, int);
	void setType(int);
	void takeDamage(int);
	void takeMagicDamage(int);
	void damage(Hero &hero);
	void chooseAttack(std::vector<Hero>&);
	void printStats();
	void dragonChooseAttack(std::vector<Hero>&);
private:
	int rng(int, int);
	std::string name;
	int hitPoints;
	int strength;
	int intelligence;
	int defence;
	int attack;
	int type;
};

