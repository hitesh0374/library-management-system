# Library Management System

A terminal based Library Management System built in C++. This project leverages Object-Oriented Programming (OOP) principles to provide a modular architecture. It features role-based access control and utilizes standard file handling for secure, persistent data storage without the need for an external database.

## Features

* **Role-Based Access Control:** Distinct login portals and privileges for Librarians, Faculty, and Students.
* **Data Persistence:** Custom file handling mechanisms to store and retrieve book records, user credentials, and transaction logs.
* **OOP Architecture:** Utilizes abstraction, inheritance, and polymorphism to separate core entity classes from the main application logic.
* **Automated Bookkeeping:** Custom borrowing rules depending on the user role, complete with automated fine calculations for overdue returns.
* **Inventory Management:** Algorithms to search, sort, add, and remove books from the library catalog using title, author, or ISBN.

## Technologies Used

* **Language:** C++ (C++11 or higher recommended)
* **Concepts:** Object-Oriented Programming (OOP), File I/O Streams, Standard Template Library (STL)

## Architecture Overview

The system is modularized into several core entities:
* **User Class:** Base class extended by Student, Faculty, and Librarian implementing polymorphic access rights.
* **Book Class:** Manages individual book attributes (ISBN, Title, Author, Status).
* **Transaction Class:** Logs check-outs, check-ins, due dates, and fine accumulations.
* **Database Manager:** Handles all file stream operations for reading and writing state to local text or CSV files.

