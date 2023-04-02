#include <iostream>
#include <fstream>
#ifndef LOGIN_SYSTEM_HPP
    #define LOGIN_SYSTEM_HPP
        #include "login_system.hpp"
#endif


namespace login_system_app {
    /**
    * @brief Function to display Commandline Menu.
    * 
    */
    void promptMenu(void){
        std::cout << "1. Register" << std::endl;
        std::cout << "2. Log In" << std::endl;
        std::cout << "3. Delete User" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Selection: ";
    }

    /**
     * @brief Function to prompt for username and password.
     * 
     * @return struct User 
     */
    User promptData(void){
        std::string username;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::string password;
        std::cin >> password;
        return {username, password};
    }

    /**
     * @brief Construct a new encdec::encdec object
     * 
     * @param fileName 
     */
    encdec::encdec(const std::string& fileName) : _file(fileName) {}

    /**
     * @brief Function definition to encrypt file.
     * 
     */
    void encdec::encrypt()
    {
    
        std::fstream fin, fout;

        fin.open(_file, std::fstream::in);
        fout.open("encrypt.dat", std::fstream::out);
    
        while (fin >> std::noskipws >> _c) {
            int temp = (_c + this->_key);
            fout << (char)temp;
        }
    
        // Closing both files
        fin.close();
        fout.close();
    }
    
    /**
     * @brief Function definition to decrypt file.
     * 
     */
    void encdec::decrypt()
    {
        std::fstream fin;
        std::fstream fout;
        fin.open("encrypt.dat", std::fstream::in);
        fout.open("decrypt.dat", std::fstream::out);
    
        while (fin >> std::noskipws >> _c) {
    
            // Remove the key from the
            // character
            int temp = (_c - this->_key);
            fout << (char)temp;
        }
    
        fin.close();
        fout.close();
    }

    /**
     * @brief Function to verify authorization to to encrypt/decrypt file.
     * 
     * @return true 
     * @return false 
     */
    bool encdec::verifyKey(){
        std::cout << "Access key: ";
        int tempKey;
        std::cin >> tempKey;
        return this->_key == tempKey ? true : false; 
    }

    /**
     * @brief Construct a new User:: User object
     * 
     * @param userName 
     * @param password 
     */
    User::User(const std::string& username, const std::string& password) : _username(username), _password(password) {}

    /**
     * @brief Function to save User object to permanent storage. 
     * 
     * @param User
     * @return bool
     */
    bool User::saveUser(const std::string& fileName){
        try {
            encdec enc(fileName);
            if(enc.verifyKey()){
                enc.decrypt();
                if(!duplicantUser(fileName)){
                    std::ofstream afile;
                    afile.open(fileName, std::ios::app);
                    afile << _username + "," + _password << std::endl;
                    afile.close();
                    enc.encrypt();
                    return true;
                } else{
                    throw ("User Duplicated");
                }
            } else {
                throw ("Incorrect Access Key!");
            }
        } catch(...){
            return false;
        }
    }

    /**
     * @brief Function to check if Username already exist.
     * 
     * @param User 
     * @return true 
     * @return false 
     */
    bool User::duplicantUser(const std::string& fileName){
        try{
            std::ifstream infile;
            infile.open(fileName, std::ios::in);
            std::string line;
            while(getline(infile, line)){
                size_t pos = line.find(",");
                std::string target = line.substr(0,pos);
                if (target == _username){
                    infile.close();
                    return true;
                }
            }
            infile.close();
            return false;
        } catch(...){
            return true;
        }
    }

    /**
     * @brief Function to delete User from storage.
     * 
     * @param User
     * @return true 
     * @return false 
     */
    bool User::deleteUser(const std::string& fileName){
        try{
            encdec enc(fileName);
            if(enc.verifyKey()){
                enc.decrypt();
                std::ifstream infile;
                infile.open(fileName, std::ios::in);
                std::string data;
                std::string line;
                while(getline(infile, line)){
                    data.append(line+"\n");
                }
                infile.close();
                std::string target = _username + "," + _password;
                size_t found = data.find(target);
                if(found != std::string::npos){
                    data.erase(found, target.length()+1);
                } else{
                    return false;
                }
                std::ofstream outfile;
                outfile.open(fileName);
                outfile << data;
                outfile.close();
                enc.encrypt();
            } else {
                throw ("Incorrect Access Code!");
            }
            return true;
        } catch(...){
            return false;
        }
    }

    /**
     * @brief Function to log User into system.
     * 
     * @param User 
     * @return true 
     * @return false 
     */
    bool User::logIn(const std::string& fileName){
        try{
            encdec enc(fileName);
            if(enc.verifyKey()){
                enc.decrypt();
                std::ifstream infile;
                infile.open(fileName, std::ios::in);
                std::string line;
                std::string target = _username + "," + _password;
                while(getline(infile, line)){
                    if (target == line){
                        infile.close();
                        return true;
                    }
                }
                infile.close();
                enc.encrypt();
            } else {
                throw ("Incorrect Access Code!");
            }
            return false;
        } catch(...){
            return false;
        }
    }
}