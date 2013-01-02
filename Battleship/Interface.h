#ifndef INTERFACE_H // if not defined
#define INTERFACE_H // define MyHeader
#include <iostream>
#include <time.h>
#include <string>

#include "StartScreen.h"
#include "Ship.h"
#include "Grid.h"
using namespace std;
//Edited by Forrest Falk

//Forward delcalarations
void gridSize(void);
int fireMenu(void);
void inGameMenu(void);
void fireHit(bool hit);
void fireSub(bool canFire);
void locationMenu(void);
void headsUp(int turn);
void skipTurn(void);
void compTurn(void);
void plusTurn(void);
void resetTurn(void);
int getTurn(void);
int fireLocation(void);
int moveMenu(void);
int moveWhere(void);
void wonGame(void);
void lostGame(void);

int grid, fire, battle, carrier, cruiser, submarine, destroyer, i, count, shipSel, moveS , turn=1, input = 0;	//Declaring variables
string name;
bool canFire, sub;
char* n;

void gridSize(void){		//Grabs the length of the of the Grid and the placement of the ships from the user.
	cout << " Let's get started with the new game of Battleship!    " << endl << endl;		
	cout << " Please enter your name in for Player 1 (3-13 Charaters, No Spaces).   " << endl << endl;
	spacing(20);
	cin >> name;
	while(name.length() < 3 || name.length() > 15){		// Checks to make sure the name is within the limits
		char name2[20];
		erase();
		cout << "Invalid number of charaters!   " << endl << endl;
		cout << " Please enter your name in for Player 1 (3-13 Charaters, No Spaces).   " << endl << endl;
		spacing(20);
		cin >> name;
	}
	erase();

	cout << " Please enter the number of grids to make the field (10-50).    " << endl;		//Asks the user how big he wants the grid to be.
	spacing(22);
	cin  >> grid;	//Places the grid size into grid
	while(grid < 10 || grid > 50){		//Checks to make sure if the input is in the limits, if not, ask to enter one that is
		erase();
		cout << "Value Out Of Bounds" << endl << endl;
		cout << " Please enter the number of grids to make the field (10-50).    " << endl;
		spacing(20);
		cin  >> grid;
	}
	erase();

	cout << endl << "Please enter the grid where you would like your battleship (0-" << grid-1 << ")" << endl ;		//Asks the user where he would like the battleship
	spacing(22);
    cin  >> battle;		//Places the battleship location into battle
	while(battle < 0  || battle > grid-1){		//Checks to see if the user's input would be somewhere on the grid.
		erase();
		cout << "Value Out Of Bounds" << endl << endl;
		cout << endl << "Please enter the grid where you would like your battleship (0-" << grid-1 << ")" << endl ;
		spacing(20);
		cin  >> battle;		//Places the battleship location into battle
	}
	erase();

	cout << endl << "Please enter the grid where you would like your carrier (0-" << grid-1 << ")" << endl ;	//Asks the user where to place the carrier
	spacing(22);	
    cin  >> carrier;			//Places the Carrier location into carrier
	while((carrier < 0  || carrier > grid-1)||(carrier == battle)){		//Checks that the ship is on the grid and not where another ship is
		if(carrier < 0  || carrier > grid-1){		//If not on the grid, tell the user the value is out of bounds
			erase();
			cout << "Value Out Of Bounds!" << endl << endl;
			cout << endl << "Please enter the grid where you would like your carrier (0-" << grid-1 << ")" << endl ;
			spacing(20);
			cin  >> carrier;	//Places the Carrier location into carrier
		}else{			//If the value is on the grid, tell the user that there must be a ship in that spot.
			erase();
			cout << "There is a ship already placed in that space." << endl << endl;
			cout << "Please enter the grid where you would like your carrier (0-" << grid-1 << ")" << endl;
			spacing(20);
			cin >> carrier;		//Places the Carrier location into carrier
		}
	}
	erase();

	cout << endl << "Please enter the grid where you would like your cruiser (0-" << grid-1 << ")" << endl ;	//Asks the user where to place the cruiser
	spacing(22);
    cin  >> cruiser;		//Places the Cruiser location into cruiser
	while((cruiser < 0  || cruiser > grid-1)||(cruiser == battle || cruiser == carrier)){		//Checks to see if it will be on the grid and also that it is not where another ship is.
		if(cruiser < 0  || cruiser > grid-1){			//If not on the grid, tell the user the value is out of bounds
			erase();
			cout << "Value Out Of Bounds" << endl << endl;
			cout << endl << "Please enter the grid where you would like your cruiser (0-" << grid-1 << ")" << endl ;
			spacing(20);
			cin  >> cruiser;		//Places the Cruiser location into cruiser
		}else{				//If the value is on the grid, tell the user that there must be a ship in that spot.
			erase();
			cout << "There is a ship already placed in that space." << endl << endl;
			cout << "Please enter the grid where you would like your cruiser (0-" << grid-1 << ")" << endl;
			spacing(20);
			cin >> cruiser;			//Places the Cruiser location into cruiser
		}
	}
	erase();

	cout << endl << "Please enter the grid where you would like your submarine (0-" << grid-1 << ")" << endl ;		//Asks the user where he would like his submarine placed
	spacing(22);
    cin  >> submarine;		//Places the submarine location into submarine
	while((submarine < 0  || submarine > grid-1)||(submarine == battle || submarine == carrier || submarine == cruiser)){		//Checks to make sure the submarine will be on the grid and is not where another ship would be
		if(submarine < 0  || submarine > grid-1){				//If not on the grid, tell the user the value is out of bounds
			erase();
			cout << "Value Out Of Bounds" << endl << endl;
			cout << endl << "Please enter the grid where you would like your submarine (0-" << grid-1 << ")" << endl ;
			spacing(20);
			cin  >> submarine;			//Places the submarine location into submarine
		}else{				//If the value is on the grid, tell the user that there must be a ship in that spot.
			erase();
			cout << "There is a ship already placed in that space." << endl << endl;
			cout << "Please enter the grid where you would like your submarine (0-" << grid-1 << ")" << endl;
		    spacing(20);
			cin >> submarine;		//Places the submarine location into submarine
		}	
	}
	erase();

	cout << endl << "Please enter the grid where you would like your destroyer (0-" << grid-1 << ")" << endl ;		//Asks the user where he would like  the destroyer placed.
	spacing(20);
    cin  >> destroyer;		//Places the destoryer location into destroyer
	while((destroyer < 0  || destroyer > grid-1)|| (destroyer == battle || destroyer == carrier || destroyer == cruiser ||destroyer == submarine)){	//Checks to see if the destroyter is on the grid and is not where another ship would be.
		if(destroyer < 0  || destroyer > grid-1){				//If not on the grid, tell the user the value is out of bounds
		cout << "Value Out Of Bounds" << endl << endl;
		cout << endl << "Please enter the grid where you would like your destroyer (0-" << grid-1 << ")" << endl ;
		cin  >> destroyer;		//Places the destoryer location into destroyer
		}else{				//If the value is on the grid, tell the user that there must be a ship in that spot.
		cout << endl << endl;
		cout << "There is a ship already placed in that space." << endl << endl;
		cout << "Please enter the grid where you would like your destroyer (0-" << grid-1 << ")" << endl;
		cin >> destroyer;		//Places the destoryer location into destroyer
		}
	}
}

