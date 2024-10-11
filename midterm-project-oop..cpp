#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits>

//coded by Kristoffer Noli Ludovice

using namespace std;

const int MAX_ITEMS = 100;
const string CATEGORIES[] = {"CLOTHING", "ELECTRONICS", "ENTERTAINMENT"};

class Item {
protected:
    string id;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item() : quantity(0), price(0.0) {}

    virtual void display() 
	{
        cout << setw(10) << id 
             << setw(20) << name 
             << setw(15) << quantity 
             << setw(10) << fixed << setprecision(2) << price;
    }

    void displayWithCategory() 
	{
        cout << setw(10) << id 
             << setw(20) << name 
             << setw(15) << quantity 
             << setw(10) << fixed << setprecision(2) << price 
             << setw(15) << category << endl;
    }
    
    void headerWithCategory()
    {
    	cout << "======================================================================" << endl;
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
        cout << "======================================================================" << endl;
	}
	
	void header()
	{
		cout << "=======================================================" << endl;
	    cout << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Quantity" << setw(10) << "Price" << endl;
	    cout << "=======================================================" << endl;
	}

    string getId() const { return id; }
    string getCategory() const { return category; }
    void setDetails(const string& id, const string& name, int quantity, double price, const string& category) 
	{
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
        this->category = category;
    }

    void updateQuantity(int newQuantity) 
	{
        quantity = newQuantity;
    }

    void updatePrice(double newPrice) 
	{
        price = newPrice;
    }

    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
};

class ClothingItem : public Item {
public:
	
    void display() override 
	{
        Item::display();
        cout << endl; 
    }
};

class ElectronicsItem : public Item {
public:

    void display() override 
	{
        Item::display();
        cout << endl;
    }
};

class EntertainmentItem : public Item {
public:

    void display() override {
        Item::display();
        cout << endl;
    }
};

class Inventory {
private:
    Item* items[MAX_ITEMS]; 
    int itemCount;

public:
    Inventory() : itemCount(0) {}

    ~Inventory() 
	{
        for (int i = 0; i < itemCount; ++i) {
            delete items[i];
        }
    }

    void addItem() 
	{
		bool looper = true;
	    string category;
	
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    while (looper) 
		{
	        cout << "Enter category (CLOTHING, ELECTRONICS, ENTERTAINMENT): ";
	        getline(cin, category);

	        if (category.find(' ') != string::npos || category.empty()) 
			{
	            cout << "Invalid category! Category cannot contain spaces or be empty." << endl;
	            continue;
	        }
	
	        for (auto& c : category) c = toupper(c);
	
	        bool categoryFound = false;
	        for (const auto& cat : CATEGORIES) 
			{
	            if (category == cat) 
				{
	                categoryFound = true;
	                break;
	            }
	        }
	
	        if (!categoryFound) 
			{
	            cout << "Category " << category << " does not exist!" << endl;
	            continue;
	        }
	        
			looper = false;
	    }
		
		looper = true;
	    string id, name;
	    int quantity;
	    double price;
	
	    while (looper) 
		{
	        cout << "Enter ID: ";
	        cin >> id;
	
	        bool idExists = false;
	        for (int i = 0; i < itemCount; ++i) 
			{
	            if (items[i]->getId() == id) 
				{
	                idExists = true;
	                break;
	            }
	        }
	
	        if (idExists) 
			{
	            cout << "ID " << id << " already exists! Please enter a unique ID." << endl;
	            continue;
	        }
	
	        looper = false;
	    }
	    
		looper = true;
	    cout << "Enter Name: ";
	    cin.ignore();
	    getline(cin, name);

	    cout << "Enter Quantity: ";
		while (looper) 
		{
		    cin >> quantity;

		    if (cin.fail() || cin.peek() != '\n' || quantity < 0) 
			{
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		        cout << "Invalid quantity! Enter again: ";
		    } 
			else 
			{
		        looper = false;
		    }
		}
		
		looper = true;
		cout << "Enter Price: ";
		while (looper) 
		{
		    cin >> price;

		    if (cin.fail() || cin.peek() != '\n' || price < 0) 
			{
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		        cout << "Invalid price! Enter again: ";
		    } 
			else 
			{
		        looper = false;
		    }
		}
	
	    Item* newItem = nullptr;
	
	    if (category == "CLOTHING") 
		{
	        newItem = new ClothingItem();
	    } 
		else if (category == "ELECTRONICS") 
		{
	        newItem = new ElectronicsItem();
	    } 
		else if (category == "ENTERTAINMENT") 
		{
	        newItem = new EntertainmentItem();
	    }
	
	    newItem->setDetails(id, name, quantity, price, category);
	    items[itemCount++] = newItem;
	    cout << "Item added successfully!" << endl;
	}


