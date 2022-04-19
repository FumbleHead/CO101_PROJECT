//Header Files
#include <iostream>
#include <fstream>  
#include <string>   
#include <stdio.h> 

using namespace std;

//Class Definition
class file 
{
    private:
        char jersey_number[50];
        char age[50];
        char first_name[50];
        char second_name[50];
        char country[50];
        char state[50];
        char team[50];
        char coach_name[50];
        int player_id;

    public:

        void input(){
			
			cout<<"\t\t\t\t\t|===========================|";
			cout<<"\n\t\t\t\t\t|ENTER THE FOLLOWING DETAILS|";
			cout<<"\n\t\t\t\t\t|===========================|";
            cout<<"\nPlayer ID: ";
        	cin>>player_id;
            cin.ignore();
            cout<<"\nTeam name: ";
            cin.getline(team,sizeof(team));
            cout<<"\nFirst Name of Player: ";
            cin>>first_name;
            cout<<"\nLast Name of Player: ";
            cin>>second_name;
            cout<<"\nAge of the player: ";
            cin>>age;
            cin.ignore();
			cout<<"\nCountry from which the player belongs: ";
            cin.getline(country,sizeof(country));
            cout<<"\nState from which the player belongs: ";
            cin.getline(state,sizeof(state));
            cout<<"\nEnter desired Jersey number: ";
            cin>>jersey_number;

        }
        void output(){
        	cout<<"\nPlayer ID: ";
            cout<<player_id; 
        	cout<<"\nTeam name: ";
            puts(team);
            cout<<"\nFirst Name of Player: ";
        	puts(first_name);
            cout<<"\nLast Name of Player: ";
            puts(second_name);
            cout<<"\nAge of the player: ";
            puts(age);           
			cout<<"\nCountry from which the player belongs: ";
            puts(country);
            cout<<"\nState from which the player belongs: ";
            puts(state);            
            cout<<"\nEnter desired Jersey number: ";
            puts(jersey_number);            	
		}
        
        //char* is a function used to return character arrays.
        int ret_player_id(){
            return player_id;
        }

};

//Function to write data into the file.
void write_record()
{
 ofstream outFile;
 outFile.open("Records.dat", ios::binary | ios::app);
 file obj;
 obj.input();

 outFile.write((char*)&obj, sizeof(obj));
 outFile.close();
}


//Function to show all the records stored in the file.
void display()
{
 ifstream inFile;
 inFile.open("Records.dat", ios::binary);
 file obj;

 while(inFile.read((char*)&obj, sizeof(obj)))
 {
 obj.output();
 }

 inFile.close();
}   

//Function to show selective records
void search()
{
 ifstream inFile;
 int search;
 cout<<"Enter the ID of player whose record is to be displayed: ";
 cin>>search;
 inFile.open("Records.dat", ios::binary);

 file obj;
 while(inFile.read((char*)&obj, sizeof(obj)))
 {
 if(obj.ret_player_id() == search)
 {
 obj.output();
 }
 }

 inFile.close();
} 

//Function to delete a record 
void delete_record()
{
 file obj;
 ifstream inFile;
 int search;
 cout<<"Enter ID of player whose record is to be deleted: ";
 cin>>search;
 inFile.open("Records.dat", ios::binary);
 ofstream outFile;
 outFile.open("temp.dat", ios::out | ios::binary);

 while(inFile.read((char*)&obj, sizeof(obj)))
 {
 if(obj.ret_player_id() != search)
 {
 outFile.write((char*)&obj, sizeof(obj));
 }
 }
 inFile.close();
 outFile.close();

 remove("Records.dat");
 rename("temp.dat", "Records.dat");
}

//Function to modify records
void modify_record()
{
 fstream file1;
 file1.open("Records.dat",ios::in | ios::out);
 file obj;
 int search;
 cout<<"Enter ID of player whose record is to be modified: ";
 cin>>search;
 while(file1.read((char*)&obj,sizeof(obj)))
 {
 if(obj.ret_player_id() == search)
 {
 cout << "\nEnter the new details of student\n";
 obj.input();

 long long int  pos = -1 * sizeof(obj);
 file1.seekp(pos, ios::cur);
 file1.write((char*)&obj, sizeof(obj));
 }
 }

 file1.close();
}


//Function Prototypes 
void get_teams();
void get_players();

//Main function
int main(){ 

    while(1){
        int choice;
        cout<<"\n\t\t\t\t|===================== NBA ======================|";
        cout<<"\n\t\t\t\t|1.Teams                                         |";
        cout<<"\n\t\t\t\t|2.Top 10 players                                |";
        cout<<"\n\t\t\t\t|3.Add a new Record                              |";
        cout<<"\n\t\t\t\t|4.Show all Records                              |";
        cout<<"\n\t\t\t\t|5.Show  a specific record                       |";
        cout<<"\n\t\t\t\t|6.Delete a record                               |";
        cout<<"\n\t\t\t\t|7.Modify a record                               |";
        cout<<"\n\t\t\t\t|8.Exit the program                              |";
        cout<<"\n\t\t\t\t|================================================|";

        cout<<"\n\n\t\t\t\tEnter your choice: ";
        cin>>choice;

        switch(choice)
		{
			case 1: get_teams(); 
                    break;
            case 2: get_players(); 
                    break;
			case 3: write_record(); 
                    break;
            case 4: display();
                    break;
            case 5: search();
                    break;
            case 6: delete_record();
            		break;
            case 7: modify_record();
            		break;
            case 8: cout<<"Exiting from program...\n";
                     exit(0);  //Closes the program
            default: cout<<"Wrong Choice. Please try again\n";
                     break;

        }
   }

}

//Function to open the file containing team names
void get_teams()
{
    ifstream tm;
    char team[1024];
    tm.open("Teams.txt");
    while(tm)
    {
        tm.getline(team, 1024 );
        cout<<team<<endl;
    }
    tm.close();

}

//Function to open the file containing top 10 players
void get_players()
{
    ifstream pl;
    char player[1024];
    pl.open("Players.txt");
    while(pl)
    {
        pl.getline(player, 1024 );
        cout<<player<<endl;
    }
    pl.close();

}
