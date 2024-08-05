#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
using namespace std;
class book{
    private:
    string name;
    string author;
    bool Availability;
    
    
    public:
    book(string n,string a){
        name=n;
        author=a;
        Availability=true;
    }
    void checkout(){
        if(Availability){
            Availability=false;
            cout<<"The Book has been checked out"<<endl;
        }
        else{
            cout<<"Book is not Available"<<endl;
        }
    }
    void returnbook(){
        if(!Availability){
            Availability=true;
            cout<<"Book has been returned"<<endl;
            
        }
        else{
            cout<<"Book has not been issued So it can't be returned"<<endl;
            
        }
    }
    string getTitle() {
        return name;
    }
    string getAuthor() {
        return author;
    }

    bool isAvailable() {
        return Availability;
    }
};
class Library{
   vector<book> collection;
   public:
   void addbook(book a){
       collection.push_back(a);
       cout<<"Book has been added to the library collection"<<endl;
   }
   void removebook(string name){
       for(int i=0;i<collection.size();i++){
           if(collection[i].getTitle()==name){
               collection.erase(collection.begin() + i);
               cout << "Book has been removed from the library." << endl;
             return;
           }
       }
       cout<<"Book to be removed is not present in the collection"<<endl;
   }
     book searchBook(string name) {
        for (int i = 0; i < collection.size(); i++) {
            if (collection[i].getTitle() == name) {
                return collection[i];
            }
        }
        cout << "Book with Name: " << name << " not found in library." << endl;
        // return nullptr;
    }
    void displayBooks(){
        cout<<"Books present in the Library are:"<<endl;
        for(int i = 0; i < collection.size(); i++){
            cout<<collection[i].getTitle()<<endl;
            cout << "Author: " << collection[i].getAuthor() << endl;
            cout<<endl;
        }
    }

};
class Patron {
private:
    string nameP;
    string ID;
    vector<book*> checkedOutBooks;
public:
     Patron(string n, string i) {
        nameP = n;
        ID = i;
    }
    void checkBook(book* b){
        if(b->isAvailable()){
            b->checkout();
            checkedOutBooks.push_back(b);
            cout<<"The book has been checked out to: "<< nameP<<endl;
        }
        else{
           cout<<"book is not available"<<endl; 
        }
        
    }
    void returnBook(book* b){
         for (int i = 0; i < checkedOutBooks.size(); i++) {
        if(!b->isAvailable()){
            b->returnbook();
              checkedOutBooks.erase(checkedOutBooks.begin() + i);
                cout << "Book has been returned by " << nameP << "." << endl;
                return;
        }
        }
       
           cout<<"book is not being issued"<<endl; 
        
        
    }
    string getNameP(){
        return nameP;
    }
    string getidP(){
        return ID;
    }
};
class Checkout{
    private:
    map<book*,pair<Patron*,time_t>>mp;
    int DAY_SECONDS = 60 * 60 * 24;
    int MAX_FINE = 10;
    
    public:
    void checkOut(book *book, Patron *patron) {
        if (book->isAvailable()) {
            patron->checkBook(book);
            cout<<"Book name: "<<book->getTitle()<<endl;
            time_t dueDate = time(0) + 60 * 60 * 24 * 7; // 7 days from current time
            mp[book] = make_pair(patron, dueDate);
        } else {
            cout << "Book is not available." << endl;
        }
    }
     void returnBook(book *book) {
        if (mp.count(book) == 1) {
            Patron *patron = mp[book].first;
            patron->returnBook(book);
            mp.erase(book);
        } else {
            cout << "Book has not been checked out." << endl;
        }
    }
    void displayCheckouts() {
        cout << "Current checkouts: " << endl;
        for (auto  x : mp) {
            cout << "Book: " << x.first->getTitle() << endl;
            cout << "Author: " << x.first->getAuthor() << endl;
            cout << "Patron: " << x.second.first->getNameP() << endl;
            cout << "Due Date: " << ctime(&x.second.second);
            cout << endl;
        }
    }
      time_t getDueDate(book *book) {
        if (mp.count(book) == 1) {
            return mp[book].second;
        }
        else {
            cout << "Book has not been checked out." << endl;
            return -1;
        }
    }
      double calculateFine(book* book) {
        time_t dueDate = getDueDate(book);
        time_t currentDate = time(0)+60 * 60 * 24 * 9;
        double secondsLate = difftime(currentDate, dueDate);
        if (secondsLate < 0) {
          
            return 0.0;
        } else {
            // calculate fine based on how many days late the book is
            int daysLate = secondsLate / DAY_SECONDS;
            double fine = daysLate * 0.50;
            // cap the fine at MAX_FINE
            return min(fine, (double)MAX_FINE);
        }
    }

};
int main() {
    // Write C++ code here
     Library library;
    book book1("The Great Gatsby", "F. Scott Fitzgerald");
    book book2("To Kill a Mockingbird", "Harper Lee");
    Patron patron1("John Smith", "123");
    Patron patron2("Jane Doe", "456");
    Checkout checkout;
     library.addbook(book1);
    library.addbook(book2);
      library.displayBooks();
      checkout.checkOut(&book1, &patron1);
      time_t dueDate = checkout.getDueDate(&book1);
    if (dueDate != -1) {
        cout << "Due Date: " << ctime(&dueDate) << endl;
    }
    
  double d=checkout.calculateFine (&book1);
  if (d > 0) {
        cout << "Fine for overdue book: Rs" << d << endl;
    }
      checkout.displayCheckouts();

    
    checkout.returnBook(&book1);


    checkout.displayCheckouts();

    return 0;
}
