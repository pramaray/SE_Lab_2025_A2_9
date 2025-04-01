# Inventory Management System
 A simple Inventory Management System in C++ using CSV files for data storage. 
 It allows sellers to manage products and customers to purchase items while maintaining a purchase history.

 ## 📌 Features
### 👨‍💼 Seller Side
✅ Add Products – Add new products with name, price, and quantity.  
✅ Update Products – Modify the stock quantity of existing products.   
✅ Delete Products – Remove a product from inventory.   
✅ Auto-Remove Out-of-Stock Items – Products with 0 quantity are automatically deleted.   

### 🛒 Customer Side
✅ View Available Products – See all available items in stock.   
✅ Purchase Products – Buy products and record purchase history.   
✅ View Purchase History – See all past purchases.   

## 📂 Data Storage
🔹 products.csv – Stores product information.   
🔹 purchases.csv – Stores purchase history.   

## 📜 File Structure
📂 Inventory-Management   
 ├── inventory.cpp        # Main C++ source code   
 ├── products.csv         # Product inventory storage   
 ├── purchases.csv        # Purchase history storage    
 ├── README.md            # Project Documentation   

## 🛠️ How to Run
### 1️⃣ Compile the Program
g++ inventory.cpp -o inventory
### 2️⃣ Run the Executable
./inventory

## 📂 CSV File Format
### products.csv (Stores Inventory)
| id	| name	| price |	quantity |
|-----|-------|-------|----------|
| 1 |	Laptop	| 800.50	| 5 |
| 2 |	Mouse	 | 20.00 | 10 |
## purchases.csv (Stores Purchase History)
| id	| product_id	| customer	| quantity	| date |
|-----|-------------|-----------|-----------|------|
| 1 |	2	| Alice |	2	 | 2025-03-31 |

## Assigned to: 
Prama Ray _(Roll no 002311001033)_

## Collaborators:
Ankita Dhara _(Roll no 002311001034)_   
Vidhi Mantry _(Roll no 002311001043)_  
