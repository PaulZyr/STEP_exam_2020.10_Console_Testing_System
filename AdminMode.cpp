#include "Header.h"
#include <iostream>
#include <string>

using namespace std;

void AdminMode(Administrator* admin, Database* base)
{
	int q = -1;
	string str;
	while (q != 0) {
		system("CLS");
		cout << "*** ADMINISTRATOR: ***\n"
			<< "--------------------\n"
			<< "** DATABASE PART **\n"
			<< "1 - Tests;\n"
			<< "2 - Users;\n"
			<< "3 - Load Database from FILE;\n"
			<< "4 - Create NEW Database;\n"
			<< "5 - Save Database to File;\n"
			<< "--------------------\n"
			<< "** ADMIN PART **\n"
			<< "11 - LOG IN;\n"
			<< "12 - Show admin STATUS;\n"
			<< "13 - Change admin Login;\n"
			<< "14 - Change admin Password;\n"
			<< "15 - Change Menu_Code;\n"
			<< "17 - LOG OUT;\n"
			<< "--------------------\n"
			<< "22 - SAVE DATABASE;\n"
			<< "0 - Return to Main Menu.\n"
			<< "Choose: ";
		getline(cin, str);
		q = IntFromString(str);
		//cin >> q; cin.ignore();
		switch (q) {
		case 1:
		{
			if (admin->CheckStatus()) WorkWithTest(base);
			else
			{
				cout << "$ LOG IN FIRST!\n";
				system("pause");
			}
			break;
		}
		case 2:
		{
			if (admin->CheckStatus()) WorkWithUsers(base);
			else
			{
				cout << "$ LOG IN FIRST!\n";
				system("pause");
			}
			break;
		}
		case 3:
		{
			if (admin->CheckStatus()) {
				string s;
				cout << "Input filename: ";
				cin >> s;
				delete base;
				base = new Database;
				base->SetPath(s);
				base->ReadDatabase();
				cout << "DONE!\n";
			}
			else
			{
				cout << "$ LOG IN FIRST!\n";
				system("pause");
			}
			break;
		}
		case 4:
		{
			if (admin->CheckStatus())
			{
				cout << "Input FILENAME for NEW Database: ";
				string s;
				getline(cin, s);
				Database* tmp = new Database;
				tmp->SetPath(s);
				tmp->SaveDatabase();
				delete base;
				base = tmp;
				tmp = NULL;
				admin->ChangeDatabasePath(s);
				cout << "Done!\n";
				system("pause");
			}
			else
			{
				cout << "$ LOG IN FIRST!\n";
				system("pause");
			}
			break;
		}
		case 5:
		{
			base->SaveDatabase();
			break;
		}
		case 11:
		{
			string log, pass;
			cout << "Input login: "; cin >> log;
			cout << "Input password: "; cin >> pass;
			admin->Login(log, pass);
			break;
		}
		case 12:
		{
			admin->Show();
			system("pause");
			break;
		}
		case 13:
		{
			if (admin->CheckStatus())
			{
				string s;
				cout << "Input NEW login: "; cin >> s;
				admin->ChangeLogin(s);
			}
			else 
			{
				cout << "$ LOG IN FIRST!\n";
				system("pause");
			}
			break;
		}
		case 14:
		{
			if (admin->CheckStatus())
			{
				string s;
				cout << "Input NEW password: "; cin >> s;
				admin->ChangePassword(s);
			}
			else 
			{
				cout << "$ LOG IN FIRST!\n";
				system("pause");
			}
			break;
		}
		case 15:
		{
			if (admin->CheckStatus())
			{
				string s;
				cout << "Input NEW Return_Code: "; cin >> s;
				admin->ChangeMenuCode(s);
			}
			else
			{
				cout << "$ LOG IN FIRST!\n";
				system("pause");
			}
			break;
		}
		case 17:
		{
			admin->Logout();
			cout << "You are OUT of account!\n";
			system("pause");
			break;
		}
		case 22: base->SaveDatabase(); break;
		case 0: admin->Logout(); break;
		default: cout << "Wrong input! Try better!\n";
		}
	}
}

