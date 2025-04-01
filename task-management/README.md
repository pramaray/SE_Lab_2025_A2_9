# Task Management CLI Tool

## 🚀 Introduction
The **Task Management CLI Tool** is a simple yet powerful command-line application written in **C++** that allows users to efficiently manage their tasks. It provides features such as adding, editing, completing, deleting, and viewing tasks. Additionally, it includes a version control system to track changes and maintain a history of all task modifications.

## ✨ Features
- ✅ **Add Task** – Create new tasks with a title and description.
- ✅ **Edit Task** – Modify existing tasks.
- ✅ **Complete Task** – Mark tasks as completed.
- ✅ **View Tasks** – Display all tasks with their current status.
- ✅ **View Task History** – Track all changes made to tasks.
- ✅ **Delete Task** – Remove tasks from the system.
- ✅ **Reset System** – Clear all tasks and reset the database.

## 🛠️ Technology Stack
- **Language:** C++
- **Database:** SQLite

## 📥 Installation
### 🔧 Prerequisites
Ensure you have the following installed:
-  **g++** (GCC Compiler)
-  **SQLite3** library

### 💻 Compilation
Run the following command to compile the program:
```sh
 g++ -std=c++11 task_management.cpp -o task_management -lsqlite3
```

### ▶️ Running the Program
After compilation, execute the program:
```sh
./task_management
```

## 📌 Usage
Upon running the program, one will see the following menu:
```
 Welcome to Task Management CLI Tool!

 Commands:
1. Add Task
2. Edit Task
3. Complete Task
4. View Tasks
5. View Task History
6. Delete Task
7. Reset System
8. Exit
```
Select an option by entering the corresponding number and follow the prompts.

## 📂 Database Structure
The tool uses **SQLite** to store tasks and their history.

### `tasks` Table
|  Column      |  Type    | Description                         |
|--------------|--------|-------------------------------------|
|  id         | INT    | Unique task ID                     |
|  title      | TEXT   | Title of the task                  |
|  description| TEXT   | Detailed task description          |
|  status     | TEXT   | Task status (e.g., "pending", "completed") |

### `history` Table
|  Column     |  Type    |  Description                        |
|------------|--------|----------------------------------|
|  id         | INT    | Unique history entry ID          |
|  task_id    | INT    | ID of the associated task        |
|  action     | TEXT   | Description of action performed  |
|  timestamp  | DATETIME | Time of the action               |

## Assigned to:
Vidhi Mantry _(Roll number 002311001043)_

## Collaborators:
Prama Ray _(Roll number 002311001033)_
Ankita Dhara _(Roll number 002311001034)_

## 📜 License
This project is open-source and licensed under the **MIT License**.

---

