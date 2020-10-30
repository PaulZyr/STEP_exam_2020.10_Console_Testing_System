#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Administrator
{
private:
	string login;
	string password;
	const string filepath = "admin.z";
	string databasepath;
	string menu_code;
	// Check
	bool status;
	// Singleton
	static Administrator* _instance;
	void SetLogin(string s);
	void SetPassword(string s);
	void SaveFile()const;
	string Crypt(const string s);
protected:
	Administrator();
public:
	void ReadFile();
	static Administrator* Instance();

	void SetDatabasePath(string s);
	void SetMenuCode(string s);

	string GetDatabasePath()const;
	string GetMenuCode()const;

	void FirstRunAdmin
	(const string log, const string pass, const string code);
	
	void ChangeLogin(const string log);
	void ChangePassword(const string pass);
	void ChangeDatabasePath(const string path);
	void ChangeMenuCode(const string code);

	bool CheckFile()const;
	void Login(const string log, const string pass);
	void Logout();
	bool CheckStatus()const;
	bool CheckMenuCode(string code);

	// For Testing
	void Show()const;
};

#endif // !ADMINISTRATOR_H



