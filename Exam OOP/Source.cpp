#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
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

    bool if_is_password(string& name , string& password, string& path) {
        ifstream fin;
        string user_n;
        string password_c;

        password += ':';

        fin.open(path);

        if (!fin.is_open()) {
            cout << "ERORE!!!";

        }
        else {

            while (!fin.eof()) {
                fin >> user_n;
                fin >> password_c;
                if (user_n == name && password_c == password ) {
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

        user_login();

    }

    void user_login() {

        ifstream fin;
        bool is = true;
        bool ac;


       
        do {
            line();
            cout << "\n" << "Enter username : ";
            cin >> name;
            cout << "Enter password : ";
            (cin >> password).get();
            line();
            cout << "\n";
            if (!if_is_user(name, path)) {
                if (if_is_password(name, password, path)) {
                    cout << "Введiть правльний пароль!!!\n";
                }
                else {
                    is = false;
                }
            }
            else {
                cout << "Такого користувача не iснує!!!\nСтворити акаунт???\n";
                cout << "0 - НI\n";
                cout << "1 - ТАК\n";
                cout << "Зробiть свiй вибiр : ";
                cin >> ac;
                if (ac == true) {
                    register_user();
                }

            }

        } while (is);

        
         
    }

    
};


class questions {
    string question;
    vector <string> answers;
    int true_answer;
   
public:

    questions() {
        true_answer = 0;
    }

    questions(const string& question , const vector<string>& answers ,const int& true_answer ) {
        this->question = question;
        for (int i = 0; i < answers.size();i++) {
            this->answers.push_back(answers[i]);
        }
        this->true_answer = true_answer;
    }

    
    questions read_file_q(ifstream& fin) {

        char c;
        int size;
        string answer;

        while (fin.get(c)) {
            if (c == ':') {
                break;
            }
            question += c;
        }
        fin >> size;

        for (int i = 0; i < size; i++) {
            while (fin.get(c)) {
                if (c == ':') {
                    break;
                }
                answer += c;
            }
            answers.push_back(answer);
        }
        
        fin >> true_answer;

        questions q(question , answers , true_answer);
        return q;

    }


};


class test : public questions {
    string title;
    vector <questions> q;
public:

    test() {}

    test(const string& title , const vector <questions>& q) {

        this->title = title;
        for (int i = 0; i < q.size(); i++) {
            this->q.push_back(q[i]);
        }

    }

    test read_file_t(ifstream& fin) {
        
        char c;
        int size;

        while (fin.get(c)) {
            if (c == ':') {
                break;
            }
            title += c;
        }
        fin >> size;

        for (int i = 0; i < size; i++) {
            q.push_back(read_file_q(fin));
        }
        
        
        test t(title , q);
        
        return t;
    }

    

};


class section : public test {
    string title;
    vector <test> t;
public:

    section() {}

    section(const string& title , const vector<test>& t ) {
        this->title = title;
        for (int i = 0; i < t.size(); i++) {
            this->t.push_back(t[i]);
        }
    }

    section read_file_s(ifstream& fin) {
        
        char c;
        int size;

        while (fin.get(c) ) {
            if (c == ':') {
                break;
            }

            title += c;
        }
        fin >> size;
         
        for (int i = 0; i < size; i++) {
            t.push_back(read_file_t(fin));
        }

        section s(title , t);

        return s;

    }

    

};


class all_sections : public section {
    vector <section> sections ;
    string path;
public:

    all_sections(){
        path = "sections.txt";
    }

    void read_file_a() {

        ifstream fin;
       
        fin.open(path);

        if (!fin.is_open()) {
            cout << "error";
        }
        else {
            while (!fin.eof()) {
                sections.push_back(read_file_s(fin));
            }
           
        }
        fin.close();

    }

    
};




int main() {
    setlocale(LC_ALL, "UKR");

    
    all_sections A;

    A.read_file_a();

   
    

    return 0;
}