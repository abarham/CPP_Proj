#include "Warrior.h"


// does physical damage, high defense
Warrior::Warrior() {
	setName("Warrior");
	setStrength(HIGH);
	setIntelligence(MED);
	setDefense(HIGH);
	setSpeed(LOW);
	setAttack(getStrength(), getIntelligence());
	setType(1);
}

Warrior::~Warrior() {
}


