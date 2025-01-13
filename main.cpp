#include <stdio.h>
#include <iostream>
#include "user.h"

std::string encStr(std::string i){
    //encrypt string and return it

    return i; // temp
}

void storeUser(user u){
    //call encStr for both the user email and user pw. Then store these two. in a file
}

user getUser(std::string email, std::string pw){
    //call encStr for both email and pw, cross reference with file to see if anything matches
    //if email is correct, store it and query terminal for another pw attempt
    //provide option to break loop
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
    while(1){

    }
    return 0;
}