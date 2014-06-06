#include "attendee.h"
#include "student.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

int mapStudents(const string& s, map<string, Student*>& m);
int splitLine(const string& s, const char& c, vector<string>& s_vec);

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

  cout << students["Alex Golubev"]->name() << endl;

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
  int start = 0, end = 0;

  while ((end = s.find(c, start)) != string::npos) {
    s_vec.emplace_back(s.substr(start, end));
    start = end + 1;
  }
  s_vec.emplace_back(s.substr(start , s.size() - start));

  return s_vec.size();
}

