#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

struct dorm
{
    string students[4];
    int num_beds;
    int num_chairs;
    int num_tables;
    int num_lockers;

    int dorm_num;
    dorm * next;
    dorm * prev;
};

int max_room_num = 70;
dorm *first = NULL;

void assign_dorm()
{
    
    dorm *new_dorm = new dorm;
    for (int i = 0; i < 4; i++)
    {
        cout<<i+1<<" Enter student name: ";
        cin>>new_dorm->students[i];
    }
    cout<<"Enter the number of beds in the dorm: ";
    cin>>new_dorm->num_beds;
    cout<<"Enter the number of chairs in the dorm: ";
    cin>>new_dorm->num_chairs;
    cout<<"Enter the number of tables in the dorm: ";
    cin>>new_dorm->num_tables;
    cout<<"Enter the number of lockers in the dorm: ";
    cin>>new_dorm->num_lockers;

    if (first == NULL)
    {
        new_dorm->dorm_num = 1;
        new_dorm->next = NULL;
        new_dorm->prev = NULL;
        first = new_dorm;
        cout<<endl<<"success"<<endl;
    }
    else
    {
        dorm *temp = first;
        while(temp->next != NULL)
        {
            temp = temp->next;
            cout<<temp->dorm_num<<endl;
        }
        temp->next = new_dorm;
        new_dorm->dorm_num = temp->dorm_num + 1;
        new_dorm->prev = temp;
        new_dorm->next = NULL;
        cout<<endl<<"Assignment successful!!"<<endl;
    }

}

void get_dorm_info()
{
    int room;
    cout<<"Enter the Room number: ";
    cin>>room;
    dorm * temp = first;
    bool found = false;
    while(temp != NULL && !found)
    {
        if(temp->dorm_num == room)
        {
            cout << "Students:" << endl;
            for(int k = 0; k < 4; k++){
                cout << temp->students[k] << endl;
            }
            cout << "Beds: " << temp->num_beds << endl;
            cout << "Chairs: " << temp->num_chairs << endl;
            cout << "Tables: " << temp->num_tables << endl;
            cout << "Lockers: " << temp->num_lockers << endl;
            found = true;
        }
        else
        {
            temp = temp->next;
        }
    }
    if(!found)
    {
        cout<<"Room not found."<<endl;
    }
}

void edit_dorm_info()
{
    int room;
    cout<<"Enter the Room number: ";
    cin>>room;
    dorm *temp = first;
    bool found = false;
    while(temp != NULL && !found)
    {
        if(temp->dorm_num == room)
        {
            for (int i = 0; i < 4; i++)
            {
                cout<<i+1<<" Enter student name: ";
                cin>>temp->students[i];
            }
            cout<<"Enter the number of beds in the dorm: ";
            cin>>temp->num_beds;
            cout<<"Enter the number of chairs in the dorm: ";
            cin>>temp->num_chairs;
            cout<<"Enter the number of tables in the dorm: ";
            cin>>temp->num_tables;
            cout<<"Enter the number of lockers in the dorm: ";
            cin>>temp->num_lockers;
            found = true;
        }
        else
        {
            temp = temp->next;
        }
    }
    if(!found)
    {
        cout<<"Room not found."<<endl;
    }
}

void display()
{
    dorm * temp = first;
    while(temp != NULL)
    {
        cout<<temp->dorm_num<<endl;
        temp = temp->next;
    }
}
int main()
{
    do
    {
        cout<<"============Main Menu========="<<endl;
        cout<<"|    1 Assign New dorm       |"<<endl;
        cout<<"|    2 Get dorm info         |"<<endl;
        cout<<"|    3 Edit dorn Info        |"<<endl;
        cout<<"|    4 Display all dorm info |"<<endl;
        int opt;
        cout<<"enter your option: ";
        cin>>opt;
        switch(opt)
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
        default:
            cout<<"please enter a valid input"<<endl;
            break;
        }
    }
    while(true);

    return 0;
}
