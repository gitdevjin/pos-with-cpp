#include "NonPerishable.h"


namespace sdds {

	char NonPerishable::itemType() const
	{
		return 'N';
	}

	std::ostream& NonPerishable::write(std::ostream& ostr) const
	{
		Item::write(ostr);
		if (Item::operator bool()) {
			if ((getDisplayType() == 1)) {
				ostr << "     N / A   |";
			}
			else if ((getDisplayType() == 2)) {
				ostr << "=============^" << std::endl;
			}
		}
		return ostr;
	}
}