    void updateItem() 
	{
	    if (itemCount == 0) 
	    {
	        cout << "The Inventory is empty!" << endl;
	        return;
	    }
	
	    bool retry = true;
	
	    while (retry) 
	    {
	        string id;
	        bool looper = true;
	        bool itemFound = false;
	
	        cout << "Enter ID to update: ";
	        cin >> id;
	
	        for (int i = 0; i < itemCount; ++i) 
	        {
	            if (items[i]->getId() == id) 
	            {   
	                itemFound = true;
	
	                while (looper) 
	                {
	                    char choice;
	                    cout << "Update (q for quantity/p for price)? ";
	                    cin >> choice;
	
	                    choice = tolower(choice);
	
	                    if (cin.fail()) 
	                    {
	                        cin.clear();
	                        cin.ignore(10000, '\n');
	                        cout << "Invalid input! Please enter a valid option (q/p)." << endl;
	                        continue;
	                    }
	
	                    if (cin.peek() != '\n') 
	                    {
	                        cin.ignore(10000, '\n');
	                        cout << "Invalid input! Please enter only one character (q/p)." << endl;
	                        continue;
	                    }
	
	                    if (choice == 'q') 
	                    {
	                        bool valid = true;
	                        int newQuantity;
	                        cout << "Enter new quantity: ";
	
	                        while (valid) 
	                        {
	                            cin >> newQuantity;
	
	                            if (cin.fail() || cin.peek() != '\n' || newQuantity < 0) 
	                            {
	                                cin.clear();
	                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
	                                cout << "Invalid quantity! Enter again: ";
	                            } 
	                            else 
	                            {
	                                if (newQuantity == items[i]->getQuantity()) 
	                                {
	                                    cout << "The new quantity is the same as the current quantity (" << newQuantity << "). No changes made." << endl;
	                                } 
	                                else 
	                                {
	                                    items[i]->updateQuantity(newQuantity);
	                                    cout << "Quantity of Item " << items[i]->getId() << " is updated to " << newQuantity << endl;
	                                }
	                                valid = false;
	                            }
	                        }
	                    } 
	                    else if (choice == 'p') 
	                    {
	                        bool valid = true;
	                        double newPrice;
	                        cout << "Enter new price: ";
	
	                        while (valid) 
	                        {
	                            cin >> newPrice;
	
	                            if (cin.fail() || cin.peek() != '\n' || newPrice < 0) 
	                            {
	                                cin.clear();
	                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
	                                cout << "Invalid price! Enter again: ";
	                            } 
	                            else 
	                            {
	                                if (newPrice == items[i]->getPrice()) 
	                                {
	                                    cout << "The new price is the same as the current price (" << newPrice << "). No changes made." << endl;
	                                } 
	                                else 
	                                {
	                                    items[i]->updatePrice(newPrice);
	                                    cout << "Price of Item " << items[i]->getId() << " is updated to " << newPrice << endl;
	                                }
	                                valid = false;
	                            }
	                        }
	                    } 
	                    else 
	                    {
	                        cout << "Invalid choice!" << endl;
	                        continue;
	                    }
	                    looper = false;
	                }
	            }
	        }
	
	        if (!itemFound) 
	        {
	            char retryChoice;
	            bool retryLoop = true;
	            cout << "Item not found!" << endl;
	            while(retryLoop)
	            {
		            cout << "Would you like to try again? (Y/N): ";
		            cin >> retryChoice;
		            
		            if (cin.fail()) 
		            {
		                cin.clear();
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter a valid option (Y/N)." << endl;
		                continue;
		            }
		
		            if (cin.peek() != '\n') 
		            {
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter only one character (Y/N)." << endl;
		                continue;
		            }
		            retryLoop = false;
				}
				
	            retryChoice = tolower(retryChoice);
	            
	            if (retryChoice == 'n') 
	            {
	                cout << "Returning to main menu..." << endl;
	                retry = false;
	            } 
	        } 
	        else 
	        {
	            retry = false;
	        }
	    }
	}


