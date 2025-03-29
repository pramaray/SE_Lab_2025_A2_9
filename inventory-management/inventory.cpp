#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

// Structure for product data
struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

// Load products from CSV
vector<Product> loadProducts() {
    vector<Product> products;
    ifstream file("products.csv");
    if (!file) {
        cerr << "Error opening products.csv\n";
        return products;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        Product p;
        string temp;
        
        getline(ss, temp, ','); p.id = stoi(temp);
        getline(ss, p.name, ',');
        getline(ss, temp, ','); p.price = stod(temp);
        getline(ss, temp, ','); p.quantity = stoi(temp);

        products.push_back(p);
    }
    file.close();
    return products;
}

// Save updated products to CSV
void saveProducts(const vector<Product>& products) {
    ofstream file("products.csv");
    if (!file) {
        cerr << "Error writing to products.csv\n";
        return;
    }

    file << "id,name,price,quantity\n"; // Write header
    for (const auto& p : products) {
        file << p.id << "," << p.name << "," << p.price << "," << p.quantity << "\n";
    }
    file.close();
}

// Display all products
void displayProducts(const vector<Product>& products) {
    cout << "\nAvailable Products:\n";
    cout << "ID\tName\t\tPrice\tQuantity\n";
    cout << "-----------------------------------\n";
    for (const auto& p : products) {
        cout << p.id << "\t" << p.name << "\t$" << p.price << "\t" << p.quantity << " pcs\n";
    }
}

// Add a new product
void addProduct(vector<Product>& products) {
    Product p;
    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Price: ";
    cin >> p.price;
    cout << "Enter Quantity: ";
    cin >> p.quantity;
    p.id = products.empty() ? 1 : products.back().id + 1;

    products.push_back(p);
    saveProducts(products);
    cout << "Product added successfully!\n";
}

// Purchase a product
void purchaseProduct(vector<Product>& products) {
    int id, qty;
    string customer;

    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Quantity: ";
    cin >> qty;
    cout << "Enter Your Name: ";
    cin.ignore();
    getline(cin, customer);

    bool found = false;
    for (auto& p : products) {
        if (p.id == id && p.quantity >= qty) {
            p.quantity -= qty;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product not found or insufficient stock.\n";
        return;
    }

    // Get current date
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);

    // Save purchase details to purchases.csv
    ofstream file("purchases.csv", ios::app);
    if (!file) {
        cerr << "Error writing to purchases.csv\n";
        return;
    }
    file << id << "," << id << "," << customer << "," << qty << "," << date << "\n";
    file.close();

    saveProducts(products);
    cout << "Purchase successful!\n";
}

// Main function
int main() {
    vector<Product> products = loadProducts();
    int choice;
    do {
        cout << "\nInventory Management System\n";
        cout << "1. Display Products\n";
        cout << "2. Add Product\n";
        cout << "3. Purchase Product\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayProducts(products); break;
            case 2: addProduct(products); break;
            case 3: purchaseProduct(products); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}

