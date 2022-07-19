#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstring>

using namespace std;
void fill_the_ATM ();
void delete_banknotes (int banknote);
int main() {

    cout << "Welcome to the ATM\n";
    char start_symbol;
    cout << ": ";
    cin >> start_symbol;

    if (start_symbol == '+'){
        fill_the_ATM ();
    } else if (start_symbol == '-') {

        ifstream file ("bank.bin",ios::binary);
        cout << "Enter the amount to withdraw in multiples of 100: ";
        int removable_banknotes;
        cin >> removable_banknotes;

        while (removable_banknotes%100 != 0) {
            cout << "Error. The amount of withdrawn banknotes must be a multiple of 100!\nEnter again";
            cin >> removable_banknotes;
        }

        vector <int> output_banknotes;

        for (int i = 0; !file.eof(); i++){ // проверка и вывод средств из банкомата
            char temp [5];
            file.read(temp,sizeof(temp));
            try {
                if (removable_banknotes - stoi(temp) > 0 || removable_banknotes - stoi(temp) == 0 ) {
                    removable_banknotes -= stoi(temp);
                    output_banknotes.push_back (stoi(temp));
                }
            }
            catch (const exception &obj) {
                cerr << obj.what ();
            }
            if (removable_banknotes == 0) { // вывод средств

                for (int j = 0; j < output_banknotes.size();j++){
                    cout << "Cash withdrawal:" << output_banknotes [j] << endl;
                    //удаление из файла
                    int tmp = output_banknotes[j];
                    delete_banknotes (tmp);
                }
                break;}
        }
        if (removable_banknotes > 0) {cout << "operation is not possible"; cout << removable_banknotes;}
        file.close ();
    }
}

void delete_banknotes (int banknote){
    ifstream inFile("bank.bin",ios::binary);
    while (!inFile.is_open()){cout << "Error";}

    vector <int> bank;
    while(!inFile.eof()){
        char temp [5];
        inFile.read(temp,sizeof(temp));
        try {
             bank.push_back (stoi(temp));
        }catch (const exception &obj) {
            cerr << obj.what ();
        }
    }
    inFile.close();

    for(int i = 0; i < bank.size(); i++){
        //cout << "bank i = " << bank [i] <<endl;
        if (bank [i] == banknote) {
           if (bank.back () > 0) {bank [i] = bank.back (); bank.pop_back();}
           else if (bank.back () -1 > 0){bank [i] = bank.back () - 1; bank.pop_back();}
           else {bank [i] = bank.back () - 2; bank.pop_back();}
            bank.resize(bank.size ()-1);
            break;}
    }

      ofstream outFile ("bank.bin",ios::binary);
    for(int i = 0; i < bank.size(); i++){
        int temp = bank [i];

        if ( temp < 1000 ) {outFile << temp << " " << endl;}
        else {outFile << temp <<endl;}
    }

    outFile.close();
}

void fill_the_ATM () {

    srand(time(nullptr));

    fstream fFile("bank.bin",  ios::binary|ios::in);
    ofstream file ("bank.bin",  ios::binary|ios::app);
    if (!fFile.is_open()) { cout << "Error opening file;"; }

        int number_of_banknotes = 0;
        int x;
        while (fFile >> x) { number_of_banknotes++; }
            fFile.close ();
            cout <<number_of_banknotes;
            int iteration = 1000 - number_of_banknotes;
        for (int i = 0; i < iteration; i++) {
            int temp = rand() % 5;
            switch (temp) {
                case 0 :
                {file << "100 " << endl;break;}
                case 1 :
                {file << "200 " << endl;break;}
                case 2 :
                {file << "500 " << endl;break;}
                case 3 :
                {file << "1000" << endl;break;}
                case 4 :
                {file << "2000" << endl;break;}
                case 5 :
                {file << "5000" << endl;break;}
                default :break;
            }
        }
    file.close();
}
//100 200 500 1000 2000 5000