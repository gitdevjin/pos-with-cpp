#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Error.h"

namespace sdds {


	Error::Error()
	{
		m_errorMessage = nullptr;
	}

	Error::Error(const char* errMessage)
	{
		if (errMessage != nullptr) {
			m_errorMessage = new char[strlen(errMessage) + 1];
			strcpy(m_errorMessage, errMessage);
		}
		else m_errorMessage = nullptr;
	}

	Error::Error(const Error& src)
	{
		*this = src;
	}

	// Seting error message 
	void Error::operator=(const char* errMessage) {
		if (errMessage != nullptr) {
			delete[] m_errorMessage;
			m_errorMessage = new char[strlen(errMessage) + 1];
			strcpy(m_errorMessage, errMessage);
		}
		else m_errorMessage = nullptr;
	}


	Error& Error::operator=(const Error& src)
	{
		if (src.m_errorMessage != nullptr) {
			delete[] m_errorMessage;
			m_errorMessage = new char[strlen(src.m_errorMessage) + 1];
			strcpy(m_errorMessage, src.m_errorMessage);
		}
		else {
			delete[] m_errorMessage;
			m_errorMessage = nullptr;
		}
		return *this;
	}

	Error::operator bool() const
	{
		return m_errorMessage != nullptr;
	}

	Error& Error::clear()
	{
		delete[] m_errorMessage;
		m_errorMessage = nullptr;

		return *this;
	}

	std::ostream& Error::display(std::ostream& ostr) const
	{
		if (m_errorMessage != nullptr)
			ostr << m_errorMessage;
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Error& right)
	{
		return right.display(ostr);
	}

	Error::~Error() {
		delete[] m_errorMessage;
	}
}
