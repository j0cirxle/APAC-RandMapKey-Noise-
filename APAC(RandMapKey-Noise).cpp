#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAX 1001

int arr[MAX];
char trans[MAX];
int numbering = 0;
int random;
int noise;

char key_code[26] = {
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z',
    'x', 'c', 'v', 'b', 'n', 'm'
};

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void decomposition(int n){
    if(isPrime(n)){
        arr[numbering++] = n;
        return;
    }
    for(int i = 2; i <= n; i++){
        if(n % i == 0){
            arr[numbering++] = i;
            decomposition(n / i);
            break;
        }
    }
}

void encryption(int N){
    numbering = 0;
    memset(arr, 0, sizeof(arr));
    memset(trans, 0, sizeof(trans));
    decomposition(N);

    for(int i = 0; i < numbering; i++){
        if(arr[i] < 26)
            trans[i] = key_code[arr[i]];
        else
            trans[i] = '?';
    }

    for(int i = 0; i < numbering; ){
        char current = trans[i];
        int count = 1;
        while(i + count < numbering && trans[i + count] == current){
            count++;
        }

        if(current == '?'){
            cout << arr[i];
        } else {
            if(count > 1)
                cout << count << current;
            else
                cout << current;
        }
        i += count;
    }
    cout << " ";
}

int strToInt(const string& s) {
    int num = 0;
    for(size_t i=0; i<s.size(); i++){
        char c = s[i];
        if(c >= '0' && c <= '9'){
            num = num*10 + (c - '0');
        } else {
            return 0;
        }
    }
    return num;
}

int decryptBlock(const string& s, bool isEven) {
    int ascii = 1;
    size_t i = 0;

    while (i < s.size()) {
        string countStr = "";
        while (i < s.size() && isdigit(s[i])) {
            countStr += s[i++];
        }
        int count = (countStr.empty()) ? 1 : strToInt(countStr);

        if (i >= s.size()) {
            ascii *= count;
            break;
        }

        char ch = s[i++];

        int prime = -1;
        for (int idx = 0; idx < 26; idx++) {
            if (key_code[idx] == ch) {
                prime = idx;
                break;
            }
        }

        if (prime == -1) {
            continue;
        }

        for (int j = 0; j < count; j++) {
            ascii *= prime;
        }
    }

    if (isEven) {
        ascii = ascii - random - noise;
    } else {
        ascii = ascii - random;
    }
    return ascii;
}

void decryption(const string& input){
    string temp = "";
    int index = 0;
    for(size_t i=0; i<=input.size(); i++){
        if(i == input.size() || input[i] == ' '){
            if(!temp.empty()){
                int ascii = decryptBlock(temp, index % 2 == 1);
                cout << (char)ascii;
                temp = "";
                index++;
            }
        } else {
            temp += input[i];
        }
    }
    cout << "\n";
}

void decryptionWithRandom(const string& input){
    size_t pos = input.find(' ');
    if(pos == string::npos){
        cout << "Invalid format.\n";
        return;
    }

    string randomStr = input.substr(0, pos);
    random = strToInt(randomStr);

    noise = rand() % 10 + 1;

    string rest = input.substr(pos + 1);

    decryption(rest);
}

int main() {
    srand((unsigned int)time(NULL));

    int po;
    cout << "Choose option: 1 (encrypt) or 2 (decrypt): ";
    cin >> po;
    cin.ignore();

    cout << "Input text (for encrypt: raw text, for decrypt: encoded blocks separated by spaces):\n";
    string line;
    getline(cin, line);

    if(po == 1){
        random = rand() % 20 + 1;
        noise = rand() % 10 + 1;

        cout << random << " " << noise << " ";
        for(size_t i = 0; i < line.size(); i++){
            char c = line[i];
            int val = (int)c;
            if(i % 2 == 0){
                encryption(val + random);
            } else {
                encryption(val + random + noise);
            }
        }
        cout << "\n";
    } else if(po == 2){
        size_t firstSpace = line.find(' ');
        if(firstSpace == string::npos){
            cout << "Invalid input format for decrypt.\n";
            return 1;
        }
        size_t secondSpace = line.find(' ', firstSpace + 1);
        if(secondSpace == string::npos){
            cout << "Invalid input format for decrypt.\n";
            return 1;
        }

        string randomStr = line.substr(0, firstSpace);
        string noiseStr = line.substr(firstSpace + 1, secondSpace - firstSpace -1);
        random = strToInt(randomStr);
        noise = strToInt(noiseStr);

        string rest = line.substr(secondSpace + 1);
        decryption(rest);
    } else {
        cout << "Invalid option.\n";
    }

    system("pause");
    return 0;
}

