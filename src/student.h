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

public:
  Student(const std::string& name, const std::string& email,
          const std::string& comment, const std::string& date, 
          const std::string& grades);
  const std::string& name() const;
  const std::string& email() const;
  const std::string& comment() const;
  const std::string& date() const;
  const std::string& grades() const;
  const int average() const;
  void output() const;

};

#endif /* __STUDENT__ */
