#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int NAME_SIZE = 50, PHONE_SIZE = 20, ADDR_SIZE = 200;
fstream people;

struct Person {
    char first_name[NAME_SIZE];
    char last_name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char address[ADDR_SIZE];
    struct Person* next;
};

//prototypes
void insertPerson(struct Person*);
int menuChoice();
void loadAddressBook();
void printAddressBook();
void printEntry(struct Person*);
void saveAddressBook();
void search();
int searchChoice();
void searchMenu(struct Person*);

//make head global
struct Person* head = NULL;


void addPerson() {
    struct Person* newPerson = new Person;
    strcpy(newPerson->first_name, "");
    strcpy(newPerson->last_name, "");
    strcpy(newPerson->phone, "");
    strcpy(newPerson->address,"");
    newPerson->next = NULL;

    cout << endl << endl;
    cout << "Enter the first name : ";
    cin.getline(newPerson->first_name, NAME_SIZE);

    cout << setw(23) << left << "Enter the last name : ";
    cin.getline(newPerson->last_name, NAME_SIZE);

    cout << setw(23) << left << "Enter phone number : ";
    cin.getline(newPerson->phone, PHONE_SIZE);

    cout << setw(23) << left << "Enter address : ";
    cin.getline(newPerson->address, ADDR_SIZE);

    insertPerson(newPerson);
}

/*void buildList() {
    struct Person* current = NULL;

    //allocate memory for new entries
    current = new Person;
    current->first_name = "Siouxsie";
    current->last_name = "Sioux";
    current->phone = "702-555-5555";
    current->address = "3570 S Las Vegas Blvd, Las Vegas, NV 89109";
    insertPerson(current);

    current = new Person;
    current->first_name = "Morticia";
    current->last_name = "Addams";
    current->phone = "415-666-1313";
    current->address = "13 Funston Street, San Francisco, CA 94129";
    insertPerson(current);

    current = new Person;
    current->first_name = "Norman";
    current->last_name = "Bates";
    current->phone = "323-555-5555";
    current->address = "1070 272nd Street, Aldergrove, BC V4W 2P8, Canada";
    insertPerson(current);
}*/

//edit menu
int editChoice() {
  int choice;
  do {
    cout << endl;
    cout << "1. Edit First Name" << endl;
    cout << "2. Edit Last Name" << endl;
    cout << "3. Edit Phone Numer" << endl;
    cout << "4. Edit Address" << endl;
    cout << "5. Edit All" << endl;
    cout << "6. Return To Main Menu" << endl;
    cout << "Enter your choice (1-6): ";
    cin >> choice;
    cin.ignore();
  } while (!(choice > 0 && choice < 7));

  return choice;
}

void editEntry(struct Person* current){
  int choice = editChoice();
  switch (choice) {
    case 1 :  cout << endl;
              cout << current->first_name << endl;
              cout << "Enter New First Name : ";
              cin.getline(current->first_name, NAME_SIZE);
              printEntry(current);
              break;
    case 2 :  cout << endl;
              cout << current->last_name << endl;
              cout << "Enter New Last Name : ";
              cin.getline(current->last_name, NAME_SIZE);
              printEntry(current);
              break;
    case 3 :  cout << endl;
              cout << current->phone << endl;
              cout << "Enter New Phone Number : ";
              cin.getline(current->phone, PHONE_SIZE);
              printEntry(current);
              break;
    case 4 :  cout << endl;
              cout << current->address << endl;
              cout << "Enter New Address : ";
              cin.getline(current->address, ADDR_SIZE);
              printEntry(current);
              break;
    case 5 :  cout << endl;
              cout << current->first_name << endl;
              cout << "Enter New First Name : ";
              cin.getline(current->first_name, NAME_SIZE);

              cout << endl;
              cout << current->last_name << endl;
              cout << "Enter New Last Name : ";
              cin.getline(current->last_name, NAME_SIZE);

              cout << endl;
              cout << current->phone << endl;
              cout << "Enter New Phone Number : ";
              cin.getline(current->phone, PHONE_SIZE);

              cout << endl;
              cout << current->address << endl;
              cout << "Enter New Address : ";
              cin.getline(current->address, ADDR_SIZE);
              printEntry(current);
              break;
  }
}

//insert entry in list alphabetically by last name
void insertPerson(struct Person* newPerson) {
  struct Person* current = head;
  if(head == NULL || strcmp(newPerson->last_name, head->last_name) < 0) {
    newPerson->next = head;
    head = newPerson;
  }
  else {
    while(current->next != NULL) {
      if(strcmp(newPerson->last_name, current->next->last_name) < 0) {
        break;
      }
      else
        current = current->next;
    }
    newPerson->next = current->next;
    current->next = newPerson;
  }
}

void loadAddressBook() {

  // Test if file exists by attempting to open it
  cout << "Looking for saved file...\n";
  people.open("address_book.dat", ios::in | ios::binary);

  if (!people.fail()) {
    cout << "\n\nReading file...\n";

    // Read the first record of the file.
    struct Person* newPerson = new Person;
    people.read(reinterpret_cast<char *>(newPerson), sizeof(*newPerson));

    // While not at the end of the file, display the records
    while (!people.eof()) {
      newPerson->next = NULL;
      printEntry(newPerson);
      insertPerson(newPerson);

      newPerson = new Person;
      cout << "Reading...\n";
      people.read(reinterpret_cast<char *>(newPerson), sizeof(*newPerson));
    }
    cout << "Closing file...\n";
    people.close();
    printAddressBook();
  }
}

