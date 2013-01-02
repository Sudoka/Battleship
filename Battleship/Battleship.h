// Written by Aaron Ogata
#pragma once
#include "Ship.h"

// A battleship is basically the same thing as a Carrier, except for the health.
// If you change something here, change it in the corresponding class!

class Battleship : public Ship {
public:
	Battleship() { type = BATTLESHIP; set_remaining_health(get_max_health()); set_last_turn_fired(-1); }
	int get_max_health() { return 4; }
	bool can_attack(int turn) { return !get_wreck(); }

	Grid* do_attack(Grid* attacked_grid, int attacked_location) {
		Ship* attacked_ship = (attacked_grid->has_ship(attacked_location) ? attacked_grid->get_ship(attacked_location) : NULL);
		if(attacked_ship == NULL) return NULL;

		return attacked_ship->defend(attacked_grid, attacked_location);
	}

	void on_ship_destruction(Grid* ship_grid, uint32_t ship_location, Grid* damaged_ships) {
		// 1.	When a carrier or battleship is destroyed, any ships downwind (right) by 1 or 2 cells are damaged by 1 health point to represent the impact from the exploding wreckages.
		Ship* s1 = ship_grid->get_ship(ship_location + 1);
		if(s1 != NULL) { Grid* g2 = s1->defend(ship_grid, ship_location + 1); if(g2 != NULL) { damaged_ships->add_grid(g2); } delete g2; damaged_ships->add_ship(ship_location + 1, s1); }
		Ship* s2 = ship_grid->get_ship(ship_location + 2);
		if(s2 != NULL) { Grid* g2 = s2->defend(ship_grid, ship_location + 2); if(g2 != NULL) { damaged_ships->add_grid(g2); } delete g2; damaged_ships->add_ship(ship_location + 2, s2); }
	}
};
