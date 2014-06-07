#include "student.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

Student::Student(const std::string& name, const std::string& email,            
                 const std::string& comment, const std::string& date, 
                 const std::string& grades)
                : _name(name), _email(email), _comment(comment), _date(date),
                _grades(grades), _upd_avg(true) 
{
  average();
}

const std::string& Student::name() const { return _name; }
const std::string& Student::email() const { return _email; }
const std::string& Student::comment() const { return _comment; }
const std::string& Student::date() const { return _date; }
const std::string& Student::grades() const { return _grades; }

void Student::calc_average() 
{
  std::vector<std::string> s_vec;
  int start = 0, end = 0;

  std::string s_temp = grades();
  while ((end = s_temp.find(',', start)) != std::string::npos) {
    s_vec.emplace_back(s_temp.substr(start, end - start));
    start = end + 1;
  }
  s_vec.emplace_back(s_temp.substr(start, s_temp.size() - start));

  float average = 0;
  int i_temp;
  for (int i = 0; i < s_vec.size(); i++) {
    std::stringstream convert(s_vec[i]);
    if (!(convert >> i_temp)) {
      std::cerr << "Couldn't convert string to int" << std::endl;
      i_temp = 0;
    }
    average += i_temp;
  }

  _average = average / s_vec.size();
  _upd_avg = false;
}

void Student::output() 
{
  std::cout << _name << ":" 
            << "\n\temail -> " << _email
            << "\n\tcomment -> " << _comment 
            << "\n\tdate -> " << _date 
            << "\n\tgrades -> " << _grades 
            << "\n\taverage -> " << average() << std::endl;
}

void Student::new_grades(std::string s)
{
  _grades = s;
  _upd_avg = true;
}

const float& Student::average()
{
  if (_upd_avg)
    calc_average();
  return _average;
}
