#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void line() {
    for (int i = 0; i < 30; i++) {
        cout << "-";
    }
}

class system {

public:

    bool if_is_user(string& name , string& path) {
        ifstream fin;
        string user_n;

        fin.open(path);

        if (!fin.is_open()) {
            cout << "ERORE!!!";
        }
        else {
           
            while (!fin.eof()) {
                fin >> user_n;
                if (user_n == name) {
                    return false;
                }
            }
        }

        fin.close();
        return true;
    }
};

class user : public system {
    string name;
    string password;
    string path;
public:
    user() {
        path = "Users.txt";
    };

    void register_user() {

        ofstream fout;
        bool is = true;

        line();
        do {
            cout << "\n" << "Enter username : ";
            cin >> name;
            cout << "Enter password : ";
            (cin >> password).get();
            line();
            cout << "\n";
            if (if_is_user(name, path)) {
                is = false;
            }
            else {
                cout << "Такий користувач вже iснує!!!\nВведiть iнше iмя";
            }
            
        } while(is);

        fout.open(path, ofstream::app);

        if (!fout.is_open()) {
            cout << "ERORE!!!";
        }
        else {
            fout << name << " " << password << ":\n";
        }
        fout.close();
    }

    
};



int main() {
    setlocale(LC_ALL, "UKR");

    user u;

    u.register_user();

    return 0;
}