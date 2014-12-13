/*****************************************************************************
 Title:       song.h
 Author:      Anna Cristina Karingal
 Created on:  Oct 12, 2014
 Description: Song class definition (Header File)
                A single song object containing song data
 
*****************************************************************************/

#ifndef ___song__
#define ___song__

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class song {
    int id;
    string title;
    string artist;
    string album;
    string genre;
    int size;
    int time;
    int time_mins;
    int time_secs;
    int year;
    string comments;
    
/******************************************************************************
    Friend classes and functions
 ******************************************************************************/

    /* friend class song_database;
    Allowes song_database class to write to song fields. Song_database
     constructor initializes all songs in jukebox from song database file.
     */
    
    friend class song_database;
    
    /* friend ostream & operator << (ostream &os, const song &s);
     Overloading operator << to display song id, title, artist, album, 
     time and year to console in a formatted user-friendly style.
     Exists outside song class as a friend function.
        @param      ofstream &os     [in/out] stream to write out to
        @param      playlist &p      [in] song to display in console
        @return     ofstream &os     [in/out] stream to write out to
        @pre        &os initialized, open, and writes to console. song s is
                    initialized and non-empty.
        @post       Song fields are displayed in columns on a single line of 80
                    chars in the following order and width: s.id (5 chars), 
                    s.artist (20 chars), s.title (30 chars), s.album (10 chars), 
                    s.time_mins:s.time_secs (2 dig each), s.time_year (4 dig). 
                    Any field longer than the allowed width is truncted to fit.
                    All fields are left aligned except for s.id which is right
                    aligned. All fields remain unchanged and at their full width.
                    Only displays are truncated.
     */
    friend ostream &operator << (ostream &os, const song &s);
    
/******************************************************************************
     Returning song variables / characteristics
******************************************************************************/

public:
    
    /* string get_title()
     Returns title of song.
        @return     string      [out] title of song
        @pre        title is a initialized and non-empty string.
        @post       title is returned and unchanged.
     */
    string get_title() const;
    
    /* string get_title()
     Returns song ID of song.
        @return      int [out] song ID of song
        @pre         song ID is an initialized and non-empty integer.
        @pos         song ID is returned and unchanged.
     */
    int get_id() const;
    
};

#endif