#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

struct student
{
    string name;
    string id;
    string department;
};

void to_json(json& j, const student& s) {
    j = json{{"name", s.name}, {"id", s.id}, {"department", s.department}};
}

void from_json(const json& j, student& s) {
    j.at("name").get_to(s.name);
    j.at("id").get_to(s.id);
    j.at("department").get_to(s.department);
}

struct dorm
{
    student students[4];
    int num_beds;
    int num_chairs;
    int num_tables;
    int num_lockers;

    int dorm_num;
    dorm *next;
    dorm *prev;
};
void to_json(json& j, const dorm& d) {
    j = json{
        {"students", json::array()},
        {"num_beds", d.num_beds},
        {"num_chairs", d.num_chairs},
        {"num_tables", d.num_tables},
        {"num_lockers", d.num_lockers},
        {"dorm_num", d.dorm_num}
    };
    for (int i = 0; i < 4; ++i) {
        j["students"].push_back(d.students[i]);
    }
}

void from_json(const json& j, dorm& d) {
    j.at("num_beds").get_to(d.num_beds);
    j.at("num_chairs").get_to(d.num_chairs);
    j.at("num_tables").get_to(d.num_tables);
    j.at("num_lockers").get_to(d.num_lockers);
    j.at("dorm_num").get_to(d.dorm_num);
    auto students_json = j.at("students");
    for (int i = 0; i < 4; ++i) {
        students_json[i].get_to(d.students[i]);
    }
}
int max_room_num = 70;
dorm *first = NULL;

void assign_dorm()
{

    dorm *new_dorm = new dorm;

    for (int i = 0; i < 4; i++)
    {
        cout << "\033[2J\033[H";
        cout << i + 1 << endl;
        student *new_stud = new student;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, new_stud->name);
        cout << "Enter student id: ";
        cin.ignore();
        getline(cin, new_stud->id);
        cout << "Enter student department: ";
        cin.ignore();
        getline(cin, new_stud->department);
        new_dorm->students[i] = *new_stud;
        cout << "\033[2J\033[H";
    }
    cout << "Enter the number of beds in the dorm: ";
    cin >> new_dorm->num_beds;
    cout << "Enter the number of chairs in the dorm: ";
    cin >> new_dorm->num_chairs;
    cout << "Enter the number of tables in the dorm: ";
    cin >> new_dorm->num_tables;
    cout << "Enter the number of lockers in the dorm: ";
    cin >> new_dorm->num_lockers;

    if (first == NULL)
    {
        new_dorm->dorm_num = 1;
        new_dorm->next = NULL;
        new_dorm->prev = NULL;
        first = new_dorm;
        cout << endl
             << "Assignment successful!!" << endl;
    }
    else
    {
        dorm *temp = first;
        while (temp->next != NULL)
        {
            temp = temp->next;
            cout << temp->dorm_num << endl;
        }
        if(temp->dorm_num == max_room_num){
            cout<<"Assignment fiaild because all rooms were assigned";
        }
        else{
                
            temp->next = new_dorm;
            new_dorm->dorm_num = temp->dorm_num + 1;
            new_dorm->prev = temp;
            new_dorm->next = NULL;
            cout << endl
                << "Assignment successful!!" << endl;
        }
    }
}

void get_dorm_info()
{
    int room;
    cout << "Enter the Room number: ";
    cin >> room;
    dorm *temp = first;
    bool found = false;
    while (temp != NULL && !found)
    {
        if (temp->dorm_num == room)
        {
            cout << "\n=========================================" << endl;
            cout << "           DORM INFORMATION" << endl;
            cout << "=========================================" << endl;
            cout << "Dorm Number: " << temp->dorm_num << endl;
            cout << "\nStudents Assigned:" << endl;
            cout << "-----------------------------------------" << endl;
            cout << left << setw(25) << "NAME" << setw(20) << "ID" << "DEPARTMENT" << endl;
            cout << "-----------------------------------------" << endl;
            for (int k = 0; k < 4; k++)
            {
                student stud = temp->students[k];
                if (!stud.name.empty()) {  // Only show if student is assigned
                    cout<<k+1<<", " << left << setw(25) << stud.name << setw(20) << stud.id << stud.department << endl;
                }
            }
            cout << "\nFacilities:" << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Beds: " << temp->num_beds << endl;
            cout << "Chairs: " << temp->num_chairs << endl;
            cout << "Tables: " << temp->num_tables << endl;
            cout << "Lockers: " << temp->num_lockers << endl;
            cout << "=========================================\n" << endl;
            found = true;
        }
        else
        {
            temp = temp->next;
        }
    }
    if (!found)
    {
        cout << "Room not found." << endl;
    }
}

