// Written by Aaron Ogata
#pragma once
#include "Ship.h"

class Submarine : public Ship {
public:
	Submarine() { type = SUBMARINE; set_remaining_health(get_max_health()); set_last_turn_fired(-2); }
	int get_max_health() { return 2; }
	bool can_attack(int turn) { return (turn - get_last_turn_fired() > 2) && (get_remaining_health() != 0); } // Turn #x: ME Turn #(x+1): ENEMY Turn #(x+2): ME

	Grid* do_attack(Grid* attacked_grid, int attacked_location) {
		Grid* result = new Grid(attacked_grid->get_max_size());
		Grid* res1 = attacked_grid->has_ship(attacked_location) ? attacked_grid->get_ship(attacked_location)->defend(attacked_grid, attacked_location) : NULL;
		Grid* res2 = NULL;
		Grid* res3 = NULL;
		// 4.	When a submarines fires, it hits 3 adjacent squares.
		Ship* s1 = attacked_grid->get_ship(attacked_location + 1);
		if(s1 != NULL) res2 = s1->defend(attacked_grid, attacked_location + 1);
		Ship* s2 = attacked_grid->get_ship(attacked_location + 2);
		if(s2 != NULL) res3 = s2->defend(attacked_grid, attacked_location + 2);
		if(res1 != NULL) { result->add_grid(res1); delete res1; }
		if(res2 != NULL) { result->add_grid(res2); delete res2; }
		if(res3 != NULL) { result->add_grid(res3); delete res3; }
		return result;
	}

	void on_ship_destruction(Grid* ship_grid, uint32_t ship_location, Grid* damaged_ships) {
		Ship* removed = ship_grid->remove_ship(ship_location); // submarines disappear from the grid whenever they are destroyed.
	}
};
