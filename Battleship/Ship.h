// Written by Aaron Ogata
#pragma once
#include "Grid.h"
#include <string>

// --------------------------------------------------------------------------------
// SHIPAPI
// --------------------------------------------------------------------------------
// - Each ship subclass implements its own attack() and defend() commands.
// Grid* attack(Grid* attacked_grid, int attacked_location, int turn);
// - Tell this ship to attack "attacked_location" on "attacked_grid".
// - The turn number is "turn".
// - Return NULL if this ship cannot attack on this turn or this ship is wrecked.
// - Return EMPTY Grid* if this ship did not hit anything. Must be manually freed.
// - Return POPULATED Grid* if this ship DID hit something. Must be manually freed.
// - Warning! The Grid* returned will need to be manually freed.
// - Grid* attack_result = ship->attack(attacked_grid, attacked_location, turn);
// - // Process attack_result ...
// - delete attack_result; // Do NOT delete the associated Ship* variables.
// - THIS SHOULD BE THE ONLY FUNCTION YOU HAVE TO CALL RELATED TO THIS CLASS.
// - SOME SHIPS ATTACK DIFFERENTLY (SUCH AS SUBMARINE). DO NOT STRAIGHT UP CALL THE
// - defend() FUNCTION.
// --------------------------------------------------------------------------------
// virtual Grid* defend(Grid* defending_grid, int defend_location) = 0;
// - DO NOT MANUALLY CALL THIS FUNCTION UNLESS YOU HAVE A GOOD REASON TO.
// - Defend this ship against an attack for one damage. (All attacks are one damage)
// - This ship is located at "defend_location" on "defending_grid".
// - Return NULL if this ship was not damaged. (This ship is already wrecked and cannot be further damaged)
// - Return POPULATED Grid* of the ships that were damaged, by attacking this hsip.
// - The Grid* must be manually freed.
// - DO NOT MANUALLY CALL THIS FUNCTION UNLESS YOU HAVE A GOOD REASON TO.
// --------------------------------------------------------------------------------
// virtual Grid* do_attack(Ship* attacked_ship, Grid* attacked_grid, int attacked_location) = 0;
// - DO NOT CALL THIS FUNCTION
// - Actually perform the ship-specific attack methods.
// - Return NULL if no ship was damaged in the attack.
// - Return POPULATED Grid* of the ships that were damaged ...
// - DO NOT CALL THIS FUNCTION
// --------------------------------------------------------------------------------

enum ShipType {
	CARRIER,
	BATTLESHIP,
	CRUISER,
	SUBMARINE,
	DESTROYER
};

class Ship {
public:
	// Getter & Setter Methods.
	int get_remaining_health() { return remaining_health; }
	void set_remaining_health(int h) { remaining_health = h; }

	ShipType get_ship_type() { return type; }

	bool get_wreck() { return remaining_health == 0; }

	int get_last_turn_fired() { return last_turn_fired; }
	void set_last_turn_fired(int i) { last_turn_fired = i; }

	Grid* attack(Grid* attacked_grid, int attacked_location, int turn);
	Grid* defend(Grid* defending_grid, int defend_location);

	// Required Implementation
	virtual int get_max_health() = 0;
	virtual bool can_attack(int turn) = 0;

	// Provided Default Implementation
	virtual void on_ship_destruction(Grid* ship_grid, uint32_t ship_location, Grid* damaged_ships) {};

	// Debugging Functions
	void print_ship();
	void print_ship_comp();
	string get_string_name();

protected:
	virtual Grid* do_attack(Grid* attacked_grid, int attacked_location) = 0;

	int remaining_health;
	ShipType type;
	int last_turn_fired;
};
