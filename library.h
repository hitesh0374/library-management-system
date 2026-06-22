#pragma once
#include <bits/stdc++.h>
#include "book.h"
#include "user.h"
#include "student.h"
#include "faculty.h"
#include "librarian.h"

using namespace std;

struct Transaction {
    string transactionID;
    string userID;
    string bookISBN;
    time_t issueTime;
    time_t returnTime;
    bool isReturned;
    int fineCalculated;
};

class Library {
private:
    vector<Transaction> transactionLog;
    int nextTxnId = 1000;

    time_t getCurrentTime() {
        return chrono::system_clock::to_time_t(chrono::system_clock::now());
    }

public:
    unordered_map<string, User*> userDB;
    void issueBook(User* user, string isbn, unordered_map<string, Book>& inventory) {
        if (!inventory.count(isbn) || inventory[isbn].availableQuantity <= 0) {
            cout << "System: Book '" << isbn << "' is unavailable.\n";
            return;
        }

        if (!user->canBorrowMore()) {
            cout << "System: Borrow limit reached.\n";
            return;
        }

        inventory[isbn].availableQuantity--;
        user->incrementBorrowed();

        Transaction txn;
        txn.transactionID = "TXN-" + to_string(nextTxnId++);
        txn.userID = user->getUserID();
        txn.bookISBN = isbn;
        txn.isReturned = false;
        txn.fineCalculated = 0;

        txn.issueTime = getCurrentTime();

        transactionLog.push_back(txn);

        cout << "\n==============================\n";
        cout << "        ISSUE RECEIPT         \n";
        cout << "==============================\n";
        cout << "Txn ID     : " << txn.transactionID << "\n";
        cout << "User       : " << user->getName() << " (" << user->getRole() << ")\n";
        cout << "Book       : " << inventory[isbn].title << "\n";
        cout << "Issue Date : " << ctime(&txn.issueTime); 
        cout << "==============================\n";
    }

    void returnBook(User* user, string isbn, unordered_map<string, Book>& inventory) {
        for (auto& txn : transactionLog) {
            if (txn.userID == user->getUserID() && txn.bookISBN == isbn && !txn.isReturned) {
                txn.returnTime = getCurrentTime(); 
                txn.isReturned = true;

                inventory[isbn].availableQuantity++;
                user->decrementBorrowed();

                double seconds = difftime(txn.returnTime, txn.issueTime);
                int daysBorrowed = round(seconds / 86400.0);

                txn.fineCalculated = user->calculateFine(daysBorrowed);

                cout << "\n==============================\n";
                cout << "        RETURN RECEIPT        \n";
                cout << "==============================\n";
                cout << "Txn ID     : " << txn.transactionID << "\n";
                cout << "User       : " << user->getName() << " (" << user->getRole() << ")\n";
                cout << "Book       : " << inventory[isbn].title << "\n";
                cout << "Issue Date : " << ctime(&txn.issueTime);
                cout << "Return Date: " << ctime(&txn.returnTime);
                cout << "------------------------------\n";
                cout << "Days Held  : " << daysBorrowed << "\n";
                
                if (txn.fineCalculated > 0) {
                    cout << "Fine Due   : Rs. " << txn.fineCalculated << "\n";
                } else {
                    cout << "Fine Due   : None\n";
                }
                cout << "==============================\n";
                return;
            }
        }
        cout << "System: No active transaction found.\n";
    }

