
/*****************************************************************************
 Title:       song.cpp
 Author:      Anna Cristina Karingal
 Created on:  Oct 12, 2014
 Description: Song class implementation
                A single song object
 
 *****************************************************************************/

#include "song.h"

string song::get_title() const { return title; }

int song::get_id() const { return id; }

/* Friend function to the class that displays song fields in a formatted, 
 user-friendly manner to the console by manipulating the output stream. 
 Note that no member variables in the song are actually changed.
 */
ostream &operator << (ostream &os, const song &s) {
    
    // Set field width w and alignment for field that follows
    os << setw(5) << right << s.id << " " ;
    
    // Also set field to display substring of only first w characters
    // if field.legth() > w
    os << setw(20) << left << s.artist.substr(0,20) << " " ;
    os << setw(30) << left << s.title.substr(0,30) << " " ;
    os << setw(10) << left << s.album.substr(0,10)<< " " ;
    
    // For integer fields, set fill to 0's instead of spaces
    os << setw(2) << setfill('0') << right << s.time_mins << ":";
    os << setw(2) << right << s.time_secs  << " " ;
    os << setw(4) << s.year << endl;
    
    // Set fill back to spaces again
    os << setfill(' ');
    
    return os;

}