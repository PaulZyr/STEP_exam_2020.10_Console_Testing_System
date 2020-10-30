#ifndef DATABASE_H
#define DATABASE_H

#include <set>
#include "Test.h"
#include "Administrator.h"
#include "User.h"

using namespace std;

class Database
{
	string path;
	vector<User*> users;
	vector<Test*> tests;
	vector<string> categories;
public:
	Database();
	~Database();

	void SetPath(const string s);

	vector<User*> GetUsers() const;
	vector<Test*> GetTests() const;

	bool CheckDatabaseFile() const;

	bool CheckCategories(const string str) const;
	void AddCategory(const string str);
	void ChangeCategory(const string old_ctg, const string new_ctg);
	
	bool CheckUserID(const string userID) const;
	bool CheckUserLogin(const string login) const;

	void AddUser(User* u);
	User* FindUserByID(const string userID) const;
	User* FindUserByLogin(const string login) const;
	vector<User*>::iterator FindUserIterator(const string userID);
	void DeleteUser(const string userID);
	
	void AddTest(Test* tst);
	bool CheckTestName(const string testName) const;
	Test* FindTest(const string testName) const;
	vector<Test*>::iterator FindTestIterator(const string testName);
	void DeleteTest(const string testName);

	void SaveDatabase() const;
	void ReadDatabase();
	
	void ShowCategories();
	void ShowTests();
	void ShowUsers();

	void SortTests();
	void SortUsers();
};

#endif // !DATABASE_H
