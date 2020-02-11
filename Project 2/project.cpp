#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<fstream>
#include<string>
using std::string;
#include<sstream>
#include <cmath>
#include<vector>
using std::vector;
#include<algorithm>

int compare_pw(string current_pw, string user_pw) {
	// compare two passwords and returns the difference between the two
	int differences = 0;
	string bigger_str = user_pw;
	string smaller_str = current_pw;

	if (current_pw.size() > user_pw.size()) {
		bigger_str = current_pw;
		smaller_str = user_pw;
	}
	// compare each char of each password
	for (int i = 0; i < (int)smaller_str.size(); i++) {
		if (smaller_str[i] != bigger_str[i])
			differences++;
	}
	// if the strings are different sizes this will account for that
	differences += bigger_str.size() - smaller_str.size();
	return differences;
}

void print_passwords(string user_pw) {
	// go through all the passwords looking for 0 differences, if none are found 
	// look for passwords with 1 differences, repeat until the first matching 
	// password is found, stop incrementing and print out all the passwords
	// that match the difference int

	int difference = 0;
	string current_pw;
	bool pw_found = false;
	std::ostringstream oss;
	vector<string> matching_pw;

	// go until a matching pw to the difference int is found
	while (!pw_found) {
		std::ifstream in_file("common_passwords.txt");
		// read in all passwords
		while (getline(in_file, current_pw)) {
			// if the current password from the text file matches the difference int
			if (compare_pw(current_pw, user_pw) == difference) {
				// read in the rest of the file looking for other same difference passwords, then stop reading in
				pw_found = true;
				matching_pw.push_back(current_pw);
			}

		}
		// if no matching password to the difference int was found
		difference++;
	}
	// construct string output according to the project specifications
	std::sort(matching_pw.begin(), matching_pw.end());
	for (string pw : matching_pw)
		oss << pw << ", ";
	cout << oss.str() << endl;
	cout << "All of which are " << difference-1 << " character(s) different." << endl;
}

int main() {
	// prompt user for password, then print out passwords most similar to the password provided
	string user_pw;
	cout << "Give me a password:";
	cin >> user_pw;
	cout << "\nYou provided a password of " << user_pw << endl;
	cout << "The most similar passwords to " << user_pw << " are:" << endl;
	print_passwords(user_pw);
}