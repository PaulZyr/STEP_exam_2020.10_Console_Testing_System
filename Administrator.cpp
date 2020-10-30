#include "Administrator.h"

Administrator::Administrator() :login("none"), 
	password("none"), status(false), databasepath("database.db"), 
	menu_code("none") { }

Administrator* Administrator::_instance = 0;

Administrator* Administrator::Instance() 
{
	if (_instance == 0) _instance = new Administrator;
	return _instance;
}

void Administrator::FirstRunAdmin
(const string log, const string pass, const string code)
{
	login = Crypt(log);
	password = Crypt(pass);
	menu_code = code;
	status = true;
	SaveFile();
	status = false;
}

void Administrator::SetLogin(const string s) { login = s; }
void Administrator::SetPassword(const string s) { password = s; }
void Administrator::SetDatabasePath(const string s) { databasepath = s; }
void Administrator::SetMenuCode(const string s) { menu_code = s; }

string Administrator::GetDatabasePath() const { return databasepath; }
string Administrator::GetMenuCode() const { return menu_code; }

bool Administrator::CheckFile() const
{
	bool b = false;
	ifstream file;
	file.open(filepath, ios_base::in);
	if (file.is_open()) b = true;
	file.close();
	return b;
}
bool Administrator::CheckStatus()const
{
	if (status) return true;
	else return false;
}
bool Administrator::CheckMenuCode(const string code)
{
	if (menu_code == code) return true;
	else return false;
}

void Administrator::ChangeLogin(const string log)
{
	if (status) {
		SetLogin(Crypt(log));
		SaveFile();
	}
	else cout << "Log in first!\n";
}
void Administrator::ChangePassword(const string pass)
{
	if (status) {
		SetPassword(Crypt(pass));
		SaveFile();
	}
	else cout << "Log in first!\n";
}
void Administrator::ChangeDatabasePath(const string path)
{
	if (status) {
		SetDatabasePath(path);
		SaveFile();
	}
	else cout << "Log in first!\n";
}
void Administrator::ChangeMenuCode(const string code)
{
	if (status) {
		SetMenuCode(code);
		SaveFile();
	}
	else cout << "Log in first!\n";
}

void Administrator::Login(const string log, const string pass)
{
	if (Crypt(log) == login && Crypt(pass) == password) {
		status = true;
		cout << "Hello, you are IN!" << endl;
	}
	else cout << "Incorrect Login or Password!" << endl;
}
void Administrator::Logout() 
{
	cout << "You are OUT!" << endl;
	status = false;
}

void Administrator::SaveFile()const
{
	if (status)
	{
		ofstream file;
		file.open(filepath, ios_base::out);
		file << login << "\n" << password << "\n"
			<< databasepath << "\n" << menu_code;
		file.close();
	}
	else cout << "Log in first!\n";
}

void Administrator::ReadFile()
{
	ifstream file;
	file.open(filepath, ios_base::in);
	if (file.is_open()) {
		string s;
		getline(file, s);
		SetLogin(s);
		getline(file, s);
		SetPassword(s);
		getline(file, s);
		SetDatabasePath(s);
		getline(file, s);
		SetMenuCode(s);
	}
	file.close();
}

string Administrator::Crypt(const string s)
{
	string tmp;
	char c;
	for (auto it : s) {
		c = it ^ 7;
		tmp += c;
	}
	return tmp;
}

void Administrator::Show() const
{
	if (status) cout << "You are logged in!\n";
	else cout << "You are NOT logged in!\n";
}