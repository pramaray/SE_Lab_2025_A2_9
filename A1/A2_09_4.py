
#Inventory Management System: Design a system to manage products for a store. Customers can make purchases, 
#and sellers can update the list of products. Use Git for version control, and maintain a purchase history of items.

# Assigned to: 
# Prama Ray (Roll no 002311001033)

# Collaborators:
# Ankita Dhara (Roll no 002311001034)
# Vidhi Mantry (Roll no 002311001043)

import sqlite3
from datetime import datetime

def initialize_db():
    conn = sqlite3.connect("A2_09_4.db")
    cursor = conn.cursor()
    
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            price REAL NOT NULL,
            quantity INTEGER NOT NULL
        )
    """)
    
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS purchases (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            product_id INTEGER,
            customer TEXT,
            quantity INTEGER,
            date TEXT,
            FOREIGN KEY (product_id) REFERENCES products(id)
        )
    """)
    
    conn.commit()
    conn.close()

def add_product():
    name = input("Enter Product Name: ")
    price = float(input("Enter Product Price: "))
    quantity = int(input("Enter Product Quantity: "))
    
    conn = sqlite3.connect("A2_09_4.db")
    cursor = conn.cursor()
    cursor.execute("INSERT INTO products (name, price, quantity) VALUES (?, ?, ?)", (name, price, quantity))
    conn.commit()
    conn.close()
    print("Product added successfully!")

def update_product():
    product_id = int(input("Enter Product ID to Update: "))
    new_qty = int(input("Enter New Quantity: "))
    
    conn = sqlite3.connect("A2_09_4.db")
    cursor = conn.cursor()
    cursor.execute("UPDATE products SET quantity = ? WHERE id = ?", (new_qty, product_id))
    conn.commit()
    conn.close()
    print("Product updated successfully!")

def delete_product():
    product_id = int(input("Enter Product ID to Delete: "))
    
    conn = sqlite3.connect("A2_09_4.db")
    cursor = conn.cursor()
    cursor.execute("DELETE FROM products WHERE id = ?", (product_id,))
    conn.commit()
    conn.close()
    print("Product deleted successfully!")

def display_products():
    conn = sqlite3.connect("A2_09_4.db")
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM products")
    products = cursor.fetchall()
    conn.close()
    
    print("\nAvailable Products:")
    print("ID\tName\tPrice\tQuantity")
    print("-----------------------------------")
    for product in products:
        print(f"{product[0]}\t{product[1]}\t${product[2]}\t{product[3]} pcs")

def purchase_product():
    product_id = int(input("Enter Product ID: "))
    qty = int(input("Enter Quantity: "))
    customer = input("Enter Your Name: ")
    
    conn = sqlite3.connect("A2_09_4.db")
    cursor = conn.cursor()
    cursor.execute("SELECT quantity FROM products WHERE id = ?", (product_id,))
    product = cursor.fetchone()
    
    if product and product[0] >= qty:
        new_qty = product[0] - qty
        cursor.execute("UPDATE products SET quantity = ? WHERE id = ?", (new_qty, product_id))
        cursor.execute("INSERT INTO purchases (product_id, customer, quantity, date) VALUES (?, ?, ?, ?)",
                       (product_id, customer, qty, datetime.now().strftime("%Y-%m-%d")))
        conn.commit()
        print("Purchase successful!")
    else:
        print("Error: Product not found or insufficient stock.")
    conn.close()

def display_purchase_history():
    conn = sqlite3.connect("A2_09_4.db")
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM purchases")
    purchases = cursor.fetchall()
    conn.close()
    
    print("\nPurchase History:")
    print("ID\tProduct ID\tCustomer\tQuantity\tDate")
    print("---------------------------------------------------")
    for purchase in purchases:
        print(f"{purchase[0]}\t{purchase[1]}\t{purchase[2]}\t{purchase[3]}\t{purchase[4]}")

def main():
    initialize_db()
    while True:
        role = int(input("\nAre you a (1) Seller or (2) Customer or (3) Exit? "))
        if role == 1:
            while True:
                choice = int(input("\n1. View Products\n2. Add Product\n3. Update Product\n4. Delete Product\n5. Back\nChoice: "))
                if choice == 1:
                    display_products()
                elif choice == 2:
                    add_product()
                elif choice == 3:
                    update_product()
                elif choice == 4:
                    delete_product()
                elif choice == 5:
                    break
        elif role == 2:
            while True:
                choice = int(input("\n1. View Products\n2. Purchase Product\n3. View Purchase History\n4. Back\nChoice: "))
                if choice == 1:
                    display_products()
                elif choice == 2:
                    purchase_product()
                elif choice == 3:
                    display_purchase_history()
                elif choice == 4:
                    break
        elif role == 3:
            print("Exiting the program. Goodbye!")
            break
        else:
            print("Invalid choice. Please enter a valid option.")

if __name__ == "__main__":
    main()
