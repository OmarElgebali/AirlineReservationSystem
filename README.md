# Airline Reservation System

## Overview

This C++ project implements an Airline Reservation System, providing functionalities for managing flight schedules, passenger reservations, and ticket records.

## System Data

### Flight Information

- Flight Number
- Number of Available Seats
- Flight Date
- Departure Information (City, Departure Time)
- Arrival Information (City, Arrival Time)

### Passenger Information

- Passenger ID
- Name
- Address
- Phone Number

### Ticket Information

- Ticket Number
- Passenger ID
- Flight Number
- Reservation Date

## Functionalities

### Flight Scheduling

- Add New Flight Schedule
- Delete Existing Flight Schedule
- Update Existing Flight Schedule

### Passenger

- Log in / Sign up
- Search Available Flights
- Add New Reservation
- Cancel Reservation
- Modify Reservation
- Show Reservation Log

## Pages Details

### MAIN

- MainDisplay allows the user to choose between entering as admin (with a password), entering as a user, or exiting the program.

### ADMIN_CHECK

- AdminCheck checks if the user entering the page is an admin by asking for a predefined password.

### ADMIN_DISPLAY

- AdminDisplay shows admin choices such as adding, editing, or deleting flights, or displaying the full flight schedule.

### USER

- UserDisplay asks the user if they are a new user (sign up) or an existing user (login).

### LOGIN

- LoginDisplay prompts the user for their existing username and password.

### SIGNUP

- SignupDisplay asks the user to enter their data, focusing on the unique username and passenger ID.

### PASSENGER

- PassengerDisplay shows user choices for adding reservations, editing existing reservations, deleting reservations, or showing the full reservation log.

### SHOW_NEW_TICKET

- Show_New_Ticket_Display saves user ticket details and displays the ticket waiting for confirmation or cancellation.

### SHOW_ALL_TICKET

- Show_All_Tickets_Display displays the full reservation log unless the user presses enter.

### SHOW_ADDED_FLIGHTS

- ShowFlightsDisplay displays the full flight schedule unless the admin presses enter.

## Implemented Functions

- `displayflight`: Display the full flight schedule.
- `addflight`: Mass add flights with admin-chosen properties.
- `deleteflight`: Delete an existing flight entered by the admin.
- `Updateflight`: Modify an existing flight's properties.
- `Search`: Search for flights by user.
- `display_selected_fligths`: Display all flights that match the user's itinerary.
- `save_Ticket`: Save flight details chosen by the user to a unique ticket.
- `display_new_ticket`: Display the user's new ticket after saving it.
- `cancel_ticket`: After displaying all reservations, the user can choose which ticket to cancel.
- `modify_ticket`: After displaying all reservations, the user can choose which ticket to modify.
- `display_all_tickets`: Display the full reservation log.

## UI Features

- `os_sleep`: Choose the sleep function based on the platform.
- `loading`: Show a loading line after some actions.
- `done`: Show a success message after successful actions.
- `error`: Show an error message for logical errors.
- `Invalid`: Show an error message for syntax errors.
- `string_output`: Print a string in the width of its length + 1.
- `compareStrings`: Compare two strings and return true if identical, false if not identical.

## How to Use

_`Login Menu:`_
- Admin (Password=4567)
- User:
  - Login: 
    1. Username
    2. Password
  - Sign-up:
    1. Username
    2. Password
    3. Passenger id
    4. Name
    5. address
    6. phone number
- Exit

_`Main Menu (User):`_
- Add
- Search:
  - **Data:** Departure / Arrival / Seats (BOOLEAN)
  - **Actions:** Confirm / Cancel
- Show reservation log:
  - **Modify:** Delete -> Repeat Search function
  - **Cancel:** Delete
- Exit

_`Main Menu (Admin):`_
- Add new flight
  1. Flight number
  2. Departure city
  3. Departure time
  4. Arrival city
  5. Arrival time
  6. flight date
  7. available seats
- Delete flight
- Modify flight
