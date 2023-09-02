#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <iostream>

namespace sdds {

	class Error {
	private:
		char* m_errorMessage = nullptr;
	public:
		Error();
		Error(const char* errMessage);
		Error(const Error& src);
		Error& operator=(const Error& src);
		void operator=(const char* errMessage);
		explicit operator bool() const;
		Error& clear();
		std::ostream& display(std::ostream& ostr) const;
		virtual ~Error();
	};

	std::ostream& operator<<(std::ostream& ostr, const Error& right);
	
}
#endif