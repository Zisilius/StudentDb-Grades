#ifndef __ATTENDEE__
#define __ATTENDEE__

#include <iostream>
#include <string>

class Attendee
{
public:
  virtual ~Attendee() = default;
  virtual const std::string& name() const = 0;
  virtual const std::string& email() const = 0;
  virtual const std::string& comment() const = 0;

};

#endif /* __ATTENDEE__ */
