#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
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
            char temp [4];
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
                cout << "Cash withdrawal:";
                for (int j = 0; j <output_banknotes.size();j++){
                    cout << output_banknotes [j] << endl;
                    //удаление из файла
                    delete_banknotes (output_banknotes[j]);
                }
                break;}
        }
        if (removable_banknotes > 0) {cout << "operation is not possible"; cout << removable_banknotes;}
        file.close ();
    }
}
void delete_banknotes (int banknote){
    ifstream inFile("bank.bin",ios::binary);
    ofstream outFile ("bank.bin",ios::binary);
    vector <int> bank;
    while(!inFile.eof()){
        char temp [4];
        inFile.read(temp,sizeof(temp));
        try {
            bank.push_back (stoi(temp));
        }catch (const exception &obj) {
            cerr << obj.what ();
        }
    }
    for(int i = 0; i < bank.size(); i++){
        if (bank [i] == banknote) {
            bank [i] = bank.back ();
            bank.pop_back();
            break;}
    }
    for(int i = 0; i < bank.size(); i++){
        outFile.write ((char*)bank[i],sizeof(bank[i]));
    }
    inFile.close();
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
        for (int i = 1; i < iteration; i++) {
            int temp = rand() % 5;
            switch (temp) {
                case 0 :
                {file << "100" << endl;break;}
                case 1 :
                {file << "200" << endl;break;}
                case 2 :
                {file << "500" << endl;break;}
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