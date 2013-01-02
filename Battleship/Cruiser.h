// Written by Aaron Ogata
#pragma once
#include "Ship.h"

// A cruiser is basically the same thing as a destroyer, except for the health.
// If you change something here, change it in the corresponding class!

class Cruiser : public Ship {
public:
	Cruiser() { type = CRUISER; set_remaining_health(get_max_health()); set_last_turn_fired(-1); }
	int get_max_health() { return 3; }
	bool can_attack(int turn) { return !get_wreck(); }

	Grid* do_attack(Grid* attacked_grid, int attacked_location) {
		Ship* attacked_ship = (attacked_grid->has_ship(attacked_location) ? attacked_grid->get_ship(attacked_location) : NULL);
		if(attacked_ship == NULL) return NULL;

		return attacked_ship->defend(attacked_grid, attacked_location);
	}
};