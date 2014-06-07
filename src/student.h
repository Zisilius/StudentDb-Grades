#ifndef __STUDENT__
#define __STUDENT__

#include "attendee.h"
#include <iostream>
#include <string>

class Student : public Attendee
{
private:
  std::string _name;
  std::string _email;
  std::string _comment;
  std::string _date;
  std::string _grades;
  float _average;
  bool _upd_avg;

  void calc_average();

public:
  Student(const std::string& name, const std::string& email,
          const std::string& comment, const std::string& date, 
          const std::string& grades);
  const std::string& name() const;
  const std::string& email() const;
  const std::string& comment() const;
  const std::string& date() const;
  const std::string& grades() const;
  void new_grades(std::string);
  const float& average();
  void output();

};

#endif /* __STUDENT__ */
