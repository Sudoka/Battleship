// Edited by Rachel Helmstetter
// Class Definition: Define the objects and methods needed for the AI
//					 in Battleship. 

#include "AI.h"
#include <iostream>


AI::AI(Grid* ai_grid) {
	this->ai_grid = ai_grid;
	this->battleship = new Battleship();
	this->carrier = new Carrier();
	this->cruiser = new Cruiser();
	this->destroyer = new Destroyer();
	this->submarine = new Submarine();

	// Initializes current health and last known health of each ship to
	// the respective max health
	battleship_status.current_health = battleship->get_max_health();
	carrier_status.current_health = carrier->get_max_health();
	cruiser_status.current_health = cruiser->get_max_health();
	destroyer_status.current_health = destroyer->get_max_health();
	submarine_status.current_health = submarine->get_max_health();

	battleship_status.last_known_health = battleship->get_max_health();
	carrier_status.last_known_health = carrier->get_max_health();
	cruiser_status.last_known_health = cruiser->get_max_health();
	destroyer_status.last_known_health = destroyer->get_max_health();
	submarine_status.last_known_health = submarine->get_max_health();

	battleship_status.shipType = battleship;
	carrier_status.shipType = carrier;
	cruiser_status.shipType = cruiser;
	destroyer_status.shipType = destroyer;
	submarine_status.shipType = submarine;

	battleship_status.hit_last_turn = false;
	carrier_status.hit_last_turn = false;
	cruiser_status.hit_last_turn = false;
	destroyer_status.hit_last_turn = false;
	submarine_status.hit_last_turn = false;

	battleship_status.isWrecked = false;
	carrier_status.isWrecked = false;
	cruiser_status.isWrecked = false;
	destroyer_status.isWrecked = false;
	submarine_status.isWrecked = false;

	// set all last_location to NULL as they have not been placed yet
	battleship_status.last_location = -1;
	carrier_status.last_location = -1;
	cruiser_status.last_location = -1;
	destroyer_status.last_location = -1;
	submarine_status.last_location = -1;

}

AI::~AI() {
	delete battleship;
	delete carrier;
	delete cruiser;
	delete destroyer;
	delete submarine;
}

// Called when game begins. Places each ship on board. 
void AI::set_board() {
	place_ship(ai_grid, battleship);
	place_ship(ai_grid, carrier);
	place_ship(ai_grid, cruiser);
	place_ship(ai_grid, destroyer);
	place_ship(ai_grid, submarine);
}

// Goes through each step in the turn.
// First checks for any ships that were hit last turn.
// Moves the most important ship that was damaged.
// Then attacks and increases turn count
void AI::do_turn(Grid* grid_to_attack, int turn) {
	update_all_status();

	Ship* hit_ship = check_ship_hits();
//	cout << "do_turn()" << endl;
	if (hit_ship != NULL) {
//		cout << "Do Move." << endl;
		place_ship(ai_grid, hit_ship);
	}

	attack(grid_to_attack, turn);
	
}

// Checks that all ships health is 0. Returns true if lost
bool AI::has_lost() {
	update_all_status();
	int remainingHealth = 0;
	remainingHealth += battleship_status.current_health;
	remainingHealth += carrier_status.current_health;
	remainingHealth += cruiser_status.current_health;
	remainingHealth += destroyer_status.current_health;
	remainingHealth += submarine_status.current_health;
	
	if (remainingHealth == 0) return true;
	else return false;
}

// Displays ships current health
void AI::display_ships_stats() {
	cout << "Ship\t\t     Health" << endl;
	cout << "---------------------------" << endl;
	cout << "Carrier\t\t\t" << carrier->get_remaining_health() << "/" << carrier->get_max_health() << endl;
	cout << "Battleship\t\t" << battleship->get_remaining_health() << "/" << battleship->get_max_health() << endl;
	cout << "Cruiser\t\t\t" << cruiser->get_remaining_health() << "/" << cruiser->get_max_health() << endl;
	cout << "Destroyer\t\t" << destroyer->get_remaining_health() << "/" << destroyer->get_max_health() << endl;
	cout << "Submarine\t\t" << submarine->get_remaining_health() << "/" << submarine->get_max_health() << endl;

}

// Updates shipStatus for each ship
void AI::update_all_status() {
	update_ship_status(&battleship_status);
	update_ship_status(&carrier_status);
	update_ship_status(&cruiser_status);
	update_ship_status(&destroyer_status);
	update_ship_status(&submarine_status);
}

// Updates shipStatus. Checks if ships was hit last turn or is it is wrecked.
void AI::update_ship_status(ShipStatus* status) {
	Ship* ship = status->shipType;
	status->hit_last_turn = false;	//resets last turn hit
	int current = ship->get_remaining_health();
	if (current == 0)		// Check if wrecked first so AI won't try to move it
		status->isWrecked = true;
	// If current health is different than last known health, the ship was hit last turn
	if (current != 0 && status->last_known_health != current) {
//		cout << "set hit" << endl;
		status->hit_last_turn = true;	
	}
	status->current_health = current;
	status->last_known_health = current;		//resets last know health to current
}

