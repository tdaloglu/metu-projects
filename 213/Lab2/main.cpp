#include <iostream>
#include <vector>
#include "ContactList.h"


int main()
{
    ContactList cl;

    // Add sample contacts
    cl.addContact("Alice", ContactInfo(std::vector<std::string>(1, "555-1111"),
                                      "alice@mail.com", "OpenAI", ""));
    cl.addPhone("Alice", "555-2222");

    cl.addContact("Bob", ContactInfo(std::vector<std::string>(1, "555-3333"),
                                    "bob@mail.com", "Google", ""));

    cl.addContact("Charlie", ContactInfo(std::vector<std::string>(1, "555-4444"),
                                        "charlie@mail.com", "Microsoft", ""));
    cl.addPhone("Charlie", "555-5555");

    // Build phone index: phone → name
    TreeMap<std::string, std::string> phoneIndex = cl.buildPhoneIndex();


    phoneIndex.print();

    return 0;
}
