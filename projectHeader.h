#include <iostream>
#include <fstream>      // We used this library because of file managing operations.
#include <string>       // We used this library because of getline.
#include <cstdlib>      // We used this library because of exit(0). 

using namespace std;

class account{
    protected:                                  //We used those variables at protected because we needed every single one of them at everywhere but mostly at app class.
        int accountBalance, sendMoneysAmount;                                               
        string personName, personSurname, personPassword, wantedPersonName, sendMoneysName;  //We define those variables to used at the later stage of this program
    public:
        bool control(string nameOrSurname);      
        void displayBalance(){                  //This is just a displayer that shows us that accounts balance.

            cout<<"Your balance is: "<<accountBalance<<endl;
        };            
        void setInformations();                
        void saveAccounts();                    
        void loadAccounts();
        void signIn();                          //This function allows us to sign up (creating a new bank) to the bank.
        void transferMoney();
        virtual int getAccountBalance()const {return accountBalance;};  //Those are get functions that we used at everywhere of this project
        virtual string getPersonName() const{return personName;};
        virtual string getPersonSurname()const{return personSurname;};
        virtual string getPersonPassword()const{return personPassword;};
};

class app : public account{             //This is our derived class from our main class"account". This class has all of the app's menu's codes down there. 
    public:                             
        app();                          //Our main constructor of this class, we will be see this later.
        ~app();                         //Our main destructor of this class, we will be see this later.
        void sendMoney();               
        void entryMenu();
        void displayProfile();          //It's just a basic displayer that shows us a informations about our profile.
        void mainMenu();                
        void logIn();                   
        void deposit();
        void withdraw();
        void exxit();
        void currencyStatus();
        int getPersonName();
        int getAccountBalance()const {return accountBalance;};
        string getPersonName() const{return personName;};
        string getPersonSurname()const{return personSurname;};
        string getPersonPassword()const{return personPassword;};
};

app::app(){
    entryMenu();                        //Our constructor will lead us to entryMenu.
}

app::~app(){    
    exxit();                            //Our destructor will close the program.
    
}

bool account::control(string nameOrSurname){ //This functions task is controlling the string's letters. If one of the letter is different type of something (like ü,ğ,ç) it will give us a warning.
    for(int i = 0; i<nameOrSurname.length();i++){
        if(!((nameOrSurname[i] >= 'A'&& nameOrSurname[i] <='Z')||(nameOrSurname[i] >= 'a'&& nameOrSurname[i] <='z'))){
            return false;
            }
        
    }
    return true;
}

void account::setInformations(){
    string name,surname,password;       //This is where all this accounts begins we get informations from the user and we get them to the accounts.txt with saveAccounts() function.
    int balance;
   
    cout<<"Enter your name please: ";
    cin>>name;

    while(!control(name)){
        cout<<"Invalid name or chracters: ";
        cin>>name;                      //We take names at here and check them first than save them to the accounts own variables that personName.

        cout<<endl;
    }
    
    personName = name;
    
    cout<<endl<<"Enter your surname please: ";
    cin>>surname;  

    while(!control(surname)){
        cout<<"Invalid surname or characters: ";
        cin>>surname;
        cout<<endl;                     //We take surnames at here and check them first than save them to the accounts own variables that personSurname.
    }
    
    personSurname = surname;

    cout<<endl<<"Enter your first entry balance please: ";
    cin>>balance; 
    
    accountBalance = balance;           //We take first entry balances at here and save them to the accounts own variables that accountBalance.

    cout<<endl<<"Enter your password please: ";
    cin>>password;

    while((password.length() < 3)&&(password.length() > 8)){
        cout<<"Invalid password: ";
        cin>>password;                  //At the last we take passwords here and check them after that we declare to personPassword variable.
        cout<<endl;
    }
    
    personPassword = password;

    cout<<"Congratulations. You have a new bank account.";

    saveAccounts();
}

void account::saveAccounts(){   //This is a file managing code we use this to save accounts names, surnames, balances and passwords.
            fstream file;
            account acc1;
            file.open("accounts.txt", ios::app);
            file<<personName<<endl<<personSurname<<endl<<accountBalance<<endl<<personPassword<<endl;
            file.close();

}

