#include "Dragon.h"

/*
 * Breath Fire hits all heroes
 * Swipe hits one hero
 * high hp
 */

Dragon::Dragon() {
	setName("Dragon");
	setStrength(HIGH);
	setIntelligence(MED);
	setDefense(HIGH);
	setAttack(getStrength(), getIntelligence());
	setType(1);
	setHitPoints(2500);
}

Dragon::~Dragon() {
}

