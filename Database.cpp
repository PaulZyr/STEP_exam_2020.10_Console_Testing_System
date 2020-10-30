#include "Database.h"

Database::Database() :path("none") {}

Database::~Database() 
{
	for (auto u : users) delete u;
	for (auto tst : tests) delete tst;
}

void Database::SetPath(const string s) { path = s; }

bool Database::CheckDatabaseFile() const
{
	bool b = false;
	ifstream file;
	file.open(path, ios_base::in);
	if (file.is_open()) b = true;
	file.close();
	return b;
}

vector<User*> Database::GetUsers() const { return users; }
vector<Test*> Database::GetTests() const { return tests; }
//vector<Test*>::iterator Database::GetTestsEnd() 
//{
//	return tests.end();
//}
//vector<User*>::iterator Database::GetUsersEnd()
//{
//	return users.end();
//}
bool Database::CheckCategories(const string str) const
{
	for (auto s : categories)
		if (s == str) return true;
		else return false;
}
void Database::AddCategory(const string str)
{
	categories.push_back(str);
	sort(categories.begin(), categories.end());
}
void Database::ChangeCategory(const string old_ctg, const string new_ctg)
{
	for (auto ctg : categories)
	{
		if (ctg == old_ctg)
		{
			ctg = new_ctg;
			for (auto t : tests)
				if (t->GetCategoryName() == old_ctg)
					t->SetCategoryName(new_ctg);
			cout << "Category " << old_ctg
				<< "\n    was changed to "
				<< new_ctg << "\n";
			return;
		}
	}
	cout << "No such Category!\n";
}

// ----- User block -----
void Database::AddUser(User* u) { users.push_back(u); }

bool Database::CheckUserID(const string userID) const
{
	for (auto u : users)
		if (u->GetUserID() == userID) return true;
	return false;
}
bool Database::CheckUserLogin(const string login) const
{
	for (auto u : users)
		if (u->CheckLogin(login)) return true;
	return false;
}

User* Database::FindUserByID(const string userID) const
{
	for (auto u : users) {
		if (u->GetUserID() == userID) return u;
	}
	return NULL;
}
User* Database::FindUserByLogin(const string login) const
{
	for (auto u : users) {
		if (u->CheckLogin(login)) return u;
	}
	return NULL;
}
vector<User*>::iterator Database::FindUserIterator(const string userID)
{
	vector<User*>::iterator it = users.begin();
	while (it != users.end()) {
		if ((*it)->GetUserID() == userID) return it;
		it++;
	}
	return it; //end() if not found
}

void Database::DeleteUser(const string userID)
{
	vector<User*>::iterator it = FindUserIterator(userID);
	if (it == users.end())
	{
		cout << "No such user\n";
		return;
	}
	delete (*it);
	users.erase(it);
	cout << "User " << userID << " deleted!\n";
}


// ----- Test block -----

void Database::AddTest(Test* tst)
{
	tests.push_back(tst);
}

bool Database::CheckTestName(const string testName) const
{
	for (auto tst : tests)
		if (tst->GetTestName() == testName) return true;
	return false;
}

Test* Database::FindTest(const string testName) const
{
	for (auto tst : tests)
		if (tst->GetTestName() == testName) return tst;
	return NULL;
}

vector<Test*>::iterator Database::FindTestIterator(const string testName)
{
	vector<Test*>::iterator it = tests.begin();
	while (it != tests.end()) {
		if ((*it)->GetTestName() == testName) return it;
		it++;
	}
	return it;
}

void Database::DeleteTest(const string testName)
{
	vector<Test*>::iterator it = FindTestIterator(testName);
	if (it == tests.end()) cout << "Test '" << testName << "' NOT exist!\n";
	else 
	{
		delete (*it);
		tests.erase(it);
		cout << "DONE!\n";
	}
	system("pause");
}


// ----- other -----
void Database::SaveDatabase() const
{
	ofstream fout;
	fout.open(path, ios_base::out);

	fout << "$Database\n";
	for (auto tst : tests) tst->SaveToFstream(fout);
	for (auto u : users) u->SaveUserToFstream(fout);
	fout << "#Database\n";
	fout.close();
}

void Database::ReadDatabase()
{
	ifstream fin;
	fin.open(path, ios_base::in);
	if (fin.is_open()) {
		string s;
		getline(fin, s);
		if (s == "$Database")
		{
			getline(fin, s);
			while (s != "#Database") {
				if (s == "$Test") {
					Test* tst_tmp = new Test;
					tst_tmp->ReadFromFstream(fin);
					tests.push_back(tst_tmp);
					categories.push_back(tst_tmp->GetCategoryName());
					tst_tmp = NULL;
				}
				else if (s == "$User") {
					User* usr_tmp = new User;
					usr_tmp->ReadUserFromFstream(fin);
					users.push_back(usr_tmp);
					usr_tmp = NULL;
				}
				getline(fin, s);
			}
		}
		
		fin.close();
	}
	else cout << "No such file!\n";
}

void Database::ShowTests()
{
	system("CLS");
	SortTests();
	string str = "";
	cout << "--------------------\n"
		<< "***   ALL TESTS   ***\n";
	int i = 0;
	for (auto tst : tests)
	{
		if (str != tst->GetCategoryName())
		{
			str = tst->GetCategoryName();
			cout << "* Category: " << str << "\n";
		}
		cout << " " << ++i << "  Test: '" << tst->GetTestName() << "'\n";
	}
	cout << "--------------------\n";
}

void Database::ShowCategories()
{
	system("CLS");
	sort(categories.begin(), categories.end());
	cout << "--------------------\n";
	cout << "* Categories *\n";
	for (auto ctg : categories)
		cout << ctg << endl;
	cout << "--------------------\n";
}

void Database::ShowUsers()
{
	SortUsers();
	system("CLS");
	cout << "--------------------\n";
	cout << "*** Users ***\n";
	set<string> res;
	string str;
	for (auto u : users) u->ShowInfo();
	cout << "--------------------\n";
	system("pause");
}

void Database::SortTests()
{
	sort(tests.begin(), tests.end(), [](Test* lhs, Test* rhs) {
		return (*lhs).GetTestName() < (*rhs).GetTestName(); });
	sort(tests.begin(), tests.end(), [](Test* lhs, Test* rhs) {
		return (*lhs).GetCategoryName() < (*rhs).GetCategoryName(); });
}

void Database::SortUsers()
{
	sort(users.begin(), users.end(), [](User* lhs, User* rhs) 
		{
			if ((*lhs).GetLastName() == (*rhs).GetLastName())
			{
				if ((*lhs).GetFirstName() == (*rhs).GetFirstName())
				{
					return (*lhs).GetMiddleName() < (*rhs).GetMiddleName();
				}
				else return (*lhs).GetFirstName() < (*rhs).GetFirstName();
			}
			else return (*lhs).GetLastName() < (*rhs).GetLastName(); 
		});
}