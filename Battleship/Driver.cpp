#include <iostream>			//Importing all of the related files
#include "StartScreen.h"
#include "Interface.h"
#include "Grid.h"
#include "Ship.h"
#include "highscores.h"
#include "Battleship.h"
#include "Carrier.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
#include "AI.h"
#include <string>
#include <stdlib.h>
#include <crtdbg.h>
#include <fstream>

using namespace std;
//Edited by Forrest Falk

int menuInput=0, gameInput=0, fireHere = 0, j=0;	//Declare global variables
string sameN;
char names[15];
char* m;
bool canMove=true;

Grid* p1 = NULL;		//Declaring the pointers as global variables
Grid* p2 = NULL;
Battleship* c1 = NULL;
Destroyer* c2 = NULL;
Cruiser* c3 = NULL;
Carrier* c4 = NULL;
Submarine* c5 = NULL;
AI* a1 = NULL;


//Forward delcalarations

void gameSwitch(void);
void mainMenu(void);
void logicTest(void);

//Creates a menu that gives the user the options to 
//fire, move ship, see health of their ships, see health of computer's ships, skip turn, or end game

void gameSwitch(void){			
	if(a1->has_lost()){			//checks to see if all comp ships are wrecked (Player Wins Game).
		wonGame();				//Prints the Won game desplay
		pause(3);
		sameN=getname();		//Set the name string into an array
		for(j=0; j < sameN.length();j++)	//Move each element into the array
			names[j]=sameN[j];
		m=names;
		highscore(m,turn-1);	//Check to see if the player got a highscore and display highscores
		pause(5);
		erase();
		start();			//display start menu
		mainMenu();			//start main menu swicth statement
		return;
	}
	if((c1->get_wreck())&&(c2->get_wreck())&&(c3->get_wreck())&&(c4->get_wreck())&&(c5->get_wreck())){ //Check to see if all of the player's ships are wrecked (PLayer Loss Game).
		lostGame();		//Prints the lost game display
		pause(3);
		print();		//Prints out all of the highscores
		pause(5);	
		erase();
		start();		//display start menu
		mainMenu;		//start main menu switch statement
	}
		erase();
		headsUp(getTurn());		//Print out the heads up display
	    inGameMenu();			//Print out the in game menu
		cin >> gameInput;		//obtain user's input

		switch(gameInput){
			case 1:		//Fire at an enemy ship
				erase();			
				headsUp(getTurn());	//Prints the heads up display
				canMove=true;						//allow the user to move a ship next turn
				switch(fireMenu()){
				case 1:
					if (c4->get_wreck()) {
						erase();
						headsUp(turn);		//Display Heads up
						cout << " You can not fire the Carrier because it is destroyed." << endl;
						cout << endl << endl << endl << endl << endl;
						pause(3);
						gameSwitch();	//Go back to Game menu
					}
					else {
						fireHere=fireLocation();		//fire Carrier and ask where to fire.
						fireHit(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck());//Check to see if a location has a ship and tells user if they hit or missed the shot
						if(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck()){		//Checks to see if there is a ship there and its not wrecked.
							cout << "You have hit an enemy " << WhereDidItHit(fireHere, p2->get_ship(fireHere)->get_ship_type()) << " at " << fireHere << "!" << endl;
							pause(4);
						}
						delete c4->attack(p2, fireHere, getTurn());	//actually attacks the gird now
					}
					break;
				case 2:
					if (c3->get_wreck()) {
						erase();
						headsUp(turn);		//Display Heads up
						cout << " You can not fire the Cruiser because it is destroyed." << endl;
						cout << endl << endl << endl << endl << endl;
						pause(3);
						gameSwitch();	//Go back to Game menu
					}
					else {
						fireHere=fireLocation();		//fire Cruiser and ask where to fire.
						fireHit(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck());	//Check to see if a location has a ship and tells user if they hit or missed the shot
						if(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck()){		//Checks to see if there is a ship there and its not wrecked.
							cout << "You have hit an enemy " << WhereDidItHit(fireHere, p2->get_ship(fireHere)->get_ship_type()) << " at " << fireHere << "!" << endl;
							pause(4);
						}
						 delete c3->attack(p2, fireHere, getTurn());	//actually attacks the gird now
					}
					break;
				case 3:
					if (c5->get_remaining_health() == 0) {
						erase();
						headsUp(turn);		//Display Heads up
						cout << "You can not fire the Submarine because it is destroyed." << endl;
						cout << endl << endl << endl << endl << endl;
						pause(3);
						gameSwitch();	//Go back to Game menu
					}
					else if(c5->get_last_turn_fired()==(turn-2)){	//Checks if the submarine was fired last turn
						erase();
						headsUp(turn);		//Display Heads up
						cout << " You can only fire the Submarine every other turn!" << endl;
						cout << endl << endl << endl << endl << endl;
						pause(3);
						gameSwitch();	//Go back to Game menu
					}
					else{
						fireHere=fireLocation();
						if(p2->get_ship(fireHere)!=NULL)	//If the grid location is not empty the player hit a ship
							cout << "You " << WhereDidItHitSub(fireHere, p2->get_ship(fireHere)->get_ship_type()) << fireHere << "!" << endl;
						else		//If the spot is empty the player has missed
							cout << "Your shot missed at " << fireHere << " !" << endl;
						if(p2->get_ship(fireHere+1)!=NULL)		//If the grid location is not empty the player hit a ship
							cout << "You " << WhereDidItHitSub(fireHere+1, p2->get_ship(fireHere+1)->get_ship_type()) << fireHere+1 << "!" << endl;
						else		//If the spot is empty the player has missed
							cout << "Your shot missed at " << fireHere+1 << " !" <<  endl;
						if(p2->get_ship(fireHere+2)!=NULL)		//If the grid location is not empty the player hit a ship
							cout << "You " << WhereDidItHitSub(fireHere+2, p2->get_ship(fireHere+2)->get_ship_type()) << fireHere+2 << "!" << endl;
						else		//If the spot is empty the player has missed
							cout << "Your shot missed at " << fireHere+2 << " !" <<  endl;
						pause(6);

						 delete c5->attack(p2, fireHere, getTurn());	//actually attacks the gird now
					}
					break;	
				case 4:
					if (c1->get_wreck()) {
						erase();
						headsUp(turn);		//Display Heads up
						cout << " You can not fire the Battleship because it is destroyed." << endl;
						cout << endl << endl << endl << endl << endl;
						pause(3);
						gameSwitch();	//Go back to Game menu
					}
					else {
						fireHere=fireLocation();		//fire Battleship and ask where to fire.
						fireHit(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck());	//Check to see if a location has a ship and tells user if they hit or missed the shot
						if(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck()){		//If the grid location is not empty the player hit a ship
							cout << "You have hit an enemy " << WhereDidItHit(fireHere, p2->get_ship(fireHere)->get_ship_type()) << " at " << fireHere << "!" << endl;
							pause(4);
						}
						delete c1->attack(p2, fireHere, getTurn());	//actually attacks the gird now	
					}
					break;
				case 5:
					if (c2->get_wreck()) {
						erase();
						headsUp(turn);		//Display Heads up
						cout << " You can not fire the Destroyer because it is destroyed." << endl;
						cout << endl << endl << endl << endl << endl;
						pause(3);
						gameSwitch();	//Go back to Game menu
					}
					else {
						fireHere=fireLocation();		//fire Destroyer and ask where to fire.
						fireHit(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck());	//Check to see if a location has a ship and tells user if they hit or missed the shot
						if(p2->has_ship(fireHere) && !p2->get_ship(fireHere)->get_wreck()){		//If the grid location is not empty the player hit a ship
							cout << "You have hit an enemy " << WhereDidItHit(fireHere, p2->get_ship(fireHere)->get_ship_type()) << " at " << fireHere << "!" << endl;
							pause(4);
						}
						delete c2->attack(p2, fireHere, getTurn());	//actually attacks the gird now
					}
					break;

				default:		//If user enters a number not 1-6, then invalid input is printed along with the menu again.
					erase();
					cout << "Invalid Input" << endl;
					pause(2);
					fireMenu();	//Reprints menu for the user to choose from again
				}
				plusTurn();			//Adds one to the turn counter.
				headsUp(getTurn());		//Print the heads up display
				compTurn();				//Tells the user that the computer is now going to move
				erase();
				headsUp(getTurn());		//Print the heads up display
				a1->do_turn(p1, turn);		//The computer now takes its turn
				pause(5);
				plusTurn();			//Adds 1 to the player's turn
				gameSwitch();		//Calls the game menu
				break;
			case 2:		//Move a ship!
				erase();
				headsUp(getTurn());		//Prints out the heads up display.
				if(canMove){		//Checks if the user already moved a ship this turn.
					switch(moveMenu()){		
					case 1:
						if(p1->move_ship(c4, moveWhere())){	 //Check to see if the Carrier can be moved to the new location and move it.
							erase();
							headsUp(turn);		//Display heads up
							cout << " Your ship has sailed to its new location!";
							cout << endl << endl << endl << endl;
							canMove = false;	//changed to false to allow the user 1 ship move per turn.
							pause(3);
						}else{			//If there is already a ship in the new location warn the user
							erase();
							headsUp(turn);	//Display heads up
							cout << " Warning: A ship is already in that location or your ship has been destroyed in battle!";
							cout << endl << endl << endl << endl;
							pause(3);
						}

						break;
					case 2:
						if(p1->move_ship(c3, moveWhere())){		//Check to see if the Cruiser can be moved to the new location and move it.
							erase();
							headsUp(turn);		//Display heads up
							cout << " Your ship has sailed to its new location!";
							cout << endl << endl << endl << endl;
							canMove = false;	//changed to false to allow the user 1 ship move per turn
							pause(3);
						}else{			//If there is already a ship in the new location warn the user
							erase();
							headsUp(turn);		//Display heads up
							cout << " Warning: A ship is already in that location!";
							cout << endl << endl << endl << endl;
							pause(3);
						}

						break;
					case 3:
						if(p1->move_ship(c5, moveWhere())){		//Check to see if the Submarine can be moved to the new location and move it.
							erase();
							headsUp(turn);		//Display heads up
							cout << " Your ship has sailed to its new location!";
							cout << endl << endl << endl << endl;
							canMove = false;	//changed to false to allow the user 1 ship move per turn
							pause(3);
						}else{			//If there is already a ship in the new location warn the user
							erase();
							headsUp(turn);		//Display heads up
							cout << " Warning: A ship is already in that location!";
							cout << endl << endl << endl << endl;
							pause(3);
						}

						break;
					case 4:
						if(p1->move_ship(c1, moveWhere())){		//Check to see if the Battleship can be moved to the new location and move it.
							erase();
							headsUp(turn);		//Display heads up
							cout << " Your ship has sailed to its new location!";
							cout << endl << endl << endl << endl;
							canMove = false;	//changed to false to allow the user 1 ship move per turn
							pause(3);
						}else{			//If there is already a ship in the new location warn the user
							erase();
							headsUp(turn);		//Display heads up
							cout << " Warning: A ship is already in that location!";
							cout << endl << endl << endl << endl;
							pause(3);
						}

						break;
					case 5:
						if(p1->move_ship(c2, moveWhere())){		//Check to see if the Destroyer can be moved to the new location and move it.
							erase();
							headsUp(turn);		//Display heads up
							cout << " Your ship has sailed to its new location!";
							cout << endl << endl << endl << endl;
							canMove = false;	//changed to false to allow the user 1 ship move per turn
							pause(3);
						}else{			//If there is already a ship in the new location warn the user
							erase();
							headsUp(turn);		//Display heads up
							cout << " Warning: A ship is already in that location!";
							cout << endl << endl << endl << endl;
							pause(3);
						}

						break;

					default:		// If the user doesn't enter 1-5, tell the user they entered an invalid input
						erase();
						cout << "Invalid Input" << endl;
						pause(2);
						moveMenu(); //Reprint the move menu
					}
				}else{		//If the user tries to move a ship 2 or more times, tell them they can only do it once per turn
					headsUp(turn);
					cout << " You can only move a ship once per turn!" << endl;
					spacing(10);
					pause(3);
				}
				gameSwitch();	//Go back to game menu
				break;
			case 3:		//Display the player's ships and their health
				erase();
				headsUp(getTurn());		//Display headsup
				p1->print_grid();		//Print out player's remaining ships and health
				pause(5);
				gameSwitch();		//Go back to game menu
				break;
			case 4:		//Display the computer's ships and their health
				erase();
				headsUp(getTurn());		//Display heads up
				a1->display_ships_stats();		//Display the computers remaining ships and their health
				pause(5);
				gameSwitch();	//Jumps back to the beginning of this menu
				break;
			case 5:			//Skips the player's turn 
				erase();
				headsUp(getTurn());	//Print the heads up display
				skipTurn();			//Prints "Skipping your turn."
				plusTurn();			//Adds one to the turn counter.
				headsUp(getTurn());	//Print the heads up display
				compTurn();			//Tell the user that the computer is now taking its turn.
				erase();
				headsUp(getTurn());		//Print the heads up display
				a1->do_turn(p1, turn);		//The computer now takes its turn
				pause(5);
				plusTurn();			//Adds one to the turn counter.
				gameSwitch();		//Jumps back to the top of this menu
				break;
			case 6:		//Exit the game to the main menu

				delete c1;		//Delete current objects
				c1 = NULL;
				delete c2;
				c2 = NULL;
				delete c3;
				c3 = NULL;
				delete c4;
				c4 = NULL;
				delete c5;
				c5 = NULL;
				delete p1;
				p1 = NULL;
				delete p2;
				p2 = NULL;
				delete a1;
				a1 = NULL;

				erase();
				start();		//Print the start menu
				mainMenu();		//Jump to the main menu switch
				break;
			default:		//If a number not 1-6 is entered, Go back to the game menu
				erase();
				gameSwitch();	// Go back to game menu
		}
}


