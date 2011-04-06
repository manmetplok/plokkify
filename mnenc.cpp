#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>

#include "mnenc.h"

using namespace std;

mnenc::mnenc() { //Constructor
	make_folder();
	get_imei(); //see get_imei below
	imei += imei; //imei now have 30 digits
	imei += imei; //imei now have 60 digits
	imei += imei; //imei now have 120 digits
	imei += imei; //imei now have 240 digits, should now be longer than any password
}

void mnenc::encrypt(string str) { //Run xor against imei
	for(int i=0; i < (signed) str.size(); i++)	{
		str[i] = str[i] ^ imei[i];
	}
	enc = str;
}
 
void mnenc::decrypt(string str) { //Same as above only the other way around
	for(int i = 0; i < (signed) enc.size(); i++)	{
		str[i] = imei[i] ^ str[i];
	}
	dec = str;
}

bool mnenc::to_file(string filename) { //Save to file
	bool worked = false;
	ofstream keyfile;
	keyfile.open(filename.c_str());
	if(keyfile.is_open()) {
		keyfile << enc;
		keyfile.close();
		worked = true;
	}
	return worked;
}

bool mnenc::from_file(string filename) { //Read password file
	bool worked = false;
	ifstream keyfile(filename.c_str());
	string encryptedpw = "";
	string line = "";
	if (keyfile.is_open()) {
		while (! keyfile.eof() ) {
			getline (keyfile,line);
			encryptedpw += line;
		}
		keyfile.close();
		worked = true;
	}
	enc = encryptedpw;
        decrypt(enc); // Automatically decrypt password on read
	return worked;
}

string mnenc::genkey() { 
	string key = "";
	srand(time(NULL));
	for(int i = 0; i < 15; i++) {
		key += (rand() % 10);  //generate a random number between 0 and 9
	}
	string filename = make_path() + ".keyfile"; //This is where the key goes 
	ofstream os;
	os.open(filename.c_str());
	if(os.is_open()) {
		os << key;
		os.close();
	}
	return key;
}
void mnenc::get_imei() {
	/* TODO 
	 * Implement this in c++ since it is realy realy ugly to shell out like this...
	 */
	  
	string username = getenv("USER"); //Get username
	string filename = make_path() + ".keyfile"; //This is where the key goes if we generate it
	string cmd = "dbus-send --system --print-reply --type=method_call --dest=com.nokia.phone.SIM /com/nokia/phone/SIM/security Phone.Sim.Security.get_imei | grep string | sed -e 's/^.*\\\"\\([0-9]\\)/\\1/' -e 's/\\\"//'"; //Command used when shelling out to get imei
	
	FILE *fp; //a file pointer
	char buffer[1024]; //Some tmp storage
	fp = popen(cmd.c_str(), "r"); //Open a pipe whith the command
	while ( fgets(buffer, 1024, fp) != NULL ) //Read the result
		imei.append(buffer); //Add the result to our attribute
	pclose(fp); //Close the pipe

    if(!is_imei(imei)) { //If we could not get imei
		ifstream keyfile(filename.c_str()); //open the keyfile
		string k = "";
		string line = "";
		if (keyfile.is_open()) { //if it worked
			while (! keyfile.eof() ) { //Get the key from there
				getline (keyfile,line);
				k += line;
			}
			keyfile.close(); //Close the file
			imei = k; //And save result
		} else { //If that didnt work 
			imei = genkey(); //generate a new key and save that to teh keyfile
		}
		
	}
}

bool mnenc::user_from_file(string filename) { //Read userfile (Added by hexagon 2010-01-17)
        bool worked = false;
        ifstream userfile(filename.c_str());
        string buf = "";
        string line = "";
        if (userfile.is_open()) {
                while (! userfile.eof() ) {
                        getline (userfile,line);
                        buf += line;
                }
                userfile.close();
                worked = true;
        }
        user = buf;
        return worked;
}

bool mnenc::user_to_file(string filename) { //Save username to file (Added by hexagon 2010-01-17)
        bool worked = false;
        ofstream userfile;
        userfile.open(filename.c_str());
        if(userfile.is_open()) {
                userfile << user;
                userfile.close();
                worked = true;
        }
        return worked;
}

void mnenc::set_user(string usr) { // Sets username (Added by hexagon 2010-01-17)
    user = usr.c_str();
}

string mnenc::get_user() { // Gets username (Added by hexagon 2010-01-17)
    return user;
}

void mnenc::make_folder() { //Create home directory
	string dirname = make_path(); 
	int ret = chdir(dirname.c_str());
	if(ret != 0) {
		mkdir(dirname.c_str(), 0755);
	}
}

bool mnenc::is_int(char c) { //See if a char is an int
	return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
}

bool mnenc::is_imei(string str) { //See if a string is made up of 15 ints
	bool proper_length = false; //Is it 15 chars?
	bool is_ints = true; //Is it only ints?
	if(str.length() == 15) { //Check length
		proper_length = true;
	} else {
		return false; //Exit early if it fails length test
	}
	for(int i = 0; i < (signed) str.length(); i++) { //Check if they are all ints
		if(!is_int(str[i])) {
			is_ints = false;
		}
	}
	if(proper_length && is_ints) { //Return true if it passes the tests
		return true;
	} else {
		return false; //And false if it doesnt
	}
}

string mnenc::make_path() { //Create path to qtify home
	string username = getenv("USER"); //Get username
	string path = "/home/" + username + "/.qtify/"; //This is home directory of qtify
	return path;
}
