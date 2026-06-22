Library Management System
A terminal-based library portal built entirely in C++. I designed this project from scratch using Object-Oriented Programming (OOP) to keep the codebase modular, clean, and easy to expand. It features a complete role-based login system and saves all your data directly into local text files, giving you a fully persistent database experience without needing to install or set up external database software.

Features
Role-Based Access Control: Creates distinct menus and system paths for Students, Faculty, and Librarians, ensuring users can only access the specific features and tools permitted for their role.

Data Persistence: Uses custom file-handling streams (fstream) to automatically read and write book lists, user profiles, and pipe-separated logs into local text files, meaning no data is lost when you close the application.

Clean OOP Structure: Relies on core concepts like inheritance and polymorphism to handle different types of users and system objects cleanly, minimizing messy, repetitive code.

Smart Bookkeeping & Fines: Uses the standard C++ <ctime> library to track borrowing timelines, enforce custom return windows depending on the user's role, and automatically compute late-fee penalty points.

Catalog Management: Built-in search and sorting tools that let you quickly browse, add, update, or remove assets from the active catalog index using their Title, Author, or ISBN.

Technologies Used
Language: C++ (C++11 or higher)

Core Concepts: Object-Oriented Programming (Abstraction, Inheritance, Polymorphism), File I/O Streams (fstream), and the Standard Template Library (STL Vectors, Strings, and Stringstreams).

Architecture Overview
User Class: The base foundation for accounts. It uses runtime polymorphism to branch out into Student, Faculty, and Librarian sub-classes, letting each role execute its own custom workflow.

Book Class: Holds all the essential attributes for a library item, tracking its Title, Author, ISBN barcode, and whether it's currently checked out or available on the shelf.

Transaction Class: Acts as the library's ledger, recording every check-out and check-in event along with active issue timestamps, due dates, and fine accruals.

Database Manager: The engine's storage handler. It takes care of reading raw text rows (like the entries in transactions.txt), parsing the data fields, and converting them seamlessly back into live objects in the program's memo

