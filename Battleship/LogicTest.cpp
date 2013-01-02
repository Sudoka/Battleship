// Written by Aaron Ogata
// Logic Testing for Grid.cpp, Ship.cpp, AI.cpp and related.
// -----------------------------------------------------
// The following code is for memory leak detection.
// Don't touch it.
#define _CRTDBG_MAPALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
// -----------------------------------------------------

// Uncomment this line to enable debug messages.
// #define DEBUG_ON

#include "AI.h"
#include "Grid.h"
#include "Ship.h"
#include "Battleship.h"
#include "Carrier.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
#include <iostream>

using namespace std;

// Debugging Macros
#define BEGIN_TEST(__NAME__, __SIZE__) { cout << (__NAME__) << endl; Grid* P1_GRID__ = new Grid(__SIZE__); Grid* P2_GRID__ = new Grid(__SIZE__); bool FAILED__ = false; bool SILENT__ = false;
#define BEGIN_SILENT_TEST(__NAME__, __SIZE__) { Grid* P1_GRID__ = new Grid(__SIZE__); Grid* P2_GRID__ = new Grid(__SIZE__); bool FAILED__ = false; bool SILENT__ = true;
#define P1_GRID() P1_GRID__
#define P2_GRID() P2_GRID__
#define CORRECT_IF_TRUE(__X__) if(!(__X__)) { cout << "Failed: " << #__X__ << endl; FAILED__ = true; cout << "[P1 Grid]" << endl; P1_GRID__->print_grid(); cout << "[P2 Grid]" << endl; P2_GRID__->print_grid(); system("pause"); }
#define END_TEST() delete P1_GRID__; delete P2_GRID__; if(!FAILED__ && !SILENT__) { cout << "Passed." << endl; } }

