#include <iostream>
#include <vector>
#include <string>
#include <cctype> // For isdigit

using namespace std;

int capacity;
int size = 0;

template<typename T>
class HashTable {
public:
    int key;
    T value;
    int count; // Initialize count to 0

    HashTable() : key(0), value(T()),count(0) {}
    HashTable(int key, T value) : key(key), value(value),count(1) {}
};

template<typename T>
class HashMap {
public:
    vector<HashTable<T>> table;

    int hashFunction(int input) {
        return input % capacity;
    }

    void insert(int input, T value) {
        int key = hashFunction(input);
        int k = key;
        int i = 1;
        // Quadratic probing
        while (table[key].value != T() && table[key].value != value) {
            key = (k + i * i) % capacity;
            i++;
        }
        if (table[key].value == T()) {
            // Empty slot found
            table[key]=HashTable<T> entry(input, value);
            size++;
        } else {
            // Element already present, update count
            cout << "Element " << input << " already present, hence updating" << endl;
            table[key].count += 1;
        }
    }

    void removeElement(int input, T value) {
        int key = hashFunction(input);
        int k = key;
        int i = 1;
        while (table[key].value != T() && table[key].value != value) {
            key = (k + i * i) % capacity;
            i++;
        }
        if (table[key].value == value) {
           table[key]=hashtable<t>();
            size--;
            cout << "Element " << input << " has been removed" << endl;
        } else {
            cout << "This element does not exist" << endl;
        }
    }

    void search(int input, T value) {
        int key = hashFunction(input);
        int k = key;
        int i = 1;
        while (table[key].value != T() && table[key].value != value) {
            key = (k + i * i) % capacity;
            i++;
        }
        if (table[key].value == value) {
            cout << "Element " << value << " is found at key " << key << endl;
        } else {
            cout << "This element does not exist" << endl;
        }
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].value == T()) {
                cout << "Hashed key " << i << " has no elements" << endl;
            } else {
                cout << "Hashed key " << i << " has value " << table[i].value
                     << " and is present " << table[i].count << " times" << endl;
            }
        }
    }

    int sizeOfTable() {
        return size;
    }
};

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool checkNumber(const string& str) {
    return !str.empty() && isdigit(str[0]);
}

template<typename T>
void perform() {
    int choice;
    T input;
    cout << "Enter the size: ";
    cin >> capacity;
    for (int i = capacity; i >= 2; i--) {
        if (isPrime(i)) {
            capacity = i;
            break;
        }
    }
    HashMap<T> h;
    h.table.resize(capacity);
    cout << "1. Inserting item in the Hash Table" << endl;
    cout << "2. Removing item from the Hash Table" << endl;
    cout << "3. Display the Hash Table" << endl;
    cout << "4. Searching for an item in the Hash Table" << endl;
    cout << "5. Check the size of the Hash Table" << endl;
    do {
        cout << "Please enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Inserting element in Hash Table" << endl;
                cout << "Enter element: ";
                cin >> input;
                if (checkNumber(input))
                    h.insert(stoi(input), input);
                else
                    h.insert(input.length(), input);
                break;
            case 2:
                cout << "Deleting in Hash Table\nEnter the key to delete: ";
                cin >> input;
                if (checkNumber(input))
                    h.removeElement(stoi(input), input);
                else
                    h.removeElement(input.length(), input);
                break;
            case 3:
                h.display();
                break;
            case 4:
                cout << "Searching element in Hash Table" << endl;
                cout << "Enter element: ";
                cin >> input;
                if (checkNumber(input))
                    h.search(stoi(input), input);
                else
                    h.search(input.length(), input);
                break;
            case 5:
                cout << "Size of Hash Table is: " << h.sizeOfTable() << endl;
                break;
            default:
                cout << "Wrong Input" << endl;
        }
        cout << "\nDo you want to continue? (press 1 for yes): ";
        cin >> choice;
    } while (choice == 1);
}

int main() {
    perform<string>();
}
