/*
 * TestOne.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: alfredo
 */
#include <iostream>
#include <fstream>


using namespace std;

  class product
    {
        int pno;
        char name[50];
        float price, qty, tax, dis;
        public:
            void create_product()
            {
                cout << "\nPlease Enter The Product No. of The Product ";
                cin >> pno;
                cout << "\n\nPlease Enter The Name of The Product ";
                cin >> name;
                cout << "\nPlease Enter The Price of The Product ";
                cin >> price;
                cout << "\nPlease Enter The Discount (%) ";
                cin >> dis;
            }

        void show_product()
        {
            cout << "\nThe Product No. of The Product : " << pno;
            cout << "\nThe Name of The Product : ";
            puts(name);
            cout << "\nThe Price of The Product : " << price;
            cout << "\nDiscount : " << dis;
        }

        int retpno()
        {
            return pno;
        }

        float retprice()
        {
            return price;
        }

        char * retname()
        {
            return name;
        }

        int retdis()
        {
            return dis;
        }

    }; //class ends here

fstream fp;
product pr;


void write_product()
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
     cin.get();
}
//***************************************************************
// function to read all records from file
//****************************************************************
void display_all()
{
    system("clear");
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        pr.show_product();
        cout << "\n\n====================================\n";
        cin.get();

    }
    fp.close();
    cin.get();
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void display_sp(int n)
{
    int flag = 0;
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() == n)
        {
            system("clear");
            pr.show_product();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\n\nrecord not exist";
     cin.get();
}
//***************************************************************
// function to modify record of file
//****************************************************************
void modify_product()
{
    int no, found = 0;
    system("clear");
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No. of The Product";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0)
    {
        if (pr.retpno() == no)
        {
            pr.show_product();
            cout << "\nPlease Enter The New Details of Product" << endl;
            pr.create_product();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char * ) & pr, sizeof(product));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    cin.get();
}
//***************************************************************
// function to delete record of file
//****************************************************************
void delete_product()
{
    int no;
    system("clear");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() != no)
        {
            fp2.write((char * ) & pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\n\n\tRecord Deleted ..";
    cin.get();
//    getch();
}
//***************************************************************
// function to display all products price list
//****************************************************************

void menu()
{
    system("clear");
    fp.open("Shop.dat", ios:: in );
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        cout << "\n\n\n Program is closing ....";
        cin.get();
        exit(0);
    }

    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product)))
    {
        cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
    }
    fp.close();
}




void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
    cin.get();
    system("clear");
    cout << "\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\ n ";
    for (int x = 0; x <= c; x++)
    {
        fp.open("Shop.dat", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof())
        {
            if (pr.retpno() == order_arr[x])
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis() / 100);
                cout << "\n" << order_arr[x] << "\t" << pr.retname() <<
                    "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }

        fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    cin.get();
}



void intro()
{
system("clear");

    cout << "SUPER MARKET";
    cout << "BILLING";
    cout << "PROJECT";
    cout << "\n\nMADE BY : RAMO";

   cin.get();

}

//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{
    system("clear");
    char ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.QUERY ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU";
    cout << "\n\n\t7.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) ";
    cin >> ch2;
    switch (ch2)
    {
    case '1':
        system("clear");
        write_product();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        system("clear");
        cout << "\n\n\tPlease Enter The Product No. ";
        cin >> num;
        display_sp(num);
        break;
    case '4':
        modify_product();
        break;
    case '5':
        delete_product();
        break;
    case '6':
        menu();
        cin.get();
    case '7':
        break;
    default:
        cout << "\a";
        admin_menu();
    }
}


int main() {

char ch;
intro();
    do
    {

        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        cin >> ch;
        switch (ch)
        {
        case '1':
        system("clear");
            place_order();
            break;
        case '2':
            admin_menu();
            break;
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');

} //main

