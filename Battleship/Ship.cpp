// Written by Aaron Ogata
#include "Ship.h"
#include <iostream>
#include <string>
#include <sstream>

Grid* Ship::attack(Grid* attacked_grid, int attacked_location, int turn) {
	if(!can_attack(turn) || get_wreck())
		return NULL;

	set_last_turn_fired(turn);

	Grid* result = do_attack(attacked_grid, attacked_location);

	if(result == NULL) { // tried to attack a wreckage
		Grid* grid = new Grid(0);
		return grid;
	}

	return result;
}

Grid* Ship::defend(Grid* defending_grid, int defend_location) {
	// If this function is called, it is assumed that this ship is actually at this location.
	assert(defending_grid->get_ship(defend_location) != NULL);
	assert(defending_grid->get_ship(defend_location) == this);

	if(get_wreck())
		return NULL;

	Grid* g = new Grid(defending_grid->get_max_size());
	g->add_ship(defend_location, this);

	set_remaining_health(get_remaining_health() - 1);

	if(get_remaining_health() == 0) { // This ship was destroyed. 
		on_ship_destruction(defending_grid, defend_location, g);
	}

	return g;
}

void Ship::print_ship() {
	string s;
	stringstream temp;
	switch(get_ship_type()) {
	case CARRIER: s += "Carrier "; break;
	case BATTLESHIP: s += "Battleship "; break;
	case CRUISER: s += "Cruiser "; break;
	case SUBMARINE: s += "Submarine "; break;
	case DESTROYER: s += "Destroyer "; break;
	default: s += "Unknown Ship "; break;
	}

	temp.str(""); temp << get_remaining_health();
	s += temp.str();
	s += "/";
	temp.str(""); temp << get_max_health();
	s += temp.str();

	s += " ";
	s += (get_wreck() ? "WRECKED" : "");

	cout << s;
}

string Ship::get_string_name() {
	switch(type) {
	case CARRIER: return "Carrier Ship";
	case BATTLESHIP: return "Battle Ship";
	case CRUISER: return "Cruiser Ship";
	case SUBMARINE: return "Submarine Ship";
	case DESTROYER: return "Destroyer Ship";
	default: return "Unknown Ship Type";
	}
}
