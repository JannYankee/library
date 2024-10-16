#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ENTRIES = 100;
const string DATA_FILE = "library_data.txt";

struct Item {
    string title;
    string author;
    string category;
    string type;
    int year;
};

Item library[MAX_ENTRIES];
int itemCount = 0;

void addItem(string t, string a, string c, string ty, int y) {
    if (itemCount < MAX_ENTRIES) {
        library[itemCount++] = { t, a, c, ty, y };
    }
    else {
        cout << "Library is full!" << endl;
    }
}

void removeItem(const string& t) {
    for (int i = 0; i < itemCount; i++) {
        if (library[i].title == t) {
            library[i] = {};
            cout << "Deleted item: '" << t << "'" << endl;
            return;
        }
    }
    cout << "Item '" << t << "' not found." << endl;
}

void findBooks(const string& a, const string& t) {
    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (library[i].type == "book" && (a.empty() || library[i].author == a) && (t.empty() || library[i].title == t)) {
            cout << "Book: " << library[i].title << ", Author: " << library[i].author << ", Category: " << library[i].category << ", Year: " << library[i].year << endl;
            found = true;
        }
    }
    if (!found) cout << "No books found." << endl;
}

void findMagazines(const string& t, int y) {
    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (library[i].type == "magazine" && (t.empty() || library[i].title == t) && (y == 0 || library[i].year == y)) {
            cout << "Magazine: " << library[i].title << ", Year: " << library[i].year << endl;
            found = true;
        }
    }
    if (!found) cout << "No magazines found." << endl;
}

void displayAll() {
    for (int i = 0; i < itemCount; i++) {
        if (!library[i].title.empty()) {
            cout << "Index: " << i << " - " << "Title: " << library[i].title << ", Author: " << library[i].author << ", Category: " << library[i].category << ", Type: " << library[i].type << ", Year: " << library[i].year << endl;
        }
    }
}

void showByIndex(int idx) {
    if (idx >= 0 && idx < itemCount) {
        cout << "Item at index " << idx << ": " << library[idx].title << ", Author: " << library[idx].author << ", Year: " << library[idx].year << endl;
    }
    else {
        cout << "Invalid index. Please enter a value between 0 and " << itemCount - 1 << ".\n";
    }
}

void listBooksByAuthor(const string& a) {
    for (int i = 0; i < itemCount; i++) {
        if (library[i].type == "book" && library[i].author == a) {
            cout << "Title: " << library[i].title << endl;
        }
    }
}

void listBooksByCategory(const string& c) {
    for (int i = 0; i < itemCount; i++) {
        if (library[i].type == "book" && library[i].category == c) {
            cout << "Title: " << library[i].title << endl;
        }
    }
}

void listMagazinesByYear(int y) {
    for (int i = 0; i < itemCount; i++) {
        if (library[i].type == "magazine" && library[i].year == y) {
            cout << "Title: " << library[i].title << endl;
        }
    }
}

int countBooksInCategory(const string& c) {
    int count = 0;
    for (int i = 0; i < itemCount; i++) {
        if (library[i].type == "book" && library[i].category == c) {
            count++;
        }
    }
    return count;
}

void saveData() {
    ofstream file(DATA_FILE);
    if (file.is_open()) {
        for (int i = 0; i < itemCount; i++) {
            if (!library[i].title.empty()) {
                file << library[i].title << ";" << library[i].author << ";" << library[i].category << ";" << library[i].type << ";" << library[i].year << endl;
            }
        }
        file.close();
        cout << "Library data saved." << endl;
    }
    else {
        cout << "Error opening file for writing." << endl;
    }
}

void loadData() {
    ifstream file(DATA_FILE);
    itemCount = 0;
    if (file.is_open()) {
        while (getline(file, library[itemCount].title, ';') && itemCount < MAX_ENTRIES) {
            getline(file, library[itemCount].author, ';');
            getline(file, library[itemCount].category, ';');
            getline(file, library[itemCount].type, ';');
            file >> library[itemCount].year;
            file.ignore();
            itemCount++;
        }
        file.close();
        cout << "Library data loaded." << endl;
    }
    else {
        cout << "Error opening file for reading." << endl;
    }
}

void sortLibrary() {
    for (int i = 0; i < itemCount - 1; i++) {
        for (int j = 0; j < itemCount - i - 1; j++) {
            if (library[j].type > library[j + 1].type || (library[j].type == library[j + 1].type && library[j].title > library[j + 1].title)) {
                swap(library[j], library[j + 1]);
            }
        }
    }
}

void showMenu() {
    cout << R"(
    Library Menu:
    1. View all items
    2. Add an item
    3. Remove an item
    4. Search for a book
    5. Search for a magazine
    6. List books by author
    7. List books by category
    8. List magazines by year
    9. Count books by category
    10. Search by index
    11. Sort library
    0. Exit
    )";
    cout << "Choose an option -->  ";
}

int main() {
    loadData();
    int option;

    do {
        showMenu();
        cin >> option;

        switch (option) {
        case 1: displayAll(); break;
        case 2: {
            string t, a, c, ty;
            int y;
            cout << "Enter title: "; cin.ignore(); getline(cin, t);
            cout << "Enter author: "; getline(cin, a);
            cout << "Enter category: "; getline(cin, c);
            cout << "Enter type (book, magazine, newspaper): "; getline(cin, ty);
            cout << "Enter year: "; cin >> y;
            addItem(t, a, c, ty, y);
            break;
        }
        case 3: {
            string t;
            cout << "Enter title to remove: "; cin.ignore(); getline(cin, t);
            removeItem(t);
            break;
        }
        case 4: {
            string a, t;
            cout << "Enter author's name (or leave blank): "; cin.ignore(); getline(cin, a);
            cout << "Enter book title (or leave blank): "; getline(cin, t);
            findBooks(a, t);
            break;
        }
        case 5: {
            string t; int y;
            cout << "Enter magazine title (or leave blank): "; cin.ignore(); getline(cin, t);
            cout << "Enter year (0 for any): "; cin >> y;
            findMagazines(t, y);
            break;
        }
        case 6: {
            string a;
            cout << "Enter author's name: "; cin.ignore(); getline(cin, a);
            listBooksByAuthor(a);
            break;
        }
        case 7: {
            string c;
            cout << "Enter book category: "; cin.ignore(); getline(cin, c);
            listBooksByCategory(c);
            break;
        }
        case 8: {
            int y;
            cout << "Enter year: "; cin >> y;
            listMagazinesByYear(y);
            break;
        }
        case 9
: {
            string c;
            cout << "Enter book category: "; cin.ignore(); getline(cin, c);
            cout << "Books in '" << c << "': " << countBooksInCategory(c) << endl;
            break;
        }
        case 10: {
            int idx;
            cout << "Enter index: "; cin >> idx;
            showByIndex(idx);
            break;
        }
        case 11: {
            sortLibrary();
            displayAll();
            break;
        }
        case 0:
            cout << "Exiting...\n";
            saveData();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 0);

    return 0;
}