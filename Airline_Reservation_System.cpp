#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef __unix__
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <unistd.h>
#define OS 0
#define CLEAR_SCREEN "clear"

#elif defined(_WIN32) || defined(WIN32)
#include <conio.h>
#include <Windows.h>
#define OS 1
#define CLEAR_SCREEN "cls" // change badges
#endif

using namespace std;

time_t now = time(0);
string dt(ctime(&now));
const int NumofFlights = 50;
const int MAIN = 0;
const int ADMIN_CHECK = 1;
const int ADMIN_DISPLAY = 2;
const int USER = 3;
const int LOGIN = 4;
const int SIGNUP = 5;
const int PASSENGER = 6;
const int SHOW_ADDED_FLIGHTS = 7;
const int SHOW_NEW_TICKET = 8;
const int SHOW_ALL_TICKETS = 9;
const int EXIT = -1;
short arr_of_width[8] = {};
short arr_of_width_for_tickets[6] = {};
int Num_of_ticket = 0;
int Accounts_Used = 0;
int Entered_Flights, Deleted_Flights = 0, Updated_Flight, Start_Flights = 0;
string AdminPassword = "3";
/*
string input_password(){
    cout << "Password : ";
    string secure_password;
    for(char c=getch(); c != '\r' ;c=getch()){
        secure_password.append(to_string(c));
    }
    return secure_password;
}
*/

//structs
struct flight
{
    char flightnumber[10];
    int availableSeats;
    int day, month, year;
    string departure, arrival;
    float departureTime, arrivalTime;

}f1[NumofFlights] = {};
struct User
{
    string username, password;
    string Passenger_ID, name, address, phone_number;
}users[50] = {};
//search function
struct wanted
{
    User Existing_User; // save information to the user he log in now &and call it when the user login again 
    int x; // nuum of flight that reseavd
    int selected_flights[51] = {}; // save flight that look like and take the flight the user choise 
}wanted1 = {};
struct tickets
{
    string index_flightnum;
    string reservation_date;
    int ticketnum; 
    string departure_city_ticket, arrival_city_ticket; // save information to show it to user
    //is the same of the normal passenger id
    string pasngr_id_tkt;
} tickets1[50] = {};

//Tecnicals
void os_sleep(int milliseconds) {
    cout << flush;
    if (OS) {
        _sleep(milliseconds); // for win
    }
    else {
        this_thread::sleep_for(chrono::milliseconds(milliseconds)); // for lunex
    }
}
void loading(string s) {
    cout << endl << s << ' ';
    for (int i = 0; i < 10; i++) {
        os_sleep(200);
        cout << '.';
    }
    cout << endl;
}
void done(string s) {
    int length = s.length();
    cout << "\n\t\t" << string(length, '-') << "\n\t\t" << s << "\n\t\t" << string(length, '-') << endl;
    os_sleep(2000);
}
void error(string s) {
    int length = s.length();
    cout << "\n\t\t" << string(length, '!') << "\n\t\t" << s << "\n\t\t" << string(length, '!') << endl;
    os_sleep(2000);
}
void Invalid() {
    string s = "# You entered an invalid input .. Please try again! #";
    int length = s.length();
    cout << "\n\t\t" << string(length, '#') << "\n\t\t" << s << "\n\t\t" << string(length, '#') << endl;
    os_sleep(3000);
}
short string_output(string s) {
    int length = s.length();
    cout << setw(length + 1) << s << '|';
    return length + 1;
}
bool compareStrings(string s1, string s2)
{
    int compare = s1.compare(s2);
    bool equal;
    if (compare == 0) { equal = true; }
    else if (compare != 0) { equal = false; }
    return equal;
}

