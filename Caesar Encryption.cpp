#include<iostream>
#include<string>
using namespace std;
int Decrypt() {
    int i, j, k;
    string s, t;
    int key;
    cout << "Enter the key:\n";
    cin >> key;
    cout << "Enter the message to decrypt:\n";
    cin >> s;
    for (i = 0; i < s.size(); i++) {
        t += (s[i] - 'a' - key + 26) % 26 + 'a';
    }
    cout << "\n\nDecrypted message is:\n" << t << '\n';
    return 0;
}
int Encrypt() {
    int i, j, k;
    string s, t;
    int key;
    cout << "Enter the key:\n";
    cin >> key;
    cout << "Enter the message:\n";
    cin >> s;
    for (i = 0; i < s.size(); i++) {
        t += (s[i] - 'a' + key) % 26 + 'a';
    }
    cout << "\n\nEncrypted message is:\n" << t << '\n';
    return 0;
}
int main()
{
    int choice;
    cout << "choice 1 = Encryption\n";
    cout << "choice 2 = Decryption\n";
    cout << "\nEnter your choice\n";
    cin >> choice;

    if (choice == 1)Encrypt();
    else if (choice = 2)Decrypt();
    else cout << "Invalid Choice\n";

    return 0;
}