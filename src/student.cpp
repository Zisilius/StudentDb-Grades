#include "student.h"
#include <iostream>
#include <string>

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
