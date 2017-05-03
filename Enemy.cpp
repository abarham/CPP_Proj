#include "Enemy.h"
#include "Hero.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

std::string Enemy::getName() {
	return name;
}

int Enemy::getHitPoints() {
	return hitPoints;
}

void Enemy::setHitPoints(int hp) {
	this->hitPoints = hp;
}

int Enemy::getStrength() {
	return strength;
}

int Enemy::getIntelligence() {
	return intelligence;
}

int Enemy::getDefense() {
	return defence;
}

int Enemy::getAttack() {
	return attack;
}

int Enemy::getType() {
	return type;
}

void Enemy::setName(std::string str) {
	this->name = str;
}

void Enemy::setStrength(int str) {
	this->strength = str;
}

void Enemy::setIntelligence(int intel) {
	this->intelligence = intel;
}

void Enemy::setDefense(int def) {
	this->defence = def;
}

void Enemy::setAttack(int str, int intel) {
	this->attack = (str * intel) / 20;
}

void Enemy::setType(int type) {
	this->type = type;
}

void Enemy::takeDamage(int damage) {
	int damageTotal = damage;
	std::cout << damageTotal << " dmg to " << Enemy::getName() << std::endl;
	if (Enemy::getHitPoints() == 0) {
		std::cout << "Enemy is already dead! Attack misses." << std::endl;
		return;
	}
	if (Enemy::getHitPoints() >= damageTotal)
		Enemy::setHitPoints(Enemy::getHitPoints() - damageTotal);
	else
		Enemy::setHitPoints(0);
	std::cout << Enemy::getHitPoints() << " hp left." << std::endl;
}

void Enemy::takeMagicDamage(int damage) {
	std::cout << damage << " magic dmg to " << Enemy::getName() << std::endl;
	if (Enemy::getIntelligence() >= damage)
		Enemy::setIntelligence(Enemy::getIntelligence() - damage / 10);
	else
		Enemy::setIntelligence(1);
}

int Enemy::rng(int min, int max) {
	std::random_device rd; // obtains random number from hardware
	std::mt19937 eng(rd()); // seed the rng
	std::uniform_int_distribution<> distr(min, max); // define range
	return distr(eng);
}

void Enemy::damage(Hero &hero) {
	hero.takeDamage(Enemy::getAttack());
}

void Enemy::chooseAttack(std::vector<Hero> &heroes) {
	if (Enemy::getType() == 1) {
		Enemy::dragonChooseAttack(heroes);
		return;
	}
	int max = heroes.size();
	int choice = Enemy::rng(1, max);
	std::cout << Enemy::getName() << " is attacking " << heroes[choice - 1].getName() << "." << std::endl;
	Enemy::damage(heroes[choice - 1]);
}

void Enemy::dragonChooseAttack(std::vector<Hero> &heroes) {
	int swipeOrFire = rng(1,2);
	int max = heroes.size();
	int choice = Enemy::rng(1, max);
	switch (swipeOrFire) {
	case 1: // swipe
		std::cout << Enemy::getName() << " is attacking " << heroes[choice - 1].getName() << "." << std::endl;
		Enemy::damage(heroes[choice - 1]);
		break;
	case 2: // breathe fire
		std::cout << Enemy::getName() << " is using Breathe Fire! All heroes are attacked." << std::endl;
		for (int i = 0; i < max; i++) {
			Enemy::damage(heroes[i]);
		}
		break;
	}
}

void Enemy::printStats() {
	std::cout << "Name: " << Enemy::getName() << std::endl;
	std::cout << "hp: " << Enemy::getHitPoints() << std::endl;
	std::cout << "atk: " << Enemy::getAttack() << std::endl;
	std::cout << "def: " << Enemy::getDefense() << std::endl;
}
