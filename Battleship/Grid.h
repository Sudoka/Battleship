// Written by Aaron Ogata
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <assert.h>

using namespace std;
class Ship;

// --------------------------------------------------------------------------------
// For the purposes of being able to demonstrate that we have full knowledge of a
// linked list, we will implement the Grid class so that the list is always sorted.
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// GRID API
// --------------------------------------------------------------------------------
// Grid(uint32_t max_size);
// - Constructor for this grid. The grid will have a maximum size of "max_size".
// ~Grid();
// - Destructor for this grid. The Ship* variables associated with each unit are NOT freed.
// - You will have to do something like this if you want to free the Ship* variables as well:
// - for(int i = 0; i < grid->get_max_size(); i++)
// -     delete remove_ship(i);
// - delete grid;
// uint32_t get_max_size();
// - Return the maximum size for this grid.
// bool add_ship(uint32_t location, Ship* ship);
// - Add the ship "ship" to location "location".
// - Return true if ship was added successfully.
// - Return false if 1. Location was invalid.
// - Return false if 2. A ship already exists at this location.
// bool add_grid(Grid* g);
// - Add all ships from grid "g" to this grid.
// - Return true if all ships were successfully added (no conflicts).
// - Return false if grid "g" contains a location in which there is Ship A and
// -   this grid also contains a ship B in this location, which is different from
// -   ship A.
// Ship* get_ship(uint32_t location);
// - Return the ship at location "location".
// - Return NULL if no ship exists at this location.
// bool has_ship(uint32_t location);
// - Return true if this location contains a ship.
// - Return false if this location does not contain a ship.
// bool move_ship(uint32_t old_location, uint32_t new_location);
// - Move the ship that was at "old_location" to "new_location".
// - Return true if the ship was moved successfully.
// - Return false if 1. There was no ship at "old_location"
// - Return false if 2. add_ship(new_location, ship @ old_location) failed.
// -   1. Location was invalid.
// -   2. A ship already exists at this location.
// - If this function returns false, the grid will remain unchanged.
// Ship* remove_ship(uint32_t location);
// - Remove the ship at location "location".
// - Return the ship object, if a ship existed at this location.
// - Return NULL if no ship was here.
// - Warning! Will not delete the ship pointer for you, you will have to do this manually.
// - delete remove_ship(location); // In C++, it is safe to delete a null pointer.
// --------------------------------------------------------------------------------
// DEBUGGING FUNCTIONS AND PRIVATE FUNCTIONS ARE NOT DESCRIBED.

struct GridUnit {
	uint32_t location;
	Ship* ship;
	GridUnit* prev;
	GridUnit* next;
};

class Grid {
public:
	Grid(uint32_t max_size);
	~Grid();

	uint32_t get_max_size() { return max_size; }
	GridUnit* get_head() { return head; }
	GridUnit* get_tail() { return tail; }

	bool add_ship(uint32_t location, Ship* ship);
	bool add_grid(Grid* g);
	Ship* get_ship(uint32_t location);
	bool has_ship(uint32_t location);
	bool move_ship(Ship* ship, uint32_t new_location);
	bool move_ship(uint32_t old_location, uint32_t new_location);
	Ship* remove_ship(uint32_t location);
	
	// AI Functions
	// Return the GridUnit* that occurs before location "location".
	// Example:
	// <25 37 45 67>
	// get_unit_before_location(25): NULL
	// get_unit_before_location(37): 25
	// get_unit_before_location(36): 25
	// get_unit_after_location(50): 67
	// get_unit_after_location(67): NULL
	GridUnit* get_unit_before_location(uint32_t location);
	GridUnit* get_unit_after_location(uint32_t location);

	// Debugging Functions
	void print_grid();
	void print_grid_comp();
	void iterate_forwards(void (*function)(GridUnit*));
	void iterate_backwards(void (*function)(GridUnit*));
	uint32_t count_ships();
private:
	GridUnit* _find_gridunit_before_location(uint32_t location);
	GridUnit* _remove_and_return_location(uint32_t location);

	uint32_t max_size;
	GridUnit* head;
	GridUnit* tail;
};