    void removeItem() 
	{
	    if (itemCount == 0)
	    {
	        cout << "The Inventory is empty!" << endl;
	        return;
	    }
	    
	    bool retry = true;
	
	    while (retry) 
	    {
	        string id;
	        cout << "Enter ID to remove: ";
	        cin >> id;
	
	        bool itemFound = false;
	        
	        for (int i = 0; i < itemCount; ++i) 
	        {
	            if (items[i]->getId() == id) 
	            {
	                cout << "Item " << items[i]->getId() << " has been removed from the inventory." << endl;
	                delete items[i];
	                items[i] = items[itemCount - 1];
	                itemCount--;
	                itemFound = true;
	                break;
	            }
	        }
	
	        if (!itemFound) 
	        {
	            bool retryLoop = true;
	            char retryChoice;
	            cout << "Item not found!" << endl;
	            while(retryLoop)
	            {
		            cout << "Would you like to try again? (Y/N): ";
		            cin >> retryChoice;
		            
		            if (cin.fail()) 
		            {
		                cin.clear();
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter a valid option (Y/N)." << endl;
		                continue;
		            }
		
		            if (cin.peek() != '\n') 
		            {
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter only one character (Y/N)." << endl;
		                continue;
		            }
		            retryLoop = false;
				}
	
	            retryChoice = tolower(retryChoice);
	            
	            if (retryChoice == 'n') 
	            {
	                cout << "Returning to main menu..." << endl;
	                retry = false;
	            } 
	        } 
	        else 
	        {
	            retry = false;
	        }
	    }
	}


    void displayItemsByCategory() 
	{
	    if (itemCount == 0)
	    {
	        cout << "The Inventory is empty!" << endl;
	        return;
	    }
	    
	    bool retry = true;
	    
	    while (retry) 
	    {
	        string category;
	        bool looper = true;
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        while(looper)
	        {
		        cout << "Enter category (CLOTHING, ELECTRONICS, ENTERTAINMENT): ";
		        getline(cin, category);
		        
		        if (category.find(' ') != string::npos || category.empty()) 
				{
		            cout << "Invalid category! Category cannot contain spaces or be empty." << endl;
		            continue;
		        }
		        looper = false;
	    	}
	        for (auto& c : category) c = toupper(c);
	    
	        bool categoryFound = false;
	        
	        for (const auto& cat : CATEGORIES) 
	        {
	            if (category == cat) 
	            {
	                categoryFound = true;
	                break;
	            }
	        }
	    
	        if (!categoryFound) 
	        {
	            bool retryLoop = true;
	            char retryChoice;
	            cout << "Category " << category << " does not exist!" << endl;
	            while(retryLoop)
	            {
		            cout << "Would you like to try again? (Y/N): ";
		            cin >> retryChoice;
		            
		            if (cin.fail()) 
		            {
		                cin.clear();
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter a valid option (Y/N)." << endl;
		                continue;
		            }
		
		            if (cin.peek() != '\n') 
		            {
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter only one character (Y/N)." << endl;
		                continue;
		            }
		            retryLoop = false;
				}
	
	            retryChoice = tolower(retryChoice);
	            
	            if (retryChoice == 'n') 
	            {
	                cout << "Returning to main menu..." << endl;
	                retry = false;
	            } 
	            else if (retryChoice != 'y') 
	            {
	                cout << "Invalid input! Returning to main menu..." << endl;
	                retry = false;
	            }
	            continue;
	        }
	    
	        bool itemsFound = false;
	    
	        system("cls");
	        cout << "=======================================================" << endl;
	        cout << "              ITEMS IN CATEGORY " << category << endl;
	        items[0]->header();
	    
	        for (int i = 0; i < itemCount; ++i) 
	        {
	            if (items[i]->getCategory() == category) 
	            {
	                items[i]->display();
	                cout << endl;
	                itemsFound = true;
	            }
	        }
	    
	        if (!itemsFound) 
	        {
	            cout << "There are no items in the " << category << " category." << endl;
	        }
	
	        retry = false;
	    }
	}