//-------------------------------

void WorkWithTest(Database* base)
{
	system("CLS");
	string str;
	int q = -1;
	while (q != 0)
	{
		cout << " *** Tests *** \n"
			<< "1 - Show Test LIST\n"
			<< "2 - New Test\n"
			<< "2 - Change Test\n"
			<< "4 - Delete Test\n"
			<< "5 - Import Test TO File\n"
			<< "6 - Export Test FROM File\n"
			<< "7 - Show Categories\n"
			<< "8 - Change Category\n"
			<< "----------------\n"
			<< "9 - SAVE DATABASE\n"
			<< "0 - return.\n"
			<< "Choose: ";
		getline(cin, str);
		q = IntFromString(str);
		//cin >> q; cin.ignore();
		switch (q)
		{
		case 1: base->ShowTests(); system("pause"); break;
		case 2: NewTest(base); break;
		case 3: ChangeTest(base); break;
		case 4:	DeleteTest(base); break;
		case 5: ImportTest(base); break;
		case 6: ExportTest(base); break;
		case 7: base->ShowCategories(); system("pause"); break;
		case 8: ChangeCategories(base); break;
		case 9: base->SaveDatabase(); break;
		case 0: break;
		default: cout << "Wrong input! Try better!\n";
		}
	}
}

void NewTest(Database* base)
{
	string testName;
	cout << "Input Test Name: ";
	getline(cin, testName);

	if (base->CheckTestName(testName))
	{
		cout << "This Name exist!\n";
		return;
	}
	string categoryName;
	cout << "Input category Name: ";

	if (!base->CheckCategories(categoryName))
	{
		cout << "This Category NOT exist yet\n"
			<< "and will be created!\n";
	}
		
	getline(cin, categoryName);

	string testDate;
	cout << "Input test Date in '2020/09/30' format:\n";
	getline(cin, testDate);

	Test* test_tmp = new Test;
	test_tmp->SetTestName(testName);
	test_tmp->SetCategoryName(categoryName);
	test_tmp->SetTestDate(testDate);

	int n;
	cout << "Number of Questions it the Test: ";
	cin >> n; cin.ignore();

	for (int i = 0; i < n; ++i)
	{
		Question* quest_tmp = new Question;
		InitQuestion(quest_tmp);
		test_tmp->AddQuestion(quest_tmp);
		quest_tmp = NULL;
	}

	base->AddTest(test_tmp);
	test_tmp = NULL;
}

void InitQuestion(Question* quest_tmp)
{
	string s;
	cout << "Input question: ";
	getline(cin, s);
	quest_tmp->SetQuestion(s);
	cout << "Number of answers: ";
	int n;
	cin >> n; cin.ignore();
	for (int i = 0; i < n; ++i)
	{
		cout << "Input Answer: ";
		getline(cin, s);
		cout << "This Answer right/wrong (1/0): ";
		bool b;
		cin >> b; cin.ignore();
		quest_tmp->AddAnswer(s, b);
	}
}

void DeleteTest(Database* base)
{
	cout << "Input test Name to DELETE:\n";
	string s;
	getline(cin, s);
	base->DeleteTest(s);
}

void ChangeTest(Database* base)
{
	system("CLS");
	cout << "Input test Name to CHANGE:\n";
	string s;
	getline(cin, s);
	Test* test_tmp = base->FindTest(s);
	if (test_tmp == NULL)
	{
		cout << "No such Test!\n";
		system("pause");
		return;
	}
	else
	{
		string str;
		int q = -1;
		while (q != 0)
		{
			system("CLS");
			cout << " *** Changing TEST *** \n"
				<< "1 - Show Test\n"
				<< "2 - Change Test NAME\n"
				<< "3 - Change Test CATEGORY\n"
				<< "4 - Change Test DATE\n"
				<< "5 - Change Questions\n"
				<< "----------------\n"
				<< "0 - return.\n"
				<< "Choose: ";
			getline(cin, str);
			q = IntFromString(str);
			//cin >> q; cin.ignore();
			switch (q)
			{
			case 1: test_tmp->ShowTest(); break;
			case 2: cout << "Input TEST NAME: "; 
				getline(cin, s);
				test_tmp->SetTestName(s); 
				break;
			case 3: cout << "Input CATEGORY Name: ";
				getline(cin, s);
				test_tmp->SetCategoryName(s);
				break;
			case 4: cout << "Input Test DATE: ";
				getline(cin, s);
				test_tmp->SetTestDate(s);
				break;
			case 5:	ChangeQuestion(test_tmp); break;
			case 0: break;
			default: cout << "Wrong input! Try better!\n";
			}
		}
	}
}

