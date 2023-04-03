//
//  main.cpp
//  Names&Surs
//
//  Created by Ivan Kotikov on 28.01.2022.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> AllNames (const map<int, string>& Names, int year) {
    vector<string> names;
    for (const auto& i : Names) {
        if (i.first <= year && (names.empty() || names.back() != i.second)) {
            names.push_back(i.second);
        }
    }
    return names;
}

string FindNameHistory (const vector<string>& names) {
    if (names.empty()) {
        return "";
    }
    string allnames;
    for (size_t i = names.size() - 1; i >= 0; --i) {
        if (allnames.size() > 0) {
            allnames += (allnames.substr(allnames.size()-1, 1) == ",") ? " " : " (";
            allnames += names[i];
            allnames += (i != 0) ? "," : ")";
        } else allnames += names[i];
    }
    return allnames;
}

string ReturnFullName (const string& name, const string& surname) {
    if (name.size() == 0 && surname.size() == 0) {
        return "Incognito";
    } else if (name.size() == 0 && surname.size() != 0) {
        return surname + " with unknown first name";
    } else if (name.size() != 0 && surname.size() == 0) {
        return name + " with unknown last name";
    } else return name + " " + surname;
}

class Person {
public:
    Person (const string& birth_name, const string& birth_surname, int year) {
        birth_year = year;
        NameHistory[birth_year] = birth_name;
        SurnameHistory[birth_year] = birth_surname;
    }
    void ChangeFirstName(int year, const string& first_name) {
        if (year >= birth_year) {
            NameHistory[year] = first_name;
        }
    }
    void ChangeLastName(int year, const string& last_name) {
        if (year >= birth_year) {
            SurnameHistory[year] = last_name;
        }
    }
    string GetFullName(int year) const {
        if (year < birth_year) {
            return "No person";
        }
        string name;
        if (!Names(year).empty()) {
            name = Names(year).back();
        }
        string surname;
        if (!Surnames(year).empty()) {
            surname = Surnames(year).back();
        }
        return ReturnFullName(name, surname);
    }
    string GetFullNameWithHistory(int year) const {
        if (year < birth_year) {
            return "No person";
        }
        string name = FindNameHistory(Names(year));
        string surname = FindNameHistory(Surnames(year));
        return ReturnFullName(name, surname);
    }
private:
    int birth_year;
    vector<string> Names (int year) const {
        return AllNames(NameHistory, year);
    };
    vector<string> Surnames (int year) const {
        return AllNames(SurnameHistory, year);
    };
    map<int, string> NameHistory;
    map<int, string> SurnameHistory;
};
