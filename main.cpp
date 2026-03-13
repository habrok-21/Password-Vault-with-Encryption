#include <iostream>  // For input output
#include <fstream>  // For file handling
#include <string>  // To use string type
using namespace std;


// ---------------- VAULT Password ----------------
const string VAULT_PASSWORD = "Habrok123"; // pass to protect the vault. Only someone with this can view decrypted passwords.


// ---------------- Encryption Functions ----------------

// XOR Cipher ~ XOR operator. By applying it twice will give back the original string
string xorCipher(string input, char key = 'K')  // Default key is 'K' but can be changed
{
    string output = input;
    for (int i = 0; i < input.size(); i++)
        output[i] = input[i] ^ key;
    return output;
}

// Caesar Cipher ~ Classic shift cipher. shift → Number of letters
string caesarCipher(string input, int shift, bool encrypt = true)
{
    string output = input;
    for (int i = 0; i < input.size(); i++)
    {
        char c = input[i];
        if (isalpha(c))  // ensures only letters are shifted; digits n symbols stay the same
        {
            char base = isupper(c) ? 'A' : 'a';
            if (encrypt)
                output[i] = (c - base + shift) % 26 + base; // This formulae convert letter into number, add shift value, %26 for loop & base convert back to letter
            else
                output[i] = (c - base - shift + 26) % 26 + base; // Decryption logic
        }
    }
    return output;
}

// Atbash Cipher ~ alphabet is reversed to encrypt message like A→Z, B→Y
string atbashCipher(string input)
{
    string output = input;
    for (int i = 0; i < input.size(); i++)
    {
        char c = input[i];
        if (isupper(c))
            output[i] = 'Z' - (c - 'A');  // c-A calculates distance of charactor from A. Z-distance find distance from alfabet
        else if (islower(c))
            output[i] = 'z' - (c - 'a');
    }
    return output;
}

// ROT13 Cipher ~ Caesar cipher with shift 13
string rot13Cipher(string input)
{
    return caesarCipher(input, 13);
}


// ---------------- Vault Functions ----------------

void addPassword()
{
    string website, password;
    int choice;

    cout << "\nEnter website : ";
    cin >> website;
    cout << "Enter password : ";
    cin >> password;

    cout << "Choose the encryption type :\n";
    cout << "1. XOR Cipher\n2. Caesar Cipher\n3. Atbash Cipher\n4. ROT13 Cipher\nEnter choice: ";
    cin >> choice;

    string encryptedPassword;

    switch(choice)
    {
        case 1:
            encryptedPassword = xorCipher(password);
            encryptedPassword = "X|" + encryptedPassword;
            break;
        case 2:
        {
            int shift;
            cout << "Enter shift value for Caesar Cipher: ";
            cin >> shift;
            encryptedPassword = caesarCipher(password, shift);
            encryptedPassword = "C|" + to_string(shift) + "|" + encryptedPassword;
            break;
        }
        case 3:
            encryptedPassword = atbashCipher(password);
            encryptedPassword = "A|" + encryptedPassword;
            break;
        case 4:
            encryptedPassword = rot13Cipher(password);
            encryptedPassword = "R|" + encryptedPassword;
            break;
        default:
            cout << "Invalid choice ! Password not saved.\n";
            return;
    }

    ofstream file("vault.txt", ios::app);  // ios::app is append mode. ofstream means write data
    file << website << " " << encryptedPassword << endl;
    file.close();

    cout << "Your Password saved securely !\n";
}

void viewPasswords()
{
    ifstream file("vault.txt");  // Open file and read data
    if (!file)
    {
        cout << "No passwords saved yet.\n";
        return;
    }

    string website, storedData;

    // Step 1 : Show ciphertext only
    cout << "\nSaved Passwords (ciphertext only) :\n";
    while(file >> website >> storedData) // loop continues till data is there / reads file word by word n assign first word to website and second to stored data
    {
        cout << website << ": " << storedData << endl;
    }
    file.close();

    // Step 2: Ask for master password to show real passwords
    string inputPassv;
    cout << "\nEnter master password to view decrypted passwords : ";
    cin >> inputPassv;

    if(inputPassv != VAULT_PASSWORD)
    {
        cout << "Incorrect password ! Access denied.\n";
        return;
    }

    // Reopen file for decryption
    ifstream file2("vault.txt");
    cout << "\nSaved Passwords (decrypted) :\n";
    while(file2 >> website >> storedData)
    {
        string decryptedPassword, cipherType;

        if(storedData[0] == 'X')
        {
            decryptedPassword = xorCipher(storedData.substr(2)); // .substr(2) skips the flag (X)
            cipherType = "XOR Cipher";
        }
        else if(storedData[0] == 'C')
        {
            size_t first = storedData.find('|');
            size_t second = storedData.find('|', first + 1);
            int shift = stoi(storedData.substr(first + 1, second - first - 1));
            string encryptedPass = storedData.substr(second + 1);
            decryptedPassword = caesarCipher(encryptedPass, shift, false);
            cipherType = "Caesar Cipher (shift " + to_string(shift) + ")";
        }
        else if(storedData[0] == 'A')
        {
            decryptedPassword = atbashCipher(storedData.substr(2));
            cipherType = "Atbash Cipher";
        }
        else if(storedData[0] == 'R')
        {
            decryptedPassword = rot13Cipher(storedData.substr(2));
            cipherType = "ROT13 Cipher";
        }

        cout << website << ": " << decryptedPassword << " (" << cipherType << ")" << endl;
    }

    file2.close();
}


// ---------------- Main Menu ----------------

int main()
{
    int choice;

    do
    {
        cout << "\n--- Password Vault ---\n";
        cout << "1. Add Password\n";
        cout << "2. View Passwords\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: addPassword(); break;
            case 2: viewPasswords(); break;
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 3);

    return 0;
}