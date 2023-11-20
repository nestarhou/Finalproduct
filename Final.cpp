#include<iostream>
#include"h.h"
using namespace std;
int main()
{

    ProductLinkedList productList;
    ShoppingCart cart;

    loadProducts(productList);

    char startValue;
    cout.width(100);
    cout << "\t\t8888888888                                                                                    " << endl;
    cout.width(100);
    cout << "\t\t888                                                                                           " << endl;
    cout.width(100);
    cout << "\t\t888                                                                                           " << endl;
    cout.width(100);
    cout << "\t\t8888888          .d8888b .d88b.  88888b.d88b.  88888b.d88b.   .d88b.  888d888 .d8888b .d88b.  " << endl;
    cout.width(100);
    cout << "\t\t888             d88P    d88**88b 888 *888 *88b 888 *888 *88b d8P  Y8b 888P*  d88P*   d8P  Y8b " << endl;
    cout.width(100);
    cout << "\t\t888      888888 888     888  888 888  888  888 888  888  888 88888888 888    888     88888888 " << endl;
    cout.width(100);
    cout << "\t\t888             Y88b.   Y88..88P 888  888  888 888  888  888 Y8b.     888    Y88b.   Y8b.     " << endl;
    cout.width(100);
    cout << "\t\t8888888888       *Y8888P *Y88P*  888  888  888 888  888  888  *Y8888  888     *Y8888P *Y8888  " << endl;
    cout << endl;
    cout << "\t\t\t\t\tPlease press s to start our program" << endl;
start:
    cin >> startValue;

    if (startValue == 's' || startValue == 'S')
    {
        // Loading UI
        cout << "\n\n\n\n\t\tLoading...\n\t\t\t";
        for (int x = 0; x <= 40; x++)
        {
            cout << char(219);
            if (x < 15)
            {
                system("Color 0c");
                Sleep(10);
            }
            else if (x < 30)
            {
                system("Color 0e");
                Sleep(50);
            }
            else if (x < 40)
            {
                system("Color 0a");
                Sleep(60);
            }
        }
    }
    else
    {
        cout << "You entered the wrong way, please start with s" << endl;
        getch();
        goto start;
    }
    system("pause");
    system("cls");
    system("color 0f");
    int cho;
    do
    {
        string adminPassword = "password123";
        cout << "\n\n\t\t\t*** Welcome to our onlineShopping paradise! ***" << endl;
        cout << "\n\n\t\t\tGet ready to fulfill your shopping dreams! \n";
        cout << "\n\n\t\t\t1. Administration (Enter secret portal) \n";
        cout << "\n\n\t\t\t2. Customer (Shop till you drop!) \n";
        cout << "\n\n\t\t\t3. Exit (Don't leave yet!) \n";
        cout << "\n\n\t\t\tEnter your choice young padawan: ";
        cin >> cho;
        cin.ignore();
        if (cho == 1)
        {
            string passwordEntered;
            cout << "\nEnter administration password: ";
            cin >> passwordEntered;

            if (passwordEntered == adminPassword)
            {
                // allow entry to admin section
                adminInteraction(productList, cart);
                system("cls");
            }
            else
            {
                cout << "Invalid password, try again!\n";
            }
        }
        switch (cho)
        {
        case 1:
        {
            if (cho == 1)
            {
                string passwordEntered;
                cout << "\nEnter administration password: ";
                cin >> passwordEntered;

                if (passwordEntered == adminPassword)
                {
                    // allow entry to admin section
                    adminInteraction(productList, cart);
                    system("cls");
                }
                else
                {
                    cout << "Invalid password, try again!\n";
                }
            }
            //  adminInteraction(productList, cart);
            //  system("cls");
            //  break;
        }
        case 2:
        {
            userInteraction(productList, cart);
            system("cls");
            break;
        }
        case 3:
        {
            cout << "Program exit";
            system("cls");
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (cho != 3);

    return 0;
}
