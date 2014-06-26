#include "student.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

/* This will be used to map command-line parameters to functions/commands */
typedef int (*cmd_func)(const int&, char *[], const map<string, Student *>&);

/* these function are for assembling and operating the database of students */
int map_students(const string& s, map<string, Student *>& m);
int split_line(const string& s, const char& c, vector<string>& s_vec);
void output_database(const map<string, Student *>&);
template <typename T>
void clear_database(T& m);

/* these function are for processing the command line input */
int command_line_interpreter(const int&, char *[],
                             const map<string, Student *>& m);
int find_average(const int& indexNum, char *arr[],
                 const map<string, Student *>& m);
int find_match(const int& indexNum, char *arr[],
               const map<string, Student *>& m);
int print_help(const int& i, char *arr[], const map<string, Student *>& m);
int direct_match(const int& indexNum, char *arr[],
                 const map<string, Student *>& m);

/* miscelaneous/all-purpose functions */
bool str_compare(const char *a, const char *b);


int main(int argc, char *argv[])
{
	fstream file("student.db.week2");
	if (!file.is_open()) {
		cerr << "Error: file couldn't be opened" << endl;
		return 1;
	}
	/* The map will serve as a simple database for students */
	map<string, Student *> students;
	string tmp;
	while (!file.eof()) {
		getline(file, tmp);
		if (tmp.size() == 0)
			continue;
		if (map_students(tmp, students)) {
			cerr << "Error: assembling the database" << endl;
			clear_database(students);
			return 1;
		}
	}
	file.close();

	/* command line processing takes over here if there is any */
	if (argc > 1) {
		if (command_line_interpreter(argc, argv, students)) {
			clear_database(students);
			return 1;
		}
	} else {
		output_database(students);
	}

	clear_database(students);
	return 0;
}


template <typename T>
void clear_database(T& m)
{
	for (auto& it : m)
		delete it.second;
}

int map_students(const string& s, map<string, Student *>& m)
{
	vector<string> v;

	if (split_line(s, ':', v) != 5)
		return 1;

	m[v[0]] = new Student(v[0], v[1], v[2], v[3], v[4]);
	return 0;
}

int split_line(const string& s, const char& c, vector<string>& v)
{
	int start = 0, end = 0;

	while ((end = s.find(c, start)) != string::npos) {
		v.emplace_back(s.substr(start, end - start));
		start = end + 1;
	}
	v.emplace_back(s.substr(start , s.size() - start));

	return v.size();
}

int command_line_interpreter(const int& indexNum, char *arr[],
                             const map<string, Student *>& m)
{
	map<string, cmd_func> cmd;

	cmd["--average"] = find_average;
	cmd["-a"] = find_average;
	cmd["--match"] = find_match;
	cmd["-m"] = find_match;
	cmd["--help"] = print_help;
	cmd["-h"] = print_help;
	cmd["--dirmatch"] = direct_match;
	cmd["-dm"] = direct_match;

	try {
		if (cmd.at(arr[1])(indexNum, arr, m))
			return 1;
	} catch (out_of_range e) {
		cerr << "Error: such command doesn't exist" << endl;
		return 1;
	}

	return 0;
}

void output_database(const map<string, Student *>& m)
{
	for (auto& it : m)
		it.second->output();
}


int find_average(const int& indexNum, char *arr[],
                 const map<string, Student *>& m)
{
	if (indexNum < 3) {
		cerr << "Error: not enough arguments" << endl;
		return 1;
	}

	int success = 0;
	map<string, bool> been_printed;
	string name;

	for (int i = 2; i < indexNum; i++) {
		for (auto& it : m) {
			if (str_compare(it.second->name().c_str(), arr[i])) {
				/* Determines if the name has been matched before */
				try {
					if (been_printed.at(it.second->name()))
						continue;
				} catch (out_of_range e) {
					been_printed[it.second->name()] = true;
				}
				/* Determines the correct suffics after a person's name */
				if (it.second->name().at(it.second->name().size() - 1) == 's')
					name = (it.second->name() + '\'');
				else
					name = (it.second->name() + "'s");
				cout << name << " average: " << it.second->average() << endl;
				success++;
			}
		}
	}
	cout << endl << success << " people were matched" << endl;
	return 0;
}

int find_match(const int& indexNum, char *arr[],
               const map<string, Student *>& m)
{
	if (indexNum < 3) {
		cerr << "Error: not enough arguments" << endl;
		return 1;
	}

	int success = 0;
	map<string, bool> been_printed;

	for (int i = 2; i < indexNum; i++) {
		for (auto& it : m) {
			if (str_compare(it.second->name().c_str(), arr[i])) {
				/* Determines if the name has been matched before */
				try {
					if (been_printed.at(it.second->name()))
						continue;
				} catch (out_of_range e) {
					been_printed[it.second->name()] = true;
				}
				it.second->output();
				success++;
			}
		}
	}
	cout << endl << success << " people were matched" << endl;
	return 0;
}

int direct_match(const int& indexNum, char *arr[],
                 const map<string, Student *>& m)
{
	if (indexNum < 3) {
		cerr << "Error: not enough arguments" << endl;
		return 1;
	}

	for (int i = 2; i < indexNum; i++)
		try {
			m.at(arr[i])->output();
		} catch (out_of_range e) {
			cout << "No direct match was made for \""
			     << arr[i] << "\""<< endl;
		}
	return 0;
}

int print_help(const int& i, char *arr[], const map<string, Student *>& m)
{
	cout << "***** Version 0.02 *****\n"
	        "\nIf used without any command line arguments, the program will"
	        " assemble the database before outputting it in full."
	        "\n\nCommand Line Options:\n\t-m, --match\n\t\t <program name> "
	        "-m <names to match>"
	        "\n\t\tOutputs the full information for matched students.\n\n\t"
	        "-dm, --dirmatch\n\t\t<program name> -dm <names to match>\n\t\t"
	        "Attempts to match the name at constant time.\n\n\t"
	        "-a, --average\n\t\t<program name> -a <names to match>\n\t\t"
	        "Outputs the average grade of matched students.\n\n\t-h, --help"
	        "\n\t\tPrints out this very helpful text :)\n\n\n"
	        "Author: Alexey Golubev" << endl;
	return 0;
}

bool str_compare(const char *a, const char *b)
{
	int i;
	while (a[0] != '\0') {
		for (i = 0; b[i] != '\0'; ++i) {
			if (b[i] == a[i])
				continue;
			else if (a[i] < 97 && a[i] + 32 == b[i])
				continue;
			else if (b[i] < 97 && b[i] + 32 == a[i])
				continue;
			else
				break;
		}
		if (b[i] == '\0')
			return true;
		a++;
	}
	return false;
}
