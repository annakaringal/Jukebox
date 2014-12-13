#include "menu.h"

/*Default Constructor for menu class. Initializes member variables depending on passed parameters and displays menu upon class construction. */
menu::menu(playlist_database &p, const song_database &s, ostream &o, istream &i, ostream &e): pDb(p), sDb(s), os(o), is(i), err(e) {
    display_menu();
}

/* Clears all user inputs so they contain no data */
void menu::clear_command () {
    cmd.clear();
    key1.clear();
    key2.clear();
}

/* Gets user input and breaks up input into three space delimited string 
    parameters, cmd, key1 and key2 using stringstream. Converts cmd to 
    lowercase so commands are case insensitive.
 */
void menu::get_command() {
    // Gets whole user input line
    string user_input;
    getline(is, user_input);
    
    // Breaks up user input line using stringstream
    // First word is cmd, second is key1 and rest of line is key 2
    // First word, key1 and key2 are separated by spaces
    istringstream ss(user_input);
    getline(ss, cmd, ' ');
    getline(ss, key1, ' ');
    getline(ss, key2);
    
    // Convert cmd to lower case
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
}

/* Converts string s to ingeter id using stringstream to read into id. Changes 
    value of integer parameter id outside of function as it is passed by 
    reference. If conversion fails, writes error message to error stream and 
    returns false. Else, conversion was successful and function returns true.
 */
bool menu::string_to_int(string s, int &id){
    istringstream ss(s);
    if (!(ss >> id)){
        err << "Sorry, there was an error with your command. Please check that you are entering an integer and try again .\n" << endl;
        return false;
    }
    
    return true;
}

/* Checks to see if sID is a valid song ID, i.e. if it is greater or equal to 
 one and less than or equal to the number of songs in the song database. 
 If sID is NOT valid, writes an error message to the error stream and returns
 false. Else, sID is valid and function returns true. */
bool menu::is_valid_sID(int sID) {
    if (sID <=0 || sID > sDb.size()) {
        err << "ERROR: Invalid Song ID. Please try again.\n" << endl;
        return false;
    }
    return true;
}

/* Handles actions based on value of cmd while in the top level user menu
    Checks user inputs for validity and decides which functions based on 
    results of validity checks and value of cmd.
 */
void menu::handle_menu_command(){
    
    // Commands with only one user input (cmd)
    if (key1.empty() && key2.empty()) {
        
        // List names of all playlists and redisplay menu
        if (cmd == "l"){
            os << pDb << endl;
            return display_menu();
        }
        
        // Display help menu
        else if (cmd == "h") {
            return display_help_menu();
        }
        
        // Exit program with no errors
        else if (cmd == "q") {
            err << "Exiting the program. Good bye!" << endl;
            exit(0);
        }
        
        // Invalid command. Prompt user to try again and redisplay menu.
        else {
                err << "Invalid command. \n Please try again." << endl;
                return display_menu();
        }
    }
    
    // Commands with 2 or more user inputs (cmd + playlist/file name)
    else {
        
        // Name can include spaces, so concatenate key1 and key2
        string pName;
        if (!key2.empty()){
            pName = key1 + ' ' + key2;
        }
        else {
            pName = key1;
        }
        
        // Get position in playlist database of playlist with name pName
        // Playlist name is case insensitive.
        // If playlist does not exist, pID = -1
        pID = pDb.is_existing_playlist(pName);
        
        
        // View playlist pName
        if (cmd =="v") {
            
            // If playlist does not exist, prompt user to try again
            if (pID < 0 || pID >= pDb.size()){
                err << "Sorry, the playlist '" << pName << "' doesn't exist. \n Please try again.\n" << endl;
                return display_menu();
            }
            
            // Playlist exists. Display songs in playlist and redisplay menu
            else {
                pDb.display_playlist(os,pID);
                return display_menu();
            }
            
        }
        
        // Create new playlist named pName
        else if (cmd =="c") {
            
            // If playlist named pName already exist, prompt user to try again
            if (pID>=0 || pID < pDb.size()) {
                err << "Sorry, the playlist '" << pName << "' already exists. \n Playlist names are not case sensitive. Please try again.\n" << endl;
                return display_menu();
            }
            
            // No playlist of name pName exists yet
            else {
                
                // Set new pID to position of playlist in playlist database
                
                // If playlist database is empty, sets pID to 0
                if (pDb.size() == 0 ) {
                    pID = 0;
                }
                
                // Playlist database is non-empty. Sets pID to last+1 index of
                // database
                else {
                    pID = pDb.size();
                }
                
                // Creates new playlist and adds to playlist database
                pDb.add_new_playlist(pName);
                
                // Go to playlist modification mode to edit new playlist
                // named pName
                return display_playlist_mod_menu();
            }
            
        }
        
        // Modify playlist named pName
        else if (cmd =="m") {
            
            // If playlist doesn't exist, prompts user to try again
            if (pID < 0 || pID >= pDb.size()){
                err << "Sorry, the playlist '" << pName << "' doesn't exist. \n Please try again.\n" << endl;
                return display_menu();
            }
            
            // Playlist exist. Go to playlist modification mode to
            // edit playlist named pName
            else {
                return display_playlist_mod_menu();
            }
            
        }
        
        // Delete playlist named pName
        else if (cmd == "d") {
            
            // If playlist doesn't exist, prompt user to try again
            if (pID < 0 || pID >= pDb.size()){
                err << "Sorry, the playlist '" << pName << "' doesn't exist. \n Please try again.\n" << endl;
                return display_menu();
            }
            
            // Playlist exists
            else {
                
                // Attempts to delete playlist. If delete was successful,
                // display success message in console and redisplay user menu
                if (pDb.delete_playlist(pID)) {
                    os << "Your playlist '" << pName << "' was deleted.\n" << endl;
                    return display_menu();
                }
                
                // Attempt to delete was unsuccessful. Write error message to
                // error stream and redisplay menu
                else {
                
                    err << "There was an error deleting your playlist." << endl;
                    return display_menu();
                }
            }
        }
        
        // Saves all playlists in playlist database to file named pName
        else if (cmd == "s") {
            if (!pDb.save(pName)) {
                err << "ERROR: Could not save to file. Please check your file name and try again.\n" << endl;
            }
            else {
                os << "Success. Your playlists were saved to " << pName << ".\n" << endl;
            }
            return display_menu();
        }
        
        // Invalid command. Prompts user to try again.
        else {
            err << "Sorry, I did not understand that command. \n Please try again." << endl;
            return display_menu();
        }
    }
}


