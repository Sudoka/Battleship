// Create highscore table consisting of top 10 names & scores
// Written by Nina Iarkova

#include <iostream>
#include <fstream> //for file input/output 
#define size 10

using namespace std;

struct playerInfo { //structure that holds names and scores of players
	char name[10];
	int score;
};

struct playerInfo scoresArray[size]; // array of ten PlayerInfo structures

void setUp(){ //sets up a premade scoreboard for testing
	for (int i=0; i<size; i++){ 
	strcpy(scoresArray[i].name,"miscplayer");
	scoresArray[i].score=10+i;
	}
}

void insertion(char name[], int score) {	// insert a new entry in highscore table	
	char tempName[15];
	int tempScore;
	bool found = false;
	int i=0;

	// find index at which new score will be inserted 
	while (i < size && scoresArray[i].score != 0 && scoresArray[i].score < score) 	
		i++;

	// move array down, iterating from end
	for (int j = size-1; j > i; j--) { 
		strcpy(scoresArray[j].name, scoresArray[j-1].name);
		scoresArray[j].score = scoresArray[j-1].score;
	}

	// now replace new score at index i
	strcpy(scoresArray[i].name, name);
	scoresArray[i].score = score;

	}
		
void print(){  //print out the scoreboard
	int i=0;
	cout << "\t\t\t\tTop Ten Players" << endl << endl;
	while(scoresArray[i].score != 0 && i < size-1){ 
		cout << "\t\t\t   " << i+1 << ".   " << scoresArray[i].score << "     " << scoresArray[i].name << endl;
		i++;
	}
	for (i; i<size-2; i++)	//print out numbers for remaining empty spots, if any
		cout << "\t\t\t   " << i+1  << "." << endl;
	
	// so the 10th score lines up nicely:
	if (scoresArray[9].score != 0)
		cout << "\t\t\t  10.   " << scoresArray[9].score << "     " << scoresArray[9].name << endl;
	else
		cout << "\t\t\t  10." << endl << endl;
}

void createScoreboard(){ // create a new scoreboard if user decides to or if scoreboard file does not exist
		for (int i=0; i<size; i++){ 
		strcpy(scoresArray[i].name,"None");
		scoresArray[i].score=0;
		}		
		cout << "New scoreboard created" << endl << endl;
}

void file_write() {  // write or overwrite file with scoreboard
   
	int i=0;
	ofstream file;   // stream class to write on files
	file.open("scoreboard.txt");

	if (file.is_open()){
	while(i < size){ 
		file << scoresArray[i].name << endl;	// write player name to file
		file << scoresArray[i].score << endl ;	// write player score to file
		i++;
	}	}

	else {
		cout << "Could not open file for saving data" << endl;	 // if could not open, write new scoreboard file
		createScoreboard();
		file_write();
	}

	file.close(); // close the file
}


void file_open(){	// open existing scoreboard to extract highscores
		
	ifstream file ("scoreboard.txt");  // open scoreboard.txt file
    if (file.is_open()) { 
            for (int i=0; i<(size); i++){
              
				if (file.good()) // false when reached end of file or an error occurred
					file >> scoresArray[i].name;
				else {
					cout << "Ran out of data! File may have been edited" << endl;
					break;
				}

				if (file.good()) // false when reached end of file or an error occurred
					file >> scoresArray[i].score;
				else {
					cout << "Ran out of data! File may have been edited" << endl;
					break;
				}
               
            }  
        
        //cout << endl << "File Opened" << endl ;		//Used for testing
        file.close();  // close the file
        }
    
    else {  // if file could not open, write new scoreboard
		cout << endl << "Unable to open file" << endl ;
		createScoreboard();
		file_write();
	}

	
}


 
void highscore(char name[15], int newScore){ //called at end of each finished game. If new score is lower than current 10th, can insert to list
    file_open();  //open scoreboard from file, save into struct playerInfo scoresArray

    if (scoresArray[9].score == 0 || scoresArray[9].score > newScore){ 
		insertion(name, newScore); 
		cout << endl << "New Score added: " << newScore  << " by " << name << endl << endl;
		file_write(); // save new scores to file scoreboard.txt
		print();
	}
    else {
		cout << "Sorry! Not new highscore" << endl << endl;
        print(); //print scoreboard		
	}
}

void Testmain(){

	int newScore=1000; //testing new highscore
	char name[] = "xxx"; 

	highscore(name, newScore);

	}
	



	