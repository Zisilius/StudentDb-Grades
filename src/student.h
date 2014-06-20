#ifndef __STUDENT__
#define __STUDENT__

#include "attendee.h"
#include <iostream>
#include <string>
#include <vector>

class Student : public Attendee
{
  public:
	Student();
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
	const float& average() const;
	void set_grades(const std::string& s);
	void set_grades(const std::vector<int>&);
	void output() const;
  private:
	void recalc_average();
	void calc_average(const std::string&);

	std::string name_;
	std::string email_;
	std::string comment_;
	std::string date_;
	std::vector<int> grades_;
	float average_;
};

#endif /* __STUDENT__ */