void ChangeQuestion(Test* test_tmp)
{
	test_tmp->ShowTest();
	cout << "Input Question to CHANGE: ";
	int i;
	cin >> i; cin.ignore();
	Question* quest_tmp = test_tmp->FindQuestion(i);
	string s, str;
	int q = -1;
	while (q != 0)
	{
		cout << " *** Changing QUESTION *** \n"
			<< "1 - Show Question\n"
			<< "2 - Change question\n"
			<< "3 - Change Answers\n"
			<< "----------------\n"
			<< "0 - return.\n"
			<< "Choose: ";
		getline(cin, str);
		q = IntFromString(str);
		//cin >> q; cin.ignore();
		switch (q)
		{
		case 1: quest_tmp->Show(); break;
		case 2:
		{
			cout << "Input New Question: ";
			getline(cin, s);
			quest_tmp->SetQuestion(s);
			break;
		}
		case 3: ChangeAnswer(quest_tmp); break;
		case 0: break;
		default: cout << "Wrong input! Try better!\n";
		}
	}
}

void ChangeAnswer(Question* quest_tmp)
{
	int q = -1, n = 0;
	while (q != 0)
	{
		quest_tmp->Show();
		cout << " *** Changing ANSWER *** \n"
			<< "1 - Change Answer;\n"
			<< "----------------\n"
			<< "0 - return.\n"
			<< "Input: ";
		string new_answ, str;
		getline(cin, str);
		q = IntFromString(str);
		//cin >> q; cin.ignore();
		switch (q)
		{
		case 1:
		{
			cout << "Input Number of ANSWER to CHANGE: ";
			cin >> n; cin.ignore();
			cout << "Input new Answer:";
			getline(cin, new_answ);
			cout << "This Answer is right or wrong (1/0):";
			bool b;
			cin >> b; cin.ignore();
			quest_tmp->ChangeAnswer(new_answ, b, n);
			break;
		}
		case 0: break;
		default: cout << "Wrong input! Try better!\n";
		}
	}
}

void ExportTest(Database* base)
{
	cout << "Input Test NAME to EXPORT to FILE:\n";
	string s;
	getline(cin, s);
	Test* tmp = base->FindTest(s);
	if (tmp != 0)
	{
		cout << "Input FILENAME to save:";
		getline(cin, s);
		tmp->ExportTest(s);
	}
	else cout << "No such test!\n";
	tmp = NULL;
}

void ImportTest(Database* base)
{
	cout << "Input FILENAME to IMPORT from:";
	string s;
	getline(cin, s);
	if (CheckFile(s))
	{
		Test* tmp = new Test;
		tmp->ImportTest(s);
		base->AddTest(tmp);
		tmp = NULL;
	}
	else cout << "No such FILE!\n";
}

void ChangeCategories(Database* base)
{
	base->ShowCategories();
	cout << "Input Old Category Name:\n";
	string old_ctg;
	getline(cin, old_ctg);
	cout << "Input NEW Category Name:\n";
	string new_ctg;
	getline(cin, new_ctg);
	base->ChangeCategory(old_ctg, new_ctg);
}

//-------------------------------