    void displayAllItems() 
	{
		if (itemCount == 0)
	    {
	        cout << "The Inventory is empty!" << endl;
	        return;
	    }
		
        items[0]->headerWithCategory();
        for (int i = 0; i < itemCount; ++i) 
		{
            items[i]->displayWithCategory();
        }
    }

    void searchItem() 
	{
	    if (itemCount == 0)
	    {
	        cout << "The Inventory is empty!" << endl;
	        return;
	    }
	
	    bool retry = true;
	
	    while (retry) 
	    {
	        string id;
	        cout << "Enter ID to search: ";
	        cin >> id;
	
	        string lowerId = id;
	        for (auto &c : lowerId) 
	        {
	            c = tolower(c);
	        }
	
	        bool itemFound = false;
	        cout << endl << "Items found with ID similar to '" << id << "':" << endl;
	        items[0]->headerWithCategory();
	
	        for (int i = 0; i < itemCount; ++i) 
	        {
	            string storedId = items[i]->getId();
	            string lowerStoredId = storedId;
	            for (auto &c : lowerStoredId) 
	            {
	                c = tolower(c);
	            }
	
	            if (lowerStoredId == lowerId) 
	            {
	                items[i]->displayWithCategory();
	                itemFound = true;
	            }
	        }
	
	        if (!itemFound) 
	        {
	            bool retryLoop = true;
	            char retryChoice;
	            cout << "No items found!" << endl;
	            while(retryLoop)
	            {
		            cout << "Would you like to try again? (Y/N): ";
		            cin >> retryChoice;
		            
		            if (cin.fail()) 
		            {
		                cin.clear();
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter a valid option (Y/N)." << endl;
		                continue;
		            }
		
		            if (cin.peek() != '\n') 
		            {
		                cin.ignore(10000, '\n');
		                cout << "Invalid input! Please enter only one character (Y/N)." << endl;
		                continue;
		            }
		            retryLoop = false;
				}
	
	            retryChoice = tolower(retryChoice);
	
	            if (retryChoice == 'n') 
	            {
	                cout << "Returning to main menu..." << endl;
	                retry = false;
	            } 
	            else if (retryChoice != 'y') 
	            {
	                cout << "Invalid input! Returning to main menu..." << endl;
	                retry = false;
	            }
	        } 
	        else 
	        {
	            retry = false;
	        }
	    }
	}


