#include <stdio.h>
#include <iostream>
#include "user.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <regex>

std::string encStr(const std::string& i) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digestLength = 0;

    EVP_Digest(i.data(), i.size(), digest, &digestLength, EVP_md5(), nullptr);

    std::ostringstream oss;
    for (unsigned int i = 0; i < digestLength; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    return oss.str();
}

void storeUser(user u){
    std::string email = u.getEmail();
    std::string password = encStr(u.getPw());
    //store email and password

}

user getUser(std::string email, std::string pw){
    //if email is correct, store it
    //ask for password, call encstr on pw and cross reference with the matching email on the same line.
    //provide option to break loop
    user u("bruh", "bruh"); // temp so func doesnt error DELETE AFTER
    return u;
}

bool isValidPw(std::string i){
    //verify that password contains the following
    //is atleast 8 characters long, has atleast 1 uppercase letter
    //has atleast 1 lowercase letter, atleast 1 number, has atleast 1 special character
    std::regex password("^(?=.*[!@#$%^&*(),.?\":{}|<>])(?=.*[A-Z])(?=.*[a-z])(?=.*\\d).{8,}$");
    return std::regex_match(i, password);
}

bool isValidEmail(std::string i){
    //verify that email contains @ and ends with " . " and max 3 letters behind the " . "
    std::regex email("^.{1,32}@.{1,16}\\.[a-zA-Z]{1,3}$");
    return std::regex_match(i, email);
}

bool isValidMenuInp(std::string i){
    //verify input to be only numbers between 0-9
    int inp = std::stoi(i);
    if(inp > 9 || inp < 0){
        return false;   
    } 
    return true;
}

int main(){
    std::string inp = "johan";
    std::string encInp = encStr(inp);

    std::cout << inp << " That was the initial message, now comes the encrypted message = " << std::endl;
    std::cout << encInp;
    return 0;
}