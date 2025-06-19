# 🌐 Web Browser History Manager

This project simulates a basic tabbed web browser 🧭 with independent navigation history for each tab. Built as part of the **Data Structures and Algorithms** course at university 🎓, the assignment focuses on practicing stacks, doubly-linked lists, dynamic memory management, and modular design in C.

## 🚀 Features

- 🗂️ **Tabbed Browsing**: Create, switch, and close browser tabs
- 📄 **Page Navigation**: Navigate pages in each tab using `BACKWARD` and `FORWARD` stacks
- 🧠 **History Tracking**: Print full navigation history for any tab
- 🧼 **Memory-Safe**: Clean memory deallocation and fully Valgrind-safe ✅
- 📑 **Persistent Pages**: Pages are read from input and stored dynamically

## 📁 Project Structure
├── browser.h # Header file with data structures & function declarations

├── lista.c # Doubly linked list implementation for tab management

├── stiva.c # Stack implementation for backward/forward navigation

├── operatii_browser.c # Core browser operations (tab/page handling)

├── main.c # Input parsing and operation dispatcher

├── Makefile # Build automation

└── README.md # You're reading it!

## 🧱 Data Structures

- `page`: contains `id`, `url`, and a dynamically allocated `description`
- `tab`: stores the current page and two stacks (`backward`, `forward`)
- `browser`: tracks the current tab and holds all tabs in a circular doubly-linked list with a sentinel

## 🧪 Sample Commands from `tema1.in`

```txt
3
1 https://google.com/
Google
2 https://github.com/
GitHub
3 https://stackoverflow.com/
Stack Overflow
15
NEW_TAB
PAGE 2
BACKWARD
FORWARD
PRINT
CLOSE
PRINT_HISTORY 0
```
---

## 📦 Build & Run

```bash
make build     # Compile the project
./tema1        # Run the program
make clean     # Clean compiled files
```
## 👨‍💻 Author

Theodor Vulpe | 
Student at University Politehnica of Bucharest – Faculty of Automatic Control and Computers
