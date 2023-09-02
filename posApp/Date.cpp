#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Date.h"
#include "POS.h"
#include "Error.h"
#include "Utils.h"

namespace sdds {

	Date::Date()
	{
		m_dateOnly = false;
		getSystemDate(m_year, m_month, m_day, m_hour, m_minute, m_dateOnly);
		validate();
	}

	Date::Date(int year, int month, int day)
	{
		m_year = year;
		m_month = month;
		m_day = day;
		m_hour = 0;
		m_minute = 0;
		m_dateOnly = true;
		validate();
	}

	Date::Date(int year, int month, int day, int hour, int min)
	{
		m_year = year;
		m_month = month;
		m_day = day;
		m_hour = hour;
		m_minute = min;
		m_dateOnly = false;
		validate();
	}
	Date::Date(const Date& src)
	{
		if (src.m_dateOnly) {
			m_year = src.m_year;
			m_month = src.m_month;
			m_day = src.m_day;
			m_dateOnly = true;
			m_error = src.m_error;
		}
		else {
			m_year = src.m_year;
			m_month = src.m_month;
			m_day = src.m_day;
			m_hour = src.m_hour;
			m_minute = src.m_minute;
			m_dateOnly = false;
			m_error = src.m_error;
		}
	}

	bool Date::validate()
	{
		bool ok = false;
		if (m_dateOnly == false) {
			if (m_year <= MAX_YEAR && m_year >= MIN_YEAR) {
				if (m_month <= 12 && m_month >= 1) {
					if (m_day <= daysOfMonth(m_year, m_month) && m_day >= 1) {
						if (m_hour <= 23 && m_hour >= 0) {
							if (m_minute <= 59 && m_minute >= 0) { ok = true; }
							else m_error="Invlid Minute";
						}else m_error="Invalid Hour";
					}else m_error="Invalid Day";
				}else m_error="Invalid Month";
			}else m_error="Invalid Year";
		}
		else {
			if (m_year <= MAX_YEAR && m_year >= MIN_YEAR) {
				if (m_month <= 12 && m_month >= 1) {
					if (m_day <= daysOfMonth(m_year, m_month) && m_day >= 1) { ok = true; }
					else m_error="Invalid Day";
				}else m_error="Invalid Month";
			}else m_error="Invalid Year";
		}

		return ok;
	}

	Date& Date::dateOnly(bool flag)
	{
		m_dateOnly = flag;
		if (flag) m_hour = m_minute = 0;
		return *this;
	}
	Date::operator bool() const
	{
		return bool(m_error) == false;
	}

	const Error& Date::error() const
	{
		return m_error;
	}

	bool Date::operator==(Date& right)
	{
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) == uniqueDateValue(right.m_year, right.m_month,
			right.m_day, right.m_hour, right.m_minute);
	}

	bool Date::operator!=(Date& right)
	{
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) != uniqueDateValue(right.m_year, right.m_month,
			right.m_day, right.m_hour, right.m_minute);
	}

	bool Date::operator<(Date& right)
	{
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) < uniqueDateValue(right.m_year, right.m_month,
			right.m_day, right.m_hour, right.m_minute);
	}

	bool Date::operator>(Date& right)
	{
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) > uniqueDateValue(right.m_year, right.m_month,
			right.m_day, right.m_hour, right.m_minute);
	}

	bool Date::operator<=(Date& right)
	{
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) <= uniqueDateValue(right.m_year, right.m_month,
			right.m_day, right.m_hour, right.m_minute);
	}

	bool Date::operator>=(Date& right)
	{
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) >= uniqueDateValue(right.m_year, right.m_month,
			right.m_day, right.m_hour, right.m_minute);
	}

	std::ostream& Date::display(std::ostream& ostr) const
	{
		if (bool(*this))
		{
			if (m_dateOnly) 
			{
				ostr << m_year << "/";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_month << "/";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_day;
			}
			else 
			{
				ostr << m_year << "/";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_month << "/";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_day << ", ";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_hour << ":";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_minute;
			}
		}
		else 
		{ 
			if (m_dateOnly) {
				m_error.display(ostr);
				ostr << "(";
				ostr << m_year << "/";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_month << "/";
				ostr.fill('0');
				ostr.width(2);
				ostr << m_day << ")";
			}
			else {
			m_error.display(ostr);
			ostr << "(";
			ostr << m_year << "/";
			ostr.fill('0');
			ostr.width(2);
			ostr << m_month << "/";
			ostr.fill('0');
			ostr.width(2);
			ostr << m_day << ", ";
			ostr.fill('0');
			ostr.width(2);
			ostr << m_hour << ":";
			ostr.fill('0');
			ostr.width(2);
			ostr << m_minute << ")";
			}
		}

		return ostr;
	}

	void Date::clear()
	{
		m_year = m_month = m_day = m_hour = m_minute = 0;
		m_error.clear();
	}

	std::istream& Date::read(std::istream& istr)
	{
		clear();
		if (m_dateOnly) {
			istr >> m_year;
			if (!istr.fail()) {
				istr.ignore();
				istr.clear();
				istr >> m_month;
				if (!istr.fail()) {
					istr.ignore();
					istr.clear();
					istr >> m_day;
					if (!istr.fail()) { validate(); }
					else m_error = "Cannot read day entry";
				}
				else m_error = "Cannot read month entry";
			}
			else m_error = "Cannot read year entry";
		}
		else
		{
			istr >> m_year;
			if (!istr.fail()) {
				istr.ignore();
				istr.clear();
				istr >> m_month;
				if (!istr.fail()) {
					istr.ignore();
					istr.clear();
					istr >> m_day;
					if (!istr.fail()) { 
						istr.ignore(); 
						istr.clear();
						istr >> m_hour;
						if (!istr.fail()) {
							istr.ignore();
							istr.clear();
							istr >> m_minute;
							if(!istr.fail()) { validate(); }
							else m_error = "Cannot read minute entry";
						}
						else m_error = "Cannot read hour entry";
					}
					else m_error = "Cannot read day entry";
				}
				else m_error = "Cannot read month entry";
			}
			else m_error = "Cannot read year entry";
		}
		istr.clear();
		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& right)
	{
		return right.display(ostr);
	}

	std::istream& operator>>(std::istream& istr, Date& right)
	{
		return right.read(istr);
	}

}