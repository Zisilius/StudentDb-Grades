#include "attendee.h"
#include "student.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

int mapStudents(const string& s, map<string, Student*>& m);
int splitLine(const string& s, const char& c, vector<string>& s_vec);
int cmdArgs(const int&, char*[], map<string, Student*>& m);
int outputDb(map<string, Student*>&);
bool findAverage(const int& indexNum, char* arr[], map<string, Student*>& m);
bool findMatch(const int& indexNum, char* arr[], map<string, Student*>& m);
template <typename T>
void clearDb(T& m)
{
  for (auto& e : m)
    delete e.second;
  cout << "Database successfully cleared" << endl;
}


enum {AVERAGE, MATCH};

int main(int argc, char* argv[])
{
  fstream file("student.db.week2");
  if (!file) {
    cerr << "File could not be opened" << endl;
    return 1;
  }

  map<string, Student*> students;

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
      cerr << "Bad shit is going down" << endl;
      clearDb(students);
      return 1;
    }
  } else
    outputDb(students);

  clearDb(students);

  return 0;
}

int mapStudents(const string& s, map<string, Student*>& m)
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

int cmdArgs(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  if (indexNum < 3) {
    cerr << "Command line argument error" << endl;
    return 1;
  }

  map<string, bool (*)(const int&, char*[], map<string, Student*>&)> cmd;

  cmd["--average"] = findAverage;
  cmd["-a"] = findAverage;
  cmd["--match"] = findMatch;
  cmd["-m"] = findMatch;

  if (!cmd[arr[1]](indexNum, arr, m))
    return 1;
  
  return 0;
}

int outputDb( map<string, Student*>& m)
{
  for (auto& e : m)
    e.second->output();
  return 0; 
}

bool findAverage(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  bool success = false;
  string name;
  for (int i = 2; i < indexNum; i++)
    for (map<string, Student*>::iterator e = m.begin(); e != m.end(); e++)
      if (e->second->name() == (string)arr[i]) {
        // This determines the correct suffics after a person's name
        if (e->second->name().at(e->second->name().size() - 1) == 's')
           name = (e->second->name() + '\'');
        else
          name = (e->second->name() + "'s");
        cout << name << " average: " << e->second->average() << endl;
        success = true;
        break;
      }
  return success;
}

bool findMatch(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  bool success = false;
  for (int i = 2; i < indexNum; i++)
    for (map<string, Student*>::iterator e = m.begin(); e != m.end(); e++)
      if ( e->second->name() == arr[i]) {
        e->second->output();
        success = true;
        break;
      }
  return success;
}
