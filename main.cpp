#include <stdio.h>
#include <iostream>
#include "user.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <regex>
#include <fstream>


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
    std::ofstream file("users.txt", std::ios::app);
    if(file.is_open()){
        file << email << "," << password << "\n";
        file.close();
    }else {
        std::cerr << "Cant open file" << std::endl;
    }

}

user getUser(std::string email, std::string pw){
    //if email is correct, store it
    //ask for password, call encstr on pw and cross reference with the matching email on the same line.
    //provide option to break loop
    std::ifstream file("users.txt");
    std::string line;
    while(getline(file, line)){
        std::stringstream ss(line);
        std::string storedEmail, storedPassword;
        if(getline(ss, storedEmail, ',') && getline(ss, storedPassword)){
            if(storedEmail == email){
                if(encStr(pw) == storedPassword){
                    user u(storedEmail, pw);
                    return u;
                }else{
                    std::cout << " Invalid password, please try again" << std::endl;
                    break;
                }
            }else{
                std::cout << " Invalid email, please try again" << std::endl;
                break;
            }
        }
    }
    return {"", ""};
}

bool isValidPw(std::string i){
    std::regex password("^(?=.*[!@#$%^&*(),.?\":{}|<>])(?=.*[A-Z])(?=.*[a-z])(?=.*\\d).{8,}$");
    return std::regex_match(i, password);
}

bool isValidEmail(std::string i){
    std::regex email("^.{1,32}@.{1,16}\\.[a-zA-Z]{2,3}$");
    return std::regex_match(i, email);
}

bool isValidMenuInp(std::string i){
    std::regex menInp("^[0-9]+$");
    if (!std::regex_match(i, menInp)) {
        std::cout << "Please input a number" << std::endl;
        return false;
    }
    int inp = std::stoi(i);
    if(inp > 3 || inp <= 0){
        std::cout << " Please enter a number between 1 and 3" << std::endl;
        return false;   
    } 
    return true;
}

int main(void){
    int userInp = 0;
    while(1){
        std::cout << " Press 1 to create a new user " << std::endl 
                  << " Press 2 to sign in " << std::endl 
                  << " Press 3 to exit " << std::endl;
        std::string sInp;
        std::cin >> sInp;
        if(!isValidMenuInp(sInp)){
            continue;
        }
        userInp = std::stoi(sInp);
        if(userInp == 1){
            std::string newEmail = "";
            std::cout << " Please input an email" << std::endl;
            std::string userInput;
            std::cin >> userInput;
            if(!isValidEmail(userInput)){
                std::cout << " Invalid email, please make sure to contain @ and .com or similar at the end" << std::endl;
                continue;
            }
            newEmail = userInput;
            std::cout << " Please input a password" << std::endl;
            std::string newPassword = "";
            while(newPassword.empty()){
                std::cin >> userInput;
                if(isValidPw(userInput)){
                    newPassword = userInput;
                    break;
                }
                std::cout << " Invalid password, please try again." << std::endl;
                continue;
            }
            user newUser(newEmail, newPassword);
            storeUser(newUser);
        }else if(userInp == 2){
            std::cout << " Please input an email" << std::endl;
            std::string userInput;
            std::cin >> userInput;
            std::string logEmail = userInput;
            std::cout << " Please input a password" << std::endl;
            std::cin >> userInput;
            std::string logPassword = userInput;
            user logU = getUser(logEmail, logPassword);
            if(logU.getEmail() == "" || logU.getPw() == ""){
                std::cout << " Invalid user " << std::endl;
                break;
            }
            std::cout << "User email is = " << logU.getEmail() << std::endl 
                      << "User password is = " << logU.getPw() << std::endl 
                      << "User encrypted password is = " << encStr(logU.getPw()) << std::endl;
        }else if(userInp == 3){
            return 0; // exit prog
        }

    }
    return 0;
}