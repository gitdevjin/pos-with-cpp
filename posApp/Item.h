#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "PosIO.h"
#include "POS.h"
#include "Error.h"

namespace sdds {
	class Item : public PosIO
	{
	private:
		char m_sku[MAX_SKU_LEN + 1];
		char* m_name = nullptr;
		double m_price = 0.0;
		bool m_taxed;
		int m_qty;
		int m_displayType;
	protected:
		Error m_error;
	public:
		virtual char itemType() const = 0;;
		Item();
		Item(const Item& src);
		Item& operator=(const Item& src);
		bool operator==(const Item& right);
		bool operator==(const char* sku);
		bool operator>(const Item& right);
		int operator+=(const int right);
		int operator-=(const int right);

		explicit operator bool() const;
		const double cost() const;
		int quantity() const;
		
		int getDisplayType() const;
		Item& displayType(int displayType);
		Item& clear();

		virtual std::ostream& write(std::ostream& ostr) const;
		virtual std::istream& read(std::istream& istr);
		virtual std::ofstream& save(std::ofstream& ostr) const;
		virtual std::ifstream& load(std::ifstream& istr);
		std::ostream& bprint(std::ostream& ostr) const;
		bool validate(char m_sku[], char* name, double m_price, bool m_taxed, int m_qty);
		virtual ~Item();
	};

	double operator+=(double& left, const Item& right);
	

}

#endif