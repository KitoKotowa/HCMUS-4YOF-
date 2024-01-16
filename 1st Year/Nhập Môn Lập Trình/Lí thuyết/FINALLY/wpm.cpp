#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#define M 100

using namespace std;

struct Account
{
    string ID;
    float wpm[M] = { 0 };
    float ac[M] = { 0 };
};

struct HighScr
{
    string ID;
    float wpm = 0;
    float ac = 0;
};

//Các prototype của chương trình
void SET_COLOR(int color);
int Random(int MIN, int MAX);
void DisplayText(int cnt, string tok[], int soTu, int checkfail, float WPM);
void HighScore(Account history[M], HighScr high[M], int songuoichoi);
int UpdateHistory(int account);
void DisplayHistory(int stt);
void CheckAcc(int songuoichoi, string& file, string& line, string st, bool& yesno, int& stt);
void UpdateGiaoDien(int& choice, char& topic, Account acc[M], HighScr high[M], string& file, int& songuoichoi);
void XuLy(int& tumuondanh, string tok[], int& checkfail, int count, string& file, float WPM);

void SET_COLOR(int color) // Hàm đổi màu chữ một vùngS
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

int Random(int MIN, int MAX)
{
    return  MIN + rand() % (MAX + 1 - MIN);
}

void DisplayText(int cnt, string tok[], int soTu, int checkfail,  float WPM) {
    int min = cnt, max = cnt + 6;
    if (min < 0) min = 0;
    if (max > soTu) max = soTu;

    cout << "\n\n";
    cout << "\t\t";
    for (int i = min; i <= max; i++) {
        if (i == cnt) {
            SET_COLOR(12);
            cout << tok[i] << ' ';
            SET_COLOR(11);
        }
        else {
            cout << tok[i] << ' ';
        }
    }
    cout << "\n\n\t  (Timer will start when you type a character)";
    cout << "\n\t  WPM: " << WPM;
    cout << "\n\t  Progress : " << cnt << " / " << soTu;
    cout << "\n\t  Error(s) Made: " << checkfail;
    cout << "\n\t  Nhap: ";
    SET_COLOR(15);
}

void HighScore(Account history[M], HighScr high[M], int songuoichoi)
{
    HighScr temp;
    string s, x;
    for (int j = 0; j < songuoichoi; j++)
    {
        int count = 0;
        ifstream ifs;
        string fl = to_string(j + 1) + ".txt";
        ifs.open(fl);
        getline(ifs, history[j].ID, '\n');
        high[j].ID = history[j].ID;
        int n = 0;
        while (!ifs.eof())
        {
            getline(ifs, s, ' ');
            getline(ifs, x, '\n');
            history[j].wpm[n] = stof(s);
            history[j].ac[n] = stof(x);
            if (history[j].wpm[n] > high[j].wpm)
            {
                high[j].wpm = history[j].wpm[n];
                high[j].ac = history[j].ac[n];
            }
            n++;
        }
        ifs.close();
    }
    for (int k = 0; k < songuoichoi - 1; k++)
    {
        for (int z = k + 1; z < songuoichoi; ++z)
        {
            if (high[z].wpm > high[k].wpm)
            {
                temp = high[k];
                high[k] = high[z];
                high[z] = temp;
            }
        }
    }
    cout << "\t\t\t\t\t" << setw(10) << "ID" << setw(10) << "WPM" << setw(11) << "AC" << endl;
    for (int x = 0; x <= 2; x++)
    {
        cout << "\t\t\t\t\t" << setw(10) << high[x].ID << setw(10) << high[x].wpm << setw(10) << high[x].ac << "%" << endl;
    }
}

int UpdateHistory(int account)
{
    int x;
    fstream fs;
    fs.open("Songuoichoi.txt", ios::in);
    fs >> x;
    fs.close();
    if (account == 2)
    {
        ++x;
        fs.open("Songuoichoi.txt", ios::out | ios::trunc);
        fs << x;
        fs.close();
    }
    return x;
}

