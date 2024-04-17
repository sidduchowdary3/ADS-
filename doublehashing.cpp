#include <iostream>
#include <vector>
#include <string>
#include <cctype> // Needed for isdigit function
using namespace std;

int capacity;
int size = 0;

template <typename T>
class hashtable {
public:
    int key;
    T value;
    int count;
    hashtable() : key(0), value(T()), count(0) {}
    hashtable(int key, T value) : key(key), value(value), count(1) {}
};

bool isPrime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; i++) { // Optimization: check up to the square root
        if (n % i == 0)
            return false;
    }
    return true;
}

bool check_number(string str) {
    return !str.empty() && isdigit(str[0]);
}

template <typename T>
class hashmap {
public:
    vector<hashtable<T>> table;
    int hashfunction(int input) {
        return (input % capacity);
    }
    int hashfunction2(int input) {
        int temp;
        for (int i = capacity - 1; i >= 2; i--) {
            if (isPrime(i)) {
                temp = i;
                break;
            }
        }
        return temp - (input % temp);
    }
    int doubleHashing(int key, int i) {
        return (hashfunction(key) + i * hashfunction2(key)) % capacity;
    }
    void insert(int input, T value) {
        int key = hashfunction(input);
        int i = 0;
        while (table[key].value != T() && table[key].value != value) {
            i++;
            key = doubleHashing(input, i);
        }
        if (table[key].value == T()) {
            table[key] = hashtable<T>(input, value);
            size++;
        } else if (table[key].value == value) {
            cout << "Element " << input << " already present, hence updating" << endl;
            table[key].count += 1;
        }
    }
    void remove_element(int input, T value) {
        int key = hashfunction(input);
        int i = 0;
        while (table[key].value != T() && table[key].value != value) {
            i++;
            key = doubleHashing(input, i);
        }
        if (table[key].value == value) {
            table[key] = hashtable<T>(); // Corrected the typo
            size--;
            cout << "Element " << input << " has been removed" << endl;
        } else {
            cout << "This element does not exist" << endl;
        }
    }
    void search(int input, T value) {
        int key = hashfunction(input);
        int i = 0;
        while (table[key].value != T() && table[key].value != value) {
            i++;
            key = doubleHashing(input, i);
        }
        if (table[key].value == value) {
            cout << "Element " << value << " is found at key " << key << endl;
        } else {
            cout << "This element does not exist" << endl;
        }
    }
    void display() {
        for (int i = 0; i < table.size(); i++) {
            if (table[i].value == T()) {
                cout << "Hashed key " << i << " has no elements" << endl;
            } else {
                cout << "Hashed key " << i << " has value " << table[i].value << " and " << table[i].count << " times" << endl;
            }
        }
    }
    int size_of_table() {
        return size;
    }
};

template <typename T>
void perform() {
    int choice;
    T input;
    hashmap<T> h;
    cout << "Enter the size:";
    cin >> capacity;
    for (int i = capacity; i >= 2; i--) {
        if (isPrime(i)) {
            capacity = i;
            break;
        }
    }
    h.table.resize(capacity);
    cout << "1.Inserting item in the Hash Table" << endl;
    cout << "2.Removing item from the Hash Table" << endl;
    cout << "3.Display a Hash Table" << endl;
    cout << "4.Searching for an item in Hash Table" << endl;
    cout << "5.Check the size of Hash Table" << endl;
    do {
        cout << "Please enter your choice :";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Inserting element in Hash Table" << endl;
            cout << "Enter element: ";
            cin >> input;
            if (check_number(to_string(input)))
                h.insert(stoi(to_string(input)), input);
            else
                h.insert(to_string(input).length(), input);
            break;
        case 2:
            cout << "Deleting in Hash Table \nEnter the key to delete: ";
            cin >> input;
            if (check_number(to_string(input)))
                h.remove_element(stoi(to_string(input)), input);
            else
                h.remove_element(to_string(input).length(), input);
            break;
        case 3:
            h.display();
            break;
        case 4:
            cout << "Searching element in Hash Table" << endl;
            cout << "Enter element: ";
            cin >> input;
            if (check_number(to_string(input)))
                h.search(stoi(to_string(input)), input);
            else
                h.search(to_string(input).length(), input);
            break;
        case 5:
            cout << "Size of Hash Table is: " << h.size_of_table() << endl;
            break;
        default:
            cout << "Wrong Input" << endl;
        }
        cout << "\nDo you want to continue:(press 1 for yes): ";
        cin >> choice;
    } while (choice == 1);
}

int main() {
    perform<int>();
    return 0;
}
