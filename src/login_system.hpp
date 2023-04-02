#include <iostream>

namespace login_system_app {
    class User {
        private:
            std::string _username;
            std::string _password;
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
            int _key = 1234;
            std::string _file;
            char _c;
    
        public:
            encdec(const std::string& fileName);
            void encrypt();
            void decrypt();
            bool verifyKey();
    };
}