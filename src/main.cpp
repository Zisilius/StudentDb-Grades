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
int output(const string&, map<string, Student*>&);
void findAverage(const int& indexNum, char* arr[], map<string, Student*>& m);
void findMatch(const int& indexNum, char* arr[], map<string, Student*>& m);

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
      return 1;
    }
  }

  file.close();


  cout << students["Alex Golubev"]->average() << endl;
  if (argc > 1) 
    if (cmdArgs(argc, argv, students))
      return 1;

  for (auto& e : students)
    delete e.second;

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
  int start = 0, n = 0, i=0;

  while ((n = s.find(c, start)) != string::npos) {
    s_vec.emplace_back(s.substr(start, n - start));
    cout << s_vec[i] << endl;
    i++;
    start = n + 1;
  }
  s_vec.emplace_back(s.substr(start , s.size() - start));

  return s_vec.size();
}

int cmdArgs(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  if (indexNum < 3) {
    cerr << "Comand line argument error" << endl;
    return 1;
  }
  int num; 
  if ((string)arr[1] == "average") {
    num = AVERAGE;
  }
  else if ((string)arr[1] == "match")
    num = MATCH;
  switch (num) {
    case AVERAGE: findAverage(indexNum, arr, m);
                  break;
    case MATCH: findMatch(indexNum, arr, m);
                  break;
    default: cout << "Command Line Argument: not found" << endl;
  }
  return 0;
}

int output(const string& s, map<string, Student*>& m)
{
  return 0; 
}

void findAverage(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  cout << "Entering findAverage" << endl;
  for (int i = 2; i < indexNum; i++) {
    for (map<string, Student*>::iterator e = m.begin(); e != m.end(); e++)
      if (e->second->name() == (string)arr[i])
        cout << e->second->average() << endl;
  }
}

void findMatch(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  for (int i = 2; i < indexNum; i++) {
    for (map<string, Student*>::iterator e = m.begin(); e != m.end(); e++)
      if ( e->second->name() == arr[i])
        e->second->output();
  }
}
