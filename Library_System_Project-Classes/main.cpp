#include <iostream>
#include <vector>
#include <algorithm>
#include "Str.h"
#include "Book.h"
#include "User.h"
#include "Loan.h"

using namespace std;
using namespace OurBook;

vector<Book*> library_books; // Assuming you have a vector to store Book objects
vector<User*> library_users;
vector<Loan*> library_loans;

vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
vector<Book*> Cart;

Librarian lib;
Student student;
Staff staff;
Faculty faculty;

void printHeader();
void printMemberMenu();
void printSearchOptions();
void printLibMenu();
bool checkBack();
bool checkClose();
void printExit();
void searchByISBN();
void searchByYear();
void searchByTitle();
void searchByAuthor();
void searchByGenre();
void searchForBook();
void viewAvailableBooks();
void addToCart();
void viewCart();
void updateMemberData();
void updateBookData();
void updateMemberMenu();
void updateBookMenu();
void updatepassword();
void diplaydata();
void loanrequest();
void viewloans();
void processloans();
void checkforoverdues();
void returnbook();
Member* checktype(str);

bool endOfProgram=false;
bool backToTheMainMenu=false;

User* login();
void memberMenu();
void libMenu();
int main() {
    checkforoverdues();// this function will be called whenever the program runs and will check if there is an overdue on any loan

    student.setName("Ziad");
    student.setId("101285");
    student.setPassword("242004");
    staff.setName("Marwan");
    staff.setId("3akeedo");
    staff.setPassword("<reham>");
    faculty.setName("Elshabeeh");
    faculty.setId("69420");
    faculty.setPassword("password");
    User *user1=&student;
    User *user2=&staff;
    User *user3=&faculty;
    library_users.push_back(user1);
    library_users.push_back(user2);
    library_users.push_back(user3);

    //User* user = login();

    // Adding books to the library
    Book* book1 = new Book("Calculus", "Hussein", "8624625635660", 2013, "Math");
    book1->setQuantity(20);
    Book* book2 = new Book("Discrete", "Atta", "8624625635661", 2012, "Not math");
    book2->setQuantity(30);
    Book* book3 = new Book("Data Structures", "Ziad", "8624625635662", 1984, "Math");
    book3->setQuantity(15);
    Book* book4 = new Book("Object oriented programming", "Larson", "8624625635663", 2012, "maybe Math");
    book4->setQuantity(1);
    Book* book5 = new Book("Linear Algebra", "Stewart", "8624625635669", 2004, "Math");
    library_books.push_back(book1);
    library_books.push_back(book2);
    library_books.push_back(book3);
    library_books.push_back(book4);
    library_books.push_back(book5);

    memberMenu();
    //libMenu();


    return 0;
}

User* login(){
    User *toReturn;
    bool flag=false;
    do {
        str id, password;
        cout << "Please Enter your ID       : ";
        cin >> id;
        cout << "Please Enter your Password : ";
        cin >> password;
        for (auto it: library_users) {
            if (id == it->getId() && password == it->getPassword()) {
                toReturn = it;
                flag = true;
                cout << "\nLogin successful" << endl;
                system("pause>0");
                break;
            }
        }
        if (!flag) {
            cout << "\nCheck Id or password!\n" << endl;
        }
    }while(!flag);

    return toReturn;
}

void updatepassword(){
    system("cls");
    cout<<"Please Enter your ID : ";
    str id;
    cin>>id;
    if (lib.Searchformember(library_users,id)){
        cout<<"Please Enter your New password : ";
        str pass;
        cin>>pass;
        lib.Searchformember(library_users,id)->setPassword(pass);
    }
    else{
        cout<<"No matching id"<<endl;
    }
    system("cls");
    checkBack();
}