void inGameMenu(void){		//Creates the in game menu
		cout << " Battleship!    " << endl << endl;
		cout << " "<< name;		//Prints the user's name
		cout << " it's your move! Please select from the following menu:" << endl << endl;
		cout << " 1. Fire at the enemy!" << endl;
		cout << " 2. Move a ship" << endl;
		cout << " 3. Display your remaining ships and their health" << endl;
		cout << " 4. Display your enemy's remaining ships and their health" << endl;
		cout << " 5. Skip Turn" << endl;
		cout << " 6. End Game" << endl;
}


int fireMenu(void){			//Creates the fire menu for the game
		cout << " Battleship    " << endl << endl;
		cout << " Please select the ship you would like to fire from." << endl<< endl;
		cout << " 1. Carrier" <<endl; 
		cout << " 2. Cruiser" <<endl;
		cout << " 3. Submarine" << endl; 
		cout << " 4. Battleship" << endl; 
		cout << " 5. Destroyer" << endl;

		cin >> shipSel;		//Captures the number from the user of what ship to fire from
		return shipSel;
}

int moveMenu(void){			//Creates the move menu, which asks the user which ship he wished to move.
		cout << " Battleship    " << endl << endl;
		cout << " Please select the ship you would like to move." << endl<< endl;
		cout << " 1. Carrier" <<endl; 
		cout << " 2. Cruiser" <<endl;
		cout << " 3. Submarine" << endl; 
		cout << " 4. Battleship" << endl; 
		cout << " 5. Destroyer" << endl;

		cin >> moveS;	//Captures the number from the user of which ship to move
		return moveS;
}

int moveWhere(void){ //Asks the player where he would like to move his ship
		erase();
		headsUp(getTurn());
		cout << " Please enter where you would like to move your ship." << endl<< endl << endl << endl << endl;
		
		cin >> moveS;		//Captures the grid number of where to move the ship
		return moveS;
}

