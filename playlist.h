/*****************************************************************************
 Title:       playlist.h
 Author:      Anna Cristina Karingal
 Created on:  Oct 12, 2014
 Description: Playlist Class Definition (Header File)

 A single playlist of songs created and modified by the user.
 - Uses existing C++ std::list class functions to insert/delete songs into 
 playlist.
 - Writes a summary of playlist to a file stream.

*****************************************************************************/

#ifndef ___playlist__
#define ___playlist__

#include <iostream>
#include <string>
#include <list>

#include "song.h"
#include "song_database.h"

using namespace std;

class playlist {
    
    // Playlist Name
    string name;
    
    // Playlist Name - All lowercase
    string name_lower;
    
    // List of songs
    list<song> playlist_songs;
    
public:
    
/******************************************************************************
     Playlist constructor
******************************************************************************/
    
    /* playlist(string list_name)
     Default constructor for playlist class. Initializes name with list_name and
     playlist_songs as an empty doubly linked list. Converts any alphabet
     characters in name that are uppercase to lowercase characters and stores in
     name_lower.
        @param      string list_name [in] name of playlist
     */
    playlist(string list_name);
    
/******************************************************************************
     Returning playlist variables / characteristics
******************************************************************************/
    
    /* string get_name()
     Returns name of playlist.
        @return     string  [out] name of playlist
        @pre        name is initialized and non-empty.
        @post       name is returned and unchanged.
     */
    string get_name();
    
    /* string get_name_lower()
     Returns name of playlist with all characters in lowercase.
        @return     string  [out] name of playlist in lowercase
        @pre        name is initialized and non-empty. name_lowercase is also
                    initialized and non-empty and is identical to name, except
                    any uppercase characters in name are their lowercase 
                    equivalent in name_lowercase.
        @post       name_lowercase is returned. Both name and name_lowercase are
                    unchanged.
     */
    string get_name_lower();
    
    /* size_t size const()
     Returns number of songs in playlist.
        @return     size_t  [out] number of elements in list
        @pre        playlist_songs list is intitialized.
        @post       playlist_songs list is unchanged. Returns number of nodes in
                    playlist_songs.
     */
    size_t size() const;
    
    /* bool is_empty()
     Returns true if playlist contains 0 songs. Else, returns false.
        @return     bool    [out] true if list is empty, else returns false
        @pre        playlist_songs list is intitialized.
        @pos        playlist_songs is unchanged. Returns true if number of nodes
                    in playlist_songs == 0. Else, returns false.
     */
    bool is_empty() const;
    
/******************************************************************************
     Modify songs in playlist
******************************************************************************/
    
    /* bool insert (song s, int pos)
     Inserts a song into the playlist at position pos.
        @param      song s  [in] song to insert
        @param      int pos [in] position to insert song into
        @return     bool    [out] returns true if insertion was successful.
                            Else, returns false
        @pre        playlist_songs list is initialized and is of size n >= 0.
        @post       s is inserted as a node in the playlist at position pos. If
                    pos > n, s is inserted as last element of list. If pos < 1,
                    s is inserted at beginning of the list. If n == 0, s is 
                    is inserted as first and only element of list. All songs
                    before pos remain in the same position and order. All songs
                    after pos are moved 1 position down the list but retain the
                    same order. Size of list increases by 1. Function returns
                    true if insertion is successful, else returns false.
     */
    bool insert (song s, int pos);
    
    
    /* int delete_song (int sID);
     Deletes any songs from the playlist that have the song ID sID.
        @param      int sID     [in] song ID of song to delete
        @return     int         [out] returns -1 if list is empty, returns 0 if 
                                no songs in playlist matched song ID. Else, 
                                returns how many times song matching song ID was 
                                deleted.
        @pre        song ID sID is initialized and >= 1 && < num_of_songs in
                    song database. List is initialized and is of size n > 0.
        @post       Any songs in the list with song ID == sID are deleted from
                    the list. Playlist now contains 0 songs with song ID == sID.
                    n decreases by the number of times a song is deleted. Al
                    other songs remaining in the playlist are unchanged and
                    retain same order. Returns -1 if n == 0, else returns number
                    of times a song was deleted from playlist.
     */
    int delete_song (int sID);

    
/******************************************************************************
    Displaying the playlist
 ******************************************************************************/
    
    /* void save_summary (ofstream &writef); 
     Writes a summary of the playlist to a file stream.
        @param      ofstream &writef [in/out] file stream to write out to
        @return     ofstream &writef [in/out] file stream to write out to
        @pre        &writef is initialized, open, and writes to file. name is
                    initialized and non-empty and playlist_songs is initialized
                    and of size n >= 0.
        @post       A space delimited list of the song IDs of songs in
                    playlist_songs is written to &writef in the same order they
                    are stored in the list. The end of the playlist is marked
                    by a line break. If n == 0, only a line break is written.
     */
    void save_summary (ofstream &writef);
    
    /* friend ostream & operator << (ostream &os, const playlist &p);
     Overloading operator << to display playlist name and songs to console.
    Exists outside playlist class as a friend function.
        @param      ofstream &os     [in/out] stream to write out to
        @param      playlist &p      [in] playlist to display in console
        @return     ofstream &os     [in/out] stream to write out to
        @pre        &os initialized, open, and writes to console. p.name is
                    initialized and non-empty. p.playlist_songs is initialized
                    and of size n >= 0. Operator << is overloaded to display
                    object of song class.
        @post       A line delimited list of each song in playlist_songs is
                    written to the console via &os in the order they are stored 
                    in the list. Using the overloaded << operator for the song 
                    class to print out songs. If n == 0, a message to the user
                    stating that the playlist is empty is written instead.
     */
    friend ostream & operator << (ostream &os, const playlist &p);
    
};


#endif