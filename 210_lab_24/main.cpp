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

int select_goat(set<Goat>);     // Function prototypes for selction, deletion, adding, displaying & main menu
void delete_goat(set<Goat> &);
void add_goat(set<Goat> &, string [], string []);
void display_trip(set<Goat>);
int main_menu();

int main() {
    bool again = 1;    // bool varaiable which will dictate if the menu loop continues
    
    ifstream fin("name.txt");    // file of names is opened and sotred in the names array
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    
    ifstream fin1("colors.txt");    // file of colors is opened and sotred in the names array
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();
    
    set<Goat> trip;
    
    int choice = 0;    // choice varaible will take branch depending on user input
    while (again)
    {
        choice = main_menu();    // choice is assigned depening on user int input
        
        if (again)
            if (choice == 1) {    // if user selected 1, a gaot is added to the set
                add_goat(trip, colors, names);    // add_goat function call
                cout << "[Goat added]" << endl;
            }
        if (choice == 2) {    // if user selected 2, a goat will be removed
            if (trip.empty())
                cout << "List is empty" << endl;    // message if set is empty
            else
            delete_goat(trip);    // delete_goat function call
        }
        if (choice == 3) {    // if user selected 2, set is printed
            if (trip.empty())
                cout << "List is empty" << endl;   // message if set is empty
            else {
                cout << "List of goats" << endl;
                display_trip(trip);    // display_trip function call
            }
        }
        if ( choice == 4)   // if user selected 4, program ends
            again = 0;
    }

    trip.clear();    // set is cleared at end
    if (trip.empty())
        cout << "List cleared" << endl;
    
    cout << "Thanks for using the GOAT MANAGER 3001" << endl;    // departing message
    cout << "----------------------------" << endl;
    return 0;
}

int main_menu()
{
    int choice = 0;
        cout << "----------------------------" << endl;
        cout << "*** GOAT MANAGER 3001 ***" << endl;    // main menu display, pronting user to enter 1-4
        cout << "[1] Add a goat" << endl;
        cout << "[2] Delete a goat" << endl;
        cout << "[3] List goats" << endl;
        cout << "[4] Quit" << endl;
        cout << "Choice --> ";
        cin >> choice;
    
        while (choice < 1 || choice > 4) {    // validation loop to ensure user choice is in range
            cout << "Out of range. Enter 1, 2, 3, or 4" << endl;
            cout << "Choice --> ";
            cin >> choice;
        }
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
    uniform_int_distribution<int>rangeC(0, SZ_COLORS - 1);    // random numbers for the age, color, and name
    uniform_int_distribution<int>rangeN(0, SZ_NAMES - 1);
    uniform_int_distribution<int>rangeA(1, MAX_AGE);
    
    num = rangeN(randNum);    // name and color are assigned from the arrays
    name = n[num];
    num = rangeC(randNum);
    color = c[num];
    num = rangeA(randNum);    // age aggined from the random age number generated
    age = num;
    
    Goat g(name, age, color);    //Goat is constructed and added to the set via .insert
    
    trip.insert(g);
}

int select_goat(set<Goat> trip)
{
    int input = 0;
    
    display_trip(trip);    //display_trip function call to ask the user which goat to select
    cout << "----------------------------" << endl;
    cout << "Selection: ";
    cin >> input;
    
    return input;
}

void delete_goat(set<Goat> &trip)
{
    int index;
    
    cout << "Which Goat do you wish to delete?" << endl;    //user asked the user which goat to delete from the set
    
    index = select_goat(trip);
    
    while (index > trip.size()) {    // validation loop to ensure user index entry is in range
        cout << "----------------------------" << endl;
        cout << "Out of range" << endl;
        cout << "Which Goat do you wish to delete?" << endl;
        index = select_goat(trip);
    }
    
    set<Goat>::iterator it;    // iterator to navigate the list, initlized to the start of the set
    it = trip.begin();
    
    for (int i = 0; i < (index - 1); i++)    // iterator moved to index location
        it++;

    trip.erase(it);    // index erased
    
    cout << "Updated set" << endl;    // Updatd set printed
    if (trip.empty())
        cout << "[Empty]" << endl;
    else
        display_trip(trip);
}

void display_trip(set<Goat> trip)
{
    int count = 1;    // count to number each element in the set when printed
    for (Goat g : trip) {    // members of the goat object called via their get functions
        cout << "[" << count << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ") " << endl;
        count++;
    }
}
