# Password-Vault-with-Encryption
A secure C++ Password Vault project that allows users to store passwords encrypted using multiple cipher methods. Includes Vault password protection and two-step password viewing.


Features :

~ Four Encryption Options :
1) XOR Cipher
2) Caesar Cipher (with user-defined shift)
3) Atbash Cipher
4) ROT13 Cipher

~ Master Password Protection: Only authorized users can view decrypted passwords.

~ Two-Step Viewing :
1) First shows ciphertext (encrypted passwords).
2) After entering master password, shows decrypted passwords with cipher type.

~ Menu-driven Interface : Add passwords, view passwords, or exit.

~ File Storage : Passwords are stored securely in a local file (vault.txt).


Installation / Running
1) Clone the repository :
git clone https://github.com/<username>/PasswordVault.git

2) Open the folder in VS Code or any C++ IDE.

3) Compile the code using g++ : g++ main.cpp -o vault.exe

4) Run the program : ./vault.exe


Usage :
~ Add Password : Input website, password, and choose encryption type.


Technologies Used :
1) Language: C++
2) File Handling: To save and retrieve passwords securely
3) Encryption: XOR, Caesar, Atbash, ROT13
