#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Forward declarations
class TourPackage;
class Customer;

// Global vector to store tour packages
vector<TourPackage*> tourPackages;
vector<Customer*> customers;

// Admin credentials
const string adminUsername = "admin";
const string adminPassword = "password";

// Class definitions

class TourPackage {
private:
    string title;
    vector<string> destinations;
    int duration; // in days
    double price;

public:
    TourPackage(string t, vector<string> dests, int dur, double p)
        : title(t), destinations(dests), duration(dur), price(p) {}

    string getTitle() const { return title; }
    int getDuration() const { return duration; }
    double getPrice() const { return price; }
    const vector<string>& getDestinations() const { return destinations; }

    void addDestination(string dest) { destinations.push_back(dest); }

    void display() const {
        cout << "Title: " << title << endl;
        cout << "Duration: " << duration << " days" << endl;
        cout << "Price: $" << price << endl;
        cout << "Destinations: ";
        for (const auto& dest : destinations) {
            cout << dest << ", ";
        }
        cout << endl << endl;
    }

    ~TourPackage() {
        // Destructor to free dynamically allocated memory in TourPackage
    }
};

class Customer {
private:
    static int nextId;
    int id;
    string username;
    string password;
    string name;
    string email;
    string phone;
    vector<TourPackage*> bookings;

public:
    Customer(string uname, string pwd, string n, string e, string ph)
        : id(nextId++), username(uname), password(pwd), name(n), email(e), phone(ph) {}

