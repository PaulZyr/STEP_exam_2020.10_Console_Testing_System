#include "Header.h"

void UserLogin(Database* base)
{
	cout << "User Login: ";
	string s;
	getline(cin, s);
	User* user = base->FindUserByLogin(s);
	if (user == NULL) cout << "Wrong login\n";
	else
	{
		cout << "User Password: ";
		getline(cin, s);
		if (user->CheckPassword(s))
		{
			system("CLS");
			TestingMenu(base, user);
		}
		else cout << "Wrong password\n";
	}
	user = NULL;
}

void TestingMenu(Database* base, User* user)
{
	string str;
	int q = -1;
	while (q != 0)
	{
		cout << "*** Testing menu ***\n"
			<< "1 - Take new test\n"
			<< "2 - Continue test\n"
			<< "3 - Show my UNDONE Tests\n"
			<< "4 - Show ALL my Results\n"
			<< "5 - Show ALL available tests\n"
			<< "0 - Finish testing\n";
		getline(cin, str);
		q = IntFromString(str);
		//cin >> q; cin.ignore();
		switch (q)
		{
		case 1: TakeNewTest(base, user); base->SaveDatabase(); break;
		case 2: ContinueTest(base, user); base->SaveDatabase(); break;
		case 3: user->ShowUndoneTests(); break;
		case 4: user->ShowStatistic(); break;
		case 5: base->ShowTests(); break;
		case 0: break;
		default: cout << "Wrong input! Try better!\n";
		}
		
	}
}

void TakeNewTest(Database* base, User* user)
{
	base->ShowTests();
	/*int i = 0;

	for (auto t : base->GetTests())
	{
		cout << ++i << " ";
		t->ShowTest();
	}*/
	cout << "Input number: ";
	int n = 0;
	cin >> n; cin.ignore();

	if (n<1 || n>base->GetTests().size())
	{
		cout << "Wrong Number!\n";
		system("pause");
		return;
	}

	Test* test = base->GetTests()[n - 1];
	Result* res_test = new Result;
	
	res_test->SetTestName(test->GetTestName());
	res_test->SetTestDate(test->GetTestDate());

	user->AddResult(res_test);

	PassTest(test, res_test);

	test = NULL;
	res_test = NULL;
}

void ContinueTest(Database* base, User* user)
{
	system("CLS");
	user->ShowStatistic();

	cout << "Input Number Test to continue: ";
	int n;
	string str;
	getline(cin, str);
	n = IntFromString(str);
	//cin >> n; cin.ignore();

	if (n < 1 || n > user->GetResults().size())
	{
		cout << "Wrong Number!\n";
		system("pause");
		return;
	}

	Result* res_test = user->GetResults()[n - 1];
	Test* test = base->FindTest(res_test->GetTestName());
	if (test == NULL) cout << "Something wrong! Sorry!\n";
	else
	{
		if (res_test->GetTestDone() == 1)
		{
			cout << "You have passed this Test already!\n"
				<< "Do you want to pass it again? (0/1):";
			getline(cin, str);
			n = IntFromString(str);
			//cin >> n; cin.ignore();
			if (n != 1) return;
			res_test->SetTestDate(test->GetTestDate());
			res_test->Clear();
		}
		else
		{
			if (res_test->GetTestDate() != test->GetTestDate())
			{
				cout << "Test have been changed!\n"
					<< "You need pass it from the beginning!\n";
				res_test->SetTestDate(test->GetTestDate());
				res_test->Clear();
			}
		}
		PassTest(test, res_test);
	}
	test = NULL;
	res_test = NULL;
}

void PassTest(Test* test, Result* res_test)
{
	int current = res_test->GetCurrent();
	int size = test->GetTestSize();

	for (int i = current; i < size; ++i)
	{
		system("CLS");
		test->GetVectorQuestions()[i]->Show();

		cout << "Input Number of ANSWER:\n"
			<< "0 - exit\n#: ";
		int q;
		cin >> q; cin.ignore();
		if (q == 0) return;
		if (test->GetVectorQuestions()[i]->CheckRightAnswer(q - 1))
			res_test->AddQuestionMark(true);
		else res_test->AddQuestionMark(false);
	}
	if (res_test->GetCurrent() == test->GetTestSize())
		res_test->SetTestDone(true);
	res_test->CountResult();
	system("CLS");
	cout << "Your RESULT:\n";
	res_test->ShowResult();
	system("pause");
}