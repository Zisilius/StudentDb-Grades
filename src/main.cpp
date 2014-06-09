#include "student.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

int mapStudents(const string& s, map<string, Student*>& m);
int splitLine(const string& s, const char& c, vector<string>& s_vec);
int cmdArgs(const int&, char *[], map<string, Student*>& m);
int findAverage(const int& indexNum, char* arr[], map<string, Student*>& m);
int findMatch(const int& indexNum, char* arr[], map<string, Student*>& m);
int printHelp(const int& i, char* arr[], map<string, Student*>& m);
void outputDb(map<string, Student*>&);
void delArr(char *arr[], size_t&& size);
bool strCmp(const char *a, const char *b);
template <typename T>
void clearDb(T& m)
{
  for (auto& e : m)
    delete e.second;
}

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
  map<string, int (*)(const int&, char*[], map<string, Student*>&)> cmd;

  cmd["--average"] = findAverage;
  cmd["-a"] = findAverage;
  cmd["--match"] = findMatch;
  cmd["-m"] = findMatch;
  cmd["--help"] = printHelp;
  cmd["-h"] = printHelp;

  try {
    if (!cmd.at(arr[1])(indexNum, arr, m)) {
      cerr << "Error: Nothing Could Be Matched" << endl;
      return 1;
    }
  } catch (out_of_range e) {
    cerr << "Error: Such Command Doesn't Exist" << endl;
  }
  
  return 0;
}

void outputDb(map<string, Student*>& m)
{
  for (auto& e : m)
    e.second->output();
}

int findAverage(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  if (indexNum < 3) {
    cerr << "Error: Not Enough Command Line Arguments" << endl;
    return false;
  }

  int success = 0;
  string name;
  for (int i = 2; i < indexNum; i++)
    for (map<string, Student*>::iterator e = m.begin(); e != m.end(); e++)
      if (strCmp(e->second->name().c_str(), arr[i])) {
        // This determines the correct suffics after a person's name
        if (e->second->name().at(e->second->name().size() - 1) == 's')
           name = (e->second->name() + '\'');
        else
          name = (e->second->name() + "'s");
        cout << name << " average: " << e->second->average() << endl;
        success++;
        break;
      }
  if (success < indexNum - 2)
    cerr << "Error: Only " << success << " People Could Be Matched" << endl;
  return success;
}

int findMatch(const int& indexNum, char* arr[], map<string, Student*>& m)
{
  if (indexNum < 3) {
    cerr << "Error: Not Enough Command Line Arguments" << endl;
    return false;
  }

  int success = 0;
  for (int i = 2; i < indexNum; i++)
    for (map<string, Student*>::iterator e = m.begin(); e != m.end(); e++)
      if (strCmp(e->second->name().c_str(), arr[i])) {
        e->second->output();
        success++;
        break;
      }
  if (success < indexNum - 2 && indexNum - 2 != 1)
    cerr << "Error: Only " << success << " People Could Be Matched" << endl;
  return success;
}

int printHelp(const int& i, char* arr[], map<string, Student*>& m)
{
  cout << "***** Version 0.01 *****\n"
       << "\nIf used without any command line arguments, the program will"
          " assemble the database before outputting it in full."
          "\n\nCommand Line Options:\n\t-m, --match\n\t\t <program name> "
          "-m <names to match>"
          "\n\t\tOutputs the full information for matched students.\n\n\t"
          "-a, --average\n\t\t<program name> -a <names to match>\n\t\t"
          "Outputs the average grade of matched students.\n\n\t-h, --help"
          "\n\t\tPrints out this very helpful text :)\n\n\n"
          "Author: Alexey Golubev" << endl;
  return true;
}

bool strCmp(const char *a, const char *b)
{
  vector<string> s_vec;

  splitLine(a, ' ', s_vec);
  char *arr1[s_vec.size()];
  for(int i = 0; i < s_vec.size(); i++) {
    arr1[i] = new char[s_vec[i].size() + 1];
    for (int j = 0; j < s_vec[i].size() + 1; j++) {
      arr1[i][j] = s_vec[i].c_str()[j];
    }
  }
  s_vec.clear();

  splitLine(b, ' ', s_vec);
  char *arr2[s_vec.size()];
  for(int i = 0; i < s_vec.size(); i++) {
    arr2[i] = new char[s_vec[i].size() + 1];
    for (int j = 0; j < s_vec[i].size() + 1; j++) {
      arr2[i][j] = s_vec[i].c_str()[j];
    }
  }

  for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++) {
    for (int j = 0; arr1[i][j] != '\0' && arr2[i][j] != '\0'; j++) {

      if (arr1[i][j] == arr2[i][j])
        continue;
      else if (arr1[i][j] > 96 && arr2[i][j] > 96) {
        if (arr1[i][j] != arr2[i][j]) {
          delArr(arr1, sizeof(arr1) / sizeof(arr1[0]));
          delArr(arr2, sizeof(arr2) / sizeof(arr2[0]));
          return false;
        }
      } else if (arr1[i][j] < 97) {
        if (arr1[i][j] + 32 != arr2[i][j]) {
          delArr(arr1, sizeof(arr1) / sizeof(arr1[0]));
          delArr(arr2, sizeof(arr2) / sizeof(arr2[0]));
          return false;
        }
      } else if (arr2[i][j] < 97) {
        if (arr2[i][j] + 32 != arr1[i][j]) {
          delArr(arr1, sizeof(arr1) / sizeof(arr1[0]));
          delArr(arr2, sizeof(arr2) / sizeof(arr2[0]));
          return false;
        }
      } else 
        cout << "Uh hu: we might have a problem" << endl;
    }  
  }

  delArr(arr1, sizeof(arr1) / sizeof(arr1[0]));
  delArr(arr2, sizeof(arr2) / sizeof(arr2[0]));
  return true;
}

void delArr(char *arr[], size_t&& size) 
{
  for (size_t i = 0; i < size; i++) {
    delete[] arr[i];
  }
}
