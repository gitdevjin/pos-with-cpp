#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include "Item.h"
#include "POS.h"
#include "Error.h"
#include "Bill.h"

namespace sdds {

	class PosApp {
	private:
		char m_name[128];
		Item* m_iptr[MAX_NO_ITEMS];
		int m_nptr = 0;
		Bill m_bill;

		void addItem();
		void removeItem();
		void stockItem();
		void listItems();
		void POS();
		void saveRecs();
		void loadRecs();
		int selectItem();
		Item* search(const char* sku);
	public:
		PosApp(const char* fileName);
		PosApp(const PosApp& source) = delete;
		PosApp& operator=(const PosApp& source) = delete;
		~PosApp();
		void run();
		int menu();

	};




}


#endif
