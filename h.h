#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>   // For getch()
#include <windows.h> // For system("Color") and Sleep()

using namespace std;

class Product
{
public:
    string productId;
    string productName;
    double price;
    string description;
    int stockQuantity;

    Product() : productId(""), productName(""), price(0.0), description(""), stockQuantity(0) {}

    Product(const string &id, const string &name, double productPrice, const string &desc, int stock)
        : productId(id), productName(name), price(productPrice), description(desc), stockQuantity(stock) {}

    void inputProductDetails()
    {
        cout << "Enter product ID: ";
        getline(cin, productId);
        cout << "Enter product name: ";
        getline(cin, productName);
        cout << "Enter price: ";
        cin >> price;
        cin.ignore();
        cout << "Enter description: ";
        getline(cin, description);
        cout << "Enter Quantity: ";
        cin >> stockQuantity;
        cin.ignore();
        ofstream file("products.txt", fstream::app);
        if (file.is_open())
        {
            file << std::fixed << std::setprecision(2);
            file << productId << "|" << productName << "|" << price << "|" << description << "|" << stockQuantity << "\n";

            file.close();
        }
        else
        {
            cout << "Unable to open file";
        }
    }

    void displayProductDetails() const
    {
        cout << "Product ID: " << productId << "\n";
        cout << "Name: " << productName << "\n";
        cout << "Price: $" << price << "\n";
        cout << "Description: " << description << "\n";
        cout << "Quantity: " << stockQuantity << "\n";
    }
};

class ProductNode
{
public:
    Product product;
    ProductNode *next;

    ProductNode(const Product &prod) : product(prod), next(nullptr) {}
};
class ProductLinkedList
{
public:
    ProductNode *head;

    ProductLinkedList() : head(nullptr) {}
    void generateReport()
    {
        if (!head)
        {
            std::cout << "No products to report.\n";
            return;
        }
        double totalValue = 0.0;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Product Report:\n";
        std::cout << "ID\tName\tPrice\tDescription\tStock\t\tTotal Value\n";
        for (ProductNode *current = head; current; current = current->next)
        {
            double productValue = current->product.price * current->product.stockQuantity;
            totalValue += productValue;
            std::cout << current->product.productId << "\t"
                      << current->product.productName << "\t$"
                      << current->product.price << "\t"
                      << current->product.description.substr(0, 10) << "...\t"
                      << current->product.stockQuantity << "\t$"
                      << productValue << "\n";
        }
        std::cout << "Total inventory value: $" << totalValue << "\n";
        ofstream file("report.txt", fstream::app);
        if (file.is_open())
        {
            file << std::fixed << std::setprecision(2);
            file << "ID\tName\tPrice\tDescription\tStock\t\tTotal Value\n";

            double totalValue = 0; // Assuming totalValue is declared somewhere

            for (ProductNode *current = head; current; current = current->next)
            {
                double productValue = current->product.price * current->product.stockQuantity;
                totalValue += productValue;
                file << current->product.productId << "\t"
                     << current->product.productName << "\t$"
                     << current->product.price << "\t"
                     << current->product.description.substr(0, 10) << "...\t"
                     << current->product.stockQuantity << "\t$"
                     << productValue << "\n";
            }

            file.close(); // Close the file
        }
        else
        {
            std::cout << "Unable to open file";
        }
    }

