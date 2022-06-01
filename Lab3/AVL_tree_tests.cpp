#include <string>
#include <iostream>
using std::cout;
using std::cin;

#include "AVL_tree_dictionary.cpp"

int main()
{
    Dictionary<string, string> newDictionary;
    string key, info, query;
    int choice;

    cout << "Note: Trees are printed rotated 90 degrees to the left.\nChoose:\n";
    while(true)
    {
        cout << "0. Add some predefinied dictionary entries\n";
        cout << "1. Add a word to the dictionary\n";
        cout << "2. Delete a word from the dictionary\n";
        cout << "3. Search for a word\n";
        cout << "4. Show the whole tree\n";
        cout << "5. Show the whole tree in order\n";
        cout << "6. Quit.\n";
        
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 0:
            newDictionary.insert("Printer", "Here goes printer definition.");
            newDictionary.insert("Keyboard", "Here goes keyboard definition.");
            newDictionary.insert("Mouse", "Here goes mouse definition.");
            newDictionary.insert("Laptop", "Here goes keyboard definition.");
            newDictionary.insert("PC", "Here goes PC definition.");
            newDictionary.insert("UDP", "Here goes UDP definition.");
            break;
        case 1:
            cout << "\nEnter the word you wish to add: ";
            std::getline(cin, key);
            cout << "Add Description:\n";
            std::getline(cin, info);
            newDictionary.insert(key, info);
            break;
        case 2:
            cout << "\nEntry to delete: ";
            std::getline(cin, query);
            newDictionary.remove(query);
            break;
        case 3:
            cout << "\nSearch: ";
            std::getline(cin, query);
            newDictionary.search(query);
            break;
        case 4:
            newDictionary.print_tree();
            break;
        case 5:
            newDictionary.inorder_();
            break;
        case 6:
            newDictionary.~Dictionary();
            return EXIT_SUCCESS;
            break;
        default:
            break;
        }
        cout << std::endl;
    }
}