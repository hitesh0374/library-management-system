#pragma once
#include <bits/stdc++.h>
using namespace std;

class User {
protected:
    string userID;
    string name;
    string password;
    int currentlyBorrowedBooks;

public:
    User(string id, string n, string pass, int borrowed=0) {
        userID = id;
        name = n;
        password = pass;
        currentlyBorrowedBooks = borrowed;
    }

    virtual ~User() = default;

    // Pure virtual functions mapping to specific rules
    virtual bool canBorrowMore() = 0;
    virtual int calculateFine(int daysBorrowed) = 0;
    virtual string getRole() = 0;

    // Common getters and setters
    string getUserID() { return userID; }
    string getName() { return name; }
    string getPassword() { return password; }
    int getBorrowedCount() { return currentlyBorrowedBooks; }
    
    void incrementBorrowed() { currentlyBorrowedBooks++; }
    void decrementBorrowed() { 
        if (currentlyBorrowedBooks > 0) {
            currentlyBorrowedBooks--; 
        }
    }
};