void WorkWithUsers(Database* base)
{
	system("CLS");
	string str;
	int q = -1;
	while (q != 0)
	{
		cout << "*** Users ***\n"
			<< "1 - Show Users\n"
			<< "2 - New User\n"
			<< "3 - Delete User\n"
			<< "4 - Change User\n"
			<< "5 - Import User TO File\n"
			<< "6 - Export User FROM File\n"
			<< "----------------\n"
			<< "9 - Save DATABASE\n"
			<< "0 - return.\n"
			<< "Choose: ";
		getline(cin, str);
		q = IntFromString(str);
		//cin >> q; cin.ignore();
		switch (q)
		{
		case 1: base->ShowUsers(); break;
		case 2: NewUser(base); break;
		case 3: DeleteUser(base); break;
		case 4: ChangeUser(base); break;
		case 5:	ImportUser(base); break;
		case 6: ExportUser(base); break;
		case 9: base->SaveDatabase(); break;
		case 0: break;
		default: cout << "Wrong input! Try better!\n";
		}
	}
}

void DeleteUser(Database* base)
{
	cout << "--------------------\n"
		<< "DELETING USER...\n";
	string s;
	cout << "Input UserID: ";
	getline(cin, s);
	base->DeleteUser(s);
}

void ChangeUser(Database* base) 
{
	cout << "--------------------\n"
		<< "CHANGING USER...\n";
	string s;
	cout << "Input UserID: ";
	getline(cin, s);
	User* tmp = base->FindUserByID(s);
	if (tmp == NULL) cout << "No such user!\n";
	else
	{
		string str;
		int q = -1;
		while (q != 0)
		{
			tmp->ShowInfo();
			cout << "--------------------\n"
				<< "1 - Change ID\n"
				<< "2 - Change login\n"
				<< "3 - Change Name\n"
				<< "4 - Change Phone\n"
				<< "5 - Change Address\n"
				<< "-----\n"
				<< "9 - Save DATABASE\n"
				<< "0 - Return\n";
			getline(cin, str);
			q = IntFromString(str);
			//cin >> q; cin.ignore();
			switch (q)
			{
			case 1: ChangeUserID(tmp); break;
			case 2: ChangeUserLogin(tmp); break;
			case 3: ChangeUserName(tmp); break;
			case 4: ChangeUserPhone(tmp); break;
			case 5: ChangeUserAddress(tmp); break;
			case 9: base->SaveDatabase(); break;
			case 0: break;
			default: cout << "Wrong Input! Try better!\n";
			}
		}
	}
}

void ChangeUserID(User* tmp)
{
	string s;
	cout << "Input NEW UserID: ";
	getline(cin, s);
	tmp->SetUserID(s);
}
void ChangeUserLogin(User* tmp)
{
	string s;
	cout << "Input NEW User LOGIN: ";
	getline(cin, s);
	tmp->SetLogin(s);
}
void ChangeUserName(User* tmp)
{
	string s;
	cout << "Input NEW User NAME: ";
	getline(cin, s);
	tmp->SetFirstName(s);
}
void ChangeUserPhone(User* tmp)
{
	string s;
	cout << "Input NEW User PHONE: ";
	getline(cin, s);
	tmp->SetPhone(s);
}
void ChangeUserAddress(User* tmp)
{
	string s;
	cout << "Input NEW UserID: ";
	getline(cin, s);
	tmp->SetAddress(s);
}

void ImportUser(Database* base)
{
	cout << "Input FILENAME to IMPORT USER from:";
	string s;
	getline(cin, s);
	if (CheckFile(s))
	{
		User* tmp = new User;
		tmp->ReadUserFromFile(s);
		base->AddUser(tmp);
		tmp = NULL;
	}
	else cout << "No such FILE!\n";
}
void ExportUser(Database* base) {
	cout << "Input User ID to EXPORT to FILE:\n";
	string s;
	getline(cin, s);
	User* tmp = base->FindUserByID(s);
	if (tmp != 0)
	{
		cout << "Input FILENAME to save:";
		getline(cin, s);
		tmp->SaveUserToFile(s);
	}
	else cout << "No such USER!\n";
	tmp = NULL;
}