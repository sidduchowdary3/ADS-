#include<iostream>
#include<vector>
#include<string>
using namespace std;

int capacity;
int size = 0;

template<typename T>
class hashtable {
public:
    int key;
    T value;
    int count;

    hashtable() : key(0), value(T()), count(0) {}
    hashtable(int key, T value) : key(key), value(value), count(1) {}
};

template<typename T>
class hashmap {
public:
    vector<hashtable<T>> table;

    int hashfunction(int input) {
        return (input % capacity);
    }

    void insert(int input, T value) {
        int key = hashfunction(input);
        // Linear probing
        while (table[key].value != T() && table[key].value != value) {
            key = (key + 1) % capacity;
        }
        if (table[key].value == T()) {
            // Empty slot found
            table[key] = hashtable<T>(input, value);
            size++;
        } else if (table[key].value == value) {
            // Element already present, update count
            cout << "Element " << input << " already present, hence updating" << endl;
            table[key].count += 1;
        }
    }

    void remove_element(int input, T value) {
        int key = hashfunction(input);
        while (table[key].value != T() && table[key].value != value) {
            key = (key + 1) % capacity;
        }
        if (table[key].value == value) {
            table[key] = hashtable<T>();  // Resetting to default
            size--;
            cout << "Element " << input << " has been removed" << endl;
        } else {
            cout << "This element does not exist" << endl;
        }
    }

    void search(int input, T value) {
        int key = hashfunction(input);
        while (table[key].value != T() && table[key].value != value) {
            key = (key + 1) % capacity;
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
                cout << "Hashed key " << i << " has value " << table[i].value << " and is present " << table[i].count << " times" << endl;
            }
        }
    }

    int size_of_table() {
        return size;
    }
};

bool isPrime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

bool check_number(const string& str) {
    if (!isdigit(str[0]))
        return false;
    return true;
}

template<typename T>
void perform() {
    int choice;
    T input;
    cout << "Enter the size:";
    cin >> capacity;
    for (int i = capacity; i >= 2; i--) {
        if (isPrime(i)) {
            capacity = i;
            break;
        }
    }
    hashmap<T> h;
    h.table.resize(capacity);
    cout << "1. Inserting item in the Hash Table" << endl;
    cout << "2. Removing item from the Hash Table" << endl;
    cout << "3. Display the Hash Table" << endl;
    cout << "4. Searching for an item in Hash Table" << endl;
    cout << "5. Check the size of Hash Table" << endl;
    do {
        cout << "Please enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Inserting element in Hash Table" << endl;
            cout << "Enter element: ";
            cin >> input;
            if (check_number(input))
                h.insert(stoi(input), input);
            else
                h.insert(input.length(), input);
            break;
        case 2:
            cout << "Deleting in Hash Table\nEnter the key to delete: ";
            cin >> input;
            if (check_number(input))
                h.remove_element(stoi(input), input);
            else
                h.remove_element(input.length(), input);
            break;
        case 3:
            h.display();
            break;
        case 4:
            cout << "Searching element in Hash Table" << endl;
            cout << "Enter element: ";
            cin >> input;
            if (check_number(input))
                h.search(stoi(input), input);
            else
                h.search(input.length(), input);
            break;
        case 5:
            cout << "Size of Hash Table is: " << h.size_of_table() << endl;
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