//search task
void display_selected_flights(int y[]) {
    string date;
    cout << "\n\n\t\t\t\t\t" << string(36, ' ') << "----------This is available flight schedule----------\n";
    cout << "\t\t\t\t\t" << string(36, ' ') << "================================================\n\n";
    cout << left;
    cout << "\t\t\t\t\t" << '|';
    arr_of_width[0] = string_output(" Index");
    arr_of_width[1] = string_output(" Flight Number");
    arr_of_width[2] = string_output(" Available Seats");
    arr_of_width[3] = string_output(" Flight Date");
    arr_of_width[4] = string_output(" Departure City");
    arr_of_width[5] = string_output(" Arrival City");
    arr_of_width[6] = string_output(" Departure Time");
    arr_of_width[7] = string_output(" Arrival Time");
    cout << endl;
    cout << "\t\t\t\t\t" << '|';
    for (int i = 0; i < 8; i++) {
        cout << string(arr_of_width[i], '-') << '|';
    }
    cout << endl;
    int numOFselectedflight = wanted1.selected_flights [51] ;
    for (int i = 0; i < numOFselectedflight; i++)
    {
        date = to_string(f1[wanted1.selected_flights[i]].day) + "/" + to_string(f1[wanted1.selected_flights[i]].month) + "/" + to_string(f1[wanted1.selected_flights[i]].year);
        cout << "\t\t\t\t\t" << '|'
            << setw(arr_of_width[0]) << i + 1 << '|' << setw(arr_of_width[1]) << f1[wanted1.selected_flights[i]].flightnumber << '|' << setw(arr_of_width[2]) << f1[wanted1.selected_flights[i]].availableSeats << '|'
            << setw(arr_of_width[3]) << date << '|'
            << setw(arr_of_width[4]) << f1[wanted1.selected_flights[i]].departure << '|' << setw(arr_of_width[5]) << f1[wanted1.selected_flights[i]].arrival << '|'
            << setw(arr_of_width[6]) << f1[wanted1.selected_flights[i]].departureTime << '|' << setw(arr_of_width[7]) << f1[wanted1.selected_flights[i]].arrivalTime << '|' << "\n";
    }
}
int search()
{
    string choice;
    string to, from;
    int counter_search, c;
above1:
    counter_search = 0;
    cout << "\nEnter Your Itenerary: \n" << string(22, '-') << endl;
    cout << "From : ";
    cin >> from;
    cout << "To : ";
    cin >> to;
    loading("Searching For Flights");
    for (int i = 0; i < Start_Flights + Entered_Flights; i++)
    {
        if (f1[i].departure == from && f1[i].arrival == to && f1[i].availableSeats > 0)
        {
            wanted1.selected_flights[counter_search] = i;
            counter_search++;
        }
    }
    wanted1.selected_flights[51] = counter_search;
    if (counter_search > 0)
    {

        display_selected_flights(wanted1.selected_flights);
        cout << "Enter Index of flight you want to book : ";
        cin >> c;
        wanted1.x = wanted1.selected_flights[c - 1];
        for (int i = 0; i < Num_of_ticket; i++)
        {
            if (f1[wanted1.x].flightnumber == tickets1[i].index_flightnum)
            {
                error("!! You already booked this flight !!");
                cout << endl << "Do you want to continue?..(Y/N)" << endl;
                cin >> choice;
                if (compareStrings(choice, "y") || compareStrings(choice, "Y")) { goto above1; }
                else { return PASSENGER; }
            }
        }
        done("Flight Choosed!");
        return SHOW_NEW_TICKET;
    }
    else
    {
        error("!! Invalid Flight !!");
        cout << endl << "Do you want to continue?..(Y/N)" << endl;
        cin >> choice;
        if (compareStrings(choice, "y") || compareStrings(choice, "Y"))
        {
            goto above1;
        }
        else
        {
            return PASSENGER;
        }
    }
}

