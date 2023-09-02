#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Error.h"

namespace sdds {

	class Date {
	private:
		int m_year;
		int m_month;
		int m_day;
		int m_hour;
		int m_minute;
		bool m_dateOnly;
		Error m_error;
	public:
		Date();
		Date(int year, int month, int day);
		Date(int year, int month, int day, int hour, int min = 0);
		Date(const Date& src);
		Date& dateOnly(bool flag);
		explicit operator bool() const; // no error -> true;
		const Error& error() const;
		bool operator==(Date& right);
		bool operator!=(Date& right);
		bool operator<(Date& right);
		bool operator>(Date& right);
		bool operator<=(Date& right);
		bool operator>=(Date& right);
		void clear();
		std::istream& read(std::istream& istr);
		std::ostream& display(std::ostream& ostr) const;
		bool validate();
	};

	std::ostream& operator<<(std::ostream& ostr, const Date& right);
	std::istream& operator>>(std::istream& istr, Date& right);
}

#endif