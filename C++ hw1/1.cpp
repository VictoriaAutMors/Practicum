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
    int getCalls();
    void newCall();
    void print();
};

Contact::Contact() {
    name = "Vladimir";
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
    size_t tmp = name.find(partOfName, 0);
    if (tmp == string::npos) {
        return false;
    }
    return true;
}

bool Contact::numberLike(int numberSuffix) {
    int current_number = 0;
    int buff = number;
    int digit = 0;
    int i = 0;
    while(buff != 0){
        digit = buff % 10;
        digit *= pow(10, i);
        current_number = digit + current_number;
        if(current_number == numberSuffix){
            return true;
        }
        i++;
        buff /= 10;
    }
    return false;
}

int Contact::getCalls() {
    return calls;
}

void Contact::newCall() {
    calls++;
}

void Contact::print() {
    cout << setw(10); 
    cout << name << " Prefix:" << prefix << " Number:" << number << " Calls:" <<  calls << endl;
}

class PhoneBook{
    int abonentNumber;
    Contact names[10];
    void printHeader();
    public:
  PhoneBook();
    void addAbonent(const string & name, int pref, int number);
    bool callAbonent(const string & prefixOfName);
    bool callAbonent(int suffixOfNumber);
    void print();
    void printTheMostCommon();
};

PhoneBook::PhoneBook() {
    for(int i = 0; i < 10; i++){
            Contact names[i];
    }
    abonentNumber = 0000000;
}
PhoneBook::addAbonent() {
    if(name.size() > 10 && number > 999999999 &&  pref > 999){
        cout << "FAIL: incorrect name or number phormat" << endl; 
    } else {
        cout << "ADD: name phone";
        for(int i = 0; i < 10 ; i++){
                 names[i].setContact(name, pref, number);
                return;
        }
    }
}

int main()
{
    Contact A;
    A.setContact("Vladislavbabydonthurtme", 111, 9090909);
    A.print();   
    return 0;
}
