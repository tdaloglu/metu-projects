#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include <string>
#include <vector>
#include "TreeMap.cpp"
#include "KeyValuePair.h"
#include "NoSuchItemException.h"

struct ContactInfo {
    std::vector<std::string> phones;
    std::string email;
    std::string company;
    std::string notes;

    ContactInfo() {}

    ContactInfo(const std::vector<std::string> &p,
                const std::string &e,
                const std::string &c,
                const std::string &n = "")
        : phones(p), email(e), company(c), notes(n) {}
};


class ContactList {

private:
    TreeMap<std::string, ContactInfo> contacts;

public:
    ContactList();
    ~ContactList();
    void addContact(const std::string &name, const ContactInfo &info);
    void updateContact(const std::string &name, const ContactInfo &newInfo);
    void addPhone(const std::string &name, const std::string &phone);
    const ContactInfo &getContact(const std::string &name) const;
    

    TreeMap<std::string, std::string> buildPhoneIndex() const;// TODO Q3
    
    // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    
    KeyValuePair<std::string, ContactInfo>& minimum() const {
        return contacts.mini();
    }

};

#endif