void account::loadAccounts(){  //One of most important codes that we have at our program. This function is search name and password that we want to ask for from accounts.txt and 
                                //read from there set to the variable. This is our login system actually.


            fstream file;
            bool serch = true;
            

            

            file.open("accounts.txt", ios::in);
            string strusbalance;
            while(serch){                           //We have while loop here it will working at the default than if it finds the personName == wantedPersonName equation it will stop
                                                    //and it will gives us a that persons name surname balance and password;
                personName ="";
                getline(file,personName);
                if (personName == "") {
                cout <<"Invalid Value"<< endl;
                break;
                }
                if(personName == wantedPersonName){
               
                    getline(file,personSurname);
                    getline(file,strusbalance);
                    getline(file,personPassword);
                    serch = false;
                accountBalance = stoi(strusbalance);
                
            }
            
            }
            
            
            file.close();
            
            

           
            }

void account::transferMoney() { //This function allows us to transfer our money. It works like if choose the money transfer button at the main menu program lead us to sendMoney() function
    fstream file;               //and we used this function inside the sendMoney() to add money to the one account and substract from the other one.
    bool search = true;         //It's actually working similar to load account but its little bit different first we found the balance that users from account.txt.
    string tname, tsurname, tbalance, tpassword;        //Than we get this "string" type variable and ve covert to the integer with stoi().
    int nahBalance;

    file.open("accounts.txt", ios::in);
    while (search) {
        tname = "";
        getline(file, tname);
        if (tname == "") {
            cout << "Invalid Value" << endl;
            break;
        }
        if (tname == wantedPersonName) {
            getline(file, tsurname);
            getline(file, tbalance);
            getline(file, tpassword);
            search = false;
            nahBalance = stoi(tbalance);
            nahBalance += sendMoneysAmount;
        }
    }
    file.close();

    
    file.open("accounts.txt", ios::in | ios::out); // At here we creating a temporary file and we edit our informations for account.txt. With that we can use informations at the
    ofstream tempFile("temp.txt");                 //account.txt.             
    string line;

    while (getline(file, line)) {
        if (line == tname) {
            tempFile << line << endl;
            getline(file, line); // surname
            tempFile << line << endl;
            getline(file, line); //balance
            tempFile << nahBalance << endl;
            getline(file, line); // password
            tempFile << line << endl;
        } else {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

  
    std::remove("accounts.txt");

    
    std::rename("temp.txt", "accounts.txt");

    cout << "Money transferred successfully." << endl;
}

void account::signIn(){     //This function is lead us to the setInformations() function and we give our informations to the program.
    system("cls");
    system("clear");
    cout<<"--------Register Menu--------"<<endl;
    setInformations();

    cout<<endl;
    
    app();
    
}

void app::currencyStatus(){        //This is a basic currency displayer.
    system("cls");
    system("clear");
    string a;
    cout<<"--------Currency Status--------"<<endl;
    cout << "1USD= 20.23TRY" << endl;
    cout << "1EUR= 21.78TRY" << endl;
    cout << "1GBP= 25.14TRY" << endl;
    cout << "1GAU= 1266.60TRY "<<endl;
    cout<<" If you want to go back please enter exit: ";
    cin>>a;
    if(a=="exit"){
    mainMenu();
    }


}

void app::entryMenu(){          //This is a enterence menu that when program first run if we have options ther and if we choose one of it it will lead us to its function.
    system("cls");
    system("clear");
    
    cout<<"--------Entry Menu--------"<<endl;
    cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;  
    cout<<"3. Exit"<<endl;

    int a,b,c;

    cout<<"Enter your choice: ";
    cin>>a;
    cout<<endl;
    system("cls");
    system("clear");
    if(a == 1){
        logIn();
    }
    else if(a == 2){
        signIn();
    }
    else if(a == 3){
        exxit();
    }
    else {
    exit(0);}
    
    
}

void app::logIn(){              //This is a login screen its takes data from loadAccounts() and we can get our informations from accounts.txt

    string password;
    
    
    cout<<"--------Login Menu--------"<<endl;
    cout<<"Please enter your name, if you want to go back just write back: ";
    cin>>wantedPersonName;
    if(wantedPersonName == "back"){
    entryMenu();}
    cout<<"Please enter your password: ";
    cin>>password;
    cout<<endl;
    loadAccounts();
   
    if( (personName == wantedPersonName)&&(personPassword== password) ){
        system("cls");
        system("clear");
        cout<<"Welcome..."<<personName<<endl;
        mainMenu();
    }
    else if((wantedPersonName=="back")||(password=="back")){
        system("cls");
        system("clear");
        entryMenu();
    }
    else {
        system("cls");
        system("clear");
        cout<<"Wrong Password..."<<endl;
        entryMenu();
    }
    
    
    
}

void app::mainMenu(){           //This is our programs main menu. At the top we can see our accounts balance and other functions that we can do with our account. 
    system("cls");
    system("clear");
    cout<<"--------Main Menu--------"<<endl;
    displayBalance();
    cout<<"1. Deposit Money"<<endl;  
    cout<<"2. Withdraw Money"<<endl;
    cout<<"3. Transfer Money"<<endl;
    cout<<"4. View Account Details"<<endl;
    cout<<"5. Currency Status"<<endl;
    cout<<"6. Log Out"<<endl;
    

    int a,b,c;

    cout<<"Enter your choice: ";
    cin>>a;
    cout<<endl;
    system("cls");
    system("clear");
    
    if(a == 1){
        deposit();
    }
    else if(a == 2){
        withdraw();
    }
    else if(a == 3){
        sendMoney();
    }
    else if(a == 4){
        displayProfile();
    }
    
    else if(a == 5){
        currencyStatus();
    }

    else if(a == 6){
        entryMenu();
    }
    
}  

void app::exxit(){              //This is a simple exit function. I did used this in destructor and many other functions.
    system("cls");
    system("clear");
    cout<<"Exiting"<<endl;
    fstream file;
            account acc1;
            file.open("accounts.txt", ios::out);
            file<<"";
            file.close();


    exit(0);
    
}

void app::sendMoney() {         //It's our Money transfer options page and this function and transferMoney() function connected each other i do take variables from here and used at transferMoney().
    system("cls");
    system("clear");
    string name;
    cout << "Please enter the account owner's name that you want to send money, if you want to go back just type back: ";
    cin >> name;
    if(name=="back"){
    mainMenu();}
    cout << "Please enter the amount of money you want to send: ";
    cin >> sendMoneysAmount;

    accountBalance -= sendMoneysAmount;

    wantedPersonName = name; // İstenen kişinin adını kaydet

    transferMoney();

    cout << "You have sent " << sendMoneysAmount << " money to " << wantedPersonName << "'s account." << endl;

    mainMenu();
}

void app::displayProfile(){     //It's a basic profile displayer.
            char a;
            cout<<"Name: "<<personName<<endl;
            cout<<"Surname: "<<personSurname<<endl;
            cout<<"Account Balance: "<<accountBalance<<endl;
            cout<<"Password: ";
            for(int i = 0; i<personPassword.size(); i++){
                cout<<"*";
            }
            cout<<endl;
            cout<<"If you want to go back just press enter";
            cin>>a;
            mainMenu();
            }

void app::deposit(){            //If you want to deposit to your account you can do it from here. Just sign your amount that you want to deposit.
            
            int amount;

            cout<<"Enter deposit amount,if you want to go back just type 0: ";
            cin>>amount;
            if(amount==0){
            mainMenu();}

            while(amount <= 0){
                cout << "Amount must be greater than 0" << endl;
                cin>>amount;
            }

            accountBalance += amount;

            saveAccounts();

            mainMenu();
            }

void app::withdraw(){           //But if wou want to withdraw from your account just sign amount that you want the withdraw.
     int amount;
            cout<<"Enter withdraw amount,if you want to go back just type 0: ";
            cin>>amount;
            if(amount == 0){
            mainMenu();}

            while(amount<=0||amount>accountBalance){
                cout<<"Invalid Amount"<<endl;
                cin>>amount;
            }

            accountBalance-=amount;

            saveAccounts();

            mainMenu();
    
}





