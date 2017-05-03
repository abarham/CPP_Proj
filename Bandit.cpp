#include "Bandit.h"

/*
 * Low hp, low defense, low strength
 */

Bandit::Bandit() {
	setName("Bandit");
	setStrength(LOW);
	setIntelligence(LOW);
	setDefense(LOW);
	setAttack(getStrength(), getIntelligence());
	setType(3);
	setHitPoints(500);
}

Bandit::~Bandit() {
}