void menu() {
  //menu and user choice
    int choice;
    do {
      choice = menuChoice();
      switch (choice) {
        case 1 :    addPerson();
                    break;
        case 2 :    //delete person
                    break;
        case 3 :    search();
                    break;
        case 4 :    printAddressBook();
                    break;
        case 5 :    search();
                    break;
        case 6 :    saveAddressBook();
                    break;
      }
   } while (choice != 7);
}

int menuChoice () {
  int choice;
  do {
    cout << endl;
    cout << "1. Add New Entry\n";
    cout << "2. Delete An Entry\n";
    cout << "3. Edit An Entry\n";
    cout << "4. List All Entries\n";
    cout << "5. Search For An Entry\n";
    cout << "6. Save to File\n";
    cout << "7. Quit Program\n";
    cout << "Enter your choice (1-7): ";
    cin >> choice;
    cin.ignore();
  } while (!(choice > 0 && choice < 8));

  return choice;
}

//prints whole address book
void printAddressBook() {
  struct Person* iter = head;
  cout << endl << endl;

  while (iter != NULL) {
      printEntry(iter);
      iter = iter->next;
  }
}

//prints one entry
void printEntry(struct Person* iter) {
  cout << endl;
  cout << iter->last_name << ", ";
  cout << iter->first_name << endl;
  cout << iter->phone << endl;
  cout << iter->address << endl;
  cout << endl;
}

//saves the address book
void saveAddressBook() {
  struct Person* iter = head;
  cout << "Opening file...\n";
  people.open("address_book.dat", ios::out | ios::binary);
  while (iter != NULL) {
    people.write(reinterpret_cast<char *>(iter), sizeof(*iter));
    iter = iter->next;
  }
  cout << "Closing file...\n";
  people.close();
}

void search() {
  struct Person* iter = head;
  string userSearch;
  int choice;
  cout << endl;

  choice = searchChoice();

  switch (choice) {
    case 1 :    cout << endl;
                cout << "Enter Last Name : ";
                getline(cin, userSearch);

                while (iter != NULL) {
                  if(userSearch == iter->last_name) {
                    printEntry(iter);
                    break;
                  }
                  else
                    iter = iter->next;
                }

                if(iter == NULL) {
                  cout << endl;
                  cout << "Entry not in address book" << endl;
                  cout << endl;
                }
                else
                  searchMenu(iter);
                break;
    case 2 :    cout << endl;
                cout << "Enter First Name : ";
                getline(cin, userSearch);

                while (iter != NULL) {
                  if(userSearch == iter->first_name) {
                    printEntry(iter);
                    break;
                  }
                  else
                    iter = iter->next;
                }

                if(iter == NULL) {
                  cout << endl;
                  cout << "Entry not in address book" << endl;
                  cout << endl;
                }
                else
                  searchMenu(iter);
                break;
    case 3 :    cout << endl;
                cout << "Enter Phone Number  (###-###-####): ";
                getline(cin, userSearch);

                while (iter != NULL) {
                  if(userSearch == iter->phone) {
                    printEntry(iter);
                    break;
                  }
                  else
                    iter = iter->next;
                }

                if(iter == NULL) {
                  cout << endl;
                  cout << "Entry not in address book" << endl;
                  cout << endl;
                }
                else
                  searchMenu(iter);
                break;
    case 4 :    cout << endl;
                cout << "Enter Address : ";
                getline(cin, userSearch);

                while (iter != NULL) {
                  if(userSearch == iter->address) {
                    printEntry(iter);
                    break;
                  }
                  else
                    iter = iter->next;
                }

                if(iter == NULL) {
                  cout << endl;
                  cout << "Entry not in address book" << endl;
                  cout << endl;
                }
                else
                  searchMenu(iter);
                break;
  }
}

//search by what parameters
int searchChoice() {
  int choice;
  do {
    cout << "1. Search By Last Name" << endl;
    cout << "2. Search By First Name" << endl;
    cout << "3. Search By Phone Number" << endl;
    cout << "4. Search By Address" << endl;
    cout << "5. Return To Main Menu" << endl;
    cout << "Enter your choice (1-5): ";
    cin >> choice;
    cin.ignore();
  } while (!(choice > 0 && choice < 6));

  return choice;
}

//post search menu
void searchMenu(struct Person* iter) {
  int choice;
  cout << endl;

  do {
    cout << "1. Edit The Entry" << endl;
    cout << "2. Delete The Entry" << endl;
    cout << "3. Return to Main Menu" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    cin.ignore();
  } while (!(choice > 0 && choice < 4));

  switch (choice) {
    case 1 :  editEntry(iter);
              break;
    case 2 :  //delete entry
              break;
    }
}

int main() {
    loadAddressBook();
    menu();
    return 0;
}
