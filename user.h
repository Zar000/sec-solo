#ifndef USER_H
#define USER_H

#include <string>

class user{

private: 
    std::string email;
    std::string pw;

public:
    user(std::string email, std::string pw);
    std::string *getPw();
    std::string *getEmail();

};


#endif