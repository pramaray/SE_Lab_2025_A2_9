#include <iostream>
#include <sqlite3.h>
#include <vector>

using namespace std;

class TaskManager {
public:
    TaskManager(const string& db_name) {
        sqlite3_open(db_name.c_str(), &db);
        createTables();
    }

    ~TaskManager() {
        sqlite3_close(db);
    }

    void addTask(const string& title, const string& description) {
        string sql = "INSERT INTO tasks (title, description, status) VALUES (?, ?, 'pending');";
        vector<string> params;
        params.push_back(title);
        params.push_back(description);
        executeSQL(sql, params);
    }
    
    void editTask(int task_id, const string& new_title, const string& new_description) {
        string sql = "UPDATE tasks SET title=?, description=? WHERE id=?;";
        vector<string> params;
        params.push_back(new_title);
        params.push_back(new_description);
        params.push_back(to_string(task_id));
        executeSQL(sql, params);
    }
    
    void completeTask(int task_id) {
        string sql = "UPDATE tasks SET status='completed' WHERE id=?;";
        vector<string> params;
        params.push_back(to_string(task_id));
        executeSQL(sql, params);
    }
    
    void deleteTask(int task_id) {
        string sql = "DELETE FROM tasks WHERE id=?;";
        vector<string> params;
        params.push_back(to_string(task_id));
        executeSQL(sql, params);
    }

    void listTasks() {
        string sql = "SELECT id, title, description, status FROM tasks;";
        vector<string> params;
        executeSQL(sql, params, true);
    }
    
    
    void showHistory() {
        string sql = "SELECT * FROM history;";
        vector<string> params; 
        executeSQL(sql, params, true);
    }
    
    void resetSystem() {
        string sql = "DROP TABLE IF EXISTS tasks; DROP TABLE IF EXISTS history;";
        vector<string> params;  
        executeSQL(sql, params);
        createTables();
        cout << "System reset successfully.\\n";
    }
    
private:
    sqlite3* db;

    void createTables() {
        const char* task_table = 
            "CREATE TABLE IF NOT EXISTS tasks ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT NOT NULL, "
            "description TEXT NOT NULL, "
            "status TEXT NOT NULL);";
    
        sqlite3_exec(db, task_table, 0, 0, 0);
    
        const char* history_table = 
            "CREATE TABLE IF NOT EXISTS history ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "task_id INTEGER, "
            "action TEXT, "
            "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";
    
        sqlite3_exec(db, history_table, 0, 0, 0);
    }
    

    void logHistory(int task_id, const string& action) {
        string sql = "INSERT INTO history (task_id, action) VALUES (?, ?);";
        vector<string> params;
        params.push_back(to_string(task_id));
        params.push_back(action);
        executeSQL(sql, params);
    }

    void executeSQL(const string& sql, const vector<string>& params, bool fetch = false) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        for (size_t i = 0; i < params.size(); ++i) {
            sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_STATIC);
        }
        
        while (sqlite3_step(stmt) == SQLITE_ROW && fetch) {
            for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                cout << sqlite3_column_text(stmt, i) << " | ";
            }
            cout << "\n";
        }
        sqlite3_finalize(stmt);
    }
};

int main() {
    cout << "\nWelcome to the Task Management Tool!\n";
    TaskManager tm("tasks.db");
    int choice;
    do {
        cout << "\nCommands:";
        cout << "\n1. Add Task";
        cout << "\n2. Edit Task";
        cout << "\n3. Complete Task";
        cout << "\n4. View Tasks";
        cout << "\n5. View Task History";
        cout << "\n6. Delete Task";
        cout << "\n7. Reset System";
        cout << "\n8. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string title, desc;
                cout << "Enter task title: ";
                getline(cin, title);
                cout << "Enter task description: ";
                getline(cin, desc);
                tm.addTask(title, desc);
                break;
            }
            case 2: {
                int id;
                string new_title, new_desc;
                cout << "Enter task ID to edit: ";
                cin >> id;
                cin.ignore();
                cout << "Enter new task title: ";
                getline(cin, new_title);
                cout << "Enter new task description: ";
                getline(cin, new_desc);
                tm.editTask(id, new_title, new_desc);
                break;
            }
            case 3: {
                int id;
                cout << "Enter task ID to complete: ";
                cin >> id;
                tm.completeTask(id);
                break;
            }
            case 4:
                tm.listTasks();
                break;
            case 5:
                tm.showHistory();
                break;
            case 6: {
                int id;
                cout << "Enter task ID to delete: ";
                cin >> id;
                tm.deleteTask(id);
                break;
            }
            case 7:
                tm.resetSystem();
                break;
            case 8:
                cout << "Exiting!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);
    return 0;
}
