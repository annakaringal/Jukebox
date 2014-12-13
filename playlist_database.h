/*****************************************************************************
 Title:       playlist_database.h
 Author:      Anna Cristina Karingal
 Created on:  Oct 12, 2014
 Description: Definition of Playlist Database Class (Header File)
 
 - Stores all playlists created by user
 - Displays a list of all playlists the user has created
 - Adds/Deletes a playlist to the playlist database
 - Saves all playlists to file
 - Checks to see if a playlist of a given name already exists
 - Returns characteristics/variables of specified playlist in database
 - Add songs to specified playlist in database
 - Delete songs from specified playlist in database
 
 *****************************************************************************/

#ifndef ___playlist_database__
#define ___playlist_database__

#include <iostream>
#include <fstream>
#include <algorithm>

#include "playlist.h"

using namespace std;

class playlist_database {
    
    // Playlist Database
    vector<playlist> database;
    
    // Stream to write to file
    ofstream &writef;
    
    // Stream to write errors to
    ostream &err;
    
public:

/******************************************************************************
    Playlist database constructor
 ******************************************************************************/
    
    /* playlist_database(ofstream &w, ostream &e = cerr);
     Default constructor for playlist database class. Initializes &writef with 
     ofstream &w to write to file and &err with ostream &e, which defaults to
     cerr, to write errors. Initializes database as an empty vector of 
     playlists.
        @param      ofstream &w     [out] stream to write to file
        @param      ostream &err    [in/out] stream to display errors to console
        @pre        &w and &err are open and initialized. 
        @post       database is an empty vector of playlists
     */
    
    playlist_database(ofstream &w, ostream &e = cerr);
    
/******************************************************************************
    Returning playlist database variables / characteristics
 ******************************************************************************/
    
    /* size_t size();
     Returns the number of playlists in the playlist database
        @return     size_t      [out] number of elements in database
        @pre        database is initialized
        @post       returns number of playlists in database
     */
    size_t size();
    
    /* int is_existing_playlist(string &pName);
     Returns the position of the playlist with name pName.
        @param      string &pName   [in] name of playlist to search for
        @return     int             [out] position in database of playlist where
                                    playlist.name == pName. If playlist does not 
                                    exist in database, returns -1.
        @pre        database is initialized. pName is a nonempty, initialized
                    string. Exists a function that can access name of playlist.
        @post       Returns integer n where database[n].name == pName. If
                    database[i].name != pName for 0 <= i < database.size(),
                    returns -1.
     */
    int is_existing_playlist(string &pName);
    
/******************************************************************************
    Modify playlist database elements
 ******************************************************************************/
    
    /* void add_new_playlist(string name);
     Creates a new playlist with playlist.name = name and an empty 
     playlist.playlist_songs list. Adds to end of playlist database.
        @param      string &name   [in] name of playlist to add
        @pre        database is an initialized database of n playlists. name is 
                    a nonempty, initialized string. Constructor for playlist
                    exists that accepts string as only parameter.
        @post       Creates a new playlist with playlist.name = name and 
                    contains an empty list of songs. n increases by 1. Playlist
                    is added to datatabase as database[n]. All other elements
                    in database remain the same.
     */
    void add_new_playlist(string name);
    
    /* bool delete_playlist(int pID);
     Deletes playlist at database[pID] from playlist database.
        @param      int pID [in] position in database of playlist to delete
        @return     bool    [out] returns true if deletion was successful, 
                            else returns false.
        @pre        database is an initialized database of n playlists. pID is a
                    non-empty, initialized integer >= 0 && < n.
        @post       n decreases by 1. playlist at database[pID] is deleted. 
                    All playlists after database[pID] move up the list by 1
                    position so that database[pID + 1] --> database[pID] ...
                    database[n+1] --> database[n]. All playlists before
                    database[pID] are unchanged.
     */
    bool delete_playlist(int pID);
    
    
    /* bool insert_song_into_playlist(int pID);
     Inserts song s into the (pos)th position in playlist database[pID].
        @param      int pID [in] position in database of playlist to insert
                            song into
        @param      song s  [in] song to insert
        @param      int pos [in] position in playlist to insert song into
        @return     bool    [out] returns true if insertion was successful,
                            else returns false.
        @pre        database is an initialized database of n playlists. pID is a
                    non-empty, initialized integer >= 0 && < n. song s is non-
                    empty and initialized. pos is non-empty initialized integer.
                    There exists a function that inserts a given song into a 
                    given function in a playlist.
        @post       s is inserted as a node in playist database[pID] at pos. If
                    pos > n, s is inserted as last element of list. If pos < 1,
                    s is inserted at beginning of the list. If n == 0, s is
                    is inserted as first and only element of list. All songs
                    before pos remain in the same position and order. All songs
                    after pos are moved 1 position down the list but retain the
                    same order. Size of list increases by 1. Function returns
                    true if insertion is successful, else returns false.
     */
    bool insert_song_into_playlist(int pID, song s, int pos);
    
