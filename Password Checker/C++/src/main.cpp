#include<iostream>
#include<string>

class passwordChecker{
    private:
    std::string password, confirmation;
    int passwordCheckList[5];
    
    public:
    passwordChecker(){
        password = "";
        confirmation = "";
        passwordCheckList[5] = {};
    }

    void run(){
        bool confirmed = false;
        while(!confirmed){
            displayRules();
            getPassword();
            bool valid = invalid();
            while(!valid){
                std::cout << "Error: Your password failed one or more password rules\n";
                displayRules();
                getPassword();
                valid = invalid();
            }
            getConfirmation();
            confirmed = confirm();
        }
        displaySuccess();
    }

    void displayRules(){
    std::cout << "Password Requirement:\n";
    std::cout << "1) The password length: 8-32 characters\n" ;
    std::cout << "2) At least one numerical, i.e., 0, 1, 2,..\n";
    std::cout << "3) At least one upper case letter, i.e., A, B, C, ...\n";
    std::cout << "4) At least one lower case letter, i.e., a, b, c, ...\n";
    std::cout << "5) At least one of the special characters, but it must be within the set:{ # $ * ( ) % & ^} a total of eight (8) special characters.no other special characters are allowed.\n";
    }

    void getPassword(){
        std::cout << "Please enter your password:\n";
        std::cin >> password;
        while(password.length()<8 || password.length()>32){
            std::cout << "Error: Invalid Length. Re-enter another password:\n";
            std::cin >> password;
        }
    }

    bool invalid(){
        for(int i =0; i<5; i++) passwordCheckList[i] = 0;
        for(int i = 0; i<password.length(); i++){
            if( (password[i]>='0') && (password[i]<='9') ) passwordCheckList[1]++;
            else if( (password[i]>='a') && (password[i]<='z') ) passwordCheckList[2]++;
            else if( (password[i]>='A') && (password[i]<='Z') ) passwordCheckList[3]++;
            else if( (password[i]>='A') && (password[i]<='Z') ) passwordCheckList[3]++;
            else if( (password[i]>='#') && (password[i]<='&') ) passwordCheckList[4]++;
            else if( (password[i]>='(') && (password[i]<='*') ) passwordCheckList[4]++;
            else if( (password[i]=='^') ) passwordCheckList[4]++;
            else passwordCheckList[0]++;
        }
        if(passwordCheckList[0]!=0) return false;
        for(int i = 1; i<5; i++) 
            if(passwordCheckList[i]==0) return false;
        return true;
    }

    bool confirm(){
        return password == confirmation;
    }

    void getConfirmation(){
        std::cout << "Enter your password again:\n";
        std::cin >> confirmation;
    }

    void displaySuccess(){
        std::cout << "Your password will be updated in 2 minuties\n";
    }
};

int main(){
    passwordChecker pw = passwordChecker();
    pw.run();
    return 0;
}
