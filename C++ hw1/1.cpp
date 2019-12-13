#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

class Contact{
    string name;
    int prefix;
    int number;
    int calls;
 public:
    Contact();
    void setContact(const string &, int, int);
    bool nameLike(const string & partOfName);
    bool numberLike(int numberSuffix);
    int getcalls();
    void newCall();
    void print();
};

Contact::Contact() {
    name = " ";
    prefix = 000;
    number = 0000000;
    calls = 0;
}

void Contact::setContact(const string & newName, int newPrefix, int newNumber) {
    name = newName;
    prefix = newPrefix;
    number = newNumber;
}

bool Contact::nameLike(const string & partOfName) {
    string tmp;
    for (int i = 0; i < 10; i++) {
        tmp = name.substr(0, i);
        if (!tmp.compare(partOfName)) {
            return true;
        }
    }
    return false;
}

bool Contact::numberLike(int numberSuffix) {
    int current_number = 0;
    int buff = number;
    int digit = 0;
    int i = 0;
    while (buff != 0) {
        digit = buff % 10;
        digit *= pow(10, i);
        current_number = digit + current_number;
        if (current_number == numberSuffix) {
            return true;
        }
        i++;
        buff /= 10;
    }
    return false;
}

int Contact::getcalls() {
    return calls;
}

void Contact::newCall() {
    calls++;
}

void Contact::print() {
    cout << setw(10) << name << " " << prefix << " " << number << " "
                                                            <<  calls << endl;
}

class PhoneBook{
    int abonentNumber;
    Contact names[10];
    void printHeader() {
       cout << setw(10) << "name" << " " << "prefix" << " " << "number" << " "
                                                            << "calls" << endl;
    }
 public:
    PhoneBook();
    void addAbonent(const string & name, int pref, int number);
    bool callAbonent(const string & prefixOfName);
    bool callAbonent(int suffixOfNumber);
    void print();
    void printTheMostCommon();
};

PhoneBook::PhoneBook() {
    abonentNumber = 0;
}

void PhoneBook::addAbonent(const string & name, int pref, int number) {
    if (abonentNumber < 10 && name.size() > 10 && number > 9999999
                                                        && pref > 333) {
        cout << "FAIL: incorrect name or number phormat\n";
    } else {
        cout << "ADD: name phone\n";
        for (int i = 0; i < 10 ; i++) {
            if (names[i].nameLike(" ") == true) {
                names[i].setContact(name, pref, number);
                return;
            }
        }
    }
}

bool PhoneBook::callAbonent(const string & prefixName) {
    int i, pos, not_unique_names = 0;
    for (i = 0; i < 10; i++) {
        if (names[i].nameLike(prefixName) == true) {
            not_unique_names++;
            if (not_unique_names > 1) {
                break;
            }
            pos = i;
        }
    }
    if (not_unique_names > 1) {
        cout << "choose unique" << endl;
        printHeader();
        for (i = pos; i < 10; i++) {
            if (names[i].nameLike(prefixName)) {
                names[i].print();
            }
        }
        return false;
    }
    if (not_unique_names == 0) {
        cout << "no such abonent" << endl;
        return false;
    }
    names[pos].newCall();
    names[pos].print();
    cout << "CALL" << endl;
    return true;
}

bool PhoneBook::callAbonent(int suffixOfNumber) {
    int i, pos, not_unique_names = 0;
    for (i = 0; i < 10; i++) {
        if (names[i].numberLike(suffixOfNumber)) {
            not_unique_names++;
            if (not_unique_names > 1) {
                break;
            }
            pos = i;
        }
    }
    if (not_unique_names > 1) {
        cout << "choose unique" << endl;
        printHeader();
        for (i = pos; i < 10; i++) {
            if (names[i].numberLike(suffixOfNumber)) {
                names[i].print();
            }
        }
        return false;
    }
    if (not_unique_names == 0) {
        cout << "no such abonent" << endl;
        return false;
    }
    names[pos].newCall();
    names[pos].print();
    cout << "CALLS" << endl;
    return true;
}

void PhoneBook::print() {
    printHeader();
    for (int i = 0; i < 10; i++) {
        names[i].print();
        cout << "\n";
    }
}

void PhoneBook::printTheMostCommon() {
    int i, max = 0;
    for (i = 0; i < 10; i++) {
        if (max < names[i].getcalls()) {
            max = names[i].getcalls();
        }
    }
    printHeader();
    for (i = 0; i < 10; i++) {
        if (max == names[i].getcalls()) {
            names[i].print();
            cout << endl;
        }
    }
}

int main() {
    PhoneBook Book;
    string command, name, prefix_name;
    int pref, number, suffix_number;
    while (1) {
        cin >> command;
        if (command == "+") {
            cin >>  name >> pref >> number;
            Book.addAbonent(name, pref, number);
        }
        if (command == "?") {
            Book.print();
        }
        if (command == "#1") {
            cin >> prefix_name;
            Book.callAbonent(prefix_name);
        }
        if (command == "#2") {
            cin >> suffix_number;
            Book.callAbonent(suffix_number);
        }
        if (command == "*") {
            Book.printTheMostCommon();
        }
        if (command == ".") {
            return 0;
        }
    }
    return 0;
}
