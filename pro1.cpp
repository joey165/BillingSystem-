#include<iostream>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<fstream>
#include<string.h>
using namespace std;

class Product
{
  public:
    int pno;
    char name[50];
    float price, qty, tax, dis, netamt, gross;
    
      void createProduct(){
       cout << "\n Product Number: "<<endl;
       cin >> pno;
       cout << "\n Product Name: "<<endl;
       cin>>name;
       cout << "\n Prdouct Price: "<<endl;
       cin >> price;
       cout<<" \nProduct Quantity: "<<endl;
       cin>>qty;
       cout << "\n Product Discount (%): "<<endl;
       cin >> dis;
       cout<<"\n Tax percent: "<<endl;
       cin>>tax;
      }

      void show_product() 
        {
            cout << "\nThe Product No. of The Product : " << pno;
            cout << "\nThe Name of The Product : "<<name;
            cout << "\nThe Price of The Product : " << price;
            cout << "\nThe Qunatity of  The Product: "<< qty;
            cout << "\nDiscount : " << dis;
            cout << "\nTax Percent : "<<tax;
        }
        int storeProductdata();
        void viewProductdata();
        void deleteProductdata();
        void updateProductdata();
        void displayall();
        void calculate();
        
};
 fstream fp;
 Product pr;
//WRITE DATA IN FILE
 int Product :: storeProductdata()
 {
   fp.open("product1.txt",ios::app|ios::binary);
   pr.createProduct();
   pr.calculate();
   fp.write((char*) &pr,sizeof(Product));
   fp.close();
   cout << "\n\nThe Product Has Been Created ";
   getch();
   return 0;
 }
