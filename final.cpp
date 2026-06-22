#include <bits/stdc++.h>

#include "book.h"
#include "user.h"
#include "student.h"
#include "faculty.h"
#include "librarian.h"
#include "library.h" 

using namespace std;

int main() {

    unordered_map<string, Book> libraryInventory;
    Library library; 

    cout << "Booting up Library System...\n";
    library.loadState(libraryInventory); 

    int mainChoice;
    
    // --- MAIN SECURITY GATE ---
    while (true) {
        cout << "\n=====================================\n";
        cout << "      WELCOME TO THE LIBRARY PORTAL  \n";
        cout << "=====================================\n";
        cout << "1. Student Portal\n";
        cout << "2. Faculty Portal\n";
        cout << "3. Librarian Admin Panel\n";
        cout << "4. Shut Down System\n";
        cout << "=====================================\n";
        cout << "Select (1-4): ";
        cin >> mainChoice;

        if(cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // ==========================================
        // 1. STUDENT PORTAL
        // ==========================================
        if (mainChoice == 1) {
            string username, password;
            cout << "\n--- STUDENT LOGIN ---\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            // Authentication Check
            if (library.userDB.count(username) && 
                library.userDB[username]->getPassword() == password && 
                library.userDB[username]->getRole() == "Student") {
                
                User* loggedInUser = library.userDB[username];
                bool loggedIn = true;
                cout << "\nWelcome, " << loggedInUser->getName() << "!\n";

                // The Dashboard Loop
                while (loggedIn) {
                    cout << "\n--- STUDENT DASHBOARD ---\n";
                    cout << "1. View All Books\n";
                    cout << "2. Issue a Book\n";
                    cout << "3. Return a Book\n";
                    cout << "4. Logout\n";
                    cout << "Choice: ";
                    
                    int choice; cin >> choice;

                    if (choice == 1) {
                        cout << "\n--- INVENTORY ---\n";
                        for (auto& pair : libraryInventory) {
                            cout << pair.second.isbn << " | " << pair.second.title 
                                 << " | Available: " << pair.second.availableQuantity 
                                 << "/" << pair.second.totalQuantity << "\n";
                        }
                    } else if (choice == 2) {
                        string isbn; cout << "Enter Book ISBN: "; cin >> isbn;
                        library.issueBook(loggedInUser, isbn, libraryInventory); 
                        library.saveState(libraryInventory);
                    } else if (choice == 3) {
                        string isbn; cout << "Enter Book ISBN: "; cin >> isbn;
                        library.returnBook(loggedInUser, isbn, libraryInventory);
                        library.saveState(libraryInventory);
                    } else if (choice == 4) {
                        cout << "Logging out...\n";
                        loggedIn = false; 
                    } else {
                        cout << "Invalid choice.\n";
                    }
                }
            } else cout << "Access Denied. Incorrect credentials or role.\n";
        } 
        
        // ==========================================
        // 2. FACULTY PORTAL
        // ==========================================
        else if (mainChoice == 2) {
            string username, password;
            cout << "\n--- FACULTY LOGIN ---\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            if (library.userDB.count(username) && 
                library.userDB[username]->getPassword() == password && 
                library.userDB[username]->getRole() == "Faculty") {
                
                User* loggedInUser = library.userDB[username];
                bool loggedIn = true;
                cout << "\nWelcome, " << loggedInUser->getName() << "!\n";

                while (loggedIn) {
                    cout << "\n--- FACULTY DASHBOARD ---\n";
                    cout << "1. View All Books\n";
                    cout << "2. Issue a Book\n";
                    cout << "3. Return a Book\n";
                    cout << "4. Logout\n";
                    cout << "Choice: ";
                    
                    int choice; cin >> choice;

                    if (choice == 1) {
                        cout << "\n--- INVENTORY ---\n";
                        for (auto& pair : libraryInventory) {
                            cout << pair.second.isbn << " | " << pair.second.title 
                                 << " | Available: " << pair.second.availableQuantity 
                                 << "/" << pair.second.totalQuantity << "\n";
                        }
                    } else if (choice == 2) {
                        string isbn; cout << "Enter Book ISBN: "; cin >> isbn;
                        library.issueBook(loggedInUser, isbn, libraryInventory); 
                        library.saveState(libraryInventory);
                    } else if (choice == 3) {
                        string isbn; cout << "Enter Book ISBN: "; cin >> isbn;
                        library.returnBook(loggedInUser, isbn, libraryInventory);
                        library.saveState(libraryInventory);
                    } else if (choice == 4) {
                        cout << "Logging out...\n";
                        loggedIn = false; 
                    } else {
                        cout << "Invalid choice.\n";
                    }
                }
            } else cout << "Access Denied. Incorrect credentials or role.\n";
        } 
        
        // ==========================================
        // 3. LIBRARIAN ADMIN PANEL
        // ==========================================
        else if (mainChoice == 3) {
            string username, password;
            cout << "\n--- LIBRARIAN LOGIN ---\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            if (library.userDB.count(username) && 
                library.userDB[username]->getPassword() == password && 
                library.userDB[username]->getRole() == "Librarian") {
                
                // dynamic_cast grants access to Librarian-specific functions like addBook
                Librarian* admin = dynamic_cast<Librarian*>(library.userDB[username]);
                bool loggedIn = true;
                cout << "\nWelcome, " << admin->getName() << "!\n";

                while (loggedIn) {
                    cout << "\n--- ADMIN DASHBOARD ---\n";
                    cout << "1. Add New Book\n";
                    cout << "2. View Inventory\n";
                    cout << "3. Register New User\n"; 
                    cout << "4. Logout\n";
                    cout << "Choice: ";
                    
                    int choice; cin >> choice;

                    if (choice == 1) {
                        string isbn, title, author; int qty;
                        cout << "Enter ISBN: "; cin >> isbn;
                        cout << "Enter Title (Use_Underscores): "; cin >> title;
                        cout << "Enter Author (Use_Underscores): "; cin >> author;
                        cout << "Enter Quantity: "; cin >> qty;
                        admin->addBook(libraryInventory, isbn, title, author, qty);
                        library.saveState(libraryInventory);
                    } else if (choice == 2) {
                        cout << "\n--- INVENTORY ---\n";
                        for (auto& pair : libraryInventory) {
                            cout << pair.second.isbn << " | " << pair.second.title 
                                 << " | Available: " << pair.second.availableQuantity 
                                 << "/" << pair.second.totalQuantity << "\n";
                        }
                    } else if (choice == 3) {
                        // --- DYNAMIC USER REGISTRATION ---
                        string role, id, name, pass;
                        cout << "\n--- USER REGISTRATION ---\n";
                        cout << "Enter Role (Student / Faculty / Librarian): "; cin >> role;
                        cout << "Enter New ID (e.g., STU-999): "; cin >> id;
                        cout << "Enter Name (Use_Underscores): "; cin >> name;
                        cout << "Enter Password: "; cin >> pass;

                        if (library.userDB.count(id)) {
                            cout << "System Error: ID '" << id << "' already exists.\n";
                        } else {
                            if (role == "Student") library.userDB[id] = new Student(id, name, pass);
                            else if (role == "Faculty") library.userDB[id] = new Faculty(id, name, pass);
                            else if (role == "Librarian") library.userDB[id] = new Librarian(id, name, pass);
                            else {
                                cout << "Error: Invalid Role. Must be Student, Faculty, or Librarian.\n";
                                continue; 
                            }
                            
                            library.saveState(libraryInventory);
                            cout << "Success: " << name << " registered as a " << role << ".\n";
                        }
                    } else if (choice == 4) {
                        cout << "Logging out...\n";
                        loggedIn = false;
                    } else {
                        cout << "Invalid choice.\n";
                    }
                }
            } else cout << "Access Denied. Incorrect credentials or role.\n";
        } 
        
        // ==========================================
        // 4. SHUTDOWN & MEMORY CLEANUP
        // ==========================================
        else if (mainChoice == 4) {
            cout << "\nInitiating Shutdown Sequence...\n";
            library.saveState(libraryInventory);
            
            // Clean up dynamically allocated memory from the Heap before exiting
            for (auto& pair : library.userDB) {
                delete pair.second;
            }
            
            cout << "System offline.\n";
            break;
        } 
        else cout << "Invalid choice.\n";
    }

    return 0;
}