    void sortItems() 
	{
		if (itemCount == 0)
	    {
	        cout << "The Inventory is empty!" << endl;
	        return;
	    }
	    
	    char criteria, order;
	    bool looper = true;
	
	    while(looper)
		{
	        cout << "Sort by (q for quantity / p for price)? ";
	        cin >> criteria;
	
	        criteria = tolower(criteria);
	        
	        if (cin.fail()) 
			{
	            cin.clear();
	            cin.ignore(10000, '\n');
	            cout << "Invalid input! Please enter 'q' for quantity or 'p' for price." << endl;
	            continue;
	        }
	
	        if (cin.peek() != '\n') 
			{
	            cin.ignore(10000, '\n');
	            cout << "Invalid input! Please enter 'q' for quantity or 'p' for price." << endl;
	            continue;
	        }
	
	        if (criteria != 'q' && criteria != 'p') 
			{
	            cout << "Invalid input! Please enter 'q' for quantity or 'p' for price." << endl;
	            continue;
	        }
	        
	        looper = false;
	    }
	
	    looper = true;
	
	    while(looper)
		{
	        cout << "Order (a for ascending / d for descending)? ";
	        cin >> order;
	
	        order = tolower(order);
	        
	        if (cin.fail()) 
			{
	            cin.clear();
	            cin.ignore(10000, '\n');
	            cout << "Invalid input! Please enter 'a' for ascending or 'd' for descending." << endl;
	            continue;
	        }
	
	        if (cin.peek() != '\n') 
			{
	            cin.ignore(10000, '\n'); 
	            cout << "Invalid input! Please enter 'a' for ascending or 'd' for descending." << endl;
	            continue;
	        }
	
	        if (order != 'a' && order != 'd') 
			{
	            cout << "Invalid input! Please enter 'a' for ascending or 'd' for descending." << endl;
	            continue;
	        }
	        
	        looper = false;
	    }
	
	    for (int i = 0; i < itemCount - 1; ++i) 
		{
	        for (int j = 0; j < itemCount - i - 1; ++j) 
			{
	            bool swapCondition = false;
	            if (criteria == 'q') 
				{ 
	                swapCondition = (order == 'a') ? (items[j]->getQuantity() > items[j + 1]->getQuantity()) : (items[j]->getQuantity() < items[j + 1]->getQuantity());
	            } 
				else if (criteria == 'p') 
				{
	                swapCondition = (order == 'a') ? (items[j]->getPrice() > items[j + 1]->getPrice()) : (items[j]->getPrice() < items[j + 1]->getPrice());
	            }
	
	            if (swapCondition) 
				{
	                swap(items[j], items[j + 1]);
	            }
	        }
	    }
	
	    cout <<endl << "Items sorted successfully!" << endl;
	    displayAllItems();
	}

    void displayLowStockItems() 
	{
	    if (itemCount == 0)
	    {
	        cout << "The Inventory is empty!" << endl;
	        return;
	    }
	
	    bool lowStockFound = false;
	
	    items[0]->headerWithCategory();
	
	    for (int i = 0; i < itemCount; ++i) 
	    {
	        if (items[i]->getQuantity() <= 5) 
	        {
	            items[i]->displayWithCategory();
	            cout << endl;
	            lowStockFound = true;
	        }
	    }
	
	    if (!lowStockFound) 
	    {
	        cout << "No items are low on stock!" << endl;
	    }
	}
};

void welcome()
{
	cout << " _     _  _______  ___      _______  _______  __   __  _______ \n";
	cout << "| | _ | ||       ||   |    |       ||       ||  |_|  ||       |\n";
	cout << "| || || ||    ___||   |    |       ||   _   ||       ||    ___|\n"; 
	cout << "|       ||   |___ |   |    |       ||  | |  ||       ||   |___ \n"; 
	cout << "|       ||    ___||   |___ |      _||  |_|  ||       ||    ___|\n"; 
	cout << "|   _   ||   |___ |       ||     |_ |       || ||_|| ||   |___ \n";
	cout << "|__| |__||_______||_______||_______||_______||_|   |_||_______|\n\n";
}

void addItemHeader()
{
	cout << "===================================================\n";                                                                              
	cout << "                    ADD ITEM\n";
	cout << "===================================================\n\n";
}

void updateItemHeader()
{
	cout << "===================================================\n";                                                                              
	cout << "                   UPDATE ITEM\n";
	cout << "===================================================\n\n";
}
void removeItemHeader()
{
	cout << "===================================================\n";                                                                              
	cout << "                   REMOVE ITEM\n";
	cout << "===================================================\n\n";
}

void displayCategoryHeader()
{
	cout << "=======================================================\n";                                                                              
	cout << "              DISPLAY ITEMS BY CATEGORY\n";
	cout << "=======================================================\n";
}

void displayAllItemHeader()
{
	cout << "======================================================================\n";
	cout << "                              ALL ITEMS\n";
}

