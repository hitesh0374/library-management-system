#pragma once
#include <bits/stdc++.h>
#include "user.h"
#include "book.h"
using namespace std;

class Librarian : public User {
public:
    Librarian(string id, string n, string pass, int borrowed=0) : User(id, n, pass, borrowed) {}

    bool canBorrowMore() override { return true; }
    int calculateFine(int daysBorrowed) override { return 0; }
    string getRole() override { return "Librarian"; }

    // --- ADMIN ACTIONS ---
    void addBook(unordered_map<string, Book>& inventory, string isbn, string title, string author, int qty) {
        if (inventory.count(isbn)) {
            // Book exists, just add to the count
            inventory[isbn].totalQuantity += qty;
            inventory[isbn].availableQuantity += qty;
        } else {
            // New book
            inventory[isbn] = Book(isbn, title, author, qty, qty);
        }
        cout << "System: Inventory updated for '" << title << "'.\n";
    }

    void removeBook(unordered_map<string, Book>& inventory, string isbn) {
        if (inventory.count(isbn)) {
            inventory.erase(isbn);
            cout << "System: Book removed completely.\n";
        } else {
            cout << "System: Error - Book not found.\n";
        }
    }
};