//flight task
void displayflight(flight f1[NumofFlights]) {
    string date;
    cout << "\n\n\t\t\t\t\t" << string(36, ' ') << "----------This is full flight schedule----------\n";
    cout << "\t\t\t\t\t" << string(36, ' ') << "================================================\n\n";
    cout << left;
    cout << "\t\t\t\t\t" << '|';
    arr_of_width[0] = string_output(" Index");
    arr_of_width[1] = string_output(" Flight Number");
    arr_of_width[2] = string_output(" Available Seats");
    arr_of_width[3] = string_output(" Flight Date");
    arr_of_width[4] = string_output(" Departure City");
    arr_of_width[5] = string_output(" Arrival City");
    arr_of_width[6] = string_output(" Departure Time");
    arr_of_width[7] = string_output(" Arrival Time");
    cout << endl;
    cout << "\t\t\t\t\t" << '|';
    for (int i = 0; i < 8; i++) {
        cout << string(arr_of_width[i], '-') << '|';
    }
    cout << endl;
    for (int i = 0; i < Start_Flights; i++)
    {
        date = to_string(f1[i].day) + "/" + to_string(f1[i].month) + "/" + to_string(f1[i].year);
        cout << "\t\t\t\t\t" << '|'
            << setw(arr_of_width[0]) << i + 1 << '|' 
            << setw(arr_of_width[1]) << f1[i].flightnumber << '|' 
            << setw(arr_of_width[2]) << f1[i].availableSeats << '|'
            << setw(arr_of_width[3]) << date << '|'
            << setw(arr_of_width[4]) << f1[i].departure << '|' 
            << setw(arr_of_width[5]) << f1[i].arrival << '|'
            << setw(arr_of_width[6]) << f1[i].departureTime << '|' 
            << setw(arr_of_width[7]) << f1[i].arrivalTime << '|' << "\n";
    }
}
int addflight(flight f1[NumofFlights])
{
    cout << "\nEnter number of flights you want to add:" << endl;
    cin >> Entered_Flights;
    for (int i = Start_Flights; i < Start_Flights + Entered_Flights; i++)
    {
        cout << "\nEnter flight number : " << endl;
        cin >> f1[i].flightnumber;
        cout << "Enter available Seats : " << endl;
        cin >> f1[i].availableSeats;
        cout << "Enter flight date : " << endl;
        cin >> f1[i].day >> f1[i].month >> f1[i].year;
        cout << "Enter your departure city : " << endl;
        cin >> f1[i].departure;
        cout << "Enter your arrival city : " << endl;
        cin >> f1[i].arrival;
        cout << "Enter your departureTime : " << endl;
        cin >> f1[i].departureTime;
        cout << "Enter your arrivalTime : " << endl;
        cin >> f1[i].arrivalTime;
        cout << string(22, '-') << "\nFlight Added Succsefully !\n" << string(22, '-') << endl;
    }
    Start_Flights += Entered_Flights;
    loading("Adding Flights");
    done("Flights Added Succesfully!");
    return ADMIN_DISPLAY;
}
int deleteflight(flight f1[NumofFlights])
{
    displayflight(f1);
try_again:
    cout << "Enter index of flight you want to delete : ";
    int z;
    bool loop = false;
    cin >> z;
    if (z <= 0) { Invalid(); goto try_again; }
    int i;
    // z-1 is the number must be deleted 
    for (i = z; i <= Start_Flights; i++)
    {
        loop = true;
        f1[i - 1] = f1[i];
    }
    if (!loop) { Invalid(); goto try_again; }
    Start_Flights--;
    loading("Deleting Flights");
    done("Flight Deleted Succesfully!");
    return SHOW_ADDED_FLIGHTS;
}
int updateflight(flight f1[NumofFlights])
{
    displayflight(f1);
    cout << "\n\nEnter index of flight you want to update:" << endl;
    int Updated_Flight; cin >> Updated_Flight;
    cout << "\n1- change flight number" << endl;
    cout << "2- change flight available seats" << endl;
    cout << "3- change flight date" << endl;
    cout << "4- change flight departure city" << endl;
    cout << "5- change flight arrival city" << endl;
    cout << "6- change flight departure time" << endl;
    cout << "7- change flight arrival time" << endl << endl;
try_again:
    cout << "Your Choice : ";
    string choice;
    cin >> choice;
    if (compareStrings(choice, "1")) {
        cout << "Enter new flight number : ";
        cin >> f1[Updated_Flight - 1].flightnumber;
    }
    else if (compareStrings(choice, "2")) {
        cout << "Enter new flight available seats : ";
        cin >> f1[Updated_Flight - 1].availableSeats;
    }
    else if (compareStrings(choice, "3")) {
        cout << "Enter new flight date (day) : ";
        cin >> f1[Updated_Flight - 1].day;
        cout << "Enter new flight date (month) : ";
        cin >> f1[Updated_Flight - 1].month;
        cout << "Enter new flight date (year) : ";
        cin >> f1[Updated_Flight - 1].year;
    }
    else if (compareStrings(choice, "4")) {
        cout << "Enter new flight arrival city : ";
        cin >> f1[Updated_Flight - 1].departure;
    }
    else if (compareStrings(choice, "5")) {
        cout << "Enter new flight arrival city : ";
        cin >> f1[Updated_Flight - 1].arrival;
    }
    else if (compareStrings(choice, "6")) {
        cout << "Enter new flight departure time : ";
        cin >> f1[Updated_Flight - 1].departureTime;
    }
    else if (compareStrings(choice, "7")) {
        cout << "Enter new flight arrival time : ";
        cin >> f1[Updated_Flight - 1].arrivalTime;
    }
    else { Invalid(); goto try_again; }
    loading("Updating Flights");
    done("Flight Updated Succesfully!");
    displayflight(f1);
    return SHOW_ADDED_FLIGHTS;
}

