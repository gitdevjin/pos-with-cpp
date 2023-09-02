#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#include <iostream>

namespace sdds {

	class PosIO {
	private:
	protected:
	public:
		virtual std::ostream& write(std::ostream& ostr) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual std::ofstream& save(std::ofstream& ostr) const = 0;
		virtual std::ifstream& load(std::ifstream& istr) = 0;
		virtual ~PosIO();
	};
	
	std::ostream& operator<<(std::ostream& ostr, const PosIO& src);
	std::ofstream& operator<<(std::ofstream& ostr, const PosIO& src);

	std::istream& operator>>(std::istream& istr, PosIO& des);
	std::ifstream& operator>>(std::ifstream& istr, PosIO& des);

}



#endif