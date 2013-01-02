// Edited by Rachel Helmstetter

#pragma once
#include "Grid.h"
#include "Ship.h"
#include "Battleship.h"
#include "Carrier.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"

// To keep track of status of each ship when deciding which ship to move
struct ShipStatus {
	int last_location;
	int last_known_health;
	int current_health;
	bool hit_last_turn;
	bool isWrecked;
	Ship* shipType;
};

class AI {
public:
	AI(Grid* ai_grid);
	~AI();
	void set_board();	// only called when game starts
	void do_turn(Grid* grid, int turn);		// called each turn. returns ship that was hit
	bool has_lost();
	void display_ships_stats();

private:
	void AI::update_all_status();
	void update_ship_status(ShipStatus* status);
	Ship* check_ship_hits();
	bool place_ship(Grid* ai_grid, Ship* ship);
	void attack(Grid* grid_to_attack, int turn);	//returns enemy ship if one was hit
	string get_ship_type(Ship* ship);
	Ship* choose_attacking_ship();
	void add_wreck(int location);

	Grid* ai_grid;
	Battleship* battleship;
	Carrier* carrier;
	Cruiser* cruiser;
	Destroyer* destroyer;
	Submarine* submarine;

	ShipStatus battleship_status;
	ShipStatus carrier_status;
	ShipStatus cruiser_status;
	ShipStatus destroyer_status;
	ShipStatus submarine_status;

	int enemy_wrecks[4];	// used so AI doesn't attack a location with wreck 
};