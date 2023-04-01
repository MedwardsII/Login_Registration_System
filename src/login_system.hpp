#include <iostream>


class User {
    private:
        std::string username;
        std::string password;
    public:
        User(const std::string& username, const std::string& password);
        bool logIn(const std::string& fileName);
        bool saveUser(const std::string& fileName);
        bool duplicantUser(const std::string& fileName);
        bool deleteUser(const std::string& fileName);
};

void promptMenu(void);
User promptData(void);

class encdec {
    private:
        int key = 1234;
        std::string file;
        char c;
 
    public:
        encdec(const std::string& fileName): file(fileName){};
        void encrypt();
        void decrypt();
        bool verifyKey();
};