//ticket task
void display_all_tickets(tickets tickets1[50]) {
    cout << "\n\n\t\t" << string(36, ' ') << "----------This is your reservation log----------\n";
    cout << "\t\t" << string(36, ' ') << string(48, '=');
    cout << "\n\n\t\t" << string(36, ' ') << "Your Passenger ID : " << wanted1.Existing_User.Passenger_ID << endl;
    cout << "\t\t" << string(36, ' ') << string(48, '=') << "\n\n";
    cout << left;
    cout << "\t\t\t\t\t" << '|';
    arr_of_width_for_tickets[0] = string_output(" Index");
    arr_of_width_for_tickets[1] = string_output(" Flight Number");
    arr_of_width_for_tickets[2] = string_output(" Ticket Number");
    arr_of_width_for_tickets[3] = string_output(" Departure City");
    arr_of_width_for_tickets[4] = string_output(" Arrival City");
    arr_of_width_for_tickets[5] = string_output("     Reservation Date    ");
    cout << endl;
    cout << "\t\t\t\t\t" << '|';
    for (int i = 0; i < 6; i++) {
        cout << string(arr_of_width_for_tickets[i], '-') << '|';
    }
    cout << endl;

    int count = 0;
    for (int i = 0; i < Num_of_ticket; i++)
    {
        if (wanted1.Existing_User.Passenger_ID == tickets1[i].pasngr_id_tkt)
        {
            count++;
            cout << "\t\t\t\t\t "
                << setw(arr_of_width_for_tickets[0]) << count << '|'
                << setw(arr_of_width_for_tickets[1]) << tickets1[i].index_flightnum << '|'
                << setw(arr_of_width_for_tickets[2]) << tickets1[i].ticketnum << '|'
                << setw(arr_of_width_for_tickets[3]) << tickets1[i].departure_city_ticket << '|'
                << setw(arr_of_width_for_tickets[4]) << tickets1[i].arrival_city_ticket << '|'
                << setw(arr_of_width_for_tickets[5]) << tickets1[i].reservation_date;
        }
    }
}
void save_Ticket(tickets tickets1[50]) // save information to search
{
    tickets1[Num_of_ticket].index_flightnum = f1[wanted1.x].flightnumber;
    tickets1[Num_of_ticket].pasngr_id_tkt = wanted1.Existing_User.Passenger_ID;
    tickets1[Num_of_ticket].reservation_date = dt;
    tickets1[Num_of_ticket].ticketnum = rand() % 1000000 + 100000;
    tickets1[Num_of_ticket].departure_city_ticket = f1[wanted1.x].departure;
    tickets1[Num_of_ticket].arrival_city_ticket = f1[wanted1.x].arrival;
}
int modify_ticket(tickets tickets1[50]) {
    display_all_tickets(tickets1);
    int z;
    bool loop = false;
try_again:
    cout << "Enter Index of ticket you want to modify : ";
    cin >> z;
    if (z <= 0) { Invalid(); goto try_again; }
    // z-1 is the number must be deleted 
    for (int i = z; i <= Num_of_ticket; i++)
    {
        loop = true;
        tickets1[i - 1] = tickets1[i];
    }
    if (!loop) { Invalid(); goto try_again; }
    Num_of_ticket--;
    loading("Modifying Ticket");
    return search();
}
int cancel_ticket(tickets tickets1[50]) {
    display_all_tickets(tickets1);
    int z;
    bool loop = false;
try_again:
    cout << "Enter Index of ticket you want to cancel : ";
    cin >> z;
    if (z <= 0) { Invalid(); goto try_again; }
    // z-1 is the number must be deleted 
    for (int i = z; i <= Num_of_ticket; i++)
    {
        loop = true;
        tickets1[i - 1] = tickets1[i];
    }
    if (!loop) { Invalid(); goto try_again; }
    Num_of_ticket--;
    loading("Canceling Ticket");
    done("Ticket Successfuly Canceled!");
    return SHOW_ALL_TICKETS;
}
void display_new_ticket(tickets tickets1[50])
{
    // show the user that he now will see his ticket
    cout << left;
    cout << "\n\n\t\t\t\t\t\t\t " << string(22, '*') << "\n";
    cout << "\t\t\t\t\t\t\t Welcome to your ticket\n ";
    cout << "\t\t\t\t\t\t\t " << string(22, '*') << "\n";
    cout << "\n\t\t" << string(18, '@') << string(100, '=') << string(18, '@') << "\n";
    cout << "\n\n\t\t Ticket Number: " << setw(16) << tickets1[Num_of_ticket].ticketnum;
    cout << "Passenger ID: " << setw(16) << tickets1[Num_of_ticket].pasngr_id_tkt;
    cout << "Flight Number: " << setw(16) << tickets1[Num_of_ticket].index_flightnum;
    cout << "Reservation Date: " << setw(26) << tickets1[Num_of_ticket].reservation_date;
    cout << "\n\t\t" << string(18, '@') << string(100, '=') << string(18, '@') << "\n";
}

