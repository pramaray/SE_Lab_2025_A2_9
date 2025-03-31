import sqlite3

teachers = {
    "T001": "math",
    "T002": "science",
    "T003": "english"
}

def initialize_database():
    conn = sqlite3.connect('marks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS marks (
                    roll_number INTEGER PRIMARY KEY,
                    name TEXT,
                    math_marks INTEGER DEFAULT 0,
                    science_marks INTEGER DEFAULT 0,
                    english_marks INTEGER DEFAULT 0,
                    total_marks INTEGER DEFAULT 0
                )''')
    conn.commit()
    conn.close()

def add_student(roll_number, name):
    conn = sqlite3.connect('marks.db')
    c = conn.cursor()
    try:
        c.execute("INSERT INTO marks (roll_number, name) VALUES (?, ?)", (roll_number, name))
        conn.commit()
        print("Student added successfully.")
    except sqlite3.IntegrityError:
        print("Error: Roll number already exists!")
    conn.close()

def update_marks(teacher_id, roll_number, marks):
    if teacher_id not in teachers:
        print("Invalid teacher ID. Access denied.")
        return

    subject = teachers[teacher_id]
    column_name = subject + "_marks"

    conn = sqlite3.connect('marks.db')
    c = conn.cursor()
    query = f"UPDATE marks SET {column_name} = ? WHERE roll_number = ?"
    c.execute(query, (marks, roll_number))
    
    # Update total marks
    c.execute("""
        UPDATE marks
        SET total_marks = COALESCE(math_marks, 0) + COALESCE(science_marks, 0) + COALESCE(english_marks, 0)
        WHERE roll_number = ?
    """, (roll_number,))
    
    conn.commit()
    conn.close()
    print(f"Marks updated successfully for {subject} by Teacher {teacher_id}.")

def sort_database():
    conn = sqlite3.connect('marks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM marks ORDER BY total_marks DESC")
    result = c.fetchall()
    conn.close()
    return result

def display_students(students):
    print("\n{:<12} {:<20} {:<12} {:<12} {:<12} {:<12}".format(
        "Roll Number", "Name", "Math Marks", "Science Marks", "English Marks", "Total Marks"))
    print("-" * 80)

    for student in students:
        print("{:<12} {:<20} {:<12} {:<12} {:<12} {:<12}".format(*student))
    print()

def display_menu():
    print("\nMenu:")
    print("1. Add Student")
    print("2. Update Marks")
    print("3. View Student Information")
    print("4. Exit")

def check_roll_number(roll_number):
    conn = sqlite3.connect('marks.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM marks WHERE roll_number = ?", (roll_number,))
    result = cursor.fetchone()
    conn.close()

    if result:
        return True
    else:
        print(f"Roll number {roll_number} does not exist in the database.")
        return False

def main():
    initialize_database()

    while True:
        display_menu()
        choice = input("Enter your choice: ")

        if choice == "1":
            roll_number = int(input("Enter roll number: "))
            name = input("Enter name: ")
            add_student(roll_number, name)

        elif choice == "2":
            teacher_id = input("Enter your Teacher ID: ").strip()
            if teacher_id in teachers:
                while True:
                    roll_number = int(input("Enter roll number: "))
                    if check_roll_number(roll_number):
                        break
                subject = teachers[teacher_id]
                marks = int(input(f"Enter marks for {subject}: "))
                update_marks(teacher_id, roll_number, marks)
            else:
                print("Invalid teacher ID. Access denied.")

        elif choice == "3":
            students = sort_database()
            display_students(students)

        elif choice == "4":
            print("Exiting program.")
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
