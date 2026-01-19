#include "ContactList.h"
#include <iostream>


TreeMap<std::string, std::string> ContactList::buildPhoneIndex() const {
    TreeMap<std::string, std::string> phoneIndex;
    // TODO:
    // Build a new TreeMap that maps:
    //   phone number  →  contact name
    //
    // Requirements:
    // - Each phone number in this ContactList must appear as a key once.
    // - If a contact has multiple phone numbers, insert each separately.
    // - Returned TreeMap must be sorted by phone number.
    //
    // Hint:
    // - Traverse your contacts and insert entries into a new TreeMap.
    
    KeyValuePair<std::string, ContactInfo> item = minimum();
    try {
        while (true) {
            std::string key = item.getKey();
            
            ContactInfo value = item.getValue(); 
            
            for (int i = 0; i < value.phones.size(); i++) {
                phoneIndex.put(value.phones[i], key);
            }
            
            item = contacts.next(item);
        }    
    } catch (NoSuchItemException& e) {
        
    }
    
    
    return phoneIndex;
}


ContactList::ContactList() {}

ContactList::~ContactList() {}

void ContactList::addContact(const std::string &name, const ContactInfo &info) {
    contacts.put(name, info);
}


void ContactList::updateContact(const std::string &name, const ContactInfo &newInfo) {
    contacts.put(name, newInfo);
}

void ContactList::addPhone(const std::string &name, const std::string &phone) {

    const ContactInfo &oldInfo = contacts.get(name);

    ContactInfo updated = oldInfo;

    bool exists = false;
    for (size_t i = 0; i < updated.phones.size(); i++)
        if (updated.phones[i] == phone)
            exists = true;

    if (!exists)
        updated.phones.push_back(phone);

    contacts.put(name, updated);
}

const ContactInfo &ContactList::getContact(const std::string &name) const {
    return contacts.get(name);
}