    ~ProductLinkedList()
    {
        while (head)
        {
            ProductNode *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void loadExistingProduct(Product product)
    {
        ProductNode *newNode = new ProductNode(product);
        newNode->next = head;
        head = newNode;
    }

    void insertProduct()
    {
        cout << "This is insert product page\n"
             << endl;
        Product newProduct;
        newProduct.inputProductDetails();
        ProductNode *newNode = new ProductNode(newProduct);
        newNode->next = head;
        head = newNode;
        cout << "Product  added" << endl;
    }

    void displayProducts()
    {
        if (!head)
        {
            cout << "No products available.\n";
            return;
        }
        for (ProductNode *current = head; current; current = current->next)
        {
            current->product.displayProductDetails();
            cout << "-----------------\n";
        }
    }

    void removeProduct()
    {
        cout << "This is remove product page\n"
             << endl;
        string productId;
        cout << "Enter product ID to remove: ";
        getline(cin, productId);

        ProductNode *temp = head, *prev = nullptr;
        while (temp && temp->product.productId != productId)
        {
            prev = temp;
            temp = temp->next;
        }

        if (!temp)
        {
            cout << "Product not found.\n";
            return;
        }

        if (!prev)
        {
            head = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }

        delete temp;
        cout << "Product removed.\n";
    }
};

class ShoppingCart
{
public:
    list<Product> cart;

    void addToCart(const Product &product)
    {
        if (product.stockQuantity > 0)
        {
            int buyQuantity;
            cart.push_back(product);
            std::cout << "Enter the Quantity: ";
            std::cin >> buyQuantity;
            cout << "Added to cart: " << product.productName << "\n";
            cout << "Quantity: " << buyQuantity << endl;
        }
        else
        {
            cout << "Product is out of stock.\n";
        }
    }

    void displayCart()
    {
        cout << "This is display cart page\n"
             << endl;
        if (cart.empty())
        {
            cout << "Your cart is empty.\n";
            return;
        }
        double total = 0.0;
        for (const auto &product : cart)
        {
            product.displayProductDetails();
            total = product.price * product.stockQuantity;
        }
        cout << "Total Cart Value: $" << total << "\n";
    }

    void clearCart()
    {
        cout << "This is payment product page\n"
             << endl;
        if (cart.empty())
        {
            std::cout << "Your cart is empty. No payment required.\n";
            return;
        }

        double total = 0.0;
        std::cout << "Items in your cart:\n";
        for (const auto &product : cart)
        {
            product.displayProductDetails();
            total += product.price * product.stockQuantity;
        }
        std::cout << "Total amount to be paid: $" << std::fixed << std::setprecision(2) << total << "\n";
        cart.clear();
        cout << " \n------------ Shopping Cart-----------" << endl;
        cout << "This is our payment pricessing *_* " << endl;
        cout << "\n";
        cout << "ABA Account : (000 474 063)" << endl;
        cout << "ACLIDA Account : (000 226 866)" << endl;
        cout << "\n";
        cout << "\nThank you for shopping with us. We love your money" << endl;
    }
};

void loadProducts(ProductLinkedList &productList)
{
    ifstream file("products.txt");
    if (!file.is_open())
    {
        return;
    }

    string line;
    while (getline(file, line))
    {
        Product product;
        istringstream iss(line);
        getline(iss, product.productId, '|');
        getline(iss, product.productName, '|');
        iss >> product.price;
        iss.ignore();
        getline(iss, product.description, '|');
        iss >> product.stockQuantity;

        productList.loadExistingProduct(product);
    }

    file.close();
}
void userInteraction(ProductLinkedList &productList, ShoppingCart &cart)
{
    int choice;
    do
    {
        cout << "1. Menu product\n";
        cout << "2. View Cart\n";
        cout << "3. Payment\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
        {
            cout << "\t\t\tThis is our product list please enjoy your shopping\n";
            productList.displayProducts();
            string productId;
            cout << "Enter product ID to add to cart: ";
            getline(cin, productId);
            Product *product = nullptr;
            // Find product by ID
            ProductNode *current = productList.head;
            while (current)
            {
                if (current->product.productId == productId)
                {
                    product = &current->product;
                    break;
                }
                current = current->next;
            }
            if (product)
            {
                cart.addToCart(*product);
            }
            else
            {
                cout << "Product not found.\n";
            }
            break;
        }
        case 2:
            cart.displayCart();
            break;
        case 3:
            cart.clearCart();
            break;
        case 4:
            cout << "Program exit";
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);
}

void adminInteraction(ProductLinkedList &productList, ShoppingCart &cart)
{
    int choice;
    do
    {
        cout << "\nMain Menu:\n";
        cout << "1. Add Product to inventory\n";
        cout << "2. View Products\n";
        cout << "3. Remove Product from Inventory\n";
        cout << "4. Generate report\n";
        cout << "5. Go back to customer feature\n";
        cout << "6. Exit\n";
        // i have to add function go back go back where? go back to menu
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
            productList.insertProduct();
            break;
        case 2:
            productList.displayProducts();
            break;
        case 3:
            productList.removeProduct();
            break;
        case 4:
            productList.generateReport();
            break;
        case 5:
            cout << "\nEnter 0 to go back: ";
            cin >> choice;
            if (choice == 0)
            {
                //  userInteraction(productList,cart);
                // write more void here
                userInteraction(productList, cart);
                break;
            }
        case 6:
            cout << "Program exit\n"<<endl;
            break;
            // write code here
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 6);
}
