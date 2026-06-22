#pragma once
#include <bits/stdc++.h>
#include "user.h" 
using namespace std;

class Student : public User {
private:
    const int MAX_BOOKS = 10;
    const int FREE_DAYS = 14;
    const int FINE_PER_DAY = 2;

public:
    Student(string id, string n, string pass, int borrowed=0) : User(id, n, pass, borrowed) {}

    bool canBorrowMore() override {
        return currentlyBorrowedBooks < MAX_BOOKS;
    }

    int calculateFine(int daysBorrowed) override {
        if (daysBorrowed <= FREE_DAYS) return 0;
        return (daysBorrowed - FREE_DAYS) * FINE_PER_DAY;
    }

    string getRole() override { 
        return "Student"; 
    }
};