/* Handles actions based on user inputs while in playlist modification mode menu. Checks user inputs for validity and decides which functions based on
    results of validity checks and value of cmd. Performs modifications on
    playlist at position pID in the playlist database. pID is determined only 
    by user input while in the top level user menu and is not changed while 
    the handle_playslist_mod_command() function is executed.
 */
void menu::handle_playlist_mod_command() {

    // Lists all songs in song database from song ID first to song ID last in
    // order of song ID.
    if (cmd =="l") {
        
        // Converts string user inputs to integer
        int first, last;
        // If conversion to integer is unsuccessful, prompts user to try again
        if (!string_to_int(key1, first) || !string_to_int(key2, last)){
            return display_playlist_mod_menu();
        }
        
        // If integer first > integer last, displays out of range error
        // Prompts user to try again
        if (first > last) {
            err << "ERROR: Out of Range. \n Please check your input values for first and/or last and try again.\n" << endl;
            return display_playlist_mod_menu();
        }
        
        // If first > number of songs in the database, displays error.
        // Prompts user to try again.
        if (first > sDb.size()) {
            err << "ERROR: Invalid Song ID. \n Please check your input value for first and try again.\n" << endl;
            return display_playlist_mod_menu();
        }

        // Lists songs in database from song ID first to song ID last
        // in ascending order
        sDb.list_songs(first, last);
        
        // Redisplay menu
        return display_playlist_mod_menu();
        
    }
    
    // Display songs containing key1 as substring of artist field
    else if (cmd =="a") {
        
        // Search through song database, display songs containing key1
        // as substring of artist field. Return how many songs were found
        int count = sDb.display_songs_by_artist(key1);
        
        // If key was not found a substring of the artist field for any song in
        // the song database
        if (count == 0) {
            os << "There were no songs with '" << key1 << "' as the artist." << endl;
        }

        // Redisplay menu
        return display_playlist_mod_menu();
    }
    
    // Display songs containing key1 as substring of title field
    else if (cmd =="t") {
        
        // Search through song database, display songs containing key1
        // as substring of title field. Return how many songs were found
        int count = sDb.display_songs_by_title(key1);
        
        // If key was not found as substring of title field for any song in
        // the song database
        if (count == 0) {
            os << "There were no songs with '" << key1 << "' in the title." << endl;
        }
        
        // Redisplay menu
        return display_playlist_mod_menu();
    }
    
    
    // Insert a song into the playlist
    else if (cmd =="insert") {
        
        // Converts user inputs from string to integer
        // If conversion to integer is unsuccessful, prompts user to try again
        int sID, pos;
        if (!string_to_int(key1, sID) || !string_to_int(key2,pos)){
            return display_playlist_mod_menu();
        }
        
        // If song ID is invalid and not a song ID in the song database,
        // Display invalid song id error and prompt user to try gain
        if (!is_valid_sID(sID)) {
            return display_playlist_mod_menu();
        }
        
        // Song ID is valid. Copy song with song ID sID from database into s
        song s = sDb.get_song(sID);
        
        // Attempt to insert song into playlist pID at position pos
        // If insertion was unsuccesful, display error and propt user
        // to try again.
        if (!pDb.insert_song_into_playlist(pID, s, pos)) {
            err << "There was an error inserting your song '" << sDb.get_song(sID).get_title() << "' into the playlist. \n Please try again. \n" << endl;
        }
        else {
            // Insertion was successful. Display success message indicating
            // where the song was inserted (beginning, end or at position pos)
            os << "Success! Your song '" << sDb.get_song(sID).get_title() << "' was inserted into playlist '" << pDb.get_playlist_name(pID) ;
            if (pos <=1) {
                os << "' at the beginning of the list";
            }
            else if (pos > pDb.get_playlist_size(pID)) {
                os << "' at the end of the list";
            }
            else {
                os << "' at position " << pos ;
            }
            
            os << ".\n" << endl;
        }
        
        // Redisplay menu
        return display_playlist_mod_menu();
    }
    
    // Delete song from playlist
    else if (cmd =="delete") {
        
        // Convert user input from string to integer
        // If conversion to integer is unsuccessful, prompts user to try again
        int sID;
        if (!string_to_int(key1, sID)){
            return display_playlist_mod_menu();
        }
        
        // If song ID is invalid and not a song ID in the song database,
        // Display invalid song id error and prompt user to try gain
        if (!is_valid_sID(sID)) {
            return display_playlist_mod_menu();
        }
        
        // Delete all instances of song with song ID sID from playlist
        // Return number of times a song was deleted
        int deletions = pDb.delete_song_from_playlist(pID, sID);
        
        if (deletions < 0) { // If deletions == -1, playlist was empty
            err << "Your playlist is empty. No deletions were made. \n" << endl;
        }
        else if (deletions == 0){ // No deletions made
            err << "Your playlist does not contain the song '" << sDb.get_song(sID).get_title() << "'. No deletions were made. \n" << endl;
        }
        else { // 1 or more deletions made successfully
            os << "Success! All instances of your song '" << sDb.get_song(sID).get_title() << "' were deleted from playlist '" << pDb.get_playlist_name(pID) <<"'.\n" << endl;
        }
        
        
        // Redisplay menu
        return display_playlist_mod_menu();
    }
    
    // Display all songs in playlist
    else if (cmd =="show") {
        
        pDb.display_playlist(os, pID);
        
        // Redisplay menu
        return display_playlist_mod_menu();
    }
    
    // Return to top level menu
    else if (cmd == "b") {
        return display_menu();
    }
    
    // Invalid command. Prompt user to try again.
    else {
        err << "Sorry, I did not understand that command. \n Please try again.\n" << endl;
        return display_playlist_mod_menu();
    }

}