void logicTest() {
	// -----------------------------------------------------
	// The following code is for memory leak detection.
	// Don't touch it.
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// -----------------------------------------------------

	// Test 1: Test Carrier death sequence: If carrier dies, carrier will hit 2 ships ahead for 1 damage each.
	BEGIN_TEST("Test #1: Carrier Death.", 6);
	Cruiser* a1 = new Cruiser();
	Carrier* c1 = new Carrier();
	Cruiser* c2 = new Cruiser();
	Cruiser* c3 = new Cruiser();
	Cruiser* c4 = new Cruiser();
	CORRECT_IF_TRUE(P1_GRID()->add_ship(0, a1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(2, c1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(3, c2));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(4, c3));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(5, c4));
	// Carrier has 5 HP.
	for(int i = 0; i < 5; i++) {
		Grid* g = a1->attack(P2_GRID(), 2, 1);
		delete g;
	}
	CORRECT_IF_TRUE(c1->get_wreck());
	CORRECT_IF_TRUE(c2->get_remaining_health() == 2);
	CORRECT_IF_TRUE(c3->get_remaining_health() == 2);
	CORRECT_IF_TRUE(c4->get_remaining_health() == 3);
	delete a1; delete c1; delete c2; delete c3; delete c4;
	END_TEST();

	// Test 2: Test Submarine Attack Sequence. Submarines can only attack every other turn.
	BEGIN_TEST("Test #2: Submarine Attack.", 6);
	Submarine* a1 = new Submarine();
	Cruiser* c1 = new Cruiser();
	Cruiser* c2 = new Cruiser();
	Cruiser* c3 = new Cruiser();
	Cruiser* c4 = new Cruiser();
	CORRECT_IF_TRUE(P1_GRID()->add_ship(0, a1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(2, c1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(3, c2));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(4, c3));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(5, c4));
	{
		Grid* g = a1->attack(P2_GRID(), 2, 1); // Player #1, Turn #1
		CORRECT_IF_TRUE(g != NULL);
		CORRECT_IF_TRUE(g->has_ship(2));
		CORRECT_IF_TRUE(g->get_ship(2)->get_remaining_health() == 2);
		CORRECT_IF_TRUE(c1->get_remaining_health() == 2);
		CORRECT_IF_TRUE(c2->get_remaining_health() == 2);
		CORRECT_IF_TRUE(c3->get_remaining_health() == 2);
		delete g;
	}
	{
		Grid* g = a1->attack(P2_GRID(), 2, 3); // Player #1, Turn #2
		CORRECT_IF_TRUE(g == NULL);
		delete g;
	}
	{
		Grid* g = a1->attack(P2_GRID(), 2, 5); // Player #1, Turn #3
		CORRECT_IF_TRUE(g != NULL);
		delete g;
	}
	CORRECT_IF_TRUE(c1->get_remaining_health() == 1);
	CORRECT_IF_TRUE(c2->get_remaining_health() == 1);
	CORRECT_IF_TRUE(c3->get_remaining_health() == 1);
	CORRECT_IF_TRUE(c4->get_remaining_health() == 3);
	delete a1; delete c1; delete c2; delete c3; delete c4;
	END_TEST();

	// Test 3: Test Submarine Death Sequence. Submarines will remove themself from the grid, instead of sinking, when they are destroyed.
	BEGIN_TEST("Test #3: Submarine Death.", 6);
	Cruiser* a1 = new Cruiser();
	Submarine* d1 = new Submarine();
	CORRECT_IF_TRUE(P1_GRID()->add_ship(0, a1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(2, d1));
	CORRECT_IF_TRUE(P2_GRID()->get_ship(2) == d1);
	// Submarine has 2 HP.
	for(int i = 0; i < 2; i++) {
		Grid* g = a1->attack(P2_GRID(), 2, 1);
		delete g;
	}
	CORRECT_IF_TRUE(d1->get_wreck());
	CORRECT_IF_TRUE(P2_GRID()->get_ship(2) == NULL);
	delete a1; delete d1;
	END_TEST();

	// Test 4: Test if a submarine still attacks the adjacent squares, if there is no ship on the square it was commanded to attack.
	BEGIN_TEST("Test #4: Submarine Attack (Adjacent).", 6);
	Submarine* a1 = new Submarine();
	Cruiser* c1 = new Cruiser();
	Cruiser* c2 = new Cruiser();
	Cruiser* c3 = new Cruiser();
	Cruiser* c4 = new Cruiser();
	CORRECT_IF_TRUE(P1_GRID()->add_ship(0, a1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(2, c1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(3, c2));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(4, c3));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(5, c4));
	{
		Grid* g = a1->attack(P2_GRID(), 0, 1); // Player #1, Turn #1
		CORRECT_IF_TRUE(g != NULL);
		CORRECT_IF_TRUE(c1->get_remaining_health() == 2);
		CORRECT_IF_TRUE(c2->get_remaining_health() == 3);
		CORRECT_IF_TRUE(c3->get_remaining_health() == 3);
		delete g;
	}
	{
		Grid* g = a1->attack(P2_GRID(), 1, 5); // Player #1, Turn #5
		CORRECT_IF_TRUE(g != NULL);
		CORRECT_IF_TRUE(c1->get_remaining_health() == 1);
		CORRECT_IF_TRUE(c2->get_remaining_health() == 2);
		CORRECT_IF_TRUE(c3->get_remaining_health() == 3);
		delete g;
	}
	delete a1; delete c1; delete c2; delete c3; delete c4;
	END_TEST();

	BEGIN_TEST("Test #5: Grid add_ship().", 6);
	Cruiser* a1 = new Cruiser();
	Cruiser* c1 = new Cruiser();
	Cruiser* c2 = new Cruiser();
	Cruiser* c3 = new Cruiser();
	Cruiser* c4 = new Cruiser();
	CORRECT_IF_TRUE(P1_GRID()->add_ship(0, a1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(2, c1));
	CORRECT_IF_TRUE(!P2_GRID()->add_ship(2, c2));
	delete a1; delete c1; delete c2; delete c3; delete c4;
	END_TEST();

	// Test 6: Test if you can move a ship onto a location with a wreckage.
	BEGIN_TEST("Test #6: Grid move_ship().", 6);
	Cruiser* a1 = new Cruiser();
	Cruiser* c1 = new Cruiser();
	Cruiser* c2 = new Cruiser();
	Cruiser* c3 = new Cruiser();
	Cruiser* c4 = new Cruiser();
	CORRECT_IF_TRUE(P1_GRID()->add_ship(0, a1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(2, c1));
	CORRECT_IF_TRUE(P2_GRID()->add_ship(3, c2));
	for(int i = 0; i < 3; i++)
	{
		Grid* g = a1->attack(P2_GRID(), 2, 1); // Player #1, Turn #1
		CORRECT_IF_TRUE(g != NULL);
		CORRECT_IF_TRUE(c1->get_remaining_health() == 3 - i - 1);
		CORRECT_IF_TRUE(c2->get_remaining_health() == 3);
		delete g;
	}
	CORRECT_IF_TRUE(c1->get_wreck());
	CORRECT_IF_TRUE(!P2_GRID()->move_ship(3, 2));
	delete a1; delete c1; delete c2; delete c3; delete c4;
	END_TEST();

	// AI Test - Test the AI 10000 to make sure there are no bugs where the AI enters an infinite loop, crashes, and/or fails to act.
	int total = 0;
	int count = 0;
	for(int j = 0; j < 10000; j++) {
		BEGIN_SILENT_TEST("AI Test", 10);
		AI* a1 = new AI(P1_GRID());
		AI* a2 = new AI(P2_GRID());
		a1->set_board(); // Warning! This function does not provide a way to see if ships were successfully placed.
		a2->set_board(); // Warning! This function does not provide a way to see if ships were successfully placed.
		uint32_t turn = 1;
		while(!a1->has_lost() && !a2->has_lost()) {
			std::cout.setstate(std::ios::failbit); // Disable output messages of the do_turn() function.
			a1->do_turn(P2_GRID(), turn++);
			std::cout.clear();
			CORRECT_IF_TRUE(P1_GRID()->count_ships() == 5 || P1_GRID()->count_ships() == 4);
			CORRECT_IF_TRUE(P2_GRID()->count_ships() == 5 || P2_GRID()->count_ships() == 4);
			if(a2->has_lost()) continue;
			std::cout.setstate(std::ios::failbit); // Disable output messages of the do_turn() function.
			a2->do_turn(P1_GRID(), turn++);
			std::cout.clear();
			CORRECT_IF_TRUE(P1_GRID()->count_ships() == 5 || P1_GRID()->count_ships() == 4);
			CORRECT_IF_TRUE(P2_GRID()->count_ships() == 5 || P2_GRID()->count_ships() == 4);
			if(turn > 1000) {
				CORRECT_IF_TRUE(false);
				break;
			}
//			system("pause");
		}

		total += turn;
		count++;

		if(j % 50 == 0)
			cout << "Iteration #" << j << " Average Turn Length: " << (double)total/count << endl;
		
		delete a1;
		delete a2;
		END_TEST();
	}
	cout << "Average Turn Length: " << (double)total/count << endl;

	// -----------------------------------------------------
	// The following code is for memory leak detection.
	// Don't touch it.
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
	_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
	// Some detected "leaks" are false positives due to the global variables!
	cout << "Note: Some of the detected \"leaks\" are false positives due to the global variables." << endl;
	_CrtDumpMemoryLeaks();
	// -----------------------------------------------------

	system("pause");
}
