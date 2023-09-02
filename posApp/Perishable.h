#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"

namespace sdds {

	class Perishable : public Item {
	private:
		Date m_expiryDate;
	public:
		char itemType() const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ofstream& save(std::ofstream& ostr) const;
		std::ifstream& load(std::ifstream& istr);

	};

}

#endif