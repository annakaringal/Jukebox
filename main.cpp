/*******************************************************************************
 Title          : main.cpp
 Author         : Anna Cristina Karingal
 Created on     : October 12, 2014
 
 Description    : A jukebox program that allows the user to organize his or her
                    music into playlists. Opens a database of songs stored in a
                    file and lets user: 
                        - create new playlists or delete existing playlists
                        - view existing playlists
                        - insert/delete songs to existing playlists
                        - save playlists to file
                        - view/search songs in the song database.
 
 Purpose        : Demonstrating usage of existing C++ std::list class,
                    processing of string data and organizing larger programs.
 
 Usage          : ./jukebox mysongs.csv     OR      ./jukebox
                (mysongs.csv is the file path and name of the songs file and is
                    an optional argument. If no argument is given, songs.csv in 
                    the program's working directory is used.)
 
 Build with     : g++ -o jukebox main.cpp menu.cpp song.cpp playlist.cpp
                    playlist_database.cpp song_database.cpp
 
 Last modified  : October 26, 2014
 
 *******************************************************************************/

#include <iostream>

#include "menu.h"
#include "playlist.h"
#include "song.h"
#include "song_database.h"

using namespace std;


/******************************************************************************
        MAIN PROGRAM
 ******************************************************************************/

int main(int argc, const char * argv[]){
    
    // File streams so we can read from file to populate song database
    // and write to file to save playists
    ifstream readf;
    ofstream writef;
    
    // New, empty playlist database
    playlist_database pDb (writef);
    
    // Name of file to read from
    string fName;
   
    // If two arguments were passed through commmand line
    if (argc == 2){
        
        // File name to read from is second argument given
        fName = argv[1];
        
        // Create new song database with data from file
        song_database sDb(readf, fName);
        
        // Create new user menu using song database newly created from file
        // and new empty playlist database
        menu m(pDb, sDb);
    }
    
    // Only one argument was passed through command line
    // No file name was given
    else if (argc == 1) {
        
        // No file name given. Create new song database with default file
        // songs.csv in working directory of program
        song_database sDb(readf);
        
        // Create new user menu using song database newly created from file
        // and new empty playlist database
        menu m(pDb, sDb);
    }
    
    // More than two arguments were passed through command line
    // Exit with errors
    else if (argc > 2) {
        cerr << "ERROR: Too Many Arguments. " << endl;
        cerr << "Please run the program by typing into the terminal" << endl;
        cerr << "     ./jukebox song_file.csv" << endl;
        cerr << "where song_file.csv is the name of your song database file." << endl;
        cerr << "If a song database file name is not provided, songs.csv in your working directory is used by default.\n" << endl;
        
         exit(-1);
    }
    
    return 0;
}

