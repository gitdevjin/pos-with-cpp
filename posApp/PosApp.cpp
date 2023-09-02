#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Item.h"
#include "PosApp.h"
#include "Perishable.h"
#include "NonPerishable.h"

namespace sdds {

	void PosApp::addItem()
	{
		std::cout.width(77);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> Adding Item to the store" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

		if (m_nptr < MAX_NO_ITEMS) {
			Item* temp = nullptr;
			char ch;
			std::cout << "Is the Item perishable? (Y)es/(N)o: ";
			std::cin >> ch;
			if (ch == 'y' || ch == 'Y') temp = new Perishable;
			else if (ch == 'n' || ch == 'N') temp = new NonPerishable;
			else return;

			bool ok = true;
			while (ok) {
				std::cin >> *temp;
				if (bool(*temp)) {
					m_iptr[m_nptr++] = temp;
					ok = false;
				}
				else {
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cout << *temp << ", try again...\n";
				}
			}
			std::cout.width(75);
			std::cout.fill('.');
			std::cout.setf(std::ios::left);
			std::cout << ">>>> DONE!" << std::endl;
			std::cout.fill(' ');
			std::cout.unsetf(std::ios::left);
		}
		else std::cout << "Inventory Full!" << std::endl;

	}

	void PosApp::removeItem()
	{
		std::cout.width(77);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> Remove Item" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

		int row = selectItem();
		std::cout << "Removing...." << std::endl;
		m_iptr[row - 1]->displayType(POS_FORM);
		std::cout << *m_iptr[row - 1];

		delete m_iptr[row - 1];
		for (int i = row; i < m_nptr; i++) {
			m_iptr[i - 1] = m_iptr[i];
		}
		m_iptr[m_nptr - 1] = nullptr;
		--m_nptr;

		std::cout.width(75);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> DONE!" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

	}

	void PosApp::stockItem()
	{
		std::cout.width(77);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> Select an item to stock" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

		int row = selectItem();
		std::cout << "Selected Item:\n";
		m_iptr[row - 1]->displayType(POS_FORM);
		std::cout << *m_iptr[row - 1];
		m_iptr[row - 1]->displayType(POS_LIST);
		std::cout << "Enter quantity to add: ";

		bool ok = true;
		int input;
		while (ok) {
			std::cin >> input;
			if (std::cin.fail()) {
				std::cout << "Invalid Integer, try again: ";
				std::cin.clear();
			}
			else {
				if (input < 1 || input > MAX_STOCK_NUMBER - m_iptr[row - 1]->quantity()) {
					std::cout << "[1<=value<=" << MAX_STOCK_NUMBER - m_iptr[row - 1]->quantity() << "], retry: Enter quantity to add: ";
					std::cin.clear();
				}
				else {
					*m_iptr[row - 1] += input;
					ok = false;
					std::cin.clear();
				}
			}
			std::cin.ignore(100, '\n');
		}

		std::cout.width(75);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> DONE!" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

	}

	void PosApp::listItems()
	{
		std::cout.width(77);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> Listing Items" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

		Item* temp;
		for (int i = 0; i < m_nptr - 1; i++) {
			for (int j = 0; j < m_nptr - 1; j++) {
				if (*m_iptr[j] > *m_iptr[j + 1]) {
					temp = m_iptr[j];
					m_iptr[j] = m_iptr[j + 1];
					m_iptr[j + 1] = temp;
				}
			}
		}

		std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << std::endl;
		std::cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << std::endl;
		double sum = .0;
		for (int i = 0; i < m_nptr; i++) {
			std::cout.width(4);
			std::cout.fill(' ');
			std::cout << i + 1 << " | ";
			m_iptr[i]->write(std::cout) << std::endl;
			sum += (m_iptr[i]->cost() * m_iptr[i]->quantity());
		}
		std::cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << std::endl;
		std::cout << "                               Total Asset: $  |";
		std::cout.width(14);
		std::cout.fill(' ');
		std::cout.setf(std::ios::fixed);
		std::cout.precision(2);
		std::cout << sum << "|\n" << "-----------------------------------------------^--------------^\n" << std::endl;
	}

	void PosApp::POS()
	{
		std::cout.width(77);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> Starting Point of Sale" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

		Item* item;
		char input[20];
		bool ok = true;
		std::cin.ignore(2000, '\n');
		while (ok) {
			std::cout << "Enter SKU or <ENTER> only to end sale...\n> ";
			std::cin.getline(input, 7, '\n');
			if (!std::cin.fail() && strlen(input) <= MAX_SKU_LEN && strlen(input) != 0) {
				if (search(input) != nullptr) {
					item = search(input);
					*item -= 1;
					item->displayType(POS_FORM);
					std::cout << *item << std::endl;
					item->displayType(POS_LIST);
					if (bool(*item)) {
						if (m_bill.add(item)) {
							std::cout << ">>>>> Added to bill" << std::endl;
							std::cout << ">>>>> Total: " << m_bill.total() << std::endl;
						}
					}
					else item->clear();
				}
				else std::cout << "!!!!! Item Not Found !!!!!" << std::endl;
			}
			else if	(!strcmp(input, "")) ok = false;
			else if (strlen(input) > MAX_SKU_LEN) {
				std::cout << "SKU too long\n";
				std::cout.clear();
			}
		}
		m_bill.print(std::cout);
	}
	

