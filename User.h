#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Result.h"

using namespace std;

class User {
	string userID;
	string login;
	string pass;
	string last_name;
	string first_name;
	string middle_name;
	string phone;
	string address;
	string Crypt(const string s);
	vector<Result*> results;
public:

	User();
	~User();

	void SetUserID(const string s);
	void SetLogin(const string s);
	void SetPassword(const string s);
	void SetLastName(const string s);
	void SetFirstName(const string s);
	void SetMiddleName(const string s);
	void SetPhone(const string s);
	void SetAddress(const string s);
	
	string GetUserID()const;
	string GetLastName()const;
	string GetFirstName()const;
	string GetMiddleName()const;
	string GetPhone()const;
	string GetAddress()const;
	
	vector<Result*> GetResults()const;

	bool CheckLogin(const string s);
	bool CheckPassword(const string s);

	void AddResult(Result* res);

	void SaveUserToFile(const string path) const;
	void SaveUserToFstream(ofstream& fout) const;

	void ReadUserFromFile(string path);
	void ReadUserFromFstream(ifstream& fin);

	void ShowInfo() const;
	void ShowStatistic();
	void ShowUndoneTests();

	void SortResults();
};

#endif // !USER_H