// Checks all ships to see which were hit.
// Goes in priority of which ship to move if more than one was hit.
// Meaning: If submarine and cruiser were both hit(damaged), it would be more
// important to move the submarine, so that is what would return as only one ship
// can be moved each turn
Ship* AI::check_ship_hits() {
	if (submarine_status.hit_last_turn)
		return submarine_status.shipType;
	else if (cruiser_status.hit_last_turn)
		return cruiser_status.shipType;	
	else if (destroyer_status.hit_last_turn)
		return destroyer_status.shipType;
	else if (battleship_status.hit_last_turn)
		return battleship_status.shipType;
	else if (carrier_status.hit_last_turn)
		return carrier_status.shipType;
	else {
//		cout << "check_ship_hits() NULL" << endl;
		return NULL;	// If no ships were hit
	}
}

// places ship onto grid in random location
bool AI::place_ship(Grid* ai_grid, Ship* ship) {
	if (ship->get_wreck())
		return false;
	else {
		int location;
		ShipStatus* status;
		if (ship == battleship)
			status = &battleship_status;
		else if (ship == carrier)
			status = &carrier_status;
		else if (ship == cruiser)
			status = &cruiser_status;
		else if (ship == destroyer)
			status = &destroyer_status;
		else 
			status = &submarine_status;
		
		location = rand() % ai_grid->get_max_size();

		// If ship has not been placed yet:
		if (status->last_location == -1) {
//			cout << "Do Place." << endl;
			while (!ai_grid->add_ship(location, ship)) {
				location = rand() % ai_grid->get_max_size();
			}
		}
		// If moving ship:
		else {
//			cout << "Do Move." << endl;
			while (!ai_grid->move_ship(ship, location)) {
				location = rand() % ai_grid->get_max_size();
			}
		}
		
		status->last_location = location;
		return true;
	}
}

// Submarine has most powerful attack, so always try submarine first.
// All other attacks are the same, so just use same ship(battleship) for all other
// attacks as it makes no difference which ship attacks.
void AI::attack(Grid* grid_to_attack, int turn) {
	if ( !submarine->get_wreck() && submarine->can_attack(turn)) {
		int location = rand() % ai_grid->get_max_size();
		
		// Check that there is no wreck on this location
		for (int i = 0; i < 4; i++) {
			while (location == enemy_wrecks[i])
				location = rand() % ai_grid->get_max_size();
		}

		cout << "The computer attacked " << location << " with its submarine." << endl;
		delete submarine->attack(grid_to_attack, location, turn);

		//Check for any new wrecks
		for (int i = 0; i < 3; i++) {
			Ship* ship = grid_to_attack->get_ship(location+i);
			
			if (ship != NULL) 
				cout << "Your " << get_ship_type(ship) << " was hit at " << location+i << "!" << endl;
			else 
				cout << "Miss!" << endl;

			if (ship != NULL && ship->get_wreck()) {
				add_wreck(location);
			}
		}
	}
	else {
		int location = rand() % ai_grid->get_max_size();
		
		// Check that there is no wreck on this location
		for (int i = 0; i < 4; i++) {
			while (location == enemy_wrecks[i])
				location = rand() % ai_grid->get_max_size();
		}
		
		Ship* attacking_ship = choose_attacking_ship();
		if (attacking_ship == NULL) {
			return;
		}
		cout << "The computer attacked " << location << " with its " << get_ship_type(attacking_ship) << "." << endl;
		grid_to_attack = attacking_ship->attack(grid_to_attack, location, turn);
		//Check for any new wrecks
		Ship* ship = grid_to_attack->get_ship(location);		

		if (ship != NULL) {
			cout << "Your " << get_ship_type(ship) << " was hit at " << location << "!" << endl;
			if (ship->get_wreck())
					add_wreck(location);
			// Carriers and Battleships damage two units to the right
			if ((ship->get_ship_type() == CARRIER || ship->get_ship_type() == BATTLESHIP) && ship->get_wreck()) {
				for (int i = 1; i <= 2 ; i++) {
					ship = grid_to_attack->get_ship(location+i);
					if (ship != NULL) {
						cout << "Your " << get_ship_type(ship) << " was hit by wreckage." << endl;	
						if (ship->get_wreck())
							add_wreck(location);
					}
				}
			}
		}
		else 
			cout << "Miss!" << endl;

		delete grid_to_attack;
	}
}

string AI::get_ship_type(Ship* ship) {
	ShipType type = ship->get_ship_type();
	if (type == 0)
		return "Carrier";
	else if (type == 1) 
		return "Battleship";
	else if (type == 2)
		return "Cruiser";
	else if (type == 3) 
		return "Submarine";
	else if (type == 4)
		return "Destroyer";
	else
		return "Invalid ship type";

}


Ship* AI::choose_attacking_ship() {
	if (!battleship->get_wreck()) return battleship;
	else if (!carrier->get_wreck()) return carrier;
	else if (!cruiser->get_wreck()) return cruiser;
	else if (!destroyer->get_wreck()) return destroyer;
	else return NULL;
}

void AI::add_wreck(int location) {
	for (int i = 0; i < 4; i++) {
		if (enemy_wrecks[i] == NULL) {
			enemy_wrecks[i] = location;
			break;
		}
	}
}