/* Displays top level user menu, calls functions to clear command, get user
    user inputs and handle actions based on user input */
void menu::display_menu(){

    clear_command();
    
    os << endl;
    os << "******************************************************" << endl;
    os << "USER MENU: " << endl;
    os << "******************************************************" << endl;
    
    os << "[L/l]             List the names of all the playlists" << endl;
    os << "[V/v] <playlist>  View a playlist" << endl;
    os << "[C/c] <playlist>  Create a new playlist" << endl;
    os << "[M/m] <playlist>  Modify an playlist" << endl;
    os << "[D/d] <playlist>  Delete an existing playlist" << endl;
    os << "[S/s] <filename>  Save all the playlists" << endl;
    os << "[H/h]             Help" << endl;
    os << "[Q/q]             Exit \n" << endl;
    os << "ENTER COMMAND: " ;
    get_command();
    
    return handle_menu_command();
}


/* Displays playlist modification mode menu, calls functions to clear commands, get user user inputs and handle actions based on user input */
void menu::display_playlist_mod_menu(){

    clear_command();
    
    os << endl;
    os << "******************************************************" << endl;
    os << "PLAYLIST MODIFICATION MODE: " << endl;
    os << "******************************************************\n" << endl;
    os << ">> You are editing playlist '" << pDb.get_playlist_name(pID) << "'.\n" << endl;
    os << "[L/l] <first><last>    List songs from database from first to last" << endl;
    os << "[A/a] <artist_key>     List all songs whose artist contains artist_key as a substring" << endl;
    os << "[T/t] <title_key>      List all songs whose title contains title_key as a substring" << endl;
    os << "Insert <songid> <pos>  Insert the songid into playlist at position <pos>" << endl;
    os << "Delete <songid>        Delete songid from playlist" << endl;
    os << "Show                   Display songs in the playlist" << endl;
    os << "[B/b]                  Return to top level user menu\n" << endl;
    os << "ENTER COMMAND: " ;
    
    get_command();
    
    return handle_playlist_mod_command();
    
}
    

