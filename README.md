# Library Management System (Qt 5, C++)

## Overview

This project is a **desktop-based Library Management System** implemented in **C++ using Qt 5.3.0. It allows users to **add, manage, borrow, return, and search** library items such as **Books** and **Magazines**. The application stores data in a local `.txt` file using a custom serialization mechanism, and supports **filtering and sorting** of library items.

---

## Features

- **Add Library Items:**  
  - Add **Books** with title, author, ID, genre, and publication year.  
  - Add **Magazines** with title, author, ID, issue number, and publisher.  

- **View and Manage Items:**  
  - View all library items in a list with **availability status**.  
  - Borrow and return items with proper status updates.  
  - Double-click an item to view full details.  

- **Filtering and Sorting:**  
  - Filter items by type (Books or Magazines) or availability (Available/Borrowed).  
  - Sort items by **Title** or **ID**.  

- **Search Functionality:**  
  - Search library items by **title** or **author**.  

- **Persistent Storage:**  
  - Library items are saved to a file (`library_data.txt`) automatically.  
  - Supports importing and exporting `.txt` files.

- **Manual GUI Creation:**  
  - All GUI elements are **manually created in code** (no Qt Designer), demonstrating proper parent-child memory management in Qt.

---

## Project Structure

LibraryManagementSystem/
├── main.cpp # Entry point
├── mainwindow.h # MainWindow class header
├── mainwindow.cpp # MainWindow class implementation
├── librarystorage.h # LibraryStorage class header
├── librarystorage.cpp # LibraryStorage class implementation
├── libraryitem.h # Base class for library items
├── book.h / book.cpp # Book class
├── magazine.h / magazine.cpp # Magazine class
├── LibraryUtils/ # Utility library for file operations and sorting
│ ├── libraryutils.h
│ └── libraryutils.cpp
├── library_data.txt # Default data file (created automatically)
└── README.md


---

## Requirements

- **Qt 5 (>=5.3.0)**
- **C++11 support**
- Windows, Linux, or macOS platform

---

## How to Build

1. Open the project in **Qt Creator**.
2. Make sure **LibraryUtils** is built first as a shared library.
3. Build the **LibraryManagementSystem** project.
4. Run the executable.  

**Note:** The application will automatically create a default dataset if `library_data.txt` does not exist.

---

## Usage

1. **Adding a Book or Magazine:**
   - Enter all required fields (Title, Author, ID, etc.)
   - Click **Add Book** or **Add Magazine**.
   - Confirmation message will appear.

2. **Borrow/Return Items:**
   - Select an item from the list.
   - Click **Borrow** or **Return**.
   - The list will update to reflect the status.

3. **Filtering and Sorting:**
   - Use **Filter ComboBox** to view specific items (Books, Magazines, Available, Borrowed).
   - Use **Sort ComboBox** to sort items by Title or ID.

4. **Searching:**
   - Enter search text in the search bar and click **Search**.

5. **Data Persistence:**
   - Data is automatically saved when the application closes.
   - Optional: Use **Export** or **Import** buttons to save/load `.txt` files.

---

## Notes

- All **IDs must be unique**.
- The application does **not use Qt Designer**; all widgets are created programmatically.
- Proper memory management is ensured using **Qt parent-child relationships** and **QSharedPointer** for dynamic objects.

---

## Authors

- **Mani Dlamini** – BSc Mathematics & Computer Science
- **Original design inspired by**: Qt/C++ design patterns tutorials

---

## License

This project is open-source under the **MIT License**.


