/*
0) System:
- Keep login-passwords in crypt mode
- One admin only

1) Testing
- Number of right/wrong answered questions
- 12 points mark system

2) User might:
- Create own account
- Enter account
- See own results
- Take test, see result, interrupt, continue, get a Mark

3) Admin only:
- registration admin account once
- change admin login-password
- Control users - create, delete, changing
- See Statistic - results in categories, one test, one user
- Any kind of results - save to file
- Control testing: 
	add/change categories, tests, questions, 
	set right/wrong question, 
	import/export categories & tests in/out file

*/

#include "Header.h"

void MyTests()
{
	User* usr = new User;
	Result* res = new Result;
	res->SetTestName("Termo 01 quagdos");
	res->SetTestDone(false);
	usr->AddResult(res);


	Result* res2 = new Result;
	res2->SetTestName("Dasert 02 Mucho");
	res2->SetTestDone(true);
	usr->AddResult(res2);


	Result* res3= new Result;
	res3->SetTestName("Nikki Maserto 03 Gaser");
	res3->SetTestDone(true);
	usr->AddResult(res3);

	Result* res4 = new Result;
	res4->SetTestName("Alibaba 04 and 40");
	res4->SetTestDone(false);
	usr->AddResult(res4);

	//vector<Result*> tmp = usr->GetResults();

	cout << "*** Stat ***\n";
	usr->ShowStatistic();

}

int main() {

	// admin: login:paul pass:zxc code:qwerty
	// user:Ivanov login:iva2020 pass:qwerty

	Administrator* admin = admin->Instance();
	Database* base = new Database;

	if (!admin->CheckFile()) FirstTimeRunMenu(admin);

	StartMenu(admin, base);
	
	return 0;
}




