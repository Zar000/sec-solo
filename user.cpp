#include "user.h"

user::user(std::string email, std::string pw){
    this->email = email;
    this->pw = pw;
}
std::string user::getEmail(){
    return email;
}
std::string user::getPw(){
    return pw;
}