int fireLocation(void){			//Asks the user where to attack
		erase();
		headsUp(getTurn());		//Display heads up
		cout << " Please enter the grid number to fire upon! (0-" << grid-1 << ")" << endl << endl;		//Ask the user to enter the grid in which to fire upon.
		cin >> fire;		//Places the players input into fire
		while (fire < 0 || fire > grid-1){	//Checks to see if the user is firing on the grid. If not tell the user their input is invalid
			erase();
			headsUp(getTurn());		//Display heads up
			cout << " Invalid Input!" << endl << endl;
			cout << " Please enter the grid number to fire upon! (0-" << grid-1 << ")" << endl << endl;
			cin >> fire;	//Places the players input into fire
		}
		return fire;
}

void fireHit(bool hit){			//Tells the user whether his shot hit or missed
		cout << " Firing upon grid number " << fire << "!" << endl << endl;		//Tell the user you are firing on that grid.
		pause(3); 
	
			if(!hit){
			cout << " The shot Missed!" << endl << endl;			//If hit is false, tell the user the shot missed
			cout << " There is no enemy ship located at " << fire << "!" << endl << endl;
			}
			pause(3);	//pause the results for 3 seconds.
}

void headsUp(int turn){		//Prints out the heads up display for the game
	cout << " Player: " << name << endl;		//Prints out the user's name
	cout << " Turn: " << turn << endl;			//Prints out the current turn
	cout << "________________________________________________________________________________" << endl;
	//loop for health on each grid piece, on new line (Grid may be up to 50)
	cout << " -Destroy all of the enemy ships to win the Game!" << endl;
	//loop for location of ships on grid, on new line
	cout << " -Each player has a Carrier, Cruiser, Submarine, Battleship, and Destroyer" << endl;
	cout << " -Submarines attack current grid and 2 down wind, but can only fire every other";
	cout << "  turn." << endl;
	cout << " -When a ship other than a Submarine is destroyed, it leaves wreckage." << endl;
	cout << " -Ships cannot be moved where wreckage is located." << endl;
	cout << "________________________________________________________________________________" << endl << endl;
}

void skipTurn(void){		//Tell the user that you are skipping his turn.
	cout << endl << endl << endl << endl << endl;
	cout << " Skipping your turn!";
	cout << endl << endl << endl << endl << endl;
	pause(3);
}

void compTurn(void){		//Tell the user that the computer is now taking its turn.
	cout << endl << endl << endl << endl << endl;
	cout << " The Computer is now taking its turn!";
	cout << endl << endl << endl << endl << endl;
	pause(3);
}

void wonGame(void){			//Prints out the "won game" display
	erase();
	cout << "                              Congratulations!                            "<< endl << endl;
	cout << "                                   " << name << endl << endl;
	cout << "                            You Won in only " << turn << " turns!" << endl;
	spacing(22);
	pause(3);
}

void lostGame(void){		//Prints out the "You Lose" Display
	erase();
	cout << "                          You have been defeated!                           " << endl << endl;
	cout << "                                  " << name << endl << endl;
	cout << "                 They were able to destroy your fleet in only " << turn << " turns!" << endl;
	spacing(22);
	pause(3);
}

string WhereDidItHit(int fireSpot, int whatShip){
	string shipHit;

		if (whatShip == 0)
		return "Carrier";
	else if (whatShip == 1) 
		return "Battleship";
	else if (whatShip == 2)
		return "Cruiser";
	else if (whatShip == 3) 
		return "Submarine";
	else if (whatShip == 4)
		return "Destroyer";
	else
		return "Invalid ship type";
}

string WhereDidItHitSub(int fireSpot, int whatShip){
	string shipHit;

		if (whatShip == 0)
		return "hit a Carrier at ";
	else if (whatShip == 1) 
		return "hit a Battleship at ";
	else if (whatShip == 2)
		return "hit a Cruiser at ";
	else if (whatShip == 3) 
		return "hit a Submarine at ";
	else if (whatShip == 4)
		return "hit a Destroyer at ";
	else
		return "missed completely at ";
}

void plusTurn(void){	//Increment the turn by 1.
	turn++;
}

void resetTurn(void){	//Reset the turn to 0.
	turn=1;
}

int getTurn(void){		//Return the value of turn.
	return turn;
}

int getBattle(void){	//Return where the battleship will be placed.
	return battle;
}

int getCarrier(void){	//Return where the carrier will be placed.
	return carrier;
}

int getCruiser(void){	//Return where the cruiser will be placed.
	return cruiser;
}

int getSub(void){		//Return where the submarine will be placed.
	return submarine;
}

int getDestroyer(void){	//Return where the destroyer will be placed.
	return destroyer;
}

int getGridSize(void){	//Return the size of the grid.
	return grid;
}

int getFire(void){		//Return where to fire.
	return fire;
}

string getname(void){	//Returns the player's name
	return name;
}

#endif