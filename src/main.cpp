#include <iostream>
#include "login_system.hpp"
using namespace login_system_app;


const std::string DataStorage::file = "decrypt.dat";

int main(){


    while(true){
        promptMenu();
        int promptMenuResult;
        std::cin >> promptMenuResult;
        if(promptMenuResult == 1){
            User user = promptData();
            if(user.saveUser(DataStorage::file)){
                std::cout << "User created!" << std::endl;
            } else{
                std::cout << "Error Creating User!" << std::endl;
            }
        } else if (promptMenuResult == 2){
            User user = promptData();
            if (user.logIn(DataStorage::file)){
                std::cout << "User logged in successfully!" << std::endl;
            } else{
                std::cout << "User log-in failed!" << std::endl;
            }
        } else if (promptMenuResult == 3) {
            User user = promptData();
            if (user.deleteUser(DataStorage::file)){
                std::cout << "User deleted successfully!" << std::endl;
            } else{
                std::cout << "User deletion failed!" << std::endl;
            }
        } else if (promptMenuResult == 4){
            std::cout << "Goodbye!" << std::endl;
            exit(EXIT_SUCCESS);
        } else{
            std::cout << "Please enter valid selection!" << std::endl;
        }
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
    return 0;
}
