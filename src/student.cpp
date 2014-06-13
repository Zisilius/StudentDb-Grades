#include "student.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

Student::Student(const std::string& name, const std::string& email,            
                 const std::string& comment, const std::string& date, 
                 const std::string& grades)
                : _name(name), _email(email), _comment(comment), _date(date),
                _update_avg(true) 
{
  calc_average(grades);
}

Student::Student(const std::string& name, const std::string& email,            
                 const std::string& comment, const std::string& date, 
                 const std::vector<int>& grades)
                : _name(name), _email(email), _comment(comment), _date(date),
                _grades(grades), _update_avg(true) 
{
  recalc_average();
}

const std::string& Student::name() const { return _name; }
const std::string& Student::email() const { return _email; }
const std::string& Student::comment() const { return _comment; }
const std::string& Student::date() const { return _date; }
const std::vector<int>& Student::grades() const { return _grades; }

void Student::recalc_average() 
{
  float temp;
  for (int i = 0; i < _grades.size(); i++)
    temp += _grades[i];
  _average = (float) temp / _grades.size();
}

void Student::calc_average(const std::string& s_temp) 
{
  std::vector<std::string> s_vec;
  int start = 0, end = 0;

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
    _grades.emplace_back(i_temp);
    average += i_temp;
  }

  _average = average / s_vec.size();
  _update_avg = false;
}

void Student::output() 
{
  std::cout << _name << ":" 
            << "\n\temail -> " << _email
            << "\n\tcomment -> " << _comment 
            << "\n\tdate -> " << _date 
            << "\n\tgrades -> ";   
  for (auto& e : _grades)
    std::cout << e << ", ";
  std::cout << "\n\taverage -> " << average() << std::endl;
}

void Student::new_grades(const std::string& s)
{
  calc_average(s);
  _update_avg = true;
}

void Student::new_grades(const std::vector<int>& i_vec)
{
  _grades = i_vec;
  _update_avg = true;
}

const float& Student::average()
{
  if (_update_avg)
    recalc_average();
  return _average;
}
