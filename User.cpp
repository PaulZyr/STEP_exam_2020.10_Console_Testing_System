#include "User.h"

User::User() 
{
	userID = "none";
	login = "none";
	pass = "none";
	last_name = "none";
	first_name = "none";
	middle_name = "none";
	phone = "none";
	address = "none";
}
User::~User() 
{
	for (auto r : results) delete r;
}

void User::SetUserID(const string s) { userID = s; }
void User::SetLogin(const string s) { login = Crypt(s); }
void User::SetPassword(const string s) { pass = Crypt(s); }
void User::SetLastName(const string s) { last_name = s; }
void User::SetFirstName(const string s) { first_name = s; }
void User::SetMiddleName(const string s) { middle_name = s; }
void User::SetPhone(const string s) { phone = s; }
void User::SetAddress(const string s) { address = s; }

string User::GetUserID() const { return userID; }
string User::GetLastName() const { return last_name; }
string User::GetFirstName() const { return first_name; }
string User::GetMiddleName() const { return middle_name; }
string User::GetPhone() const { return phone; }
string User::GetAddress() const { return address; }

void User::AddResult(Result* res) { results.push_back(res); }
vector<Result*> User::GetResults() const { return results; }

bool User::CheckLogin(const string s)
{
	if (Crypt(s) == login) return true;
	else return false;
}

bool User::CheckPassword(const string s)
{
	if (Crypt(s) == pass) return true;
	else return false;
}

string User::Crypt(const string s)
{
	string tmp;
	char c;
	for (auto it : s) {
		c = it ^ 7;
		tmp += c;
	}
	return tmp;
}

void User::SaveUserToFile(const string path)const
{
	ofstream fout;
	fout.open(path, ios_base::out);
	fout << "$User\n" << userID << "\n"
		<< login << "\n" << pass << "\n"
		<< last_name << "\n" << first_name << "\n" 
		<< middle_name << "\n" << phone << "\n"
		<< address << "\n";
	for (auto r : results) 
		r->SaveResultToFstream(fout);
	fout << "#User\n";
	fout.close();
}
void User::SaveUserToFstream(ofstream& fout) const
{
	fout << "$User\n" << userID << "\n"
		<< login << "\n" << pass << "\n"
		<< last_name << "\n" << first_name << "\n"
		<< middle_name << "\n" << phone << "\n"
		<< address << "\n";
	for (auto r : results)
		r->SaveResultToFstream(fout);
	fout << "#User\n";
}

void User::ReadUserFromFile(const string path)
{
	ifstream fin;
	fin.open(path, ios_base::in);
	string s;
	getline(fin, s);
	if (s != "#User") SetUserID(s);
	getline(fin, s);
	if (s != "#User") login = s;
	getline(fin, s);
	if (s != "#User") pass = s;
	getline(fin, s);
	if (s != "#User") SetLastName(s);
	getline(fin, s);
	if (s != "#User") SetFirstName(s);
	getline(fin, s);
	if (s != "#User") SetMiddleName(s);
	getline(fin, s);
	if (s != "#User") SetPhone(s);
	getline(fin, s);
	if (s != "#User") SetAddress(s);
	getline(fin, s);
	while (s != "#User") {
		if (s == "$Result") {
			Result* tmp = new Result;
			tmp->ReadResultFromFstream(fin);
			results.push_back(tmp);
			tmp = NULL;
		}
		getline(fin, s);
	}
	fin.close();
}
void User::ReadUserFromFstream(ifstream& fin) 
{
	string s;
	getline(fin, s);
	if (s != "#User") SetUserID(s);
	getline(fin, s);
	if (s != "#User") login = s;
	getline(fin, s);
	if (s != "#User") pass = s;
	getline(fin, s);
	if (s != "#User") SetLastName(s);
	getline(fin, s);
	if (s != "#User") SetFirstName(s);
	getline(fin, s);
	if (s != "#User") SetMiddleName(s);
	getline(fin, s);
	if (s != "#User") SetPhone(s);
	getline(fin, s);
	if (s != "#User") SetAddress(s);
	getline(fin, s);
	while (s != "#User") {
		if (s == "$Result") {
			Result* tmp = new Result;
			tmp->ReadResultFromFstream(fin);
			results.push_back(tmp);
			tmp = NULL;
		}
		getline(fin, s);
	}
}

void User::SortResults()
{
	sort(results.begin(), results.end(), [](Result* lhs, Result* rhs) {
		return (*lhs).GetTestName() < (*rhs).GetTestName();});
}

void User::ShowUndoneTests()
{
	SortResults();
	system("CLS");
	cout << "--------------------\n"
		<< last_name << " " << first_name << " "
		<< middle_name << "\n";
	if (results.size() != 0)
	{
		int k = 0;
		for (auto r : results)
		{
			if (r->GetTestDone() == 0)
			{
				r->ShowResult();
				k++;
			}
		}
		if (k == 0) cout << "You have No undone tests!\n";	
	}
	else cout << "   NO Results TO SHOW yet!\n";
	cout << "--------------------\n";

}

void User::ShowStatistic()
{
	SortResults();
	system("CLS");
	cout << "--------------------\n"
		<< last_name << " " << first_name << " "
		<< middle_name << "\n";
	int i = 0;
	if (results.size() != 0) 
	{
		for (auto r : results)
		{
			cout << ++i << " ";
			r->ShowResult();
		}
	}
	else cout << "  NOTHING TO SHOW!\n";
	cout << "--------------------\n";
}

void User::ShowInfo() const
{
	cout << "ID = " << userID << "; Name: " 
		<< last_name << " " << first_name << " "
		<< middle_name << "; Phone: " 
		<< phone << "; Address: " << address << "\n";
}