//READ DATA FROM FILE
 void Product :: viewProductdata()
 {
     fp.open("product1.txt",ios::in|ios::binary);
     if(!fp){
         cout<<"file not found"<<endl;
     }
     else{
         fp.read((char*) &pr,sizeof(Product));
         while(!fp.eof()){
             show_product();
             fp.read((char*) &pr,sizeof(Product));
         }
         fp.close();
     }
 }
 void Product ::deleteProductdata()
 {
    int no;
    system("CLS");
    cout << "\n\nDelete Record: ";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete: ";
    cin >>no;
    fp.open("product1.txt", ios:: in | ios::out);
    fstream fp2;
    fp2.open("temp1.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(Product))) 
    {
        if (pr.pno != no) 
        {
            fp2.write((char * ) & pr, sizeof(Product));
        }
    }
    fp2.close();
    fp.close();
    remove("product1.txt");
    rename("temp1.txt", "product1.txt");
    cout << "\n\n\tRecord Deleted ..";
    getch();
 }
 void Product:: updateProductdata()
 {
   int num, found=0;
   system("CLS");
   cout<<"\n\n Update record: "<<endl;
   cout<<"\n\n Please enter the Product no. of the product you want to update:  ";
   cin>>num;
   fp.open("product1.txt",ios::in|ios::binary);
   while(fp.read((char * ) & pr, sizeof(Product)))
   {
     if(pr.pno==num)
     {
       pr.show_product();
       cout<<"\n please enter new details of the product: "<<endl;
       pr.createProduct();
       int pos=1*sizeof(pr);
       fp.seekp(pos, ios::cur);
       fp.write((char * ) & pr, sizeof(Product));
       cout << "\n\n\t Record Updated";
       found = 1;

     }
   }
   fp.close();
   if(found==0)
     cout<<"Record not found!!!!!!"<<endl;
     getch();
 }
 void Product:: calculate()
 {
   gross=price+(price*(tax/100));
   netamt=qty*(gross-(gross*(dis/100)));
 }
 void Product:: displayall(){
   system("CLS");
   int flag;
   flag=0;
   int num;
   cout<<"ENTER PRODUCT NUMBER: "<<endl;
   cin>>num;
   fp.open("product1.txt",ios::in);
   if(!fp){
     cout<<"FILE NOT FOUND!!!!!!!!!!!!"<<endl;
     
   }
   
  while( fp.read((char * ) & pr, sizeof(Product))){
   int x=pr.pno; 
   if(x==num) {
     
     pr.show_product();
  
     cout<<"\n";
     cout<<"********************************************************************************"<<endl;
     cout<<"                                  DETAILS                                       "<<endl;
     cout<<"********************************************************************************"<<endl;
     cout<<"    PRICE                                                 "<<pr.price<<endl; 
     cout<<"    QUANTITY                                              "<<pr.qty<<endl;
     cout<<"    TAX PERCENT                                           "<<pr.tax<<endl;
     cout<<"    DISCOUNT                                              "<<pr.dis<<endl;
     cout<<"    NETAMOUNT                                             "<<pr.netamt<<endl;
     flag=1;
     break;
   }
   }
   if(flag==0)
   cout<<"\n\n Item does not exist............please retry"<<endl;
   fp.close();
   getch();
 }
 void intro()
 {
    system("CLS");
    cout<<"***************************************************************************************"<<endl;
    cout<<"                         GRAPHIC ERA HILL UNIVERSITY                           "<<endl;
    cout<<"***************************************************************************************"<<endl;
    cout<<"                         MINI PROJECT                                          "<<endl;
    cout<< "                SUPER MARKET BILLING PROJECT"<<endl;

    cout<<"MADE BY : JOJO CHAUHAN"<<endl;
    cout<<"UNIVERSITY ROLL NO: 1918400"<<endl;
    cout<<"COURSE: BTECH CSE"<<endl;
    cout<<"SUBMITTED TO: MS. PREETI CHAUDHARY"<<endl;
    cout<<"RESOURCE PERSON: MS. ADITYA VERMA"<<endl;
    getch();
 }
 void BillD(){
     char ch1;
     cout<<"******************"<<endl;
     cout<<"   BILL DETAILS    "<<endl;
     cout<<"******************"<<endl;
     cout<<"1. ALL ITEMS"<<endl;
     cout<<"2. BACK TO MAIN MENU"<<endl;
     cout<<"PLEASE ENTER YOUR OPTION: "<<endl;
     ch1=getche();
     switch(ch1){
        case '1':
        system("CLS");
        break;
        case '2':
        exit(0);
            
     }
 }
 void BillEditor()
 {
   char ch2;
   cout<<"***************************************"<<endl;
   cout<<"              BILL EDITOR                  "<<endl;
   cout<<"***************************************"<<endl;
   cout<<"1. DELETE ITEM DETAILS"<<endl;
   cout<<"2. UPDATE ITEM DETAILS"<<endl;
   cout<<"3. BACK TO MAIN MENU"<<endl;
   ch2=getche();
   switch(ch2)
   {
     case '1':
      system("CLS");
      pr.deleteProductdata();
      getch();
      break;
     case '2':
      system("CLS");
      pr.updateProductdata();
      getch();
      break;
     default:
      cout<<"\a";
      getch();

   } 
 }
 void MENU(){
   char ch;
   do{
     
   system("CLS");
    cout<<"*********************************"<<endl;
    cout<<"   SUPER MARKET BILLING SYSTEM    "<<endl;
    cout<<"*********************************"<<endl;
    cout<<"1.BILL REPORT "<<endl;
    cout<<"2.BILL EDITOR "<<endl;
    cout<<"3.SHOW ITEM DETAILS"<<endl;
    cout<<"4.EXIT "<<endl;
    cout<<"PLEASE ENTER YOUR CHOICE:  "<<endl;
    ch=getche();
    switch(ch)
    {
      case '1': 
        system("CLS");
        BillD();
        pr.storeProductdata();
        getch();
        break;
      case '2':
        system("CLS");
        BillEditor();
        break;
      case '3':
        system("CLS");
        pr.displayall();
        MENU();
        getch();
        break;
      case '4':
        exit(0);
      default:
        cout<<"\a"; 
         
    }
   }while(ch!='3');
 }

int main()
{
  intro();
  MENU();
  return 0;
}