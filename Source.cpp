#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void FirstTimeRunMenu(Administrator* admin)
{
	system("CLS");
	string log, pass;
	string code;
	cout << "*** HELLO! ***" << endl
		<< "The Testing System, v.1.0" << endl
		<< "First Time Run:" << endl
		<< "Creating Administrator Account..." << endl
		<< "Input admin Login: ";
	getline(cin, log);
	cout << "Input admin Password: ";
	getline(cin, pass);
	cout << "Input admin menu_code: ";
	getline(cin, code);
	admin->FirstRunAdmin(log, pass, code);
	cout << "Keep your login, password and menu_code in safe place!" << endl;
	system("pause");
}

void Welcome() {
	cout << "   ************************" << endl
		<< "   *       WELCOME!       *" << endl
		<< "   *  TESTING SYSTEM v.1  *" << endl
		<< "   *  ------------------  *" << endl
		<< "   *      GOOD LUCK!      *" << endl
		<< "   ************************" << endl;
}

void StartMenu(Administrator* admin, Database* base) {
	// 1 - Student; 2 - Administrator; 0 - Exit Program;
	admin->ReadFile();
	base->SetPath(admin->GetDatabasePath());
	if (!base->CheckDatabaseFile()) base->SaveDatabase();
	else base->ReadDatabase();
	// test ------------------
	/*cout << "------ test ---------\n";
	base->ShowUsers();
	cout << "------ test end ---------\n";*/
	// end test ------------
	system("CLS");
	Welcome();
	string code, str;
	int q = -1;
	while (q != 0) {
		// Hidden variant <12345> to enter Admin Mode
		// Then admin needs to enter menu_code
		cout << "1 - Log in\n"
			<< "2 - Create New User Account\n"
			<< "0 - Exit.\n"
			<< "$: ";
		getline(cin, str);
		q = IntFromString(str);
		//cin >> q; cin.ignore();
		switch (q)
		{
		case 1: UserLogin(base); break;
		case 2: NewUser(base); break;
		case 0: break;
		case 12345:
			cout << "code: ";
			getline(cin, code);
			if (admin->CheckMenuCode(code))
				AdminMode(admin, base);
			else cout << "Wrong code!\n";
			break;
		default: cout << "Wrong input! Try better!\n";
		}
	}
}

void NewUser(Database* base)
{
	cout << "--------------------\n"
		<< "CREATING NEW USER...\n";
	bool b = false;
	string s;
	while (!b)
	{
		cout << "Input login: ";
		getline(cin, s);
		if (base->CheckUserLogin(s)) cout << "This login in use!\n";
		else b = true;
	}
	User* tmp = new User;
	tmp->SetLogin(s);
	tmp->SetUserID(s);
	cout << "Input password: ";
	getline(cin, s);
	tmp->SetPassword(s);
	cout << "Last Name: ";
	getline(cin, s);
	tmp->SetLastName(s);
	cout << "First Name: ";
	getline(cin, s);
	tmp->SetFirstName(s);
	cout << "Middle Name: ";
	getline(cin, s);
	tmp->SetMiddleName(s);
	cout << "Phone: ";
	getline(cin, s);
	tmp->SetPhone(s);
	cout << "Address: ";
	getline(cin, s);
	tmp->SetAddress(s);
	base->AddUser(tmp);
	tmp = NULL;
	base->SaveDatabase();
}

bool CheckFile(string path)
{
	bool b = false;
	ifstream file;
	file.open(path, ios_base::in);
	if (file.is_open()) b = true;
	file.close();
	return b;
}

int IntFromString(string str)
{
	if (str.size() == 0) return -1;
	else
	{
		int size = str.size() - 1, K = 1, x=0;
		for (auto c : str)
		{
			if (c < 48 || c > 57) return -1;
			for (int j = 0; j < size; ++j) K *= 10;
			x += (c - 48) * K;
			size--;
			K = 1;
		}
		return x;
	}

}