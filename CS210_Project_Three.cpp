#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

// Class to track grocery items
class GroceryTracker {
private:
    map<string, int> itemFrequency; // Stores items and their counts

public:
    // Load items from input file and count frequency
    void loadItems(const string& filename) {
        ifstream inputFile(filename);
        string item;
        if (!inputFile) {
            cout << "Error: Could not open input file." << endl;
            return;
        }
        while (inputFile >> item) {
            itemFrequency[item]++; // Increment count for this item
        }
        inputFile.close();
    }

    // Return frequency of a specific item
    int getItemFrequency(const string& item) {
        if (itemFrequency.find(item) != itemFrequency.end())
            return itemFrequency[item];
        return 0; // If item not found, return 0
    }

    // Print all items with their frequency
    void printFrequencyList() {
        cout << "\nItem Frequency List:" << endl;
        for (auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Print histogram of items
    void printHistogram() {
        cout << "\nItem Histogram:" << endl;
        for (auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++)
                cout << "*";
            cout << endl;
        }
    }

    // Save backup file with frequency data
    void saveBackup(const string& filename) {
        ofstream outputFile(filename);
        if (!outputFile) {
            cout << "Error: Could not create backup file." << endl;
            return;
        }
        for (auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }
        outputFile.close();
    }
};

int main() {
    GroceryTracker tracker;

    // Load items from input file
    tracker.loadItems("CS210_Project_Three_Input_File.txt");

    // Create backup file
    tracker.saveBackup("frequency.dat");

    int choice;
    string itemName;

    // Menu loop
    do {
        cout << "\n--- Corner Grocer Menu ---\n";
        cout << "1 - Search for an item\n";
        cout << "2 - Print frequency list\n";
        cout << "3 - Print histogram\n";
        cout << "4 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter item to search: ";
            cin >> itemName;
            cout << itemName << " appears " << tracker.getItemFrequency(itemName) << " times." << endl;
            break;
        case 2:
            tracker.printFrequencyList();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}