    void saveState(unordered_map<string, Book>& inventory) {
        // 1. Save the Books
        ofstream bookFile("books.txt", ios::trunc); 
        if (bookFile.is_open()) {
            for (auto& pair : inventory) {
                Book b = pair.second;
                bookFile << b.isbn << "|" << b.title << "|" << b.author << "|"
                         << b.totalQuantity << "|" << b.availableQuantity << "\n";
            }
            bookFile.close();
        }

        // 2. Save the Transactions
        ofstream txnFile("transactions.txt", ios::trunc);
        if (txnFile.is_open()) {
            for (auto& txn : transactionLog) {
                txnFile << txn.transactionID << "|" << txn.userID << "|" << txn.bookISBN << "|"
                        << txn.issueTime << "|" << txn.returnTime << "|" 
                        << txn.isReturned << "|" << txn.fineCalculated << "\n";
            }
            txnFile.close();
        }
        cout << "System: Database state saved to disk.\n";
        // 3. Save the Users
        ofstream userFile("users.txt", ios::trunc);
        if (userFile.is_open()) {
            for (auto& pair : userDB) {
                User* u = pair.second;
                userFile << u->getRole() << "|" << u->getUserID() << "|" << u->getName() << "|" 
                         << u->getPassword() << "|" << u->getBorrowedCount() << "\n";
            }
            userFile.close();
        }
        cout << "System: Database state saved to disk.\n";
    }





    void loadState(unordered_map<string, Book>& inventory) {
        string line;

        // 1. Load the Books
        ifstream bookFile("books.txt");
        if (bookFile.is_open()) {
            while (getline(bookFile, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                string isbn, title, author, totalQty, availQty;

                // Split the string at every pipe '|'
                getline(ss, isbn, '|');
                getline(ss, title, '|');
                getline(ss, author, '|');
                getline(ss, totalQty, '|');
                getline(ss, availQty, '|');

                // Reconstruct the book in the hash map (stoi converts String TO Integer)
                inventory[isbn] = Book(isbn, title, author, stoi(totalQty), stoi(availQty));
            }
            bookFile.close();
            cout << "System: Book inventory loaded.\n";
        } else {
            cout << "System: No previous book data found. Starting fresh.\n";
        }

        // 2. Load the Transactions
        ifstream txnFile("transactions.txt");
        if (txnFile.is_open()) {
            int highestTxnId = 999; // Used to prevent ID overlap when we start issuing new books
            
            while (getline(txnFile, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                string id, uid, isbn, issue, ret, isRet, fine;

                getline(ss, id, '|');
                getline(ss, uid, '|');
                getline(ss, isbn, '|');
                getline(ss, issue, '|');
                getline(ss, ret, '|');
                getline(ss, isRet, '|');
                getline(ss, fine, '|');

                Transaction txn;
                txn.transactionID = id;
                txn.userID = uid;
                txn.bookISBN = isbn;
                // stoll converts String TO Long Long (needed for large time_t integers)
                txn.issueTime = stoll(issue); 
                txn.returnTime = stoll(ret);
                txn.isReturned = (isRet == "1"); // "1" is true, "0" is false
                txn.fineCalculated = stoi(fine);

                transactionLog.push_back(txn);

                // Extract the number from "TXN-1005" to update our ID counter
                int numId = stoi(id.substr(4));
                if (numId > highestTxnId) highestTxnId = numId;
            }
            nextTxnId = highestTxnId + 1; // Make sure the next checkout gets a brand new ID
            txnFile.close();
            cout << "System: Transaction ledger loaded.\n";
        }

        // 3. Load the Users
        ifstream userFile("users.txt");
        if (userFile.is_open()) {
            while (getline(userFile, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                string role, id, name, pass, borrowedStr;
                getline(ss, role, '|'); getline(ss, id, '|'); getline(ss, name, '|');
                getline(ss, pass, '|'); getline(ss, borrowedStr, '|');

                int borrowed = stoi(borrowedStr);
                if (role == "Student") userDB[id] = new Student(id, name, pass, borrowed);
                else if (role == "Faculty") userDB[id] = new Faculty(id, name, pass, borrowed);
                else if (role == "Librarian") userDB[id] = new Librarian(id, name, pass, borrowed);
            }
            userFile.close();
            cout << "System: User database loaded.\n";
        }
        if (userDB.empty()) {
            cout << "System: No users found. Generating default accounts.\n";
            userDB["STU-157"] = new Student("STU-157", "Anurag", "iitk123");
            userDB["FAC-201"] = new Faculty("FAC-201", "Dr. Sharma", "fac123");
            userDB["admin"] = new Librarian("admin", "System Admin", "pass");
        }
    }
};