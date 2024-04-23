#ifndef LIBRARY_SYSTEM_PROJECT_USER_H
#define LIBRARY_SYSTEM_PROJECT_USER_H


#include <vector>
#include "Str.h"
#include "Book.h"

using namespace std;
using namespace OurBook;

class Librarian;
class Member;
class Loan;
/*****************************************/
class User {
protected:
    str name;
    str id;
    str password;
public:
    User() : name(""), password(""), id(""){}
    User(const str &n, const str &i, const str &pass) : name(n), id(i), password(pass){}

    str getName() const;
    str getId() const;
    str getPassword() const;

    void setName(str s);
    void setPassword(str pass);

    /******** overriden methods **********/
    virtual void displayInfo() const = 0;
    virtual void setId(str i)  = 0;

    /********* User methods *********/
    Book*  searchForBook_title(const vector<Book*> &, const str &);
    Book*  searchForBook_isbn(const vector<Book*> &, const str &);
    vector<Book *> searchForBook_author(const vector<Book*> &, const str &);
    vector<Book *> searchForBook_genre(const vector<Book*> &, const str &);
    vector<Book *> searchForBook_publicationyear(const vector<Book*> &, const short &);



    virtual ~User(){}
};



/****************************************************************************************/

class Member : public User {
protected:
    /****** attributes ******/
    vector<Book*> checked_out_books;
    vector<Loan*> member_loans;
    float overdue_fines = 0;

    /****** private methods ******/

public:
    /****** public methods ******/

    Member();
    Member(str, str, str);
    //~Member() override{}

    void setCheckedOutBooks(vector<Book*>&);
    void addToCheckedOutBooks(Book* &);
    void removeFromCheckedOutBooks(Book* &);
    void setMemberLoans(vector<Loan*> &);
    void removeFromMemberLoans(Loan* &);
    void setOverdueFines(float&);

    vector<Book*> getCheckedOutBooks() const;
    vector<Loan*> getMemberLoans() const;
    float getOverdueFines() const;
    int getCheckedOutBooksSize() const;

    /********* Member Methods ********/
    void viewCheckedOutBooks() const;

    /********** Loan related methods ********/

    virtual Loan* requestLoan(Book* &) = 0;

    virtual void returnBorrowedBook(Book* &, vector<Loan*> &) = 0;
};
/****************************************************************************************/

class Librarian : public User, private Book{
private:
    void proceedToCheckOut(Loan* &);
public:
    /************ Constructors ***********/
    Librarian();
    Librarian(str, str, str);
    ~Librarian() override{}
    /********** overriden methods **********/
    void displayInfo() const override;
    void setId(str i) override;

    /************** Operations on books **************/

    // (Use allocation for new books and use setters for assigning values)
    void viewBooks(vector<Book*>&) const;
    void addBook(vector<Book*> &);
    void removeBook(vector<Book*> &, Book* &book);

    void updateBookTitle(Book* &);
    void updateBookAuthor(Book* &);
    void updateBookISBN(Book* &);
    void updatePublicationYear(Book* &);
    void updateBookGenre(Book* &);
    void updateBookQuantity(Book* &);

    /******************* Opeerations on Members *****************/
    void addMember(vector<User *> &,int);
    void removeMember(vector<User *> &, Member*);
    void updateMemberName(Member*);
    void updateMemberId(Member*);
    Member* Searchformember(vector<User*>,str);

    /******************** Operations on Loans ****************/
    void processLoanRequest(Loan* &, bool);
    void CheckForOverdues(Loan* &);
    void printAllLoans(vector<Loan*>) const;
    void printPendingLoans(vector<Loan*>) const;
};
/****************************************************************************************/

class Student : public Member {
public:
    Student();
    Student(str, str, str);
    ~Student() override{}

    void setId(str i) override;
    void displayInfo() const override;

    Loan* requestLoan(Book* &);
    void returnBorrowedBook(Book* &, vector<Loan*> &);

    friend class Librarian;
};

class Faculty : public Member {
public:
    Faculty();
    Faculty(str, str, str);
    ~Faculty() override{}

    void setId(str i) override;
    void displayInfo() const override;

    Loan* requestLoan(Book* &);
    void returnBorrowedBook(Book* &, vector<Loan*> &);

    friend class Librarian;
};

class Staff : public Member {
public:
    Staff();
    Staff(str, str, str);
    ~Staff() override{}
    void setId(str i) override;
    void displayInfo() const override;

    Loan* requestLoan(Book* &);
    void returnBorrowedBook(Book* &, vector<Loan*> &);

    friend class Librarian;
};

/****************************************************************************************/

#endif //LIBRARY_SYSTEM_PROJECT_USER_H