#include <stdio.h>
#include <iostream>
#include "user.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>

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
    //call encStr for both the user email and user pw. Then store these two. in a file
}

user getUser(std::string email, std::string pw){
    //call encStr for both email and pw, cross reference with file to see if anything matches
    //if email is correct, store it and query terminal for another pw attempt
    //provide option to break loop
    user u("bruh", "bruh");
    return u;
}

bool isValidPw(std::string i){
    //verify that password contains the following
    //is atleast 8 characters long, has atleast 1 uppercase letter
    //has atleast 1 lowercase letter, atleast 1 number, has atleast 1 special character
    return true;
}

bool isValidEmail(std::string i){
    //verify that email contains @ and ends with " . " and max 3 letters behind the " . "
    //good opportunity for regex ;)
    return true;
}

bool isValidMenuInp(std::string i){
    //verify input to be only numbers between 0-9
    return true;
}

int main(){
    std::string inp = "johan";
    std::string encInp = encStr(inp);

    std::cout << inp << " That was the initial message, now comes the encrypted message = " << std::endl;
    std::cout << encInp;
    return 0;
}