void searchItemHeader()
{
	cout << "======================================================================\n";                                                                             
	cout << "                            SEARCH ITEM\n";
	cout << "======================================================================\n\n";
}

void sortItemHeader()
{
	cout << "======================================================================\n";                                                                              
	cout << "                             SORT ITEMS\n";
	cout << "======================================================================\n\n";
}

void displayLowItemHeader()
{
	cout << "======================================================================\n";                                                                              
	cout << "                           LOW STOCK ITEMS\n";
}

void exit()
{
	cout << " _______  __   __  ___   _______  ___   __    _  _______ \n";
	cout << "|       ||  |_|  ||   | |       ||   | |  |  | ||       |\n";
	cout << "|    ___||       ||   | |_     _||   | |   |_| ||    ___|\n";
	cout << "|   |___ |       ||   |   |   |  |   | |       ||   | __ \n";
	cout << "|    ___| |     | |   |   |   |  |   | |  _    ||   ||  |\n";
	cout << "|   |___ |   _   ||   |   |   |  |   | | | |   ||   |_| |\n";
	cout << "|_______||__| |__||___|   |___|  |___| |_|  |__||_______|\n\n";
}

void menuDisplay() 
{                                                   
	cout <<"========================================\n";                                                                              
	cout <<"      INVENTORY MANAGEMENT SYSTEM\n";
	cout <<"========================================\n";
    cout << "Menu" << endl;
    cout << "1 - Add Item" << endl;
    cout << "2 - Update Item" << endl;
    cout << "3 - Remove Item" << endl;
    cout << "4 - Display Items by Category" << endl;
    cout << "5 - Display All Items" << endl;
    cout << "6 - Search Item" << endl;
    cout << "7 - Sort Items" << endl;
    cout << "8 - Display Low Stock Items" << endl;
    cout << "9 - Exit" << endl;
    cout << "Enter your choice: ";
}

int main() 
{
    Inventory inventory;
    bool looper = true;
    int choice;
    
    welcome();
    system("pause");

    while(looper)
	{
		system("cls");
        menuDisplay();
        cin >> choice;

        if(cin.fail())
		{
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number between 1 and 9." << endl;
            cout << endl;
            system("pause");
            continue;
        }
        
        if (cin.peek() != '\n') 
        {
            cin.ignore(10000, '\n'); 
            cout << "Invalid input! Please enter a number between 1 and 9 without extra characters." << endl;
            cout << endl;
            system("pause");
            continue;
        }

        if (choice < 1 || choice > 9) {
            cout << "Invalid input! Please enter a number between 1 and 9." << endl;
            cout << endl;
            system("pause");
            continue; 
        }

        switch (choice) 
		{
            case 1:
            	system("cls");
            	addItemHeader();
                inventory.addItem();
                cout << endl;
                system("pause");
                break;
            case 2:
            	system("cls");
            	updateItemHeader();
                inventory.updateItem();
                cout << endl;
                system("pause");
                break;
            case 3:
            	system("cls");
            	removeItemHeader();
                inventory.removeItem();
                cout << endl;
                system("pause");
                break;
            case 4:
            	system("cls");
            	displayCategoryHeader();
                inventory.displayItemsByCategory();
                cout << endl;
                system("pause");
                break;
            case 5:
            	system("cls");
            	displayAllItemHeader();
                inventory.displayAllItems();
                cout << endl;
                system("pause");
                break;
            case 6:
            	system("cls");
            	searchItemHeader();
                inventory.searchItem();
                cout << endl;
                system("pause");
                break;
            case 7:
            	system("cls");
            	sortItemHeader();
                inventory.sortItems();
                cout << endl;
                system("pause");
                break;
            case 8:
            	system("cls");
            	displayLowItemHeader();
                inventory.displayLowStockItems();
                cout << endl;
                system("pause");
                break;
            case 9:
            	system("cls");
                exit();
                system("pause");
                looper = false;
                break;
            default:
                cout << "Invalid choice!" << endl <<endl;
                system("pause");
        }
    };
    return 0;
}
