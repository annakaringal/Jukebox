#include "playlist_database.h"

/* Default constructor for playlist_database class */
playlist_database::playlist_database (ofstream &w, ostream &e) : writef(w), err(e) {}

/* Returns number of playlists in playlist_database */
size_t playlist_database::size() { return database.size(); }

/* Returns the position of playlist in the database whose name is equal to pName.
    Comparison is case insenstive. Creates a lowercase copy of pName. Iterates
    through playlist database and creates a lowercase copy of playlist name. 
    Compares the two lowercase copies, and if they are equal, returns current
    position in the databae. If no matches are made, returns -1.
 */
int playlist_database::is_existing_playlist(string &pName){
    
    // Creates an all lowercase copy of pName
    string pName_lower = pName;
    transform(pName_lower.begin(), pName_lower.end(), pName_lower.begin(), ::tolower);
    
    for (int i=0; i<size(); i++) {
        
        // Creates an all lowercase copy of database[i].name
        string sName_lower = database[i].get_name();
        transform(sName_lower.begin(), sName_lower.end(), sName_lower.begin(), ::tolower);
        
        // Compares the two lowercase copies
        if (pName_lower == sName_lower) {
            return i;
        }
    }
    
    return -1;
}

/*Creates new playlist instance with passed parameter name. Pushes this to 
 database vector as the last element in the vector. */
void playlist_database::add_new_playlist(string name){
    playlist p(name);
    database.push_back(p);
}

/* Checks to see if pID is valid, i.e. is the position of an existing playlist
 in database. If pID is valid, erases the playlist from the database and returns
 true. Else does nothing and returns false.
 */
bool playlist_database::delete_playlist(int pID) {
    if (pID < 0 || pID > size()-1) {
        // pID invalid
        return false;
    }
    else {
        // pID is valid. Remove playlist from database.
        database.erase(database.begin()+pID);
    }
    
    return true;
}

/* Attempts so insert a song into playlist at database[pID]. If successful,
    returns true. Else, returns false.
 */
bool playlist_database::insert_song_into_playlist(int pID, song s, int pos) {
    
    if (database[pID].insert(s,pos)) {
        return true;
    }
    else { return false; }
    
}

/* Deletes all instances of a song with song ID sID into playlist at 
    database[pID]. Returns number of times song was deleted. Will return 0 if
    no songs in the ID have song ID sID and so no deletions were made. If
    playlist is empty, returns -1 to indicate no deletions were attempted.
 */
int playlist_database::delete_song_from_playlist(int pID, int sID) {
    return database[pID].delete_song(sID);
}

/* Writes database[pID] to &os using overloaded operator << function for
    palaylists.
 */
void playlist_database::display_playlist(ostream &os, int pID){
    os << database[pID] << endl;
}

/* Returns name of playlist database[pID] */
string playlist_database::get_playlist_name(int pID){
    return database[pID].get_name();
}

/* Returns number of songs in playlist database[pID] */
int playlist_database::get_playlist_size(int pID) {
    return database[pID].size();
}

/* Saves contents of playlists database to file named fName. If fName already
 exists, it is overwritten. Else, a new file named fName is created. File is 
 opened and nuber of playlists in database is written to first line. Iterate
 through database and write name of playlist, number of songs in playlist and
 an orderd list of song IDs of songs in playlist file stream. Each playlist is
 delimited by a new line.
 */
bool playlist_database::save(string fName) {
    
    // Open file named fName.
    writef.open(fName.c_str());
    
    // Error opening file. Write to error stream and return.
    if (writef.fail()){
        return false;
    }
    
    // File opened successfully
    if (writef.is_open()){
        
        // Write size to first name
        writef << size() << endl;
        
        // Iterate through playlists in database
        for (int i=0; i<size(); i++) {
            
            // Write playlist name, number of songs and ordered list of song IDs
            // for each song in playlist
            writef << get_playlist_name(i) << "\t" << get_playlist_size(i) << ": ";
            database[i].save_summary(writef);
        }
        
    }
    
    // Close file
    writef.close();
    
    return true;
}

/* Friend function of the playlist database class that displays playlists to
 console in user-friendly formatted manner. Iterates through each playlist in 
 database and writes playlist name and number of songs in playlist to ostream.
 */
ostream &operator << (ostream &os, playlist_database &pDb){
    
    // If no playlists in database
    if (pDb.size()==0) {
        os << "Sorry, you do not have any playlists.\n" << endl;
        return os;
    }
    
    // 1 or more playlists in datbase
    else {
        
        // Number of playlists in database
        os << "You have " << pDb.size() << " playlists.\n" << endl;
        
        // Iterates through each playlist in database
        // Writes playlist name and number of songs in playlist on new line
        for (int i=0; i<pDb.size(); i++) {
            os << pDb.database[i].get_name() << ": ";
            os << pDb.database[i].size() << " songs" << endl;
        }
        
        return os;
    }

    os << endl;
}