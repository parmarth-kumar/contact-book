#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

/* Display the main menu and return a validated choice. */
int menu()
{
    std::cout << "\n===== CONTACT BOOK =====\n\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. View All Contacts\n";
    std::cout << "3. Search Contact\n";
    std::cout << "4. Update Contact\n";
    std::cout << "5. Delete Contact\n";
    std::cout << "6. Exit\n\n";

    int option = 0;
    while (true) {
        std::cout << "Enter choice : ";

        if (!(std::cin >> option) || option < 1 || option > 6) {
            std::cout << "Invalid choice. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return option;
    }
}

/* Validate that a phone number contains exactly 10 digits. */
bool isValidPhoneNumber(const std::string& phoneNumber)
{
    if (phoneNumber.length() != 10)
    {
        return false;
    }

    for (char ch : phoneNumber)
    {
        if (!std::isdigit(ch))
        {
            return false;
        }
    }

    return true;
}


/* Find contacts whose names match the search query and store their indexes. */
int searchContacts(const std::string names[], int contactCount, const std::string &searchQuery, int searchResults[]) 
{
    int resultCount = 0;
    for (int i = 0; i < contactCount; i++) {
        if (searchQuery == names[i]) {
            searchResults[resultCount] = i;
            resultCount++;
        }
    }
    return resultCount;
}


/* Print matching contacts and return the index chosen by the user. */
int selectContact(int resultCount, const std::string names[], const std::string numbers[], const int searchResults[]) 
{
    for (int i=0; i < resultCount; i++) {
        std::cout << "  " << std::right << std::setw(2) << i + 1 
        << ") Name : " << names[searchResults[i]]
        << "\n      Phone : " << numbers[searchResults[i]] << "\n";
    }

    std::cout << "Enter choice : ";
    int selectedChoice;
    while (!(std::cin >> selectedChoice) || selectedChoice < 1 || selectedChoice > resultCount) {
        std::cout << "Invalid choice. Try again.\n";
        std::cout << "Enter choice : ";
    }
    
    return searchResults[selectedChoice - 1];
}

int main() {
    std::string names[100];
    std::string numbers[100];
    int contactCount = 0;
    while (true) {
        int choice = menu();

        /* Add Contact */
        if (choice == 1) {
            if (contactCount >= 100) {
                std::cout << "\nMaximum contact limit reached. Cannot add more contacts.\n";
                continue;
            }
            std::string name;
            std::string phoneNumber;
            
            std::cout << "\nENTER CONTACT DETAILS\n";

            std::cout << "  Name : ";
            while (!(std::cin >> name)) 
            {
                std::cout << "Invalid name. Try again.\n";
                std::cout << "  Name : ";
            }

            while (true){
                std::cout << "  Phone : ";
                std::cin >> phoneNumber;

                if (isValidPhoneNumber(phoneNumber)) { break; }
                std::cout << "Invalid phone number. Enter exactly 10 digits.\n";
            }

            names[contactCount] = name;
            numbers[contactCount] = phoneNumber;
            contactCount++;

            std::cout << "  Contact added successfully.\n";
        }


        /* View All Contacts */
        else if (choice == 2) {

            if (contactCount == 0) {
                std::cout << "\nNo contacts added yet.\n";
                continue;
            }

            /* Display all contacts in a table-like format. */
            std::cout << "\nCONTACT LIST\n";
            std::cout << "  Name              Phone Number\n";
            std::cout << "  -------------------------------\n";
            for (int i=0; i < contactCount; i++) {
                std::cout << "  " 
                        << std::left 
                        << std::setw(15) << names[i] << "   "
                        << numbers[i] << "\n";
            }
        }


        /* Search Contact */
        else if (choice == 3) {

            if (contactCount == 0) {
                std::cout << "\nContact List empty.\n";
                continue;
            }

            std::cout << "\nSEARCH CONTACTS\n";
            std::cout << "  Search Name : ";
            std::string searchQuery;
            while (!(std::cin >> searchQuery)) {
                std::cout << "Invalid input. Try again.\n";
                std::cout << "  Search Name : ";
            }
            std::cout << "\n";

            
            int searchResults [100];
            int resultCount = searchContacts(names, contactCount, searchQuery, searchResults);

            if (resultCount == 0) {std::cout << "No contacts found with the given name.\n";}
            else {
                std::cout << "\n" << resultCount << " results(s) found for " << searchQuery << "\n";
                for (int i=0; i < resultCount; i++) {
                    std::cout << "  " << std::right << std::setw(2) << i + 1 
                    << ") Name  : " << names[searchResults[i]] 
                    << "\n      Phone : " << numbers[searchResults[i]] << "\n";
                }
            }
        }


        /* Update Contact */
        else if (choice == 4) {

            if (contactCount == 0) {
                std::cout << "\nContact List empty.\n";
                continue;
            }

            std::cout << "\nUPDATE CONTACTS\n";
            std::cout << "  Search Name : ";
            std::string searchQuery;
            while (!(std::cin >> searchQuery)) {
                std::cout << "Invalid input. Try again.\n";
                std::cout << "  Search Name : ";
            }
            std::cout << "\n";


            int searchResults [100];
            int resultCount = searchContacts(names, contactCount, searchQuery, searchResults);

            if (resultCount == 0) {
                std::cout << "No contacts found with the given name.\n";
            }

            else {

                std::cout << "Choose contact to update.\n";
                
                int indexToUpdate = selectContact(resultCount, names, numbers, searchResults);

                std::string newNumber;

                while (true) {
                    std::cout << "  Enter new number : ";
                    std::cin >> newNumber;

                    if (isValidPhoneNumber(newNumber)) { break; }
                    std::cout << "Invalid phone number. Enter exactly 10 digits.\n";
                }

                numbers[indexToUpdate] = newNumber;
                std::cout << "Contact updated successfully.\n";
            }
        }


        /* Delete Contact */
        else if (choice == 5) {

            if (contactCount == 0) {
                std::cout << "\nContact List empty.\n";
                continue;
            }

            std::cout << "\nDELETE CONTACTS\n";
            std::cout << "  Search Name : ";
            std::string searchQuery;
            while (!(std::cin >> searchQuery)) {
                std::cout << "Invalid input. Try again.\n";
                std::cout << "  Search Name : ";
            }
            std::cout << "\n";

            
            int searchResults [100];
            int resultCount = searchContacts(names, contactCount, searchQuery, searchResults);

            if (resultCount == 0) {
                std::cout << "No contacts found with the given name.\n";
            }

            else {

                std::cout << "Choose contact to delete.\n";

                int indexToDelete = selectContact(resultCount, names, numbers, searchResults);

                for (int i = indexToDelete; i < contactCount - 1; i++) {
                    names[i] = names[i + 1];
                    numbers[i] = numbers[i + 1];
                }

                contactCount--;
                std::cout << "Contact deleted successfully.\n";
                }
            }

        else if (choice == 6) {
            std::cout << "\nExiting Contact Book. Goodbye!\n";
            break;
    }
}
}
