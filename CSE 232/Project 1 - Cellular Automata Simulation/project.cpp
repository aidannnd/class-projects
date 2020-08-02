#include<iostream>
#include<string>
using std::cout; using std::cin; using std::string; using std::endl;
using std::to_string;

int get_line_sum(string line) {
    int sum = 0;
    // reads through each char in line, adds it to the sum
    for (int i = 0; i < (int)line.length(); i++) {
        sum += (line[i]-'0'); // converts char to int
    }
    
    return sum;
}

char get_next_state(string neighborhood, string rules) {
    bool read_rule = false;
    string current_rule = "";
        
    // loops through all rules, if the neighborhood string is found in the rules string, it returns the 
    // associated number
    for (int i = 0; i < (int)rules.length(); i++) {
        if (rules[i] != ' ' && read_rule == false) {
            current_rule += rules[i];
        } else if (read_rule == false) {
            // finished reading a 3 digit rule into current_rule
            read_rule = true;
            // compare the read-in rule (current_rule) to the neighborhood
            if (neighborhood.compare(current_rule) == 0) {
                return rules[i+4]; // print out the associated number
            }
            // neighborhood does not equal the current_rule
            current_rule = "";
            continue;
        }
        // end of a line in input
        if (rules[i] == '\n') {
            read_rule = false;
        }
    }
    // neighborhood was not found in the input
    return '0';
}

void update_line(string &line, string rules) {
    string line_copy((int)line.length(), '0'); // a string to make changes to
    for (int i = 0; i <= (int)line_copy.length(); i++) {
        // loop through line and check each combination of 3 numbers, see if they equal
        // a given rule by calling get_next_state()
        char next_state = get_next_state(line.substr(i,3), rules);
        if (next_state != '0') {
            // if a match is found the associated number will be added to line_copy
            line_copy.replace(i+1,1,1,next_state);
        }
    }
    // defining the two edge cases of "#0000000##" and "##0000000#"
    string wrap_check_1{line[(int)line.length()-2], line[(int)line.length()-1], line[0]};
    string wrap_check_2{line[(int)line.length()-1], line[0], line[1]};
    // checking for the first edge case
    if (get_next_state(wrap_check_1, rules) != '0') {
        char next_state = get_next_state(wrap_check_1, rules);
        line_copy.replace((int)line.length()-1,1,1,next_state);
    }
    // checking for the second edge case
    if (get_next_state(wrap_check_2, rules) != '0') {
        char next_state = get_next_state(wrap_check_2, rules);
        line_copy.replace(0,1,1,next_state);
    }
    line = line_copy;
}

string run_cellular_automata(string rules, int generations, string start) {
    string output = "";
    // adds the initial line, formatted to specifications, to the output
    output += start + " sum = " + to_string(get_line_sum(start)) + '\n';
    for (int i = 0; i < generations-1; i++) {
        // updates according to the generations int and adds each to the output
        update_line(start, rules);
        output += start + " sum = " + to_string(get_line_sum(start)) + '\n';
    }
    return output;
}

int main() {
    // adds '\n' to each line to work with my code
    string text = "";
    string line;
    while (getline(cin, line)){
        text += line + '\n';
    }
    
    string rules = "";
    string num_lines = "";
    string start_line = "";
    
    // picks out the rules from the beginning of the input and stores them in rules
    int index = 0;
    for (int i = 0; i < (int)text.length(); i++) {
        if (text[i] != '.') {
            rules += text[i];
        } else {
            index = i+2;
            break;
        }
    }
    //picks out the number of lines from the input and stores it in num_lines
    for (int i = index; i < (int)text.length(); i++) {
        if (text[i] != '\n') {
            num_lines += text[i];
        } else {
            index = i+1;
            break;
        }
    }
    // picks out the start line from the input and stores it in start_line
    for (int i = index; i < (int)text.length(); i++) {
        if (text[i] != '\n') {
            start_line += text[i];
        } else {
            break;
        }
    }
    // the final output
    cout << run_cellular_automata(rules, stoi(num_lines), start_line);
}