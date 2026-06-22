#pragma once
#include <bits/stdc++.h>
using namespace std;

class Book {
public:
    string isbn;
    string title;
    string author;
    int totalQuantity;
    int availableQuantity;
 
    Book() = default;

    Book(string i, string t, string a, int total, int available) {
        isbn = i;
        title = t;
        author = a;
        totalQuantity = total;
        availableQuantity = available;
    }
};