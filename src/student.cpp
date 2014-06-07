#include "student.h"
#include <iostream>
#include <string>
#include <vector>

Student::Student(const std::string& name, const std::string& email,                    
                 const std::string& comment, const std::string& date,                  
                 const std::string& grades)
                : _name(name), _email(email), _comment(comment), _date(date),
                _grades(grades) {}

const std::string& Student::name() const { return _name; }
const std::string& Student::email() const { return _email; }
const std::string& Student::comment() const { return _comment; }
const std::string& Student::date() const { return _date; }
const std::string& Student::grades() const { return _grades; }

const int Student::average() const
{
  std::vector<std::string> s_vec;
  int start = 0, end = 0;

  std::string temp = grades();
  while ((end = temp.find(',', start)) != std::string::npos) {
    s_vec.emplace_back(temp.substr(start, end));
    start++;
  }
  s_vec.emplace_back(temp.substr(start, temp.size() - start));

  int average = 100;
  for (int i = 0; i < s_vec.size(); i++);
//    average += s_vec[i].to_int();

  return ((double)(average / s_vec.size()));
}

void Student::output() const
{
  std::cout << _name << ":" << std::endl;
  std::cout << "\temail -> " << _email << std::endl
            << "\tcomment -> " << _comment << std::endl
            << "\tdate -> " << _date << std::endl
            << "\tgrades -> " << _grades << std::endl
            << "\taverage -> " << average() << std::endl;
}