    /* int delete_song_from_playlist(int pID, int sID);
     Deletes all instances of song with song ID sID from playlist at 
     datababase[pID]. Returns -1 if playlist is empty, else returns number of 
     times song instance was deleted.
        @param      int pID [in] position in database of playlist to delete from
        @param      int sID     [in] song ID of song to delete
        @return     int         [out] returns -1 if list is empty, returns 0 if
                                no songs in playlist matched song ID. Else,
                                returns how many times song matching song ID was
                                deleted.
        @pre        database is an initialized database of n playlists. pID is a
                    non-empty, initialized integer >= 0 && < n. song sID is a
                    non-empty, initialzed integer >= 1 && < song_database.size()
                    There exists a function that deletes all instances of a
                    given song from a playlist. playlist database[pID] is an
                    initialized playlist of ns songs.
        @post       Any songs in the database[pID].list with song ID == sID are
                    deleted from the list. Playlist now contains no songs where
                    song ID == sID. All other songs remaining in the playlist
                    are unchanged and retain same order. Returns -1 if ns, == 0, 
                    else returns number of times a song was deleted from
                    playlist and ns decreases by 1.
     */
    int delete_song_from_playlist(int pID, int sID);
    
    /* void display_playlist(ostream &os, int pID);
     Displays songs and song data in playlist database[pID]
        @param      int pID         [in] position in database of playlist
        @param      ostream &os     [in/out] stream to display playlist to
        @pre        database is an initialized database of n playlists. pID is a
                    non-empty, initialized integer >= 0 && < n. playlist
                    database[pID] is an initialized playlist of ns songs. &os
                    is open and initialized. The operator << has been overloaded
                    to write a playlist instance and a song instance.
        @post       Writes the playlist database[pID] to &os, using an 
                    overloaded << operator for the playlist class.
     */
    void display_playlist(ostream &os, int pID);
    
    /* int get_playlist_size(int pID);
     Returns the number of songs in playlist database[pID].
        @param      int pID [in] position in database of playlist
        @return     int     [out] number of songs in playlist
        @pre        database is an initialized database of n playlists. pID is a
                    non-empty, initialized integer >= 0 && < n. playlist 
                    database[pID] is an initialized playlist of ns songs.
                    There exists a function that returns the size of any
                    playlist.
        @post       Returns ns.
     */
    int get_playlist_size(int pID);
    
    /* string gt_playlist_name(int pID);
     Returns name of playlist database[pID].
        @param      int pID [in] position in database of playlist
        @return     string  [out] name of playlist
        @pre        database is an initialized database of n playlists. pID is a
                    non-empty, initialized integer >= 0 && < n. playlist
                    database[pID] is an initialized playlist of ns <= 0 songs.
                    database[pID].name is an initialized, non-empty string.
                    There exists a function that returns the name of any
                    playlist.
        @post       Returns database[pID].name
     */
    string get_playlist_name(int pID);

/******************************************************************************
    Displaying playlist database
 ******************************************************************************/
    
   /* void save(string fName); 
    Saves all playlists in database to file named fName. 
        @param      string fName    [in] name of file to write to
        @return     bool            [out] returns true if save was successful, 
                                    else returns false.
        @pre        fName is the name of a valid file (including extension).
                    database is an initialized vector of n playlists. There 
                    exists a function that writes a summary of any playlist to a
                    file stream.
        @post       If file by name of fName doesn't already exist, a new file 
                    named fName is created. If fName already exists, it is
                    overwritten. Number of playlists in database is displayed on
                    first line of the file, followed by a line delimited list of 
                    each playlist in pDb. Each playlist line begins with the
                    name of the playlist, followed by the tab character,
                    followed by the number of songs in the playlist. This is 
                    followed by the song id of each song in the playlist, in the
                    order they exist in the playlist. Total of n+1 lines written
                    to file.
    */
    bool save(string fName);
    
    /* friend ostream & operator << (ostream &os, const playlist_database &pDb);
     Overloading operator << to display the number of playlists in pDb, the name
     of each playlist in pDb, as well as the number of songs in the playlist.
     Exists outside playlist_database class as a friend function.
        @param      ofstream &os                [in/out] stream to write out to
        @param      playlist_database &pDb      [in] playlist_database to
                                                display in console
        @return     ofstream &os                [in/out] stream to write out to
        @pre        &os initialized, open, and writes to console. &pDb is
                    initialized and contains n non-empty playlists.
        @post       Number of playlists in pDb is displayed on first line in
                    console, followed by a line delimited list of each playlist
                    in pDb in the format playlist.name : playlist.size(). n+1 
                    lines displayed total.
     */
    friend ostream &operator << (ostream &os, playlist_database &pDb);
    
};

#endif