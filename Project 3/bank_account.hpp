#pragma once

#include<sstream>
#include <iomanip>
#include<string>
using std::string;

void deposit(double &balance, double amount) {
	balance += amount;
}

bool withdraw(double &balance, double amount) {
	if (amount > balance)
		return false;
	else {
		balance -= amount;
		return true;
	}
}

void overdraft(double &balance, double amount) {
	balance -= (amount + 35);
}

double interest_for_month(double &balance, double apr) {
	double interest = std::floor((balance*(apr*0.01)/12)*100.0)/100.0;
	return interest;
}

void string_date_to_int_ptrs(const string date, int* year, int* month, int* day) {
	std::istringstream iss(date);
	string temp;
	int date_part = 1;

	// parse the line for year, month, and day
	while (getline(iss, temp, '-')) {
		switch (date_part) {
			case 1: // on year
				*year = stoi(temp, nullptr);
				break;
			case 2: // on month
				*month = stoi(temp, nullptr);
				break;
			case 3: // on day
				*day = stoi(temp, nullptr);
				break;
		}
		date_part++;
	}
}

void string_date_to_ints(const string date, int &year, int &month, int &day) {
	std::istringstream iss(date);
	string temp;
	int date_part = 1;

	// parse the line for year, month, and day
	while (getline(iss, temp, '-')) {
		switch (date_part) {
		case 1: // on year
			year = stoi(temp, nullptr);
			break;
		case 2: // on month
			month = stoi(temp, nullptr);
			break;
		case 3: // on day
			day = stoi(temp, nullptr);
			break;
		}
		date_part++;
	}
}

int number_of_first_of_months(string earlier, string later) {
	// defining variables
	int earlier_year, earlier_month, earlier_day;
	string_date_to_ints(earlier, earlier_year, earlier_month, earlier_day);

	int later_year, later_month, later_day;
	string_date_to_ints(later, later_year, later_month, later_day);

	// checking for no firsts cases
	if (earlier_year > later_year)
		return 0;
	else if (earlier_year == later_year && earlier_month >= later_month)
		return 0;
	// counting number of firsts of months
	else {
		int firsts = 0;
		// decrement the later date until it equals the earlier date
		while (later_day--) {
			if (later_day == 1)
				firsts++;
			if (later_day == earlier_day) {
				// has reach the end of the counting (the dates are the same)
				if (earlier_year == later_year && earlier_month == later_month)
					break;
			}
			if (later_day == 0) { // update month
				later_day = 31;
				later_month--;
			}
			if (later_month == 0) { // update year
				later_month = 12;
				later_year--;
			}
		}
		return firsts;
	}
}

double interest_earned(double balance, double apr, string begin_date, string end_date) {
	if (balance < 0) // case for $0 balance
		return 0.00;
	
	int firsts = number_of_first_of_months(begin_date, end_date);
	double total_interest = 0;
	for (int i = 0; i < firsts; i++) {
		total_interest += interest_for_month(balance, apr);
		balance += interest_for_month(balance, apr);
	}
	return total_interest;
}

string process_command(string line, string &previous_date, double &balance, double apr) {
	// process the line for variables
	std::istringstream iss(line);

	string current_date;
	getline(iss, current_date, ' ');
	string command;
	getline(iss, command, ' ');
	string money_str;
	getline(iss, money_str);
	double money = stod(money_str.substr(1, string::npos));

	// case for if this is the first time accessing account
	if (previous_date == "")
		previous_date = current_date;

	// setting up output text according to specifications
	std::ostringstream oss;
	oss << std::setprecision(2) << std::fixed;
	oss << "On " << current_date << ": Instructed to perform \"" << command << " " << money_str << "\"\n";

	double initial_balance = balance; // for use in interest calculations
	
	// calculate interest and apply it to the account
	int times_accrued = number_of_first_of_months(previous_date, current_date);
	if (times_accrued > 0) { // make sure there is interest to apply
		double total_interest = interest_earned(initial_balance, apr, previous_date, current_date);
		oss << "Since " << previous_date << ", interest has accrued " << times_accrued << " times.\n$" << total_interest << " interest has been earned.\n";
		balance += total_interest;
	}

	// deposit/withdraw based on command
	if (command == "Deposit")
		deposit(balance, money);
	else if (command == "Withdraw") {
		// overdraft
		if (!withdraw(balance, money)) {
			overdraft(balance, money);
			oss << "Overdraft!\n";
		}
	}
	
	oss << "Balance: " << balance << "\n";

	previous_date = current_date;
	return oss.str();
}

string process_commands(string lines, double apr) {
	std::istringstream iss(lines);
	string line;

	string previous_date = "";
	double balance = 0;

	// process the lines, add them to the oss
	std::ostringstream oss;
	while (getline(iss, line))
		oss << process_command(line, previous_date, balance, apr);

	return oss.str();
}