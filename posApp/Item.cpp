#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Item.h"
namespace sdds {

	Item::Item()
	{
		strcpy(m_sku, "");
		m_name = nullptr;
		m_price = 0.0;
		m_qty = 0;
		m_taxed = false;
		m_displayType = POS_LIST;
		m_error.clear();
	}

	Item::Item(const Item& src)
	{
		if (src.m_sku[0] != '\0') {
			strcpy(m_sku, src.m_sku);
			if (src.m_name != nullptr) {
				delete[] m_name;
				m_name = new char[strlen(src.m_name) + 1];
				strcpy(m_name, src.m_name);
			}
			m_price = src.m_price;
			m_qty = src.m_qty;
			m_taxed = src.m_taxed;
			m_displayType = src.m_displayType;
			m_error = src.m_error;
		}
	}

	Item& Item::operator=(const Item& src)
	{
		if (src.m_sku[0] != '\0') {
			strcpy(m_sku, src.m_sku);
			if (src.m_name != nullptr) {
				delete[] m_name;
				m_name = new char[strlen(src.m_name) + 1];
				strcpy(m_name, src.m_name);
			}
			m_price = src.m_price;
			m_qty = src.m_qty;
			m_taxed = src.m_taxed;
			m_displayType = src.m_displayType;
			m_error = src.m_error;
		}
		return *this;
	}

	bool Item::operator==(const Item& right)
	{
		return !strcmp(this->m_sku, right.m_sku);
	}

	bool Item::operator==(const char* sku)
	{
		return !strcmp(m_sku, sku);
	}

	bool Item::operator>(const Item& right)
	{
		return (strcmp(this->m_name, right.m_name) > 0 ? true : false);
	}

	int Item::operator+=(const int right)
	{
		if (m_qty + right <= MAX_STOCK_NUMBER) m_qty += right;
		else {
			this->m_qty = MAX_STOCK_NUMBER;
			m_error = ERROR_POS_QTY;
		}

		return this->m_qty;
	}

	int Item::operator-=(const int right)
	{
		if (m_qty - right >= 0) m_qty -= right;
		else {
			m_qty = 0;
			m_error = ERROR_POS_STOCK;
		}
		return m_qty;
	}

	Item::operator bool() const
	{
		return bool(m_error) == false;
	}

	int Item::getDisplayType() const
	{
		return m_displayType;
	}

	Item& Item::displayType(int displayType)
	{
		m_displayType = displayType;
		return *this;
	}

	const double Item::cost() const
	{
		double result = 0.0;
		if (m_taxed) result += m_price * 1.13;
		else result = m_price;

		return result;
	}

	int Item::quantity() const
	{
		return m_qty;
	}

	Item& Item::clear()
	{
		m_error.clear();
		return *this;
	}

	std::ostream& Item::write(std::ostream& ostr) const
	{
		if (m_displayType == POS_LIST && bool(*this)) {
			ostr.width(7);
			std::cout.setf(std::ios::left);
			ostr.fill(' ');
			ostr << m_sku << "|";

			char name[40];
			if (m_name != nullptr) {
				if ((strlen(m_name) > 20)) {
					strncpy(name, m_name, 20);
					name[20] = '\0';
					ostr << name << "|";
				}
				else {
					ostr.width(20);
					ostr.fill(' ');
					ostr << m_name << "|";
				}
			}
			ostr.unsetf(std::ios::left);

			ostr.width(7);
			ostr.setf(std::ios::fixed);
			ostr.precision(2);
			ostr << m_price << "|";
			ostr.unsetf(std::ios::fixed);
			ostr << (m_taxed ? " X |" : "   |");

			ostr.width(4);
			ostr << m_qty << "|";

			ostr.width(9);
			ostr.setf(std::ios::fixed);
			ostr.precision(2);
			ostr << cost() * quantity() << "|";
			ostr.unsetf(std::ios::fixed);
		}
		else if (m_displayType == POS_FORM && bool(*this)) {
			ostr << "=============v" << std::endl;
			ostr.width(13);
			ostr.setf(std::ios::left);
			ostr.fill(' ');
			ostr << "Name:";
			ostr << m_name << std::endl;

			ostr.width(13);
			ostr << "Sku:";
			ostr << m_sku << std::endl;

			ostr.width(13);
			ostr << "Price:";
			ostr.setf(std::ios::fixed);
			ostr.precision(2);
			ostr << m_price << std::endl;

			ostr.width(13);
			ostr << "Price + tax:";
			if (m_taxed) ostr << cost();
			else ostr << "N/A";
			ostr << std::endl;

			ostr.width(13);
			ostr << "Stock Qty:" << m_qty << std::endl;
			ostr.unsetf(std::ios::left);

		}
		else if (bool(*this) == 0) m_error.display(ostr);

		return ostr;
	}

