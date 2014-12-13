/*****************************************************************************
 Title:       menu.h
 Author:      Anna Cristina Karingal
 Created on:  Oct 12, 2014
 Description: Menu Class Definition (Header File)
 
 Instance of a menu class that retrieves data from a given song database object
 and retrieves/modifies data from a playlist database object. Modifications and
 data retrieved/modified depends on user inputs. Menu class takes user inputs, 
 interprets it and make decisions on which functions to call based on this input.
 
 *****************************************************************************/

#ifndef ____menu____
#define ____menu____

#include <iostream>
#include <string>
#include <algorithm>

#include "song_database.h"
#include "playlist.h"
#include "playlist_database.h"

using namespace std;

class menu {
    
    // User inputs
    string cmd;
    string key1;
    string key2;
    
    // Streams to display prompts and errors, get user input
    ostream &os;
    istream &is;
    ostream &err;
    
    // Playlist to edit
    int pID;
    
    // Databases to store/get information
    playlist_database &pDb;
    const song_database &sDb;
    
public:

/******************************************************************************
     Menu constructor
******************************************************************************/
    
    /* menu(playlist_database &p, const song_database &s, ostream &o = cout,
        istream &i = cin, ostream &e = cerr);
     Default constructor for menu class.
        @param      playlist_database &p    [in/out] playlist database to 
                                            create/modify/read existing playlist 
                                            data
        @param      const song_database &s  [in] song database to read song
                                            data from
        @param      ostream &o      [in/out] stream to display prompt to console
        @param      istream &i      [in] stream to get user input from
        @param      ostream &err    [in/out] stream to display errors to console
        @pre        &s is initialized from file. &p is initialized and non-
                    empty. &o, &i and &err are open and initialized.
        @post       menu is initialized where &pDb = &p, &sDb = &s, &os = &o, 
                    &is = &i, &err = &e. All other member variables are empty
     */
    menu(playlist_database &p, const song_database &s, ostream &o = cout, istream &i = cin, ostream &e = cerr);
    
    
/******************************************************************************
     Input getters and manipulators
******************************************************************************/
    
    /* void get_command();
        Gets and parses commands from user.
        @pre        &is is open and initialized. cmd, key1 and key2 are             
                    initialized.
        @post       cmd is non-empty and contains a new lowercase string
                    captured from user. key1 and key2 may also be non-empty and
                    contain new strings obtained from user input. Any data in 
                    cmd, key1 and key2 before function was called is replaced by
                    new user input.
     */
    void get_command();
    
    /* void clear_command 
    Clears all user input variables: cmd, key1 and key2.
        @pre        cmd, key1 and key2 are initialized.
        @post       cmd, key1 and key2 only contain the null character \0 and
                    are cleared of any other data.
     */
    void clear_command();

    /* bool string_to_int(string s, int &id);
    Converts a variable of type string to type int
        @param      string s        [in] string to turn to int
        @param      int &id         [in/out] variable to store newly converted
                                             int
        @return     bool            [out] returns true if conversion was 
                                        successful, else returns false
        @pre        s is a string of numeric characters only. &id exists as a
                    declared variable outside the function. &err is open and
                    initialized.
        @post       Returns true if &id gets the integer value of the numeric
                    characters in s. Else, returns false, &id remains unchanged
                    outside function and error message is written to &err.
     */
    bool string_to_int(string s, int &id);
    
    /* bool is_valid_sID(int sID); 
    Checks if a given integer is the song ID of an existing song in the song
    database
        @param      int sID     [in] integer song ID to check
        @return     bool        [out] returns true if sID is the song id of some
                                song in the song database. Else returns false.
        @pre        sID is a non-empty, initialized integer. Song database is
                    initialized database of n songs. &err is open and 
                    initialized.
        @post       Returns true if sID is the song ID of an existing song in
                    the database. Else, returns false and error message written
                    to &err.
    */
    bool is_valid_sID(int sID);
    
    
/******************************************************************************
     Display menu functions
******************************************************************************/

    /* void display_menu();
        Clears any existing command variables. Displays top level user menu, 
        gets command from user. 
        @pre        There exists functions to clear command, get commands from
                    user. &os, &is are initialized and open.
        @post       Menu is written to &os and cmd, key1 and key2 contain new
                    data captured from user inputs
     */
    void display_menu();
    
    
    /* void display_playlist_mod_menu();
     Clears any existing command variables. Displays playlist modification mode
     menu, gets command from user.
        @pre        There exists functions to clear command, get commands from
                    user. &os, &is are initialized and open.
        @post       Menu is written to &os and cmd, key1 and key2 contain new
                    data captured from user inputs
     */
    void display_playlist_mod_menu();
    
    /* void display_help_menu();
    Displays help menu text.
     @pre        &os is  initialized and open.
     @post       Menu is written to &os.
     */
    void display_help_menu();
    
    
/******************************************************************************
        Handle menu command functions
******************************************************************************/

    /* void handle_menu_command()
    Calls functions and performs validity checks based on user inputs while
    in the top level menu.
        @pre        cmd is initialized and non-empty lowercase string of 1 
                    character length. sDb is an intialized song database of ns 
                    songs and pDb is an initialized playlist database of np 
                    playlists. &os and &err are both initialized and open.
                    Depending on function user is attempting to call, key1 may  
                    also need to be initialized and non-empty: if cmd == "l" , 
                    "v" , "c", "m", "d" or "s", key1 must be a string containing 
                    no spaces.
        @post       Functions to view or modify data or perform validity checks
                    on inputs are called based on the value of cmd: 
                    cmd == l : Writes contents of pDb to &os stream
                    cmd == h : Diplays help menu
                    cmd == q : exits program with no errors
                        For the below values of cmd, pID gets the position in 
                    pDb of the playlist named key1. If such a playlist does not
                    exist, pID = -1.
                    cmd == v : Displays all songs in playlist named key1
                    cmd == c : Creates a new playlist named key1 and adds it to
                                playlist database. pID = pDb.size(). Calls 
                                display_playlist_modification_mode();
                    cmd == m : Calls display_playlist_modification_mode();
                    cmd == d : Deletes playlist named key1 from playlist
                                database
                    If command does not equal any of the above strings, user
                    menu is displayed again.
     */
    void handle_menu_command();
    
    /* void handle_menu_command()
     Calls functions and performs validity checks based on user inputs while
     in the playlist modification mode menu.
        @pre        cmd is initialized and non-empty lowercase string. sDb is an        
                    intialized song database of ns songs and pDb is an 
                    initialized playlist database of np >= 1 playlists. &os and 
                    &err are both initialized and open. pID is an integer >= 0 
                    && <= pDb.size(). Depending on function user is attempting 
                    to call, both key1 and key2 may also need to be initialized 
                    and non-empty.
        @post       Functions to view or modify data or perform validity checks
                    on inputs are called based on the value of cmd.
                    cmd == l : List all songs in song database from song with  
                                song ID key1 to song with song ID key2.
                    cmd == a : Display all songs in song database with key1 as
                                a substring in the song artist
                    cmd == t : Display all songs in song database with key1 as
                                a substring in the song title
                    cmd == insert : Insert song with song ID matching key1 into
                                    playlist with id pID at position key2.
                    cmd == delete : Delete all songs with song ID matching key1
                                    from playlist with id pID.
                    cmd == show : Lists all songs in playlist with id pID.
                    cmd == b : Display top level user menu
     */
    void handle_playlist_mod_command();
    
};

#endif