// login task + base (Pages)
int Show_All_Tickets_Display() {
    display_all_tickets(tickets1);
    cout << "Press Enter to get back to passenger page...";
    getchar();
    getchar();
    return PASSENGER;
}
int Show_New_Ticket_Display() {
    save_Ticket(tickets1);
    loading("Loading Ticket");
    display_new_ticket(tickets1);
    Num_of_ticket++;
    string choice;
    cout << "1- Confirm\n2- Cancel\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1")) {
        loading("Saving Ticket");
        done("Successfully Registration!");
        return PASSENGER;
    }
    else if (compareStrings(choice, "2")) {
        Num_of_ticket--;
        //tickets1[Num_of_ticket]={0};
        loading("Canceling Reservation");
        done("Canceled Successfully!");
        return PASSENGER;
    }
    else { Invalid(); return SHOW_NEW_TICKET; }
    return PASSENGER;
}
int ShowFlightsDisplay() {
    displayflight(f1);
    cout << "Press Enter to get back to admin page...";
    getchar();
    getchar();
    return ADMIN_DISPLAY;
}
int PassengerDisplay() {
    string choice;
    cout << "\n\t    ==================================================\nPassenger Menu:\n-----------\n";
    cout << "1- Add new reservation\n2- Cancel existing reservation\n3- Modify existing reservation\n4- Show reservation log\n5- Logout\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1")) {
        system(CLEAR_SCREEN);
        cout << "\n\t    ==================================================\n";
        return search();
    }
    else if (compareStrings(choice, "2")) {
        system(CLEAR_SCREEN);
        return cancel_ticket(tickets1);
    }
    else if (compareStrings(choice, "3")) {
        system(CLEAR_SCREEN);
        return modify_ticket(tickets1);
    }
    else if (compareStrings(choice, "4")) {
        return SHOW_ALL_TICKETS;
    }
    else if (compareStrings(choice, "5")) {
        done("You Are Loged out!");
        return USER;
    }
    else { Invalid(); return PASSENGER; }
}
int SignupDisplay() {
    string temp_username, temp_id;
    bool new_user = true;
    bool new_id = true;
try_again1:
    cout << "\n\t    ==================================================\nSignup Menu:\n-----------\n";
    if (Accounts_Used == 50) { cout << "\t\tSorry but the amount of users is full\n"; return USER; }
    else {
        cout << "Hello Passenger!\nPlease enter your data\n";

        cout << string(22, '_') << "\nUsername : ";
        cin >> temp_username;
        cout << "Password : ";
        cin >> users[Accounts_Used].password;
        for (int i = 0; i < 50; i++) {
            if (compareStrings(temp_username, users[i].username)) {
                new_user = false;
                error("!!!! This Ussername is already used !!!!");
                system(CLEAR_SCREEN);
                goto try_again1;
                break;
            }
        }
        if (new_user) { users[Accounts_Used].username = temp_username; }
    try_again2:
        cout << string(22, '_') << "\nPassenger ID : ";
        cin >> temp_id;
        for (int i = 0; i < 50; i++) {
            if (compareStrings(temp_id, users[i].Passenger_ID)) {
                new_id = false;
                error("!!!! This Passenger ID is already used !!!!");
                goto try_again2;
                break;
            }
        }
        if (new_user) { users[Accounts_Used].Passenger_ID = temp_id; }

        cout << "Name : ";
        cin >> users[Accounts_Used].name;
        cout << "Address : ";
        cin >> users[Accounts_Used].address;
        cout << "Phone Number : ";
        cin >> users[Accounts_Used].phone_number;
        wanted1.Existing_User = users[Accounts_Used];
        Accounts_Used++;
        done("Account Created Succesfully!");
        return PASSENGER;
    }
}
int LoginDisplay() {
    string temp_username, temp_password;
    bool found_user = false;
    cout << "\n\t    ==================================================\nLogin Menu:\n-----------\n";
    cout << "Username : ";
    cin >> temp_username;
    cout << "Password : ";
    cin >> temp_password;
    for (int i = 0; i < 50; i++) {
        if (compareStrings(temp_username, users[i].username) && compareStrings(temp_password, users[i].password)) {
            found_user = true;
            wanted1.Existing_User = users[i];
            break;
        }
    }
    if (found_user) {
        done("Login Succesfully!");
        return PASSENGER;
    }
    else { error("!!!!Invalid username and password !!!!"); return USER; }
}
int AdminDisplay() {
    cout << "\n\t    ==================================================\n";
    cout << "\n\t\t" << string(16, '-') << "\n\t\t" << "Welcome Admin :)" << "\n\t\t" << string(16, '-') << endl;
    cout << "Admin Menu:\n-----------\n";
    string choice;
    
    cout << "\n1- Add flights schedule\n2- Delete existing flight schedule\n3- Update existing flight schedule\n4- Show existing flights schedule\n5- Return to main menu\n\n";
    cout << "Your Choice : ";
    //cin.clear();
    cin >> choice;
    if (compareStrings(choice, "1")) {
        system(CLEAR_SCREEN);
        cout << "\n\t    ==================================================\n";
        return addflight(f1);
    }
    else if (compareStrings(choice, "2")) {
        system(CLEAR_SCREEN);
        return deleteflight(f1);
    }
    else if (compareStrings(choice, "3")) {
        system(CLEAR_SCREEN);
        return updateflight(f1);
    }
    else if (compareStrings(choice, "4")) {
        return SHOW_ADDED_FLIGHTS;
    }
    else if (compareStrings(choice, "5")) {
        return MAIN;
    }
    else { Invalid(); return ADMIN_DISPLAY; }
}
int AdminCheck() {
    string admin_password;
    cout << "\n\t    ==================================================\nAdmin Login Menu:\n" << string(17, '-') << endl;
    cout << "Password : ";
    cin >> admin_password;
    if (!compareStrings(admin_password, AdminPassword)) {
        error("!!!! Invalid username and password !!!!");
        return MAIN;
    }
    return ADMIN_DISPLAY;
}
int UserDisplay() {
    string choice;
    
    cout << "\n\t    ==================================================\nUser Menu:\n----------\n";
    cout << "1- Existing User\n2- New User\n3- Return to main menu\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1")) {
        return LOGIN;
    }
    else if (compareStrings(choice, "2")) {
        return SIGNUP;
    }
    else if (compareStrings(choice, "3")) {
        return MAIN;
    }
    else { Invalid(); return USER; }
}
int MainDisplay() {
    string choice;
    
    cout << "\n\t    ==================================================\nMain Menu:\n-----------\n";
    cout << "1- Admin\n2- User\n3- Exit\n\n";
    cout << "Your Choice : ";
    cin >> choice;
    if (compareStrings(choice, "1")) {
        return ADMIN_CHECK;
    }
    else if (compareStrings(choice, "2")) {
        return USER;
    }
    else if (compareStrings(choice, "3")) {
        return EXIT;
    }
    else { Invalid(); return MAIN; }
}


