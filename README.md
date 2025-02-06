# Travel Agency Management System

## Overview
The **Travel Agency Management System** is a C++ console application designed to manage tour packages and customer bookings efficiently. This system allows administrators to add and display tour packages, while customers can browse, book, modify, and cancel their tour bookings.

## Features
### Admin Features:
- Admin authentication system.
- Add new tour packages with title, destinations, duration, and price.
- View all available tour packages.

### Customer Features:
- Customer authentication system.
- View all available tour packages.
- Search tour packages by destination.
- View detailed package information.
- Book a tour package.
- Modify or cancel an existing booking.
- View all booked tour packages.

## Technologies Used
- Programming Language: **C++**
- Standard Template Library (**STL**) for vector operations
- Object-Oriented Programming (**OOP**) concepts

## Setup and Usage
### Prerequisites
Ensure you have a **C++ compiler** installed (e.g., g++ for GCC or MSVC for Windows).

### Steps to Run the Program
1. **Clone the Repository:**
   ```sh
   git clone https://github.com/Gayatridandgal/Travel-Agency-Management.git
   cd Travel-Agency-Management
   ```
2. **Compile the Code:**
   ```sh
   g++ -o travel_agency travel_agency.cpp
   ```
3. **Run the Executable:**
   ```sh
   ./travel_agency
   ```

## Usage Guide
- **Admin Login**:
  - Default credentials: **Username:** `admin`, **Password:** `password`
  - Navigate to the admin menu to add or view tour packages.

- **Customer Login**:
  - Predefined customers exist for testing (**customer1 / pass1**, **customer2 / pass2**)
  - Browse and book available tour packages.

## Future Improvements
- Implement database storage for persistent data.
- Add a GUI for a better user experience.
- Integrate payment processing for real-world applications.
