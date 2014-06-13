#ifndef __STUDENT__
#define __STUDENT__

#include "attendee.h"
#include <iostream>
#include <string>
#include <vector>

class Student : public Attendee
{
private:
  std::string _name;
  std::string _email;
  std::string _comment;
  std::string _date;
  std::vector<int> _grades;
  float _average;
  bool _update_avg;

  void recalc_average();
  void calc_average(const std::string&);

public:
  Student(const std::string& name, const std::string& email,
          const std::string& comment, const std::string& date, 
          const std::string& grades);
  Student(const std::string& name, const std::string& email,
          const std::string& comment, const std::string& date, 
          const std::vector<int>& grades);
  const std::string& name() const;
  const std::string& email() const;
  const std::string& comment() const;
  const std::string& date() const;
  const std::vector<int>& grades() const;
  void new_grades(const std::string& s);
  void new_grades(const std::vector<int>&);
  const float& average();
  void output();

};

#endif /* __STUDENT__ */
