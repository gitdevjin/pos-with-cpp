#include "PosIO.h"

namespace sdds {


	std::ostream& operator<<(std::ostream& ostr, const PosIO& src)
	{
		return src.write(ostr);
	}

	std::ofstream& operator<<(std::ofstream& ostr, const PosIO& src)
	{
		return src.save(ostr);
	}

	std::istream& operator>>(std::istream& istr, PosIO& des)
	{
		return des.read(istr);
	}

	std::ifstream& operator>>(std::ifstream& istr, PosIO& des)
	{
		return des.load(istr);
	}


	PosIO::~PosIO()
	{
		;
	}

}