	std::istream& Item::read(std::istream& istr)
	{
		bool ok = true;
		std::cout << "Sku\n" << "> ";
		while (ok) {
			istr >> m_sku;
			if (!istr.fail() && (strlen(m_sku) <= MAX_SKU_LEN)) {
				m_error.clear();
				ok = false;
			}
			else {
				m_error = ERROR_POS_SKU;
				m_error.display(std::cout);
				std::cout << "\n> ";
				istr.clear();
			}
			istr.ignore(100, '\n');
		}

		ok = true;
		std::cout << "Name\n" << "> ";
		while (ok) {
			char name[100];
			istr.getline(name, 100, '\n');
			if (!istr.fail() && ((strlen(name) < MAX_NAME_LEN))) {
				delete[] m_name;
				m_name = new char[strlen(name) + 1];
				strcpy(m_name, name);
				ok = false;
				m_error.clear();
			}
			else {
				m_error = ERROR_POS_NAME;
				m_error.display(std::cout);
				std::cout << "\n> ";
				istr.clear();
			}
		}

		ok = true;
		std::cout << "Price\n" << "> ";
		while (ok) {
			istr >> m_price;
			if (!istr.fail() && m_price > 0) {
				m_error.clear();

				ok = false;
			}
			else {
				m_error = ERROR_POS_PRICE;
				m_error.display(std::cout);
				std::cout << "\n> ";
				istr.clear();
				istr.ignore(100, '\n');
			}
		}

		ok = true;
		std::cout << "Taxed?\n(Y)es/(N)o: ";
		while (ok) {
			char c = ' ';
			istr >> c;
			if (!istr.fail() && (c == 'y' || c == 'n')) {
				if (c == 'y') m_taxed = true;
				else m_taxed = false;
				m_error.clear();
				ok = false;
			}
			else {
				std::cout << "Only 'y' and 'n' are acceptable: ";
				istr.clear();
				istr.ignore(100, '\n');
			}
		}

		ok = true;
		std::cout << "Quantity\n> ";
		while (ok) {
			istr >> m_qty;
			if (!istr.fail() && m_qty > 0 && m_qty < MAX_STOCK_NUMBER) {
				m_error.clear();
				ok = false;
			}
			
			else {
				m_error = ERROR_POS_QTY;
				m_error.display(std::cout);
				std::cout << "\n> ";
				istr.clear();
				istr.ignore(100, '\n');
			}
		}

		return istr;
	}

	std::ofstream& Item::save(std::ofstream& ostr) const
	{
		if (bool(*this)) {
			ostr << itemType() << "," << m_sku << ",";
			ostr.setf(std::ios::fixed);
			ostr.precision(2);
			ostr << m_name << ",";
			ostr << m_price << ",";
			ostr << m_taxed << "," << m_qty;
			ostr.unsetf(std::ios::fixed);
		}
		else m_error.display(std::cerr);
		return ostr;
	}

	std::ifstream& Item::load(std::ifstream& istr)
	{
		clear();
		char sku[100];
		char name[100];
		double price = 0.0;
		int taxed = -1;
		int qty = 0;
		istr.getline(sku, 100, ',');
		istr.getline(name, 100, ',');
		istr >> price;
		istr.ignore();
		istr >> taxed;
		istr.ignore();
		istr >> qty;

		if (validate(sku, name, price, taxed, qty)) {
			strcpy(m_sku, sku);
			delete[] m_name;
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
			m_price = price;
			m_taxed = taxed;
			m_qty = qty;
		}

		return istr;
	}

	std::ostream& Item::bprint(std::ostream& ostr) const
	{
		ostr << "| ";
		ostr.width(20);
		std::cout.fill(' ');
		ostr.setf(std::ios::left);
		char name[30];
		if (strlen(m_name) > 20) {
			strncpy(name, m_name, 20);
			name[20] = '\0';
			ostr << name << "|";
		}
		else {
			ostr.width(20);
			ostr.setf(std::ios::left);
			ostr << m_name << "|";
		}

		ostr.width(10);
		ostr.setf(std::ios::fixed);
		ostr.setf(std::ios::right);
		ostr.precision(2);
		
		ostr << (m_taxed ? m_price * TAX : m_price);
		ostr << (m_taxed ? " |  T  |" : " |     |");
		ostr << std::endl;
		ostr.unsetf(std::ios::right);

		return ostr;
	}

	bool Item::validate(char m_sku[], char* m_name, double m_price, bool m_taxed, int m_qty)
	{
		bool ok = false;
		if (strlen(m_sku) <= MAX_SKU_LEN) {
			if (strlen(m_name) < MAX_NAME_LEN) {
				if (m_price > 0) {
					if (m_taxed == 1 || m_taxed == 0) {
						if (m_qty <= MAX_STOCK_NUMBER) { ok = true; }
						else m_error = ERROR_POS_QTY;
					}
					else m_error = ERROR_POS_TAX;
				}
				else m_error = ERROR_POS_PRICE;
			}
			else m_error = ERROR_POS_NAME;
		}
		else m_error = ERROR_POS_SKU;

		return ok;
	}

	Item::~Item()
	{
		delete[] m_name;
	}

	double operator+=(double& left, const Item& right)
	{
		return left + (right.cost() * right.quantity());
	}


}

