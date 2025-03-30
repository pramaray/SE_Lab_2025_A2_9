#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

struct Purchase {
    int id;
    int product_id;
    string customer;
    int quantity;
    string date;
};

// Load products from CSV
vector<Product> loadProducts() {
    vector<Product> products;
    ifstream file("products.csv");

    if (!file) {
        cerr << "Error opening products.csv. Creating a new file...\n";
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

// Save updated products to CSV (removes out-of-stock items)
void saveProducts(const vector<Product>& products) {
    ofstream file("products.csv");
    if (!file) {
        cerr << "Error writing to products.csv\n";
        return;
    }

    file << "id,name,price,quantity\n"; // Write header
    for (const auto& p : products) {
        if (p.quantity > 0) { // Auto-remove out-of-stock items
            file << p.id << "," << p.name << "," << p.price << "," << p.quantity << "\n";
        }
    }
    file.close();
}

// Display available products
void displayProducts(const vector<Product>& products) {
    cout << "\nAvailable Products:\n";
    cout << "ID\tName\t\tPrice\tQuantity\n";
    cout << "-----------------------------------\n";
    for (const auto& p : products) {
        cout << p.id << "\t" << p.name << "\t$" << p.price << "\t" << p.quantity << " pcs\n";
    }
}

// Seller: Add a new product
void addProduct(vector<Product>& products) {
    Product newProduct;
    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, newProduct.name);
    cout << "Enter Product Price: ";
    cin >> newProduct.price;
    cout << "Enter Product Quantity: ";
    cin >> newProduct.quantity;

    newProduct.id = products.empty() ? 1 : products.back().id + 1;
    products.push_back(newProduct);

    ofstream file("products.csv", ios::app);
    if (!file) {
        cerr << "Error writing to products.csv\n";
        return;
    }
    file << newProduct.id << "," << newProduct.name << "," << newProduct.price << "," << newProduct.quantity << "\n";
    file.close();

    cout << "Product added successfully!\n";
}

// Seller: Update product quantity
void updateProduct(vector<Product>& products) {
    int id, newQty;
    cout << "Enter Product ID to Update: ";
    cin >> id;
    cout << "Enter New Quantity: ";
    cin >> newQty;

    bool found = false;
    for (auto& p : products) {
        if (p.id == id) {
            p.quantity = newQty;
            found = true;
            break;
        }
    }

    if (found) {
        saveProducts(products);
        cout << "Product updated successfully!\n";
    } else {
        cout << "Product not found.\n";
    }
}

// Seller: Delete a product
void deleteProduct(vector<Product>& products) {
    int id;
    cout << "Enter Product ID to Delete: ";
    cin >> id;

    bool found = false;
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == id) {
            products.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        saveProducts(products);
        cout << "Product deleted successfully!\n";
    } else {
        cout << "Product not found.\n";
    }
}

// Get the next available purchase ID
int getNextPurchaseID() {
    ifstream file("purchases.csv");
    if (!file) return 1; 

    string line, lastLine;
    while (getline(file, line)) lastLine = line;
    file.close();

    if (lastLine.empty() || lastLine.find("id,product_id") != string::npos) return 1;

    stringstream ss(lastLine);
    string lastID;
    getline(ss, lastID, ',');
    return stoi(lastID) + 1;
}

// Customer: Purchase a product
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

    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);

    int purchaseID = getNextPurchaseID();

    ifstream checkFile("purchases.csv");
    bool fileExists = checkFile.good();
    checkFile.close();

    ofstream file("purchases.csv", ios::app);
    if (!file) {
        cerr << "Error writing to purchases.csv\n";
        return;
    }

    if (!fileExists) {
        file << "id,product_id,customer,quantity,date\n";
    }

    file << purchaseID << "," << id << "," << customer << "," << qty << "," << date << "\n";
    file.close();

    saveProducts(products);
    cout << "Purchase successful! Data stored in purchases.csv\n";
}

// Display purchase history
void displayPurchaseHistory() {
    ifstream file("purchases.csv");
    if (!file) {
        cerr << "Error opening purchases.csv\n";
        return;
    }

    string line;
    getline(file, line);
    cout << "\nPurchase History:\n";
    cout << "ID\tProduct ID\tCustomer\tQuantity\tDate\n";
    cout << "---------------------------------------------------\n";
    
    while (getline(file, line)) {
        stringstream ss(line);
        string id, product_id, customer, quantity, date;
        
        getline(ss, id, ',');
        getline(ss, product_id, ',');
        getline(ss, customer, ',');
        getline(ss, quantity, ',');
        getline(ss, date, ',');

        cout << id << "\t" << product_id << "\t" << customer << "\t" << quantity << "\t" << date << "\n";
    }
    file.close();
}

// Main Menu
int main() {
    vector<Product> products = loadProducts();
    int choice;
    cout << "Are you a (1) Seller or (2) Customer? ";
    cin >> choice;

    if (choice == 1) {
        int sellerChoice;
        do {
            cout << "\n1. Add Product\n2. Update Product\n3. Delete Product\n4. Exit\nChoice: ";
            cin >> sellerChoice;
            if (sellerChoice == 1) addProduct(products);
            else if (sellerChoice == 2) updateProduct(products);
            else if (sellerChoice == 3) deleteProduct(products);
        } while (sellerChoice != 4);
    } else {
        int customerChoice;
        do {
            cout << "\n1. View Products\n2. Purchase Product\n3. View Purchase History\n4. Exit\nChoice: ";
            cin >> customerChoice;
            if (customerChoice == 1) displayProducts(products);
            else if (customerChoice == 2) purchaseProduct(products);
            else if (customerChoice == 3) displayPurchaseHistory();
        } while (customerChoice != 4);
    }
    return 0;
}

