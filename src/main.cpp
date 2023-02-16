#include <iostream>
#include <fstream>
#include <vector>

struct User {
    std::string username;
    std::string password;
} User;

void promptMenu(void);
bool logIn(const struct User, std::string fileName);
struct User promptData(void);
bool saveUser(const struct User, std::string fileName);
bool duplicantUser(const struct User, std::string fileName);
bool deleteUser(const struct User, std::string fileName);

class encdec {
    private:
        int key = 1234;
        std::string file = "decrypt.dat";
        char c;
 
    public:
        void encrypt();
        void decrypt();
        bool verifyKey();
};

int main(){
    const std::string fileName = "decrypt.dat";
    while(true){
        promptMenu();
        int promptMenuResult;
        std::cin >> promptMenuResult;
        if(promptMenuResult == 1){
            User = promptData();
            if(saveUser(User, fileName)){
                std::cout << "User created!" << std::endl;
            } else{
                std::cout << "Error Creating User!" << std::endl;
            }
        } else if (promptMenuResult == 2){
            User = promptData();
            if (logIn(User, fileName)){
                std::cout << "User logged in successfully!" << std::endl;
            } else{
                std::cout << "User log-in failed!" << std::endl;
            }
        } else if (promptMenuResult == 3) {
            User = promptData();
            if (deleteUser(User, fileName)){
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
 * @brief Function to log User into system.
 * 
 * @param User 
 * @return true 
 * @return false 
 */
bool logIn(const struct User, std::string fileName){
    try{
        encdec enc;
        if(enc.verifyKey()){
            enc.decrypt();
            std::ifstream infile;
            infile.open(fileName, std::ios::in);
            std::string line;
            std::string target = User.username + "," + User.password;
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


/**
 * @brief Function to prompt for username and password.
 * 
 * @return struct User 
 */
struct User promptData(void){
    std::cout << "Username: ";
    std::cin >> User.username;
    std::cout << "Password: ";
    std::cin >> User.password;
    return User;
}

/**
 * @brief Function to save User object to permanent storage. 
 * 
 * @param User
 * @return bool
 */
bool saveUser(const struct User, std::string fileName){
    try {
        encdec enc;
        if(enc.verifyKey()){
            enc.decrypt();
            if(!duplicantUser(User, fileName)){
                std::ofstream afile;
                afile.open(fileName, std::ios::app);
                afile << User.username + "," + User.password << std::endl;
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
bool duplicantUser(const struct User, std::string fileName){
    try{
        std::ifstream infile;
        infile.open(fileName, std::ios::in);
        std::string line;
        while(getline(infile, line)){
            int pos = line.find(",");
            std::string target = line.substr(0,pos);
            if (target == User.username){
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
bool deleteUser(const struct User, std::string fileName){
    try{
        encdec enc;
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
            std::string target = User.username + "," + User.password;
            std::size_t found = data.find(target);
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
 * @brief Function definition to encrypt .dat file.
 * 
 */
void encdec::encrypt()
{
 
    std::fstream fin, fout;

    fin.open(file, std::fstream::in);
    fout.open("encrypt.dat", std::fstream::out);
 
    while (fin >> std::noskipws >> c) {
        int temp = (c + this->key);
        fout << (char)temp;
    }
 
    // Closing both files
    fin.close();
    fout.close();
}
 
/**
 * @brief Function definition to decrypt .dat file.
 * 
 */
void encdec::decrypt()
{
    std::fstream fin;
    std::fstream fout;
    fin.open("encrypt.dat", std::fstream::in);
    fout.open("decrypt.dat", std::fstream::out);
 
    while (fin >> std::noskipws >> c) {
 
        // Remove the key from the
        // character
        int temp = (c - this->key);
        fout << (char)temp;
    }
 
    fin.close();
    fout.close();
}

/**
 * @brief Function to verify authorization to to encrypt/decrypt .dat file.
 * 
 * @return true 
 * @return false 
 */
bool encdec::verifyKey(){
    std::cout << "Access key: ";
    int tempKey;
    std::cin >> tempKey;
    return this->key == tempKey ? true : false; 
}