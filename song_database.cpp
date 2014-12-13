
#include "song_database.h"

/* Default constructor for song_database.
    Populates song database vector with song data from file provided by user.
    Performs several checks for file validity: checks to see if headers are
    valid, whether all lines in file contain 8 tab delimited fields, whether
    file can be opened successfuly and whether each song contains a non-empty
    artist and title field. Ensures all inputs are read in as the appropriate 
    datatypes and escapes all enclosing double quotes ("). If file is invalid,
    writes errors to error stream and exits with error code -1. 
 */
song_database::song_database(ifstream &readf, string fName, ostream &o, ostream &err): os(o) {
    
    // Open file
    readf.open(fName.c_str());
    
    // If file could not be opened, exit with errors
    if (readf.fail()){
        err << "ERROR: Could not open " << fName << " file. \nPlease check your file name and location and try again from the command line." << endl;
        exit(-1);
    }
    
    // If file was opened correctly
    if (readf.is_open()){
        
        string line;
        
        // Keeps track of which line we're on
        int n=0;
        
        // Read line, while we are able to read lines
        while (getline(readf,line)){
            
            // Create new stringstream with current line
            istringstream ss(line);
            vector<string> song_fields;
            string field;
            
            // While we are able to read fields in the current line
            //      Read line until we reach a tab character
            //      Push back what we've read into song_fields vector
            //      Start again and read the next field in current line
            while (getline(ss,field,'\t')) {
                song_fields.push_back(field);
            }
            
            // Checks the number of fields in line
            // If a line doesn't contain 8 fields, file is invalid so must
            // Exit with errors
            if (song_fields.size() != 8) {
                err << "INVALID FILE: One or more of the lines in your songs file either has missing fields, \ncontains fields not separated by single tabs or \nhas more than 8 fields.\nPlease check your file and try again. \n" << endl;
                
                exit(-1);
            }
            
            // Checks if one or more of the song fields in current line is empty
            // If so, file is invalid. Exit with errors.
            for (int i=0; i<song_fields.size(); i++){
                if (song_fields[i].empty()) {
                    err << "INVALID FILE: One or more of the lines in your songs file has missing fields or\ncontains fields not separated by single tabs.\nPlease check your file and try again. \n" << endl;
                    exit(-1);
                }
                
                // Remove double quotes from all fields
                for (int j=0; j<song_fields[i].length(); j++) {
                    if (song_fields[i][j] == '\"'){
                        song_fields[i].erase(song_fields[i].begin()+j);
                        j--;
                    }
                }                
            }

            // We are at the first line in the file. Must verify headings are
            // correct. If any are incorrect, exit with errors.
            if (n == 0) {
                if (song_fields[0] != "Name" || song_fields[1] != "Artist" || song_fields[2] != "Album" || song_fields[3] != "Genre" || song_fields[4] != "Size" || song_fields[5] != "Time" || song_fields[6] != "Year" || song_fields[7] != "Comments") {
                    
                    err << "INVALID FILE: Incorrect header(s).\nPlease check your file and try again. \n" << endl;
                    exit(-1);
                }
                
            }
            // We have passed the first line in the file.
            // Rest of lines in file now contain song data.
            // Create new instance of a song
            song s;
            
            // Check to see if Name or Artist field is empty
            // If so, exit with errors
            if (song_fields[0].empty() || song_fields[1].empty()) {
                err << "INVALID FILE: One or more of the songs in your songs file is missing a Name and/or an Artist field. \nPlease check your file and try again. \n" << endl;
                exit(-1);
            }
            
            // Populate new song instance from fields read into song_fields vec
            // Song id is determined by what line in the file we're on
            s.id = n;
            s.title = song_fields[0];
            s.artist = song_fields[1];
            s.album = song_fields[2];
            s.genre = song_fields[3];
            
            // Must pass s.size, s.time and s.year as integers, not strings
            // If field is not empty, read as integer datatype using
            // stringstream.
            if (!song_fields[4].empty()){
                istringstream ssSize(song_fields[4]);
                ssSize >> s.size;
            }
            else {
                s.size = '\0';
            }
            
            if (!song_fields[5].empty()){
                int time;
                istringstream ssTime(song_fields[5]);
                ssTime >> time;
                
                // Convert time in seconds to mins and secs
                s.time_mins = time/60;
                s.time_secs = time%60;
            }
            else {
                s.time_mins = '\0';
                s.time_secs = '\0';
            }
            
            if (!song_fields[6].empty()){
                istringstream ssYear(song_fields[6]);
                ssYear >> s.year;
            }
            else {
                s.year = '\0';
            }
            
            s.comments = song_fields[7];
            
            // Add s as last song in database
            database.push_back(s);
            
            // Advance to next line
            n++;
            
        }
    }
    
    // Close file
    readf.close();
    
    // Number of songs is number of elements in datbase minus
    // field headers line at database[0]
    num_of_songs = database.size()-1;
    
    // Tell user database was successfully loaded
    // If load was unsuccessful, program would have exited with errors
    os << "SUCCESS! " << num_of_songs << " songs were loaded. \n" << endl;
}

/* Convert a string to lowercase*/
string song_database::lowercase(string word) const{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

/* Returns a song from database at database[songid]
    1 <= songid <= num_of_songs as the first element in the song database is
    made up of the song headers
 */
song song_database::get_song(int songid) const { return database[songid]; }


/* Returns how many songs are in the database */
const int song_database::size() const { return num_of_songs; }


/* Displays songs from datbase[first] to databse[last]. Performs checks on first
    and last to ensure this can be done with no out of range errors. Iterates
    through songs in database using a for loop and displays each song using
    overloaded << operator.
 */
const void song_database::list_songs(int first, int last) const{
    
    // If last > num_of_songs, only displays until database[num_of_songs]
    if (last > num_of_songs ) { last = num_of_songs; }
    
    // If first < 1, only displays starting at datbase[1]
    if (first < 1) { first = 1; }
    
    // Displays songs from first to last
    for (int i=first; i<last+1; i++) {
        os << database[i];
    }
    
}

/* Displays songs containing key string as a substring of the artist field.
    Compares lowercase versions of both key and artist field to make search case
    insensitive. Returns number of times key was found as substring
 */
const int song_database::display_songs_by_artist(string &key) const{
    
    // Number of times key is found as substring
    int count = 0;
    
    // Lowercase version of key
    string key_lower = lowercase(key);
    
    // Iterate through all songs in database
    for (int i=1; i<num_of_songs; i++) {
        
        // Lowercase of artist field
        string artist_lower = lowercase(database[i].artist);
        
        // If key == artist, display in console and increase count by 1
        if(artist_lower.find(key_lower) != artist_lower.npos){
            os << database[i];
            count++;
        }
    }

    return count;
}

/* Displays songs containing key string as a substring of the title field.
    Compares lowercase versions of both key and title field to make search case
    insensitive. Returns number of times key was found as substring.
 */
const int song_database::display_songs_by_title(string &key) const{
    
    // Number of times key is found as substring
    int count = 0;
    
    // Lowercase version of key
    string key_lower = lowercase(key);
    
    // Iterate through database
    for (int i=1; i<=num_of_songs; i++) {
        
        // Lowercase version of title
        string title_lower = lowercase(database[i].title);
        
        // If key == title, display in console and increase count by 1
        if(title_lower.find(key_lower) != title_lower.npos){
            os << database[i];
            count++;
        }
    }
    
    return count;
}