void mainMenu(void){
	
		
		menuInput = 0;		//Reset menu input
		cin>>menuInput;		//Grabs the users input


		switch (menuInput){
		case 1:				//If the user enters 1 start the game

			erase();
			gridSize();				//Calls the GridSize to get the size of the grid and ask the player where to plavce ships.

			p1 = new Grid(getGridSize());		//Creates two new grid objetcs, p1 is the player's grid, p2 is the computer's grid.
			p2 = new Grid(getGridSize());
			c1 = new Battleship();		//Creates all of the objects for the ships
			c2 = new Destroyer();		//C1-C5 are player ships
			c3 = new Cruiser();
			c4 = new Carrier();
			c5 = new Submarine();
			a1 = new AI(p2);		//Creates the computer's AI object
			

			p1->add_ship(getBattle(), c1);		//Places the player's Battleship
		    p1->add_ship(getDestroyer(), c2);	//Places the player's Destroyer
			p1->add_ship(getCruiser(), c3);		//Places the player's Cruiser
			p1->add_ship(getCarrier(), c4);		//Places the player's Carrier
			p1->add_ship(getSub(), c5);			//Places the player's Submarine

			a1->set_board();		//The computer adds ships to its grid
			
			erase();
			resetTurn();			//Set the turn back to 1.
			gameSwitch();			//Go to the game menu
			
			break;
		case 2:				//If the user enters 2 show the high scores
			erase();		
			file_open();	//Open the highscore.txt file
			print();		//Print out the highscores from the file
			spacing(15);
			pause(5);
			erase();
			start();
			mainMenu();
			break;
		case 3:				//If the user enters 3 exit the game
			erase();

			delete c1;		//Delete current objects
			c1 = NULL;
			delete c2;
			c2 = NULL;
			delete c3;
			c3 = NULL;
			delete c4;
			c4 = NULL;
			delete c5;
			c5 = NULL;
			delete p1;
			p1 = NULL;
			delete p2;
			p2 = NULL;
			delete a1;
			a1 = NULL;
			exit (1);		//Exit the program
			break;
		case 4:
			logicTest();
			break;
		default:		//Reprint the selection menu if another number is entered
			erase();
			start();		//Print the start menu
			mainMenu();		//Start the main menu switch
			break;
		}
}

void main() {

		startup();		//Calls the startup method from the StartScreen.h 
		mainMenu();		//Starts up the main game interface.

		delete c1;		//Delete current objects
		c1 = NULL;
		delete c2;
		c2 = NULL;
		delete c3;
		c3 = NULL;
		delete c4;
		c4 = NULL;
		delete c5;
		c5 = NULL;
		delete p1;
		p1 = NULL;
		delete p2;
		p2 = NULL;
		delete a1;
		a1 = NULL;
}