    int getId() const { return id; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    const vector<TourPackage*>& getBookings() const { return bookings; }

    void bookTour(TourPackage* pkg) {
        bookings.push_back(pkg);
    }

    void cancelBooking(const string& title) {
        auto it = find_if(bookings.begin(), bookings.end(), [&](TourPackage* pkg) {
            return pkg->getTitle() == title;
        });

        if (it != bookings.end()) {
            bookings.erase(it);
            cout << "Booking for " << title << " cancelled successfully.\n";
        } else {
            cout << "Booking for " << title << " not found.\n";
        }
    }

    void displayBookings() const {
        if (bookings.empty()) {
            cout << "No bookings found.\n";
        } else {
            cout << "\n===== Your Bookings =====\n";
            for (const auto& pkg : bookings) {
                pkg->display();
            }
        }
    }

    ~Customer() {
        // Destructor to free dynamically allocated memory in Customer
    }
};

int Customer::nextId = 1;

// Function prototypes
void adminMenu();
void addTourPackage();
void displayTourPackages();
void cleanupMemory();
bool authenticateAdmin();

void customerMenu(Customer* customer);
bool authenticateCustomer(const string& username, const string& password);
Customer* findCustomer(const string& username);
// Additional function prototypes
void searchTourPackagesByDestination();
void viewDetailedPackageInfo();
void bookTour(Customer* customer);
void modifyBooking(Customer* customer);
void cancelBooking(Customer* customer);

// Main function

int main() {
    int choice;

    // Add some initial customers to the global customer vector for testing
    customers.push_back(new Customer("customer1", "pass1", "John Doe", "john@example.com", "+1234567890"));
    customers.push_back(new Customer("customer2", "pass2", "Jane Smith", "jane@example.com", "+1987654321"));

    do {
        cout << "\n===== Travel Agency Management System =====\n";
        cout << "1. Admin Login\n";
        cout << "2. Customer Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (authenticateAdmin()) {
                    adminMenu();
                } else {
                    cout << "Admin authentication failed.\n";
                }
                break;
            case 2:
                {
                    string username, password;
                    cout << "\n===== Customer Login =====\n";
                    cout << "Username: ";
                    cin >> username;
                    cout << "Password: ";
                    cin >> password;

                    if (authenticateCustomer(username, password)) {
                        Customer* customer = findCustomer(username);
                        if (customer) {
                            customerMenu(customer);
                        } else {
                            cout << "Customer not found!\n";
                        }
                    } else {
                        cout << "Customer authentication failed.\n";
                    }
                }
                break;
            case 3:
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    cleanupMemory();
    return 0;
}

// Admin authentication function

bool authenticateAdmin() {
    string username, password;
    cout << "===== Admin Login =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    return (username == adminUsername && password == adminPassword);
}

// Customer authentication function

bool authenticateCustomer(const string& username, const string& password) {
    for (auto cust : customers) {
        if (cust->getUsername() == username && cust->getPassword() == password) {
            return true;
        }
    }
    return false;
}

// Function to find customer by username

Customer* findCustomer(const string& username) {
    for (auto cust : customers) {
        if (cust->getUsername() == username) {
            return cust;
        }
    }
    return nullptr;
}

// Admin menu function

void adminMenu() {
    int choice;

    do {
        cout << "\n===== Admin Menu =====\n";
        cout << "1. Add Tour Package\n";
        cout << "2. Display Tour Packages\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTourPackage();
                break;
            case 2:
                displayTourPackages();
                break;
            case 3:
                cout << "Exiting the admin menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// Function to add a tour package

void addTourPackage() {
    string title;
    vector<string> destinations;
    int duration;
    double price;
    int numDestinations;

    cout << "\nEnter Tour Package Details:\n";
    cout << "Title: ";
    cin.ignore(); // to clear the input buffer
    getline(cin, title);
    cout << "Number of destinations: ";
    cin >> numDestinations;
    cout << "Enter destinations (one per line):\n";
    cin.ignore(); // to clear the input buffer
    for (int i = 0; i < numDestinations; ++i) {
        string dest;
        getline(cin, dest);
        destinations.push_back(dest);
    }
    cout << "Duration (days): ";
    cin >> duration;
    cout << "Price: $";
    cin >> price;

    TourPackage* newPackage = new TourPackage(title, destinations, duration, price);
    tourPackages.push_back(newPackage);
    cout << "Tour Package added successfully!\n";
}

// Function to display all tour packages

void displayTourPackages() {
    if (tourPackages.empty()) {
        cout << "No tour packages available.\n";
        return;
    }

    cout << "\n===== Tour Packages =====\n";
    for (const auto& pkg : tourPackages) {
        pkg->display();
    }
}

// Customer menu function

void customerMenu(Customer* customer) {
    int choice;

    do {
        cout << "\n===== Customer Menu =====\n";
        cout << "1. View All Tour Packages\n";
        cout << "2. Search Tour Packages by Destination\n";
        cout << "3. View Detailed Package Information\n";
        cout << "4. Book Tour Package\n";
        cout << "5. Modify Booking\n";
        cout << "6. Cancel Booking\n";
        cout << "7. Display Bookings\n";
        cout << "8. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayTourPackages();
                break;
            case 2:
                searchTourPackagesByDestination();
                break;
            case 3:
                viewDetailedPackageInfo();
                break;
            case 4:
                bookTour(customer);
                break;
            case 5:
                modifyBooking(customer);
                break;
            case 6:
                cancelBooking(customer);
                break;
            case 7:
                customer->displayBookings();
                break;
            case 8:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

// Function to search tour packages by destination

void searchTourPackagesByDestination() {
    string destination;
    cout << "\nEnter destination to search: ";
    cin.ignore(); // Clear input buffer
    getline(cin, destination);

    bool found = false;
    cout << "\n===== Tour Packages Matching Destination: " << destination << " =====\n";
    for (const auto& pkg : tourPackages) {
        const vector<string>& destinations = pkg->getDestinations();
        if (find(destinations.begin(), destinations.end(), destination) != destinations.end()) {
            pkg->display();
            found = true;
        }
    }

    if (!found) {
        cout << "No tour packages found for destination: " << destination << endl;
    }
}

// Function to view detailed package information

void viewDetailedPackageInfo() {
    string title;
    cout << "\nEnter the title of the package to view details: ";
    cin.ignore(); // Clear input buffer
    getline(cin, title);

    bool found = false;
    for (const auto& pkg : tourPackages) {
        if (pkg->getTitle() == title) {
            pkg->display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Tour package with title \"" << title << "\" not found.\n";
    }
}

// Function to book a tour package for a customer

void bookTour(Customer* customer) {
    string title;
    cout << "\nEnter the title of the tour package to book: ";
    cin.ignore(); // Clear input buffer
    getline(cin, title);

    bool found = false;
    for (auto& pkg : tourPackages) {
        if (pkg->getTitle() == title) {
            customer->bookTour(pkg);
            cout << "Tour package \"" << title << "\" booked successfully.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Tour package with title \"" << title << "\" not found.\n";
    }
}

// Function to modify booking for a customer

void modifyBooking(Customer* customer) {
    string title;
    cout << "\nEnter the title of the tour package to modify booking: ";
    cin.ignore(); // Clear input buffer
    getline(cin, title);

    bool found = false;
    for (auto& pkg : tourPackages) {
        if (pkg->getTitle() == title) {
            customer->cancelBooking(title);
            customer->bookTour(pkg);
            cout << "Booking for tour package \"" << title << "\" modified successfully.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Tour package with title \"" << title << "\" not found.\n";
    }
}

// Function to cancel booking for a customer

void cancelBooking(Customer* customer) {
    string title;
    cout << "\nEnter the title of the tour package to cancel booking: ";
    cin.ignore(); // Clear input buffer
    getline(cin, title);

    customer->cancelBooking(title);
}

// Function to clean up dynamically allocated memory

void cleanupMemory() {
    for (auto pkg : tourPackages) {
        delete pkg;
    }
    for (auto cust : customers) {
        delete cust;
    }
    tourPackages.clear();
    customers.clear();
}
