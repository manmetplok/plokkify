/* --------------------------------------------------------------------------------------------
Copyright 2010 Micke Nordin <mickewiki@gmail.com>. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Micke Nordin ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Micke Nordin OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Micke Nordin.
------------------------------------------------------------------------------------------- */


#ifndef _mnenc_h_
#define _mnenc_h_
#include <string>

using namespace std;

class mnenc {
	private:
		string dec; //Decrypted password
		string enc; //Encrypted password
                string user; //Username
		string imei; //Imei
		void get_imei(); //Gets the imei of the phone
		void set_enc(string str) {enc = str;}; //set encrypted password
		void set_dec(string str) {dec = str;}; //set decrypted password
		string genkey(); //generate a key to be used instead of imei
		bool is_int(char c); //see if a char is actualy an int
		string make_path();
	public:
		mnenc();
		void encrypt(string str); //encrypt password
		void decrypt(string str); //decrypt password
		string get_dec() {return dec;}; //get decrypted password
		string get_enc() {return enc;}; //Get encrypted password
		bool to_file(string filename); //Save to file
		bool from_file(string filename); //get from file
		void make_folder(); //Create /home/user/.qtify if it doesnt exist
		bool is_imei(string str); //see if a string passes as an imei
                /* Added by hexagon */
                bool user_to_file(string filename); //Save to file
                bool user_from_file(string filename); //get from file
                void set_user(string user);
                string get_user();
};
#endif
