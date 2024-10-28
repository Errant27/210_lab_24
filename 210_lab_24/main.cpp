// 210 | Lab 24 | Neil Orton
// IDE used: Xcode
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat>);
void delete_goat(set<Goat> &);
void add_goat(set<Goat> &, string [], string []);
void display_trip(set<Goat>);
int main_menu();

int main() {
    bool again = 1;
    
    ifstream fin("name.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();
    
    set<Goat> trip;
    
    int c = 0;
    while (again)
    {
        c = main_menu();
        
        if (again)
            if (c == 1) {
                add_goat(trip, colors, names);
                cout << "[Goat added]" << endl;
            }
        if (c == 2) {
            if (trip.empty())
                cout << "List is empty" << endl;
            else
            delete_goat(trip);
        }
        if (c== 3) {
            if (trip.empty())
                cout << "List is empty" << endl;
            else {
                cout << "List of goats" << endl;
                display_trip(trip);
            }
        }
        if ( c == 4)
            again = 0;
    }

    trip.clear();
    if (trip.empty())
        cout << "List cleared" << endl;
    
    cout << "Thanks for using the GOAT MANAGER 3001" << endl;
    cout << "----------------------------" << endl;
    return 0;
}

int main_menu()
{
    int choice = 0;
        cout << "----------------------------" << endl;
        cout << "*** GOAT MANAGER 3001 ***" << endl;
        cout << "[1] Add a goat" << endl;
        cout << "[2] Delete a goat" << endl;
        cout << "[3] List goats" << endl;
        cout << "[4] Quit" << endl;
        cout << "Choice --> ";
        cin >> choice;
        cout << "----------------------------" << endl;
    
    return choice;
}

void add_goat(set<Goat> &trip, string c[], string n[])
{
    string color;
    string name;
    int age;
    int num;
    
    
    random_device randNum;
    uniform_int_distribution<int>rangeC(0, 24);
    uniform_int_distribution<int>rangeN(0, 199);
    uniform_int_distribution<int>rangeA(1, 20);
    
    num = rangeN(randNum);
    name = n[num];
    num = rangeC(randNum);
    color = c[num];
    num = rangeA(randNum);
    age = num;
    
    Goat g(name, age, color);
    
    trip.insert(g);
}

int select_goat(set<Goat> trip)
{
    int wi = 0;
    
    display_trip(trip);
    cout << "----------------------------" << endl;
    cout << "Selection: ";
    cin >> wi;
    
    return wi;
}

void delete_goat(set<Goat> &trip)
{
    int index;
    
    cout << "Which Goat do you wish to delete?" << endl;
    
    index = select_goat(trip);
    
    while (index > trip.size()) {
        cout << "----------------------------" << endl;
        cout << "Out of range" << endl;
        cout << "Which Goat do you wish to delete?" << endl;
        index = select_goat(trip);
    }
    
    set<Goat>::iterator it;
    
    it = trip.begin();
    
    for (int i = 0; i < (index - 1); i++)
        it++;

    trip.erase(it);
    
    cout << "Updated list" << endl;
    if (trip.empty())
        cout << "[Empty]" << endl;
    else
        display_trip(trip);
}

void display_trip(set<Goat> trip)
{
    int count = 1;
    for (Goat g : trip) {
        cout << "[" << count << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ") " << endl;
        count++;
    }
}