void edit_dorm_info()
{
    int room;
    cout << "Enter the Room number: ";
    cin >> room;
    dorm *temp = first;
    bool found = false;
    while (temp != NULL && !found)
    {
        if (temp->dorm_num == room)
        {
            for (int i = 0; i < 4; i++)
            {
                cout << "\033[2J\033[H";
                cout << i + 1 << endl;
                student *new_stud = new student;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, new_stud->name);
                cout << "Enter student id: ";
                cin.ignore();
                getline(cin, new_stud->id);
                cout << "Enter student department: ";
                cin.ignore();
                getline(cin, new_stud->department);
                temp->students[i] = *new_stud;
                cout << "\033[2J\033[H";
            }
            cout << "Enter the number of beds in the dorm: ";
            cin >> temp->num_beds;
            cout << "Enter the number of chairs in the dorm: ";
            cin >> temp->num_chairs;
            cout << "Enter the number of tables in the dorm: ";
            cin >> temp->num_tables;
            cout << "Enter the number of lockers in the dorm: ";
            cin >> temp->num_lockers;
            found = true;
        }
        else
        {
            temp = temp->next;
        }
    }
    if (!found)
    {
        cout << "Room not found." << endl;
    }
}

void display()
{
    dorm *temp = first;
    if (temp == NULL) {
        cout << "No dorms assigned yet." << endl;
        return;
    }
    cout << "\n=========================================" << endl;
    cout << "         ALL DORM INFORMATION" << endl;
    cout << "=========================================\n" << endl;
    while (temp != NULL)
    {
        cout << "-----------------------------------------" << endl;
        cout << "Dorm Number: " << temp->dorm_num << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Students Assigned:" << endl;
        cout << left << setw(25) << "NAME" << setw(20) << "ID" << "DEPARTMENT" << endl;
        cout << string(45, '-') << endl;
        for (int k = 0; k < 4; k++)
        {
            student stud = temp->students[k];
            if (!stud.name.empty()) {  // Only show if student is assigned
                cout<<k+1<<", "<< left << setw(25) << stud.name << setw(20) << stud.id << stud.department << endl;
            }
        }
        cout << "\nFacilities:" << endl;
        cout << "Beds: " << temp->num_beds << endl;
        cout << "Chairs: " << temp->num_chairs << endl;
        cout << "Tables: " << temp->num_tables << endl;
        cout << "Lockers: " << temp->num_lockers << endl;
        cout << "=================================================================";
        cout << "\n";
        temp = temp->next;
    }
    cout << "=========================================\n" << endl;
}

void check_assigned(){
    int num;
    cout<<"Enter the room number to check: ";
    cin>>num;
    dorm *temp = first;
    while (temp != NULL)
    {
        if(temp->dorm_num == num){
            cout<<"The room has already been assigned";
        }
        else{
            temp = temp->next;
        }
    }
    
}

void save_to_json() {
    json j = json::array();
    dorm *temp = first;
    while (temp != NULL) {
        j.push_back(*temp);
        temp = temp->next;
    }
    ofstream file("dorms.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        cout << "Data saved to dorms.json" << endl;
    } else {
        cout << "Error opening file for saving." << endl;
    }
}

void load_from_json() {
    ifstream file("dorms.json");
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();
        // Clear existing list
        dorm *temp = first;
        while (temp != NULL) {
            dorm *next = temp->next;
            delete temp;
            temp = next;
        }
        first = NULL;
        // Load from json
        for (auto& dorm_json : j) {
            dorm *new_dorm = new dorm;
            dorm_json.get_to(*new_dorm);
            new_dorm->next = NULL;
            new_dorm->prev = NULL;
            if (first == NULL) {
                first = new_dorm;
            } else {
                dorm *t = first;
                while (t->next != NULL) {
                    t = t->next;
                }
                t->next = new_dorm;
                new_dorm->prev = t;
            }
        }
        cout << "Data loaded from dorms.json" << endl;
    } else {
        cout << "Error opening file for loading." << endl;
    }
}

int main()
{
    cout << "\033[2J\033[H";
    load_from_json();
    do
    {
        cout << "|===============Main Menu==============|" << endl;
        cout << "|    1 Assign New dorm                 |" << endl;
        cout << "|    2 Get dorm info                   |" << endl;
        cout << "|    3 Edit dorm Info                  |" << endl;
        cout << "|    4 Display all dorm info           |" << endl;
        cout << "|    5 Chech if the dorm is assgned    |" << endl;
        cout << "|    6 Clear screen                    |" << endl;
        cout << "|    7 Exit                            |" << endl;
        cout << "|======================================|" << endl;
        int opt;
        cout << "enter your option: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
            assign_dorm();
            break;
        case 2:
            get_dorm_info();
            break;
        case 3:
            edit_dorm_info();
            break;
        case 4:
            display();
            break;
        case 5:
            check_assigned();
            break;
        case 6:
            cout << "\033[2J\033[H";
        case 7:
            save_to_json();
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "please enter a valid input" << endl;
            break;
        }
    } while (true);

    return 0;
}