int main() {
    srand(time(0));
    system("background color rgb(25, 12, 41)");
    int state = MAIN;
    cout << "\n\t\tWelcome to Airline Reservation Application";
    do {
        system(CLEAR_SCREEN);
        if (state == EXIT) { break; }
        switch (state)
        {
        case MAIN:
            state = MainDisplay();
            break;
        case ADMIN_CHECK:
            state = AdminCheck();
            break;
        case ADMIN_DISPLAY:
            state = AdminDisplay();
            break;
        case USER:
            state = UserDisplay();
            break;
        case LOGIN:
            state = LoginDisplay();
            break;
        case SIGNUP:
            state = SignupDisplay();
            break;
        case PASSENGER:
            state = PassengerDisplay();
            break;
        case SHOW_NEW_TICKET:
            state = Show_New_Ticket_Display();
            break;
        case SHOW_ALL_TICKETS:
            state = Show_All_Tickets_Display();
            break;
        case SHOW_ADDED_FLIGHTS:
            state = ShowFlightsDisplay();
            break;

        default:
            Invalid();
            state = MAIN;
            break;
        }
    } while (true);
    cout << "\t\tThank you for using our application!\n\t\t" << string(36, '=') << endl;
    cout << "Press Enter to exit...";
    getchar();
    getchar();
    return 0;
}