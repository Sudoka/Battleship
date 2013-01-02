#ifndef START_H // if not defined
#define START_H // define MyHeader
#include <iostream>
#include <time.h>
using namespace std;
//Edited by Forrest Falk

//Forward delcalarations
void erase(void);
void logo(void);
void pause(int seconds);
void creators(void);
void start(void);
void ship(void);
void startup(void);
void spacing(void);


void erase(){		//Makes command prompt appear "erased"
	for(int i=0; i<60; i++)		//adds 50 blank lines 
		cout << endl;
}
void spacing (int i){
	for(int i=0; i<10; i++)		//Adds 10 blank lines to move the Battleship logo up
		cout << endl;
}
void logo(void){

	erase();	//erases window

	cout << "      BBBBBB    A    TTTTTTTTTTTT LL    EEEEE  SSSSSS HH   HH II  PPPPPP" << endl;		//Prints out Battleship Logo
	cout << "      BB  BB   AAA     TT    TT   LL    EE     SS  SS HH   HH II  PP  PP" << endl;
	cout << "      BB  BB   AAA     TT    TT   LL    EE     SS     HH   HH II  PP  PP" << endl;
	cout << "      BBBBB   AA AA    TT    TT   LL    EEEEE   SSS   HHHHHHH II  PP  PP" << endl;
	cout << "      BB  BB  AA AA    TT    TT   LL    EE        SS  HH   HH II  PPPPPP" << endl;
	cout << "      BB  BB AAAAAAA   TT    TT   LL    EE     SS  SS HH   HH II  PP"     << endl;
	cout << "      BB  BB AA   AA   TT    TT   LL    EE     SS  SS HH   HH II  PP"     << endl;
	cout << "      BBBBBB AA   AA   TT    TT   LLLLL EEEEE  SSSSSS HH   HH II  PP"	   << endl;
	
	spacing(10);
}

void pause(int seconds){		//Creates a pasue in the code based on how many seconds are needed.
	clock_t endtime;			//captures the current clock
	endtime = clock () + seconds * CLOCKS_PER_SEC ;		//Calculates the end clock based on CLOCKS_PER_SEC
	while (clock() < endtime) {}		//Keeps looping, until the endtime is no longer bigger than the current clock

}
void creators(void){

	cout << "                                  Created by:"			    << endl << endl << endl;	//Prints out all of the creators of Battleship
	cout << "                                  Nina Iarkova"		    << endl; 
	cout << "                               Rachel Helmstetter"         << endl;
	cout << "                                 Kimberly Enos  "         << endl;
    cout << "                                  Aaron Ogata"             << endl;
	cout << "                                  Adam Hensley"            << endl;
	cout << "                                  Forrest Falk"		    << endl;

	for(int i=0; i<10; i++)
		cout << endl;
}
void ship(){
	cout << endl << "                           Welcome to the game of...                    " << endl << endl;	//Prints the Intro with a Battleship
	cout << "                                             `                                  " << endl;
	cout << "                                 `           .                                  " << endl;
	cout << "                                ``           -:.                                " << endl;
	cout << "                               `           ./`                                  " << endl;
	cout << "                                `/+-.```:::-///.                                " << endl;
	cout << "                               `./+/:..`:://+//--.-.`````````                   " << endl;
	cout << "             ``````....-.-----./-//::-..:-//+-::-.-::...::-----..-.```````````  " << endl;
	cout << "  ...`....-.---.-/-..-.-..--:-..--..---.---..---..-:..--.-:-------.--...-..-..` " << endl;
	cout << "` -///////////////::::::::::::::::::::::::::::::::::::::::::::///://::::::::::-`" << endl;
	cout << "    :://+///:://////:////////////////:://////:::::::::::::::///://////:::::/::- " << endl;
	cout << "     ` ``.-----------------------------:------------------------..---.....``    " << endl;

}
void start(void){
	cout << "                                    Welcome to                          " << endl << endl;		//Prints the start menu for the game.
	cout << "      BBBBBB    A    TTTTTTTTTTTT LL    EEEEE  SSSSSS HH   HH II  PPPPPP" << endl;		//Prints out Battleship Logo
	cout << "      BB  BB   AAA     TT    TT   LL    EE     SS  SS HH   HH II  PP  PP" << endl;
	cout << "      BB  BB   AAA     TT    TT   LL    EE     SS     HH   HH II  PP  PP" << endl;
	cout << "      BBBBB   AA AA    TT    TT   LL    EEEEE   SSS   HHHHHHH II  PP  PP" << endl;
	cout << "      BB  BB  AA AA    TT    TT   LL    EE        SS  HH   HH II  PPPPPP" << endl;
	cout << "      BB  BB AAAAAAA   TT    TT   LL    EE     SS  SS HH   HH II  PP"     << endl;
	cout << "      BB  BB AA   AA   TT    TT   LL    EE     SS  SS HH   HH II  PP"     << endl;
	cout << "      BBBBBB AA   AA   TT    TT   LLLLL EEEEE  SSSSSS HH   HH II  PP    " << endl << endl << endl;
	cout << " Please select from the following menu:                                 " << endl <<endl;
	cout << " 1. Start Game															 " << endl;
    cout << " 2. High Scores														 " << endl;
    cout << " 3. Quit														         " << endl << endl;
	

}
void startup(void){	//Contains the methods in the order they need to be executed for a perfect Battleship Intro.
	ship();
	pause(3);
	logo();
	pause(1);
	erase();
	pause(.75);
	logo();
	pause(1);
	erase();
	pause(.75);
	logo();
	pause(3);
	erase();
	creators();
	pause(3);
	erase();
	start();

}

#endif