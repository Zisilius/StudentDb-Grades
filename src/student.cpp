#include "student.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

Student::Student() : name_(""), email_(""), comment_(""), date_(""), grades_()
{ }

Student::Student(const std::string& name, const std::string& email,            
                 const std::string& comment, const std::string& date, 
                 const std::string& grades)
                 : name_(name), email_(email), comment_(comment), date_(date)
{
	calc_average(grades);
}

Student::Student(const std::string& name, const std::string& email,            
                 const std::string& comment, const std::string& date, 
                 const std::vector<int>& grades)
                 : name_(name), email_(email), comment_(comment), date_(date),
                 grades_(grades) 
{
	recalc_average();
}

const std::string& Student::name() const { return name_; }
const std::string& Student::email() const { return email_; }
const std::string& Student::comment() const { return comment_; }
const std::string& Student::date() const { return date_; }
const std::vector<int>& Student::grades() const { return grades_; }
const float& Student::average() const { return average_; }

void Student::recalc_average() 
{
	float tmp;
	for (int i = 0; i < grades_.size(); i++)
		tmp += grades_[i];
	average_ = (float) tmp / grades_.size();
}

void Student::calc_average(const std::string& s) 
{
	std::vector<std::string> v;
	int start = 0, end = 0;

	while ((end = s.find(',', start)) != std::string::npos) {
		v.emplace_back(s.substr(start, end - start));
		start = end + 1;
	}
	v.emplace_back(s.substr(start, s.size() - start));

	float average = 0;
	int tmp;

	for (int i = 0; i < v.size(); i++) {
		std::stringstream convert(v[i]);
		if (!(convert >> tmp)) {
			std::cerr << "Couldn't convert string to int" << std::endl;
			tmp = 0;
		}
		grades_.emplace_back(tmp);
		average += tmp;
	}

	average_ = average / v.size();
}

void Student::output() const
{
	std::cout << name_ << ":" 
	          << "\n\temail -> " << email_
	          << "\n\tcomment -> " << comment_ 
	          << "\n\tdate -> " << date_ 
	          << "\n\tgrades -> ";   
	for (auto& e : grades_)
		std::cout << e << ", ";
	std::cout << "\n\taverage -> " << average() << std::endl;
}

void Student::set_grades(const std::string& s)
{
	calc_average(s);
}

void Student::set_grades(const std::vector<int>& v)
{
	grades_ = v;
	recalc_average();
}
