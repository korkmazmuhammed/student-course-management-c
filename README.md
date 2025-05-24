# Student Course Management System in C

This is a menu-driven C program to manage and analyze student and instructor data.  
It reads user, course, and grade information from text files, allows various queries, and prints GPA, class statistics, and department info.

## Features

- Menu-based interface with these options:
    - Print pass/fail status of all users
    - Query by first initial (print users whose name starts with a given letter)
    - Calculate and display GPA of a given student
    - Print pass/fail status of all users in the same class
    - Display the number of classes an instructor teaches
    - List department for all users by role (student/instructor)
    - Show course ID for a student
    - Quit program
- Reads data from `first.txt` and `second.txt`
- Supports both student and instructor queries
- GPA calculation and class averages
- Works with comma and semicolon separated values

## How to Use

1. Prepare your input files:
    - `first.txt`: User data with grades and class IDs
    - `second.txt`: User data with names, roles, departments, etc.

2. Compile the program:
    ```bash
    gcc 220104004043.c -o student_course_manager
    ```

3. Run the program:
    ```bash
    ./student_course_manager
    ```

4. Choose an option from the menu and follow the prompts.

## Example Menu

