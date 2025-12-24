// Corner Grocer Item-Tracking Program (CS210 Project Three)
// Reads CS210_Project_Three_Input_File.txt, counts item frequencies,
// writes backup file frequency.dat, and provides a menu to query/print results.

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

class GroceryTracker {
public:
   GroceryTracker() = default;

   // Loads item frequencies from an input file
   bool LoadFromFile(const string& inputFileName) {
      ifstream inFS(inputFileName);
      if (!inFS.is_open()) {
         return false;
      }

      itemCounts.clear();

      string item;
      while (inFS >> item) {
         ++itemCounts[item];
      }

      inFS.close();
      return true;
   }

   // Writes frequencies to backup file (frequency.dat)
   bool WriteBackupFile(const string& outputFileName) const {
      ofstream outFS(outputFileName);
      if (!outFS.is_open()) {
         return false;
      }

      for (const auto& pair : itemCounts) {
         outFS << pair.first << " " << pair.second << "\n";
      }

      outFS.close();
      return true;
   }

   // Returns frequency of a single item (0 if not found)
   int GetFrequency(const string& item) const {
      auto it = itemCounts.find(item);
      if (it == itemCounts.end()) {
         return 0;
      }
      return it->second;
   }

   // Prints each item with its frequency
   void PrintAllFrequencies() const {
      for (const auto& pair : itemCounts) {
         cout << pair.first << " " << pair.second << "\n";
      }
   }

   // Prints histogram with asterisks equal to frequency
   void PrintHistogram(char symbol = '*') const {
      for (const auto& pair : itemCounts) {
         cout << pair.first << " ";
         for (int i = 0; i < pair.second; ++i) {
            cout << symbol;
         }
         cout << "\n";
      }
   }

private:
   map<string, int> itemCounts;
};

static void PrintMenu() {
   cout << "\n===== Corner Grocer Item Tracker =====\n";
   cout << "1. Look up an item frequency\n";
   cout << "2. Print all item frequencies\n";
   cout << "3. Print histogram\n";
   cout << "4. Exit\n";
   cout << "Select an option (1-4): ";
}

static int ReadMenuChoice() {
   int choice;
   while (true) {
      if (cin >> choice && choice >= 1 && choice <= 4) {
         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear line
         return choice;
      }
      cout << "Invalid input. Enter 1, 2, 3, or 4: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }
}

int main() {
   const string inputFileName = "CS210_Project_Three_Input_File.txt";
   const string backupFileName = "frequency.dat";

   GroceryTracker tracker;

   if (!tracker.LoadFromFile(inputFileName)) {
      cout << "Error: Could not open input file: " << inputFileName << "\n";
      cout << "Make sure the file is in the same folder as the program.\n";
      return 1;
   }

   // Create backup file automatically at program start
   if (!tracker.WriteBackupFile(backupFileName)) {
      cout << "Warning: Could not write backup file: " << backupFileName << "\n";
   }

   while (true) {
      PrintMenu();
      int choice = ReadMenuChoice();

      if (choice == 1) {
         string item;
         cout << "Enter item to search: ";
         getline(cin, item);

         int freq = tracker.GetFrequency(item);
         cout << item << " " << freq << "\n";
      }
      else if (choice == 2) {
         tracker.PrintAllFrequencies();
      }
      else if (choice == 3) {
         tracker.PrintHistogram('*');
      }
      else { // choice == 4
         cout << "Goodbye.\n";
         break;
      }
   }

   return 0;
}