	void PosApp::saveRecs()
	{
		std::cout << ">>>> Saving Data............................................................." << std::endl;
		//std::cout << "Saving data in " << m_name << std::endl;
		std::ofstream outfile(m_name);
		for (int i = 0; i < m_nptr; i++) outfile << *m_iptr[i] << std::endl;
	}

	void PosApp::loadRecs()
	{
		std::cout << ">>>> Loading Items..........................................................." << std::endl;
		std::ifstream infile(m_name);
		if (!infile.is_open()) {
			std::ofstream outfile(m_name);
			outfile.close();
		}

		for (int i = 0; i < MAX_NO_ITEMS; i++) m_iptr[i] = nullptr;
		while (infile.good()) {
			char ch{};
			infile.get(ch);
			infile.ignore();
			if (ch == 'P') {
				m_iptr[m_nptr] = new Perishable;
				infile >> *m_iptr[m_nptr++];
			}
			else if (ch == 'N') {
				m_iptr[m_nptr] = new NonPerishable;
				infile >> *m_iptr[m_nptr++];
			}
			infile.ignore(100, '\n');
		}
	}

	int PosApp::selectItem()
	{
		std::cout.width(77);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> Item Selection by row number" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

		std::cout << "Press <ENTER> to start....";
		std::cin.ignore(100, '\n');
		std::cin.ignore(100, '\n');


		std::cout.width(77);
		std::cout.fill('.');
		std::cout.setf(std::ios::left);
		std::cout << ">>>> Listing Items" << std::endl;
		std::cout.fill(' ');
		std::cout.unsetf(std::ios::left);

		Item* temp;
		for (int i = 0; i < m_nptr - 1; i++) {
			for (int j = 0; j < m_nptr - 1; j++) {
				if (*m_iptr[j] > *m_iptr[j + 1]) {
					temp = m_iptr[j];
					m_iptr[j] = m_iptr[j + 1];
					m_iptr[j + 1] = temp;
				}
			}
		}

		std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << std::endl;
		std::cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << std::endl;
		double sum = .0;
		for (int i = 0; i < m_nptr; i++) {
			std::cout.width(4);
			std::cout.fill(' ');
			std::cout << i + 1 << " | ";
			m_iptr[i]->write(std::cout) << std::endl;
			sum += (m_iptr[i]->cost() * m_iptr[i]->quantity());
		}
		std::cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << std::endl;

		bool ok = true;
		std::cout << "Enter the row number: ";
		int input;
		while (ok) {
			std::cin >> input;
			if (std::cin.fail()) {
				std::cout << "Invalid Integer, try again: ";
				std::cin.clear();
			}
			else {
				if (input < 1 || input > m_nptr) {
					std::cout << "[1<=value<=" << m_nptr << "], retry: Enter the row number: ";
					std::cin.clear();
				}
				else {
					ok = false;
					std::cin.clear();
				}
			}
			std::cin.ignore(100, '\n');
		}
		return input;
	}

	Item* PosApp::search(const char* sku)
	{
		Item* address = nullptr;
		for (int i = 0; i < m_nptr; i++) {
			if (*m_iptr[i] == sku) address = m_iptr[i];
		}
		return address;
	}

	//------------------------constructor---------------------------

	PosApp::PosApp(const char* fileName)
	{
		int slen;
		if (fileName != nullptr) {
			slen = strlen(fileName);
			if (slen > 128) strcpy(m_name, "");
			else strcpy(m_name, fileName);
		}
		
	}

	//------------------------public methods--------------------------

	PosApp::~PosApp()
	{
		for (int i = 0; i < MAX_NO_ITEMS; i++)
			delete m_iptr[i];
	}

	void PosApp::run()
	{
		loadRecs();
		bool main = true;
		int input;
		while (main)
		{
			input = menu();
			switch (input)
			{
			case 1:
				listItems();
				break;
			case 2:
				addItem();
				break;
			case 3:
				removeItem();
				break;
			case 4:
				stockItem();
				break;
			case 5:
				POS();
				break;
			case 0:
				saveRecs();
				std::cout << "Goodbye!" << std::endl;
				main = false;
				break;
			}
		}
	}

	
	int PosApp::menu()
	{
		int input = -1;
		bool iter = true;
		std::cout << "The Sene-Store\n";
		std::cout << "1- List items\n";
		std::cout << "2- Add item\n";
		std::cout << "3- Remove item\n";
		std::cout << "4- Stock item\n";
		std::cout << "5- POS\n";
		std::cout << "0- exit program" << std::endl;
		std::cout << "> ";

		while (iter)
		{
			std::cin >> input;
			if (!std::cin)
			{
				std::cout << "Invalid Integer, try again: ";
				std::cin.clear();
				std::cin.ignore(2000, '\n');
			}
			else
			{
				if (input > 5 || input < 0) {
					std::cout << "[0<=value<=5], retry: > ";
				}
				else {
					iter = false;
				}
			}
		}
		return input;
	}

}//sdds