void DisplayHistory(int stt)
{
    system("cls");
    SET_COLOR(13);
    cout << "\n\n\n";
    cout << "\t\t\t\t # #  #   ###  ###   ##   ###  #  # \n";
    cout << "\t\t\t\t ###  #   #     #   #  #  ##    ##  \n";
    cout << "\t\t\t\t # #  # ###     #    ##   # #   ##  \n\n\n";
    string s = to_string(stt) + ".txt";
    string line, data;
    ifstream ifs;
    ifs.open(s);
    int count = 1;
    getline(ifs, line, '\n');
    cout << "\t\t\t\t" << setw(10) << "STT" << setw(10) << "WPM" << setw(10) << "AC" << endl;
    while (!ifs.eof())
    {
        getline(ifs, line, ' ');
        getline(ifs, data, '\n');
        cout << "\t\t\t\t" << setw(10) << count << setw(10) << line << setw(10) << data << endl;
        count++;
    }
    ifs.close();

}

void CheckAcc(int songuoichoi, string& file, string& line, string st, bool& yesno, int& stt)
{
    for (int i = 1; i <= songuoichoi; i++)
    {
        ifstream ifs;
        file = to_string(i) + ".txt";
        ifs.open(file);
        getline(ifs, line, '\n');
        ifs.close();
        if (line == st)
        {
            yesno = true;
            stt = i;
            break;
        }
    }
}

void UpdateGiaoDien(int& choice, char& topic, Account acc[M], HighScr high[M], string& file, int& songuoichoi)
{
    int n, stt = -1;
    string line;
    string st;
    bool yesno = false;
    char s;
    SET_COLOR(12);
    cout << endl << endl << endl;
    cout << "\t\t #######  #    #  ####    ##   #   #   ####    #######  ######    ####  #######  \n";
    cout << "\t\t    #      #  #   #   #   ##   ##  #  #           #     #        ##        #     \n";
    cout << "\t\t    #       ##    ####    ##   # # #  #   ###     #     ######    ##       #     \n";
    cout << "\t\t    #       ##    #       ##   #  ##  #    #      #     #          ##      #     \n";
    cout << "\t\t    #       ##    #       ##   #   #   ####       #     ######  ####       #     \n\n\n";
    SET_COLOR(14);
    cout << "\t\t\t\t\t\t --- HIGH SCORE ---\n";
    SET_COLOR(13);
    songuoichoi = UpdateHistory(1);
    HighScore(acc, high, songuoichoi);
    SET_COLOR(10);
    cout << endl << "\t\t\t\t\t\t Did you have an account? \n";
    cout << "\t\t\t\t\t\t 1.Yes \n";
    cout << "\t\t\t\t\t\t 2.No \n\n";
    do
    {
        cout << "\t\t Press 1 if you already had an account, press 2 if you don't have one : ";
        cin >> n;
    } while (n < 1 || n>2);
    if (n == 1)
    {
        cout << endl;
        cout << "\t\t\t\t\t\t Enter the ID : ";
        cin >> st;
        CheckAcc(songuoichoi, file, line, st, yesno, stt);
        while (yesno == false)
        {
            cout << "\t\t\t\t\t\t ID is invalid, please re-enter : ";
            cin >> st;
            CheckAcc(songuoichoi, file, line, st, yesno, stt);
        }
    }
    else
    {
        bool checkspace = false;
        cout << endl;
        cout << "\t\t\t\t\t\t -------- Create an account ------- \n";
        cout << "\t\t\t\t\t\t Enter the ID : ";
        cin.ignore();
        getline(cin, st, '\n');
        CheckAcc(songuoichoi, file, line, st, yesno, stt);
        do
        {
            checkspace = false;
            yesno = false;
            char pch[100];
            strcpy_s(pch, st.c_str());
            size_t name = strlen(pch);
            for (int i = 0; i < name; i++)
            {
                if (pch[i] == ' ' || pch[i] == '\t')
                {
                    checkspace = true;
                    break;
                }
            }
            if (checkspace)
            {
                cout << "\t\t\t The name is not valid, please re-type : ";
                getline(cin, st);
                CheckAcc(songuoichoi, file, line, st, yesno, stt);
            }

            CheckAcc(songuoichoi, file, line, st, yesno, stt);
            if (yesno == true)
            {
                cout << "\t\t This account has already existed, please enter another account : ";
                getline(cin, st);
            }
        } while (checkspace == true || yesno == true);
        songuoichoi = UpdateHistory(2);
        stt = songuoichoi;
        file = to_string(stt) + ".txt";
        ofstream ofs;
        ofs.open(file, ios::out | ios::app);
        ofs << st;
        ofs.close();
    }
    do
    {
        s = 'N';
        cout << endl;
        cout << "\t\t\t\t\t\t 1.RANDOM TEXT \n";
        cout << "\t\t\t\t\t\t 2.TEXT BY TOPIC \n";
        cout << "\t\t\t\t\t\t 3.HISTORY \n\n";
        do
        {
            cout << "\t\t Choose 1 if you want Random text, choose 2 if you want choose the topic :  ";
            cin >> choice;
        } while (choice < 1 || choice>3);
        bool back = true;
        if (choice == 1)
        {
            srand((int)time(0));
            topic = Random(1, 7) + '0';
        }
        else if (choice == 2)
        {
            cout << endl;
            string st;
            ifstream ifs;
            ifs.open("Topic.txt");
            while (!ifs.eof())
            {
                getline(ifs, st);
                cout << "\t\t\t\t\t" << st << "\n";
            }
            ifs.close();
            cout << endl;
            do
            {
                cout << "\t\t Enter the serial number (1->7) of the topic you want to choose : ";
                cin >> choice;
            } while (choice < 1 || choice>7);
            topic = choice + '0';
        }
        else
        {
            DisplayHistory(stt);
            do
            {
                cout << "\n\n\n\n\n\n\n\n\t Do you want return? (Y/N) : ";
                cin >> s;
            } while (s != 'Y' && s != 'N' && s != 'y' && s != 'n');
            if (s == 'N' || s == 'n')exit(0);
            system("cls");
        }
    } while (s == 'y' || s == 'Y');
}

