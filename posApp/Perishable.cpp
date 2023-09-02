#include <fstream>
#include "Perishable.h"
namespace sdds {

	char Perishable::itemType() const
	{
		return 'P';
	}

	std::ostream& Perishable::write(std::ostream& ostr) const
	{
		Item::write(ostr);
		if (Item::operator bool()) {
			if (getDisplayType() == 1) {
				ostr << "  ";
				m_expiryDate.display(ostr) << " |";
			}
			else if (getDisplayType() == 2) {
				ostr << "Expiry date: ";
				m_expiryDate.display(ostr) << std::endl;
				ostr << "=============^" << std::endl;
			}
		}

		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr)
	{
		Item::read(istr);
		if (istr && Item::operator bool()) {
			Date temp;
			temp.dateOnly(true);
			std::cout << "Expiry date (YYYY/MM/DD)\n" << "> ";
			temp.read(istr);
			if (bool(temp)) m_expiryDate = temp;
			else m_error = temp.error();
		}

		return istr;
	}

	std::ofstream& Perishable::save(std::ofstream& ostr) const
	{
		Item::save(ostr);
		if (Item::operator bool()) {
			ostr << "," << m_expiryDate;
		}
		return ostr;
	}

	std::ifstream& Perishable::load(std::ifstream& istr)
	{
		Item::load(istr);
		if (Item::operator bool() && istr) {
			Date temp;
			temp.dateOnly(true);
			istr.ignore();
			temp.read(istr);
			if (bool(temp)) m_expiryDate = temp;
			else m_error = temp.error();
		}
		return istr;
	}

}