#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip> // For formatting output
using namespace std;

class Item {
private:
    string ItemName;
    int Rate, Quantity;

public:
    Item() : ItemName(""), Rate(0), Quantity(0) { }
    Item(string item, int rate, int quant) : ItemName(item), Rate(rate), Quantity(quant) { }

    void setItem(string item) { ItemName = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }
    
    // Mark getter methods as const
    string getItem() const { return ItemName; }
    int getRate() const { return Rate; }
    int getQuant() const { return Quantity; }
};


// Global unordered_map to store items
unordered_map<string, Item> M;

void addItem() {
    bool moreItem = true;
    while (moreItem) {
        int choice;
        cout << "\t1. Add." << endl;
        cout << "\t2. Close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;

            if (M.find(item) != M.end()) {
                M[item].setQuant(M[item].getQuant() + quant); // Update quantity
            } else {
                M[item] = Item(item, rate, quant); // Add new item
            }

            cout << "\tItem Added Successfully!" << endl;
        } else if (choice == 2) {
            system("cls");
            moreItem = false;
            cout << "\tBack To Main Menu!" << endl;
        } else {
            cout << "\tInvalid Choice. Try Again!" << endl;
        }
    }
}

void showBill(const vector<Item>& Bill, int totalAmount) {
    cout << "\n\t=================== BILL ===================" << endl;
    cout << "\tItem Name    Rate    Quantity    Amount" << endl;
    cout << "\t------------------------------------------" << endl;

    for (const auto& item : Bill) {
        int amount = item.getRate() * item.getQuant();
        cout << "\t" << left << setw(12) << item.getItem()
             << setw(8) << item.getRate()
             << setw(12) << item.getQuant()
             << amount << endl;
    }

    cout << "\t------------------------------------------" << endl;
    cout << "\tTotal Amount: " << totalAmount << endl;
    cout << "\t==========================================" << endl;
}

void printBill() {
    system("cls");
    vector<Item> Bill; // To store customer's demanded items
    bool moreItems = true;
    int totalAmount = 0;

    while (moreItems) {
        string itemName;
        int quantity;
        cout << "\tEnter Item Name (or type 'done' to finish): ";
        cin >> itemName;

        if (itemName == "done") {
            moreItems = false;
            continue;
        }

        cout << "\tEnter Quantity: ";
        cin >> quantity;

        if (M.find(itemName) != M.end()) {
            Item &stockItem = M[itemName]; // Reference to the item in stock
            if (quantity <= stockItem.getQuant()) {
                // Deduct quantity and calculate total price
                stockItem.setQuant(stockItem.getQuant() - quantity);
                int price = quantity * stockItem.getRate();
                totalAmount += price;
                Bill.emplace_back(itemName, stockItem.getRate(), quantity);
                cout << "\t" << quantity << " units of " << itemName << " added to the bill." << endl;
            } else {
                // Add available quantity to the bill
                int availableQuantity = stockItem.getQuant();
                int price = availableQuantity * stockItem.getRate();
                totalAmount += price;
                Bill.emplace_back(itemName, stockItem.getRate(), availableQuantity);
                cout << "\tOnly " << availableQuantity << " units of " << itemName << " were available and added to the bill." << endl;

                // Set stock quantity to zero
                stockItem.setQuant(0);
            }
        } else {
            cout << "\tItem not found in stock!" << endl;
        }
    }

    // Show the bill and total amount
    showBill(Bill, totalAmount);
}

int main() {
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**" << endl;
        cout << "\t1. Add Item." << endl;
        cout << "\t2. Print Bill." << endl;
        cout << "\t3. Exit." << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        switch (val) {
            case 1:
                system("cls");
                addItem();
                break;

            case 2:
                printBill();
                break;

            case 3:
                system("cls");
                exit = true;
                cout << "\tGood Luck!" << endl;
                break;

            default:
                cout << "\tInvalid Choice. Try Again!" << endl;
        }
    }
    return 0;
}