/* Displays help menu and re-displays top level user menu */
void menu::display_help_menu(){
    
    os << endl;
    os << "=======================================================================" << endl;
    os << "         HELP MENU" << endl;
    os << "=======================================================================\n" << endl;

    os << "To enter a command, enter a single letter followed by the name of a"<< endl;
    os << "playlist or file name. You don't have to put the name of your playlist" << endl;
    os << "or file name in <> brackets, unless your playlist is named as such, or" << endl;
    os << "you want to name your playlist as such.\n" << endl;

    os << "-----------------------------------------------------------------------" << endl;
    os << "         MAIN USER MENU COMMANDS" << endl;
    os << "-----------------------------------------------------------------------\n" << endl;

    os << "[L/l]             Lists the name of each playlist and the number of songs" << endl;
    os << "                  in the playlist.\n" << endl;

    os << "[V/v] <playlist>  View a playlist" << endl;
    os << "                  Displays a list of the songs in the playlist named" << endl;
    os << "                  <playlist>. Playlist names are NOT case sensitive.\n" << endl;

    os << "[C/c] <playlist>  Create a new playlist named <playlist>. You'll be taken" << endl;
    os << "                  into playlist modification mode to edit your playlist.\n" << endl;

    os << "[M/m] <playlist>  Modify an existing playlist named <playlist>. You'll be" << endl;
    os << "                  taken into playlist modification mode to make changes.\n" << endl;

    os << "[D/d] <playlist>  Delete an existing playlist named <playlist>.\n" << endl;

    os << "[S/s] <filename>  Save all your playlists to a file named <filename>.\n" << endl;

    os << "[H/h]             Displays this help menu you're looking at now!\n" << endl;

    os << "[Q/q]             Exits the program. \n" << endl;


    os << "-----------------------------------------------------------------------" << endl;
    os << "         PLAYLIST MODIFICATION MODE COMMANDS" << endl;
    os << "-----------------------------------------------------------------------" << endl;
    os << "Playlist modification mode is where you can make changes to your" << endl;
    os << "playlist. To get to Playlist Modification Mode, you have to modify" << endl;
    os << "or create a playlist from the main user menu.\n" << endl;

    os << "[L/l] <first><last>    List all songs from database from song ID <first>" << endl;
    os << "                       to song ID <last> in order by song ID number. " << endl;
    os << "                       Take note of the songID number, because you'll need" << endl;
    os << "                       that to add a song to your playlist!\n" << endl;

    os << "[A/a] <artist_key>     Looking for a specific artist? This will print out" << endl;
    os << "                       a list of songs whose artist contains the <artist_key>" << endl;
    os << "                       as part of their name. Artist keys and names are NOT" << endl;
    os << "                       case sensitive.\n" << endl;

    os << "[T/t] <title_key>      Looking for a specific song title? This will print out" << endl;
    os << "                       a list of songs whose title contains the <artist_key>" << endl;
    os << "                       as part of their name. Title keys and names are NOT" << endl;
    os << "                       case sensitive.\n" << endl;

    os << "Insert <songid> <pos>  Insert a song with the song ID <songid> into your" << endl;
    os << "                       playlist at position number <pos>\n" << endl;

    os << "Delete <songid>        Delete a song with the song ID <songid> from your" << endl;
    os << "                       playlist. Be careful, if your song appears more"<< endl;
    os << "                       than once... it will get deleted everywhere" << endl;
    os << "                       it appears!\n" << endl;

    os << "Show                   Display all the songs in your playlist.\n" << endl;
    
    os << "[B/b]                  Exits playlist modification mode. Returns to main menu.\n\n" << endl;
    
    return display_menu();
}


