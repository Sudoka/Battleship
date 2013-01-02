// Written by Aaron Ogata
#include "Grid.h"
#include "Ship.h"

Grid::Grid(uint32_t max_size) {
	this->max_size = max_size;
	this->head = NULL;
	this->tail = NULL;
}

// ---------------------------------------------------------
// Will not delete the Ship* pointer for you. Might change.
// ---------------------------------------------------------
Grid::~Grid() {
	GridUnit* last = this->head;
	while(last != NULL) {
		GridUnit* next = last->next;
		delete last;
		last = next;
	}
}

// ---------------------------------------------------------
// Add the ship to location. Return true if ship was added.
// Return false if ship was not added. No two ships can occupy
// the same location.
// ---------------------------------------------------------
bool Grid::add_ship(uint32_t location, Ship* ship) {
	// Is the location valid?
	if(location >= this->max_size)
		return false;

	if(has_ship(location))
		return false;

	GridUnit* prev = _find_gridunit_before_location(location);

	GridUnit* unit = new GridUnit();
	unit->next = NULL;
	unit->prev = NULL;
	unit->location = location;
	unit->ship = ship;

	unit->prev = prev;
	unit->next = (prev != NULL ? prev->next : this->head);

	if(unit->prev != NULL) unit->prev->next = unit;
	if(unit->next != NULL) unit->next->prev = unit;
	
	if(head == NULL) head = unit;
	if(tail == NULL) tail = unit;

	while(head->prev != NULL) head = head->prev;
	while(tail->next != NULL) tail = tail->next;

	return true;
}

// Add all elements of grid into this grid. If a gridunit has the same Ship* as one already in this grid, ignore it.
// If there is a conflicting location with different ships, return false. SOME ELEMENTS WILL BE ADDED AND OTHERS NOT DEPENDING ON THE LOCATION.
bool Grid::add_grid(Grid* grid) {
	GridUnit* last = grid->head;
	while(last != NULL) {
		if(!add_ship(last->location, last->ship))
			if(last->ship != get_ship(last->location))
				return false;

		last = last->next;
	}

	return true;
}

// Return the ship if it exists. Return NULL if the location does not exist.
Ship* Grid::get_ship(uint32_t location) {
	GridUnit* prev = _find_gridunit_before_location(location);

	/* Sanity Check Version. */
	GridUnit* result = NULL;
	int count = 0;
	for(GridUnit* unit = get_head(); unit != NULL; unit = unit->next) {
		if(unit->ship != NULL && unit->location == location) {
			result = unit;
			count++;
		}
	}

	assert(count <= 1);
	assert(result == NULL || result->location == location);

	return result == NULL ? NULL : result->ship;
	/*
	if(prev != NULL && prev->next != NULL && prev->next->location == location) 
		return prev->next->ship;

	if(prev == NULL && head != NULL && head->location == location)
		return head->ship;

	return NULL;*/
}

// Return true if a ship exists at this location. Return false if a ship does not exist.
bool Grid::has_ship(uint32_t location) {
	GridUnit* prev = _find_gridunit_before_location(location);

	if(prev != NULL && prev->next != NULL && prev->next->location == location) 
		return true;

	if(prev == NULL && head != NULL && head->location == location)
		return true;

	return false;
}

// Move ship from old_location to new_location. Return true if ship was moved.
// Return false if ship was not moved. The ship will be in old_location if
// it could not be moved.
bool Grid::move_ship(uint32_t old_location, uint32_t new_location) {
	GridUnit* unit = _remove_and_return_location(old_location);
	if(unit == NULL) return false;

	bool return_val = true;
	if(!add_ship(new_location, unit->ship)) {
		bool readd_old = add_ship(old_location, unit->ship);
		assert(readd_old); // we just removed this successfully, if we can't add it again, something is wrong
		return_val = false;
	}

	delete unit;

	return return_val;
}

// Return FALSE if the ship could not be found as well.
bool Grid::move_ship(Ship* ship, uint32_t new_location) {
	GridUnit* last = this->head;
	int old_location = -1;
	while(last != NULL) {
		if(last->ship == ship)
			old_location = last->location;

		last = last->next;
	}

	if(old_location == -1) return false;

	return move_ship(old_location, new_location);
}

Ship* Grid::remove_ship(uint32_t location) {
	GridUnit* unit = _remove_and_return_location(location);

	if(unit == NULL) return NULL;

	Ship* old_ship = unit->ship;
	unit->ship = NULL;
	delete unit;

	return old_ship;
}

GridUnit* Grid::_remove_and_return_location(uint32_t location) {
	assert(location < this->max_size);
	

	GridUnit* prev = _find_gridunit_before_location(location);
	GridUnit* old_location = (prev == NULL) ? this->head : prev->next;

	if(old_location == NULL || old_location->location != location)
		return NULL;

	assert(old_location->location == location);

	// Actually delete this location.

	if(old_location->next != NULL) old_location->next->prev = prev;
	if(old_location->prev != NULL) old_location->prev->next = old_location->next;

	if(this->head == old_location) head = old_location->next;
	if(this->tail == old_location) tail = old_location->prev;

	return old_location;
}

// --------------------------------------------------------------------
// Return the GridUnit that exists directly before where the given
// location would be placed.
// Return NULL if no linked list exists yet (head == NULL).
// --------------------------------------------------------------------
GridUnit* Grid::_find_gridunit_before_location(uint32_t location) {
	GridUnit* last = this->head;
	while(last != NULL && last->next != NULL) {
		if(last->next->location >= location)
			return (last->location < location ? last : NULL);

		last = last->next;
	}

	if(last == NULL) return NULL;

	return (last->location < location ? last : NULL);
}

// --------------------------------------------------------------------
// AI Helper Functions
// --------------------------------------------------------------------
GridUnit* Grid::get_unit_before_location(uint32_t location) {
	return _find_gridunit_before_location(location);
}

GridUnit* Grid::get_unit_after_location(uint32_t location) {
	GridUnit* prev = _find_gridunit_before_location(location);
	while(prev != NULL && prev->location <= location)
		prev = prev->next;

	return prev;
}


// --------------------------------------------------------------------
// Debugging Functions
// --------------------------------------------------------------------
void Grid::iterate_forwards(void (*function)(GridUnit*)) {
	GridUnit* last = this->head;
	while(last != NULL) {
		(*function)(last);
		last = last->next;
	}
}

void Grid::iterate_backwards(void (*function)(GridUnit*)) {
	GridUnit* last = this->tail;
	while(last != NULL) {
		(*function)(last);
		last = last->prev;
	}
}

void Grid::print_grid() {
	GridUnit* last = this->head;
	while(last != NULL) {
		cout << last->location << ": ";
		if(last->ship == NULL)
			cout << "no ship";
		else
			last->ship->print_ship();
		cout << endl;
		last = last->next;
	}
}

uint32_t Grid::count_ships() {
	uint32_t shipCount = 0;
	for(GridUnit* unit = get_head(); unit != NULL; unit = unit->next) {
		if(unit->ship != NULL)
			shipCount++;
	}

	return shipCount;
}

void Grid::print_grid_comp() {
	GridUnit* last = this->head;
	while(last != NULL) {
		if(last->ship == NULL)
			cout << " no ship";
		else{
			cout << " ";
			last->ship->print_ship();
		}
		cout << endl;
		last = last->next;
	}
}
