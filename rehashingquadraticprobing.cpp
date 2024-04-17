#include<iostream>
#include<vector>
#include<string>
#include<cctype>  // for isdigit function
using namespace std;

int capacity, cap;
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

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool check_number(string str) {
    return !str.empty() && isdigit(str[0]);
}

template<typename T>
class hashmap {
public:
    vector<hashtable<T>> table;

    int hashfunction(int input) {
        return input % capacity;
    }

    void rehash() {
        cout << "Load factor exceeds 0.5. Rehashing..." << endl;
        display();
        size = 0;
        vector<hashtable<T>> newTable(capacity);
        for (int i = 0; i < table.size(); i++) {
            if (table[i].value != T()) {
                int newKey = hashfunction(table[i].key);
                int j = 1;
                while (newTable[newKey].value != T()) {
                    newKey = (newKey + j * j) % capacity;
                    j++;
                }
                newTable[newKey] = table[i];
                size++;
            }
        }
        table = move(newTable);
        display();
    }

    void insert(int input, T value) {
        int key = hashfunction(input);
        int k=key;
        int i = 1;
        while (table[key].value != T() && table[key].value != value) {
            key = (k + i * i) % capacity;
            i++;
        }
        if (table[key].value == T()) {
           table[key]= hashtable<T> (input,value);
            size++;
        } else {
            cout << "Element " << input << " already present, hence updating" << endl;
            table[key].count++;
        }
    }

    void remove_element(int input, T value) {
        int key = hashfunction(input);
        int i = 1;
        while (table[key].value != T() && table[key].value != value) {
            key = (k + i * i) % capacity;
            i++;
        }
        if (table[key].value == value) {
            table[key] = hashtable<T>();
            size--;
            cout << "Element " << input << " has been removed" << endl;
        } else {
            cout << "This element does not exist" << endl;
        }
    }

    void search(int input, T value) {
        int key = hashfunction(input);
        int i = 1;
        while (table[key].value != T() && table[key].value != value) {
            key = (key + i * i) % capacity;
            i++;
        }
        if (table[key].value == value) {
            cout << "Element " << input << " is found at key " << key << endl;
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

template<typename T>
void perform() {
    int choice;
    float loadFactor;
    T input;
    hashmap<T> h;

    cout << "Enter the size:";
    cin >> capacity;
    cap = capacity;
    for (int i = capacity; i >= 2; i--) {
        if (isPrime(i)) {
            capacity = i;
            break;
        }
    }
    h.table.resize(capacity);

    cout << "1. Inserting item in the Hash Table" << endl;
    cout << "2. Removing item from the Hash Table" << endl;
    cout << "3. Display a Hash Table" << endl;
    cout << "4. Searching for an item in Hash Table" << endl;
    cout << "5. Check the size of Hash Table" << endl;
    do {
        cout << "Please enter your choice :";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Inserting element in Hash Table" << endl;
                cout << "Enter element: ";
                cin >> input;
                if (check_number(to_string(input)))
                    h.insert(stoi(input), input);
                else
                    h.insert(input.length(), input);
                loadFactor = static_cast<float>(h.size_of_table()) / capacity;
                if (loadFactor > 0.5) {
                    capacity = 2 * cap;
                    cap = capacity;
                    for (int i = capacity; i >= 2; i--) {
                        if (isPrime(i)) {
                            capacity = i;
                            break;
                        }
                    }
                    h.rehash();
                }
                break;
            case 2:
                cout << "Deleting in Hash Table \nEnter the key to delete: ";
                cin >> input;
                if (check_number(to_string(input)))
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
                if (check_number(to_string(input)))
                    h.search(stoi(input), input);
                else
                    h.search(input.length(), input);
                break;
            case 5:
                cout << "Size of Hash Table is: " << h.size_of_table() << endl;
                break;
            default:
                cout << "Wrong Input" << endl;
                break;
        }
        cout << "\nDo you want to continue:(press 1 for yes): ";
        cin >> choice;
    } while (choice == 1);
}

int main() {
    perform<string>();
}