void printHeader(){
    cout << "Welcome to our university system project. Please choose one of the following options:" << endl;
}
void printMemberMenu(){
    cout << "[1] Search for a book" << endl
         << "[2] View Available books" << endl
         << "[3] Add to cart "<<endl
         << "[4] View Cart "<<endl
         << "[5] Update Password"<<endl
         << "[6] Return Book"<<endl
         << "[7] Exit system"<<endl;
}
void printExit(){
    cout<<"--------------------------------------------Thanks for using our program---------------------------------------------\n\n";
    cout<<"-------------------------------------------------------Credits-------------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Salah eldin Elsayed------------------------------------------------\n\n";
    cout<<"-----------------------------------------------------Hussein Sayed---------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Abdulrahman Abogendia----------------------------------------------\n\n";
    cout<<"-----------------------------------------------------Fouad Hashesh---------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Soliman Elhassanin-------------------------------------------------\n\n";
    cout<<"------------------------------------------------------Kareem Yasser---------------------------------------------------\n\n";
    cout<<"-------------------------------------Under the Supervision of Dr. Fatma Elshehaby------------------------------------\n\n";
}
bool checkBack(){
    short back=1;
    do {
        cout << "\n\n[1] Back to the last page" << endl << "[2] Back to the main menu\n\n";
        cout << "Please enter your choice : ";
        cin >> back;
        if (back == 2)
            backToTheMainMenu = true;
    }while(back!=1 && back!=2);
    return (back==2);
}
bool checkClose(){
    short back=1;
    do {
        cout << "\n\n[1] Back to the last page" << endl << "[2] Close the program\n\n";
        cout << "Please enter your choice : ";
        cin >> back;
        if (back == 2)
            endOfProgram = true;
    }while(back!=1 && back!=2);
    return (back==2);
}
void printSearchOptions(){
    cout << "Search by : " << endl
         << "[1] isbn" << endl
         << "[2] year" << endl
         << "[3] title" << endl
         << "[4] author" << endl
         << "[5] genre ";
}
void searchByISBN(){
    system("cls");
    str isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;
    if((student.searchForBook_isbn(library_books, isbn))==nullptr)
        cout<<"\nNo results\n";
    else {
        Search_results.push_back(student.searchForBook_isbn(library_books, isbn));
        Search_results.at(0)->printData();
    }
}
void searchByYear(){
    system("cls");
    short year;
    cout << "Enter year : ";
    cin >> year;
    Search_results = student.searchForBook_publicationyear(library_books, year);
    if(Search_results.empty())
        cout<<"\nNo results\n";
    else {
        for (auto it: Search_results) {
            it->printData();
        }
    }
}
void searchByTitle(){
    system("cls");
    str title;
    cout << "Enter Title : ";
    cin >> title;
    if((student.searchForBook_title(library_books, title))==nullptr)
        cout<<"\nNo results\n";
    else {
        Search_results.push_back( student.searchForBook_title(library_books, title));
        Search_results.at(0)->printData();
    }
}
void searchByAuthor(){
    system("cls");
    str author;
    cout << "Enter Author: ";
    cin >> author;
    Search_results = student.searchForBook_author(library_books, author);
    for (auto it:Search_results) {
        it->printData();
    }
}
void searchByGenre(){
    system("cls");
    str genre;
    cout << "Enter Genre: ";
    cin >> genre;
    Search_results = student.searchForBook_genre(library_books, genre);
    for (auto it:Search_results) {
        it->printData();
    }
}
void printLibMenu(){
    cout << "[1] Search for a book" << endl
         << "[2] View Available books" << endl
         << "[3] Update Users Data "<<endl
         << "[4] Update Book Data "<<endl
         << "[5] View User Data"<<endl
         << "[6] Update password"<<endl
         << "[7] View Loan Requests"<<endl
         << "[8] Process Loan Requests"<<endl
         << "[9] Exit system"<<endl;
}
void searchForBook(){
    short choice=1;
    do{
        system("cls");
        printSearchOptions();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if(choice==1)
            searchByISBN();
        else if(choice==2)
            searchByYear();
        else if(choice==3)
            searchByTitle();
        else if(choice==4)
            searchByAuthor();
        else if(choice==5)
            searchByGenre();
        if(choice>0 && choice<6)
            checkBack();
        Search_results.clear();
    }while(!backToTheMainMenu);
}
void viewAvailableBooks(){
    system("cls");
    for (auto it : library_books) {
        if (it->getAvailability())
            it->printData();
    }
    checkClose();
}
void addToCart(){
    system("cls");
    str input;
    bool cartFound = false;
    Book* cartBook;
    cout<<"Please Enter the title or isbn of the needed book :";
    cin>>input;
    for (auto it:library_books) {
        if ((it->getTitle() == input || it->getIsbn() == input) && it->getAvailability()) {
            cartFound = true;
            cartBook = it;
        }
    }
    if (cartFound){
        cout<<"Book added to Cart successfully!"<<endl;
        Cart.push_back(cartBook);
        cartBook->setQuantity(cartBook->getQuantity()-1);
    }
    else{
        cout<<"\nThis book doesn't exist\n";
    }
    checkClose();
}
void viewCart(){
    system("cls");
    if(Cart.empty())
        cout<<"The cart is empty\n\n";
    else
        for(auto it:Cart)
            it->printData();
    if(!Cart.empty()) {
        char confirmLoanRequest = '1';
        do {
            cout << "\nDo you want to request loan ? " << endl
                 << "[0] No" << endl
                 << "[1] Yes" << endl;
            cout << "Please enter your choice : ";
            cin >> confirmLoanRequest;
            if (confirmLoanRequest == '1') {
                loanrequest();
            }
        } while (confirmLoanRequest != '1' && confirmLoanRequest != '2');
    }

    checkClose();
}
void memberMenu(){
    system("cls");
    printHeader();
    short choice=1;
    do{
        printMemberMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if(choice==1)
            searchForBook();
        else if(choice==2)
            viewAvailableBooks();
        else if(choice==3)
            addToCart();
        else if(choice==4)
            viewCart();
        else if(choice==5)
            updatepassword();
        else if(choice==6)
            returnbook();
        system("cls");
        if(backToTheMainMenu) {
            choice = 1;
            backToTheMainMenu=false;
        }
        if(endOfProgram)
            break;
    }while(choice!=7);

    printExit();
    system("pause>0");
}

