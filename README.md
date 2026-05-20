# Company Management System (CMS)

A console-based C project for managing employee records.  
The system stores employee data in a text file and allows the user to add, delete, modify, search, print/sort, save, and quit safely.

## Project Overview

This project was developed for the CSE 126N course. It is designed as a simple employee database management system for a company. Each employee record contains:

- Employee ID
- Full name
- Salary
- Date of birth
- Address
- Mobile number
- Date of enrollment
- Email address

The program uses a text file named `data.txt` as the database.

## Main Features

- Load employee records from `data.txt`
- Add a new employee
- Prevent duplicated employee IDs
- Validate employee name, salary, birth date, mobile number, and email
- Delete employee by ID
- Modify employee data
- Search employee by full or partial name
- Print employees sorted by:
  - Name
  - Salary
  - Date of birth
- Save updates to the file
- Warn before quitting without saving

## Repository Structure

```text
company-management-system/
├── main.c
├── data.txt
├── README.md
├── .gitignore
└── docs/
    └── project-report.pdf
```

## How to Compile

Using GCC:

```bash
gcc main.c -o cms
```

## How to Run

```bash
./cms
```

On Windows:

```bash
gcc main.c -o cms.exe
cms.exe
```

## Important Note

The file `data.txt` must exist in the same folder as the compiled program, because the code opens this file when the program starts.

## Example Data Format

Each line in `data.txt` should follow this format:

```text
ID,Name,Salary,day-month-year,Address,Mobile,day-month-year,Email
```

Example:

```text
123,Steven Thomas,15000.00,10-6-1994,26 Elhoreya Street,0123456789,15-9-2022,sthomas@gmail.com
```

## Menu Options

When the program starts, it displays this menu:

```text
1- ADD
2- DELETE
3- MODIFY
4- SEARCH
5- PRINT
6- SAVE
7- QUIT
```

## Algorithms Used

The project mainly uses:

- File handling in C
- Structures
- Arrays of structures
- Input validation
- Linear search
- Bubble sort for sorting employees

## Authors

Course project for CSE 126N, Computer & Communication Engineering.
