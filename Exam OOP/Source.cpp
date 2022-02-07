#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <math.h> 
using namespace std;

void line() {
    for (int i = 0; i < 30; i++) {
        cout << "-";
    }
}

class system1 {

public:

    bool if_is_user(string& name, string& path) {
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

    bool if_is_password(string& name, string& password, string& path) {
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
                if (user_n == name && password_c == password) {
                    return false;
                }
            }
        }

        fin.close();
        return true;
    }
};

class user : public system1 {
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
            cout << "\nREGISTER USER";
            cout << "\n" << "Enter username : ";
            cin >> name;
            cout << "Enter password : ";
            (cin >> password).get();
            line();
            cout << "\n";
            system("cls");
            if (if_is_user(name, path)) {
                is = false;
            }
            else {
                cout << "����� ���������� ��� i���!!!\n����i�� i��� i��";
            }
            cout << "\n";
            line();
        } while(is);
        system("cls");

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
            cout << "\nLOGIN USER";
            cout << "\n" << "Enter username : ";
            cin >> name;
            cout << "Enter password : ";
            (cin >> password).get();
            system("cls");
            if (!if_is_user(name, path)) {
                if (if_is_password(name, password, path)) {
                    cout << "����i�� ���������� ������!!!\n";
                }
                else {
                    is = false;
                }
            }
            else {
                cout << "������ ����������� �� i���!!!\n�������� ������???\n";
                cout << "0 - �I\n";
                cout << "1 - ���\n";
                cout << "����i�� ��i� ���i� : ";
                cin >> ac;
                system("cls");
                if (ac == true) {
                    register_user();
                    is = false;
                }

            }

        } while (is);

        
         
    }

    string return_name() {
        return name;
    }
    
};

class user_m {
    user u;
    vector<int> mark_s;
    vector<string> test_name;
    string path;
public:
    user_m() {
        path = "marks.txt";
    }

    void reg_us() {
        u.register_user();
    }

    void login_us() {
        u.user_login();
    }

    void add_mark(int mark, string t_n) {

        print_mark_after_test(mark);

        mark_s.push_back(mark);
        test_name.push_back(t_n);

        write_mark();

    }

    void print_mark_after_test(int& mark) {

        int procent = 100 / 6;
        procent *= mark;

        line();

        cout << "\n������� ���������� �i����i��� : " << procent << "%\n";

        cout << "�i���i��� ���������� �i����i��� : " << mark << "\n";

        mark *= (12 / 6);

        cout << "���� : " << mark << "\n";

      
    }

    void write_user_name() {

        ofstream fout;

        fout.open(path, ofstream::app);

        if (!fout.is_open()) {
            cout << "error";
        }
        {
            fout << u.return_name();
        }
        fout.close();

    }

    void write_mark() {

        ofstream fout;

        fout.open(path, ofstream::app);

        if (!fout.is_open()) {
            cout << "error";
        }
        {

           
            for (int i = 0; i < test_name.size(); i++) {
                fout << " " << test_name[i] << ": " << mark_s[i] << "\n";
            }


        }
        fout.close();

    }

    void read_mark() {
        ifstream fin;

        fin.open(path);
        string word;
        char c;
        int num;

        if (!fin.is_open()) {
            cout << "error";
        }
        else {
            while (!fin.eof()) {
                fin >> word;
                if (word == u.return_name()) {
                    word.clear();
                    while (fin.get(c)) {
                        if (c == ':') {
                            break;
                        }
                        word += c;
                    }
                    test_name.push_back(word);
                    fin >> num;
                    mark_s.push_back(num);

                }
                else {
                    while (fin.get(c)) {
                        if (c == ':') {
                            break;
                        }
                        word += c;
                    }
                    fin >> num;
                }
                word.clear();

            }
        }

        print();
    }

    void print() {
        line();
        for (int i = 0; i < mark_s.size(); i++) {
            cout << "\n����� ����� :" << test_name[i] ;
            cout << "\n��� �� ���� : " << mark_s[i] << "\n";
        }
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

    questions(const string& question, const vector<string>& answers, const int& true_answer) {
        this->question = question;
        for (int i = 0; i < answers.size(); i++) {
            this->answers.push_back(answers[i]);
        }
        this->true_answer = true_answer;
    }


    questions read_file_q(ifstream& fin) {

        char c;
        int size;
        string answer;
        question.clear();
        answers.clear();
        true_answer = 0;

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
            answer.clear();
        }

        fin >> true_answer;

        questions q(question, answers, true_answer);
        return q;

    }

    void print_q() {

        cout << question << " :";
        for (int i = 0; i < answers.size(); i++) {
            cout << "\n" << answers[i] << " - " << i + 1;
        }

    }

    int choise_q() {
        int choise;
        cout << "\n����i�� ��i� ���i� : ";
        cin >> choise;
        system("cls");

        if (choise == true_answer) {
            return 1;
        }
        else {
            return 0;
        }
    }



};

class test : public questions , user_m {
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
        title.clear();
        q.clear();

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

    void print_t() {
        int mark = 0;
        for (int i = 0; i < q.size(); i++) {
            system("cls");
            line();
            cout << "\n" << i + 1 << ") ";
            q[i].print_q();
            mark += q[i].choise_q();
        }

        add_mark(mark , title);

    }
    
    void print_title(int i) {
        
        cout << title << " - " << i + 1;
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
        title.clear();
        t.clear();

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

    void print_s(int i ) {
        cout << title << " - " << i + 1;
    }

    void choice_s() {
        line();
        for (int i = 0; i < t.size(); i++) {
            t[i].print_title(i);
        }
        int i;
        cout << "\n����i�� ��i� ���i� : ";
        cin >> i;
        i--;
        system("cls");
        t[i].print_t();
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

    

    void print(){
        
        line();
        cout << "\n";
        for (int i = 0; i < sections.size(); i++) {
            sections[i].print_s(i);
        }
        choise();
        
    }

    void choise() {

        int i;
        cout << "\n����i�� ��i� ���i� : ";
        cin >> i;
        i--;
        system("cls");
        sections[i].choice_s();
      

    }
    
};

void reg_and_log(user_m& u_m) {
    int choise;
    
    while (true) {
        line();
        cout << "\n�������������� - 0\n";
        cout << "�����i������ - 1\n";
        cout << "����i�� ��i� ���i� : ";
        cin >> choise;

        if (choise < 0 || choise > 1) {
            cout << "\n�� ����� �� i������ �i����i��\n";
        }
        else {
            break;
        }
    }
    system("cls");
    if (choise == 0) {
        u_m.reg_us();
    }
    else {
        u_m.login_us();
    }

}

int menu1() {
    int menu;
    line();
    while (true) {
        cout << "\n1 - ���������� ���������� ���� ����i�\n";
        cout << "2 - ����� ����� ����\n";
        cout << "����i�� ��i� ���i� : ";
        cin >> menu;

        if (menu < 1 || menu > 2) {
            cout << "\n�� ����� �� i������ �i����i��\n";
        }
        else {
            break;
        }
        system("cls");
    }

    return menu;
}

void call_functions(all_sections& a_s , user_m& u_m) {

    int menu;

    reg_and_log(u_m);

    while (true) {

        menu = menu1();
        system("cls");
        switch (menu) {
        case 1:
            u_m.read_mark();
            break;
        case 2:
            u_m.write_user_name();
            a_s.read_file_a();
            a_s.print();
            break;
        }

    }

}

int main() {
    setlocale(LC_ALL, "UKR");

    int menu;
    all_sections a_s;
    user_m u_m;

    call_functions(a_s, u_m);
   
    return 0;
}