void updateMemberMenu(){
    cout<<"[1] Add a member"<<endl
        <<"[2] Remove a member"<<endl;
}
void updateMemberData(){
    system("cls");
    short choice;
    str id;
    do{
        updateMemberMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if (choice<1 || choice > 2) {
            system("cls");
            continue;
        }
        if (choice == 1) {
            int type;
            cout<<"Please Enter type of member to add "<<endl
                <<"1-Student"<<endl
                <<"2-Staff"<<endl
                <<"3-Faculty"<<endl;
            cout<<"\nPlease enter your choice : ";
            cin>>type;
            if (type>0 && type< 4)
                lib.addMember(library_users,type);
            else
                cout<<"Wrong choice Please try again"<<endl;
        }
        else if (choice == 2) {
            cout<<"please Enter member ID : ";
            cin>>id;
            Member*tosend=lib.Searchformember(library_users, id);
            if (!tosend)
                cout<<"Member not found"<<endl;
            else {
                lib.updateMemberId(lib.Searchformember(library_users, id));
                cout << "Updated member ID successfully" << endl;
            }
        }
        if(choice>0 && choice<5)
            checkBack();

    }while(!backToTheMainMenu);
}
void updateBookMenu(){
    cout<<"1-Add book "<<endl
        <<"2-Remove book"<<endl
        <<"3-Update title"<<endl
        <<"4-Update Author"<<endl
        <<"5-Update ISBN"<<endl
        <<"6-Update Genre"<<endl
        <<"7-Update Quantity"<<endl
        <<"8-Update Year"<<endl;
}
void updateBookData() {
    system("cls");
    short choice;
    str ans;
    do {
        system("cls");
        updateBookMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if (choice<1 || choice > 8) {
            system("cls");
            continue;
        }
        if (choice==1){
            lib.addBook(library_books);
        } else if(choice==2){
            cout << "Please enter Book isbn or number : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.removeBook(library_books, tosend);
        }else if(choice==3){
            cout << "Please enter Book isbn or number : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookTitle(tosend);

        }else if (choice==4){
            cout << "Please enter Book isbn or number : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookAuthor( tosend);

        } else if (choice == 5){
            cout << "Please enter Book isbn or number : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookISBN(  tosend);
        } else if (choice == 6){
            cout << "Please enter Book isbn or number : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookGenre(  tosend);
        }else if(choice == 7){
            cout << "Please enter Book isbn or number : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found\n";
            else
                lib.updateBookQuantity(  tosend);
        } else if(choice==8){
            cout << "Please enter Book isbn or number : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found\n";
            else
                lib.updatePublicationYear(  tosend);
        }
        if(choice>0 && choice<9)
            checkBack();
    } while (!backToTheMainMenu);
}
void loanrequest(){
    str id;
    cout<<"Please enter your ID: ";
    cin>>id;

    Member* member = checktype(id);
    Loan* new_loan = member->requestLoan(Cart.front()); // assign the loan object returned by requestLoan function to new_loan
    library_loans.push_back(new_loan); // add new_loan object to library_loans vector in main to be checked later by librarian
    Cart.erase(Cart.begin()); // remove book from cart to checkout
}
void diplaydata(){
    system("cls");
    do {
        cout<<"Please Enter Id : " ;
        str id;
        cin>>id;
        if (lib.Searchformember(library_users,id)){
            lib.Searchformember(library_users,id)->displayInfo();
        }
        checkBack();
    } while (!backToTheMainMenu);
}
void viewloans(){
    short choice=1;
    cout << "[1] View All Loan Requests"<<endl
         << "[2] View Pending Loan Requests"<<endl;

    cout<<"\nPlease enter your choice : ";
    cin>>choice;
    if(choice==1)
        lib.printAllLoans(library_loans);
    if(choice==2)
        lib.printPendingLoans(library_loans);
}
void processloans(){
    char response;
    for (auto loan:library_loans) {
        loan->generateReport();
        cout<<"Do you want to accept this loan"<<endl
            <<"[1] Yes"
            <<"[2] No"<<endl;
        cin>>response;
        if(response=='1') {
            lib.processLoanRequest(loan, true);
            cout<<"Loan accepted."<<endl;
        }
        else if(response=='2') {
            lib.processLoanRequest(loan, false);
            cout << "Loan rejected." << endl;
        }
        else {
            cout << "Wrong input, input range[1,2]." << endl;
            break;
        }
    }
}
void checkforoverdues(){
    for (auto loan:library_loans) {
        lib.CheckForOverdues(loan);
    }
}
void returnbook() {
    str id;
    cout<<"Please enter your ID: ";
    cin>>id;

    Member* member = checktype(id);
    vector<Book*> checkedoutbooks = member->getCheckedOutBooks();
    Book* tocheck;

    char choice;
    cout << "Search by : " << endl
         << "[1] isbn" << endl
         << "[2] title" << endl;
    cin>>choice;
    if(choice==1){
        str isbn;
        cout << "Enter ISBN: ";
        cin >> isbn;
        if((student.searchForBook_isbn(checkedoutbooks, isbn))==nullptr)
            cout<<"\nNo results\n";
        else
            tocheck = student.searchForBook_isbn(checkedoutbooks, isbn);
    }
    else if(choice==2) {
        str title;
        cout << "Enter Title : ";
        cin >> title;
        if((student.searchForBook_title(checkedoutbooks, title))==nullptr)
            cout<<"\nNo results\n";
        else
            tocheck = student.searchForBook_title(checkedoutbooks, title);
    }
    for (auto book: checkedoutbooks) {
            if(tocheck->getIsbn() == book->getIsbn() || tocheck->getTitle() == book->getTitle())
                member->returnBorrowedBook(book, library_loans);
    }

}
void libMenu(){
    system("cls");
    printHeader();
    short choice=1;
    do{
        printLibMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if(choice==1)
            searchForBook();
        else if(choice==2)
            viewAvailableBooks();
        else if(choice==3)
            updateMemberData();
        else if(choice==4)
            updateBookData();
        else if(choice==5)
            diplaydata();
        else if (choice==6)
            updatepassword();
        else if(choice==7)
            viewloans();
        else if(choice==8)
            processloans();
        system("cls");
        if(backToTheMainMenu) {
            choice = 1;
            backToTheMainMenu=false;
        }
        if(endOfProgram)
            break;
    }while(choice!=9);

    printExit();
    system("pause>0");
}
Member* checktype(str id) {
    //stu fac sta
    str tocheck = id.str2string();
    if(tocheck[2] == 'u' ){
        Member* member = &student;
        return member;
    }
    else if(tocheck[2] == 'c' ){
        Member* member = &faculty;
        return member;
    }
    else if(tocheck[2] == 'a' ){
        Member* member = &staff;
        return member;
    }
}