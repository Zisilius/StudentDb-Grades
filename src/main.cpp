#include "student.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

int mapStudents(const string& s, map<string, Student *>& m);
int splitLine(const string& s, const char& c, vector<string>& s_vec);
int cmdArgs(const int&, char *[], const map<string, Student *>& m);
int findAverage(const int& indexNum, char* arr[], const map<string, Student *>& m);
int findMatch(const int& indexNum, char* arr[], const map<string, Student *>& m);
int printHelp(const int& i, char *arr[], const map<string, Student *>& m);
int dirMatch(const int& indexNum, char *arr[], const map<string, Student *>& m);
void outputDb(map<string, Student *>&);
bool strCmp(const char *a, const char *b);
template <typename T>
void clearDb(T& m);

int main(int argc, char *argv[])
{
  fstream file("student.db.week2");
  if (!file) {
    cerr << "File could not be opened" << endl;
    return 1;
  }

  map<string, Student *> students;

  string temp;
  while (!file.eof()) {
    getline(file, temp);
    if (temp.size() == 0)
      continue;
    if (mapStudents(temp, students)) {
      cerr << "Error: assembling the database" << endl;
      clearDb(students);
      return 1;
    }
  }

  file.close();

  if (argc > 1) {
    if (cmdArgs(argc, argv, students)) {
      clearDb(students);
      return 1;
    }
  } else outputDb(students);

  clearDb(students);

  return 0;
}

template <typename T>
void clearDb(T& m)
{
  for (auto& e : m)
    delete e.second;
}

int mapStudents(const string& s, map<string, Student *>& m)
{
  vector<string> s_vec;
  
  if (splitLine(s, ':', s_vec) != 5)
    return 1;

  m[s_vec[0]] = new Student(s_vec[0], s_vec[1], s_vec[2], s_vec[3], s_vec[4]);
  return 0;
}

int splitLine(const string& s, const char& c, vector<string>& s_vec)
{
  int start = 0, n = 0;

  while ((n = s.find(c, start)) != string::npos) {
    s_vec.emplace_back(s.substr(start, n - start));
    start = n + 1;
  }
  s_vec.emplace_back(s.substr(start , s.size() - start));

  return s_vec.size();
}

int cmdArgs(const int& indexNum, char *arr[], const map<string, Student *>& m)
{
  map<string, int (*)(const int&, char *[], const map<string, Student *>&)> cmd;

  cmd["--average"] = findAverage;
  cmd["-a"] = findAverage;
  cmd["--match"] = findMatch;
  cmd["-m"] = findMatch;
  cmd["--help"] = printHelp;
  cmd["-h"] = printHelp;
  cmd["--dirmatch"] = dirMatch;
  cmd["-dm"] = dirMatch;

  try {
    if (!cmd.at(arr[1])(indexNum, arr, m)) return 1;
  } catch (out_of_range e) {
    cerr << "Error: Such Command Doesn't Exist" << endl;
    return 1;
  }
  
  return 0;
}

void outputDb(map<string, Student *>& m)
{
  for (auto& e : m)
    e.second->output();
}


int findAverage(const int& indexNum,char *arr[],const map<string, Student *>& m)
{
  if (indexNum < 3) {
    cerr << "Error: Not Enough Command Line Arguments" << endl;
    return false;
  }

  int success = 0;
  string name;
  for (int i = 2; i < indexNum; i++)
    for (auto& e : m)
      if (strCmp(e.second->name().c_str(), arr[i])) {
        // This determines the correct suffics after a person's name
        if (e.second->name().at(e.second->name().size() - 1) == 's')
           name = (e.second->name() + '\'');
        else
          name = (e.second->name() + "'s");
        cout << name << " average: " << e.second->average() << endl;
        success++;
      }

  cout << endl << success << " people were matched" << endl;
  return true;
}

int findMatch(const int& indexNum, char* arr[], const map<string, Student*>& m)
{
  if (indexNum < 3) {
    cerr << "Error: Not Enough Command Line Arguments" << endl;
    return false;
  }

  bool first;
  int success = 0;
  for (int i = 2; i < indexNum; i++)
    for (auto& e : m)
      if (strCmp(e.second->name().c_str(), arr[i])) {
        e.second->output();
        success++;
      }
  cout << endl << success << " people were matched" << endl;
  return true;
}

int dirMatch(const int& indexNum, char* arr[], const map<string, Student *>& m)
{
  if (indexNum < 3) {
    cerr << "Error: Not Enough Command Line Arguments" << endl;
    return false;
  }

  for (int i = 2; i < indexNum; i++) 
    try {
      m.at(arr[i])->output();
    } catch (out_of_range e) {
      cout << "No direct match was made for \""
           << arr[i] << "\""<< endl;
    }
  return true;
}

int printHelp(const int& i, char* arr[], const map<string, Student*>& m)
{
  cout << "***** Version 0.02 *****\n"
       << "\nIf used without any command line arguments, the program will"
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
  return true;
}

bool strCmp(const char *a, const char *b)
{
  int i;
  for (; a[0] != '\0'; a++) {
    for (i = 0; b[i] != '\0'; i++)
      if (b[i] == a[i]) continue;
      else if (a[i] < 97 && a[i] + 32 == b[i]) continue;
      else if (b[i] < 97 && b[i] + 32 == a[i]) continue;
      else break;
    if (b[i] == '\0') return true;
  }
  return false;
}