void XuLy(int& tumuondanh, string tok[], int& checkfail, int count, string& file, float WPM) {
    char ch;
    int cnt = 0;
    system("cls");
    string s;
    clock_t Time = 0;
    DisplayText(cnt, tok, tumuondanh, 0, WPM);
    clock_t start = clock();
    while (cnt < tumuondanh || s != tok[cnt]) { 
        ch = _getch();
        
            Time = clock();
      
        switch (ch) {
        case '\b':
            if (s.size() > 0) {
                cout << "\b \b";
                s.erase(s.size() - 1, 1);
            }
            break;
        case ' ':
            cout << ' ';
            if (s == "") { cout << "\b \b"; break; } //Turn off = Test mode (enable spacebar)
            if (s != tok[cnt])checkfail++;
            cnt++;
            s = "";
            system("cls");
            DisplayText(cnt, tok, tumuondanh, checkfail, WPM);
            break;
        case '\r': case '\n': case '\t':
            break;
        default:
            s = s + ch;
            cout << ch;
            break;
        } 
        WPM = float(cnt / (((float)(clock() - start) / CLOCKS_PER_SEC) / 60));
    }
    Time = clock() - Time;
    float a = ((float)Time / CLOCKS_PER_SEC) / 60;
    SET_COLOR(11);
    system("cls");
    int l = tumuondanh - checkfail;
    double ac = double(l) * 100 / double(tumuondanh);
    double wpm = double(l) / a;
    cout << "\n\n\t\t\t---SUCCESS---\n";
    cout << "\t\tTime Finished: " << setprecision(4) << a << " minute" << "(" << "s" << ")." << '\n';
    cout << "\t\tYour Words-per-Minute (WPM) Score: " << setprecision(4) << wpm << '\n';
    cout << "\t\tErrors Made: " << checkfail << " - Total Words: " << tumuondanh << "\n\n";
    ofstream ofs;
    ofs.open(file, ios::out | ios::app);
    ofs << "\n" << wpm << " " << ac;
    ofs.close();
}

int main() {
    Account acc[M] = {};
    HighScr high[M] = {};
    string tok[300], file;
    int count = 0, checkfail = 0, choice = 0, tumuondanh = 0, songuoichoi = 0;
    float WPM = 0;
    string input = "Text.txt";
    char topic;
    UpdateGiaoDien(choice, topic, acc, high, file, songuoichoi);
    input.insert(input.begin() + 4, topic);
    ifstream ifs;
    // Custom Test
    //input = "CustomTest.txt"; 
    ifs.open(input);
    while (!ifs.eof())
    {
        ifs >> tok[count];
        count++;
    }
    ifs.close();
    cout << "\t\t The total number of words in this passage is : " << count << endl;
    cout << "\t\t Enter the number of words you want to type (40-> " << count << ") : ";
    cin >> tumuondanh;
    while (tumuondanh<40 || tumuondanh>count)
    {
        cout << "\t\t The number of words is not valid, please re-enter : ";
        cin >> tumuondanh;
    }
    SET_COLOR(11);
    XuLy(tumuondanh, tok, checkfail, count, file, WPM);
    return 0;
}