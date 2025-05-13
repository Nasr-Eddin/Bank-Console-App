# Bank Console App 🏦

A C++ console application simulating a banking system with user authentication, client management, transactions, and currency exchange. The project uses a modular design with custom header files and file-based storage for persistence.

## 🚀 Features

- **User Authentication**: Secure login system with role-based access (Admin vs. regular users).
- **Client Management**:
  - Add, delete, update, and find client accounts.
  - Display a list of all clients.
- **Transactions**:
  - Deposit and withdraw funds.
  - Check total balances across all accounts.
  - Transfer money between accounts with a transaction log.
- **Currency Exchange**:
  - List available currencies and their exchange rates.
  - Update currency rates (Admin only).
  - Convert amounts between currencies using a calculator.
- **Logging**:
  - Track login activity (`LoginRegister.txt`).
  - Maintain a transfer log (`TransferRegister.txt`).
- **Modular Design**: Organized code using custom header files for each screen and functionality.
- **File-Based Storage**: Persist data using `.txt` files as a local database.

## 🛠️ How to Run

1. **Clone or Download**:
   - Clone this repository or download the ZIP file and extract it.
   - Ensure all files are in the same folder.

2. **Compile the Project**:
   - Open a terminal in the project folder.
   - Run the following command to compile:
   ```g++ main.cpp```

text

Copy

3. **Run the Executable**:
- After compilation, run the program with:
```./a.out```


## 📁 Project Structure

### Source Files
- `main.cpp`: Entry point of the application.
- **Header Files**:
- `clsBankClient.h`, `clsUser.h`, `clsCurrency.h`: Core data structures for clients, users, and currencies.
- `clsLoginScreen.h`, `clsMainScreen.h`, `clsTransactionsScreen.h`, etc.: Screen modules for each menu.
- `clsInputValidate.h`, `clsUtil.h`, `clsString.h`: Utility functions for input validation and string manipulation.
- `Global.h`: Global variables and constants.
- `InterfaceComunication.h`: Interface definitions for communication between modules.

### Data Files
These files act as the application's local database:
- `Clients.txt`: Stores client data (e.g., account number, balance).
- `Users.txt`: Stores user data (e.g., username, password, role).
- `Currencies.txt`: Stores currency codes and exchange rates.
- `TransferRegister.txt`: Logs all transfer transactions.
- `LoginRegister.txt`: Logs login activity.

### Other Files
- `.gitignore`: Ignores unnecessary files (e.g., compiled binaries).
- `LICENSE`: Project license (update with your preferred license).

## 📌 Notes

- This project was developed for educational purposes to demonstrate file handling, modular programming, and system simulation in C++.
- **Future Improvements**:
- Add a graphical user interface (GUI).
- Replace file-based storage with a proper database.
- Enhance security for user passwords.
- Contributions and suggestions are welcome!

## 💡 Author

**Nasr** – Aspiring top computer engineer. Building projects now to let results speak later. ⚔️🧱  
Connect with me on GitHub to see more of my work!
