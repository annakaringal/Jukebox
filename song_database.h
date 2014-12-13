/*****************************************************************************
 Title:       song_database.h
 Author:      Anna Cristina Karingal
 Created on:  Oct 12, 2014
 Description: Definition of Song Database Class (Header File)

 Song database of all songs in the program and their song data. Initialized from 
 user supplied file.

- Displays songs with given given song IDs
- Displays songs containing given key as a substring in song artist.
- Displays songs containing given key as a substring in the song title.
 
*****************************************************************************/

#ifndef ___song_database__
#define ___song_database__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "song.h"

using namespace std;

class song_database {
    
    // Database of songs
    vector<song> database;
    
    // Number of songs in database
    int num_of_songs;

    // Stream to display songs to console
    ostream &os;
    
public:
    
/******************************************************************************
     Song database constructor
******************************************************************************/
    
    /* song_database(ifstream &readf, string fName = "songs.csv", ostream &o = cout,  ostream &err = cerr);
     Default constructor for song database class. Initializes database from file
     fName via ifstream &readf and checks file for validity. If file is invalid, 
     program exits gracefully with errors sent to the error stream.
        @param      ifstream &readf [in] file stream to read file input from
        @param      string fName    [in] path & name of file to read file input
                                    from. By default, is songs.csv in program's
                                    working directory
        @param      ostream &o      [in/out] stream to display prompt to console
        @param      ostream &err    [in/out] stream to display errors to console
        @pre        &readf is open and intialized. fName is intialized string       
                    that is the path and name to a valid, properly formatted 
                    .csv file containing n songs. First line of the file 
                    contains field headers and each subsequent line containing 8 
                    tab delimited fields of a single song in the order: Name, 
                    Artist, Album, Genre, Size, Time, Year and Comments. Name 
                    and Artist fields cannot be blank. All fields are enclosed 
                    by double quotes ("), even if empty. &o and &err are both 
                    open and initialized.
        @post       If constructor is successful and file is valid, database
                    contains n+1 elements and num_of_songs = n. database[0] 
                    contains fields headers and each subsequent element, 
                    database[1] ... database [n], contains a non-empty, 
                    intialized instance of the song class, in which each member
                    variable contains the appropriate data read from file. Each
                    song receives a unique song ID number that corresponds to
                    its position in the song database. Song IDs start at 1. A
                    message is printed to the console displaying the number of 
                    songs added to the database (n).
                        If file is not valid, constructor fails and program
                    exits gracefully with all errors written to the error
                    stream.
     */
    song_database(ifstream &readf, string fName = "songs.csv", ostream &o = cout,  ostream &err = cerr);
    
    /* string lowercase(string word) const;
     Returns an all-lowercase string version of the input string.
        @param      string word     [in] string to convert to lowercase
        @return     string          [out] string is identical to word but any
                                    uppercase characters are now their lowercase
                                    equivalent.
        @pre        word is an intialized, non-empty string
        @post       returns a string that is identical to word but any uppercase
                    characters are now their lowercase equivalent.
     */
    string lowercase(string word) const;
    
/******************************************************************************
    Returning song database variables / characteristics
 ******************************************************************************/
    
    /* song get_song (int songid) const;
        Returns a song from the database with song ID songid.
            @param      int songid  [in] song id of song to return
            @return     song        [out] instance of song class where 
                                    song.id == songid
            @pre        songid is an intialized, non-empty integer >= 1 && 
                        <= num_of_songs
            @post       database[songid] (song where song.id == songid) is 
                        returned
     */
    song get_song(int songid) const;
    
    /* song get_song (int songid) const;
     Returns the number of songs in the song database
        @return     int         [out] number of songs in database vector
        @pre        num_of_songs is a non-empty and intialized integer that 
                    is equal to the number of songs stored in the database, 
                    not including headers at database[0]
        @post       returns num_of_songs
     */
    const int size() const;
    
    
/******************************************************************************
    Displaying songs from the song database
 ******************************************************************************/
    
    /* const void list_songs(int first, int last) const;
     Displays songs starting with song where song.id == first to song where 
     song.id == last.
        @param      int     [in] song ID of first song to display
        @param      int     [in] song ID of last song to display
        @pre        first and last are non-empty and initalized integers where
                    first <= last && last <= num_of_songs && first >= 1.
                    database is an initialized vector of num_of_songs songs.
                    Overloaded << operator function exists to write songs to
                    &os.
        @post       All songs from database[first] (song with song.id == first)
                    to database[last] (song.id == last) are written to &os.
                    If first < 1, displays from database[1] to database[last]. 
                    If last > num_of_songs, displays from database[first] to 
                    database[num_of_songs]. If first > last, returns without 
                    displaying anything. Songs delimited by a line break.
     */
    const void list_songs(int first, int last) const;
    
    
    /* const int display_songs_by_artist(string &key) const;
     Case insensitive search through database that displays all and any songs
     that have key as a substring of song.artist.
     @param      string &key  [in] string to search for
     @pre        database is an initialized vector of num_of_songs songs. 
                 &key is an initialized, nonempty string. Overloaded << operator
                 function exists to write songs to os stream.
     @post       A line delimited list of all songs that contain key in any
                 mixture of cases as all or part of song.artist is written to
                 &os.
     */
    const int display_songs_by_artist(string &key) const;
    
    /* const int display_songs_by_title(string &key) const;
     Case insensitive search through database that displays all and any songs
     that have key as a substring of song.title.
     @param     string &key  [in] string to search for
     @pre       database is an initialized vector of num_of_songs songs.
                &key is an initialized, nonempty string. Overloaded << operator
                function exists to write songs to os stream.
     @post      A line delimited list of all songs that contain key in any
                mixture of cases as all or part of song.title is written to 
                &os.
     */
    const int display_songs_by_title(string &key) const;
};

#endif