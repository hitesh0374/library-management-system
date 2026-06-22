#pragma once
#include <bits/stdc++.h>
#include "user.h"
using namespace std;

class Faculty : public User {
public:
    Faculty(string id, string n, string pass, int borrowed=0) : User(id, n, pass, borrowed) {}

    bool canBorrowMore() override {
        return true; // Unlimited
    }

    int calculateFine(int daysBorrowed) override {
        return 0; // Always free
    }

    string getRole() override { 
        return "Faculty"; 
    }
};