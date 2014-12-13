#include "playlist.h"


/* Default Constructor
    Transforms given playlist name into all lowercase and saves in name_lower
    Playlist_songs is an empty list
 */
playlist::playlist(string list_name): name(list_name) {
    name_lower = name;
    transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);
}


/* Returns name of playlist */
string playlist::get_name() { return name; }


/* Returns name of playlist in all lowercase */
string playlist::get_name_lower() { return name_lower; }


/* Returns number of songs in playlist */
size_t playlist::size() const { return playlist_songs.size(); }


/* Returns true if playlist is empty, else returns false */
bool playlist::is_empty() const{ return playlist_songs.empty(); }


/* Returns true if song s is inserted into playlist at position pos successfully. Else returns false. Performs checks to see if pos is valid. 
    If pos <= 1 || pos > size(), changes value of pos so insertion can be
    performed smoothly. Insertion is performed by using an iterator to advance
    to the (pos-1)th position in the list, then using std::list::insert to 
    insert song s after (pos-1)th element.
 */
bool playlist::insert (song s, int pos){
    
    // If pos <= 1, insert s to as the first element of the list
    if (pos <= 1) {
        playlist_songs.push_front(s);
        return true;
    }
    
    // If pos > size, insert s as last element of list
    else if (pos > size()) {
        playlist_songs.push_back(s);
        return true;
    }
    
    // If 1 < pos <= size, insert s at position pos in list
    else {
        // Advance an iterator to (pos-1)th position
        list<song>::iterator it = playlist_songs.begin();
        advance(it, pos-1);
        
        // Inserts s after (pos-1)th element, so s is now (pos)th element in
        // list
        playlist_songs.insert(it, s);
        
        return true;
        
    }
    
    return false;
}

/* Deletes all instances of songs that have song ID SID from playlist.
    Returns number of times a song was deleted from playlist. Returns -1 if 
    playlist is originally empty and so deletion could not be performed.
    Performs deletion by using an iterator to iterate through the list. If 
    iterator points to a song that has a song ID equal to sID, the song is 
    deleted after the iterator increments.
 */
int playlist::delete_song(int sID) {
    
    // If playlist is empty, return -1 and do not attempt deletions
    if (is_empty()) {
        return -1;
    }
    
    // Playlist is non-empty
    else {
        
        // Number of times a deletion is performed
        int count = 0;
        
        // Iterator starts at beginning of list
        list<song>::iterator it = playlist_songs.begin();
        
        // While iterator is not at end of the list
        while (it !=playlist_songs.end()){
            
            // If iterator is pointing to song that has a song ID of SID
            // Increment iterator before deleting song, then delete song
            // and add to deletion count
            if ( (*it).get_id() == sID) {
                playlist_songs.erase(it++);
                count ++ ;
            }
            // Otherwise, advance iterator to next node
            else {
                it ++ ;
            }
                
        }
        
        return count;
    }
}



/* Writes the summary of a playlist to a file stream. Indicates songs in 
    playlist by song ID and displays songs in the order stored in the 
    playlist. Writes new line to mark end of playlist.
 */
void playlist::save_summary(ofstream &writef){
    
    // If no songs in playlist, do not display anything
    // Display new line to mark end of playlist
    if (is_empty()) {
        writef << endl;
        return;
    }
    
    // 1 or more songs in playlist
    else {
        
        // Iterate through all songs in playlist in order.
        // For each song, write song ID to playlist followed by a space
        for (list<song>::const_iterator ci=playlist_songs.begin(); ci != playlist_songs.end(); ci++){
            song s = *ci;
            
            writef << s.get_id() << " " ;
        }
    }
    
    // new line marks end of playlist
    writef << endl;
    
}


/* Friend function of the playlist class that displays playlist to console in 
    user-friendly formatted manner. Iterates through each node in the list
    and writes to stream using overloaded << operator for song class. 
 */
ostream & operator << (ostream &os, const playlist &p) {
    
    // Playlist is empty, nothing to display
    if (p.is_empty()) {
        os << "Your playlist is empty!" << endl;
        return os;
    }
    
    // Playlist contains songs
    else {
        
        os << "Songs in playlist '" << p.name << "':" << endl;
        
        // Iterates through all songs in playlist in order
        // For each song, write to stream using overloaded << for song class
        for (list<song>::const_iterator ci=p.playlist_songs.begin() ; ci != p.playlist_songs.end(); ci++) {
            song s = *ci;
            os << s;
        }
        
        return os;
    }
}