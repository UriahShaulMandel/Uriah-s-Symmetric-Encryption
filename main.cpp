#include <string>
#include <map>
#include <math.h>
#include <bitset>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>

#define PBSTR "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
#define PBWIDTH 60
#define PROGRESS_BAR_DELAY 2000000

using namespace std;

signed long file_size(string file_path) {
	ifstream test_file(file_path, ios::binary);
	const auto begin = test_file.tellg();
	test_file.seekg(0, ios::end);
	const auto end = test_file.tellg();
	const auto f_size = (end - begin);
	test_file.close();
	return f_size;
}

inline void print_progress(const double percentage) {
	const int lpad = (int)(percentage * PBWIDTH);
	printf("\r%3d%% [%.*s%*s]", (int)(percentage * 100), lpad, PBSTR, PBWIDTH - lpad, "");
	fflush(stdout);
}

inline bool ends_with(std::string const& fullString, std::string const& ending) {
	return
		(fullString.length() >= ending.length())
		&&
		(0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
}


int main() {
	const char* text = R"V0G0N(
Uriah's Symmetric Encryption

This encryption is based on the one-time pad encryption method, which, when used once, cannot be cracked
This program takes an ascii key, and divides it to multiple keys using the space char
It then XORs each char from the original message with the key[0][counter++ % key[0].length()], key[1][counter++ % key[1].length()]....
Mathematically, it's just a pseudo-random generator for a one-time pad long xor key,
But the catch about it is that extremely long textual key can be used easily

For example, the Pentagon wants to send a single large message to the Kremlin
It can send a few soldiers with the info, of the algorithm and the short info 'The key is the first two paragraphs of Harry Poter'
When the soldiers come back from the Kremlin to the Pentagon, and this short info is passed securely, they can use this algorithm to encrypt the message with the first two paragraphs of Harry Poter
If the first chapter of Harry Potter is long enough, and this encryption algorithm stays between the two nations,
It may be mathematically impossible to crack this encryption.

In conclusion, this encryption is good only when:
1. There is a secure way to pass this code and short info like 'first two paragraphs of Harry Potter'
2. It is only used once
3. The key is quite long, with multiple spaces and words

While I can't think of use to it now, I think it's still kinda cool

Now,
)V0G0N";

	cout << text;


	string file_path, new_file_path, line, input_key;
	vector<string> key = vector<string>();
	char buffer;
	ifstream in_file;
	double f_size;
	bool file_opened;
	do {
		cout << "Please enter a file's path:" << endl;
		getline(cin, file_path);
		f_size = file_size(file_path);
		in_file = ifstream(file_path, std::ios::binary);
		file_opened = in_file.is_open();
		cout <<
			(file_opened ?
				"File opened succesfully!\r\n\r\n" :
				"Unable to open file!\r\nPlease try again.\r\n\r\n");
	} while (!file_opened);

	const bool ends_with_use = ends_with(file_path, ".use");
	if (ends_with_use)
		new_file_path = file_path.substr(0, file_path.length() - 4);
	else
		new_file_path = file_path + ".use";
	ofstream out_file(new_file_path, ios::binary | ios::ate);

	cout
		<< "Now, In order to "
		<< (ends_with_use ? "decrypt" : "encrypt")
		<< " the file, Please enter the secret key:"
		<< endl;
	getline(cin, input_key);


	///////////////////////////////////////////////////////////////
	////////////////////////KEY PARSING////////////////////////////
	///////////////////////////////////////////////////////////////
	int after_last_space = 0;
	for (int i = 0; i < input_key.length(); i++) {
		if (input_key[i] == ' ') {
			if (i - after_last_space - 1 > 0)
				key.push_back(input_key.substr(after_last_space, i - after_last_space));
			after_last_space = i + 1;
		}
	}
	key.push_back(input_key.substr(after_last_space, input_key.length() - after_last_space));
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	/////////////////////ACTUAL ALGORITHM//////////////////////////
	///////////////////////////////////////////////////////////////
	///////////NOTICE - counter is outside the WHILE loop!/////////
	///////////////////////////////////////////////////////////////
	const unsigned long int time_before = time(NULL);
	const unsigned int key_size = key.size();
	unsigned long counter = 0;
	double progress_counter = 0;
	while ((in_file).get(buffer)) {
		if (counter % PROGRESS_BAR_DELAY == 0)
			print_progress(progress_counter / f_size);
		progress_counter = progress_counter + 1;

		for (unsigned int i = 0; i < key_size; i++) {
			buffer ^= char(key[i][counter++ % key[i].length()]);
		}
		out_file << buffer;

	}
	///////////////////////////////////////////////////////////////


	const unsigned long int seconds_taken = time(NULL) - time_before;
	print_progress(1);
	cout << endl << "Took " << seconds_taken << " seconds!" << endl;
	in_file.close();
	out_file.close();
	return 0;
}