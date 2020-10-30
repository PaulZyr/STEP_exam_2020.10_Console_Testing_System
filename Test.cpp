#include "Test.h"


Test::Test() :categoryName("none"), 
		testName("none"), testDate("0") {}
Test::~Test() {
	for (auto q : test) delete q;
}

void Test::SetTestName(const string s) { testName = s; }
void Test::SetCategoryName(const string s) { categoryName = s; }
void Test::SetTestDate(const string s) { testDate = s; }


string Test::GetCategoryName() const { return categoryName; }
string Test::GetTestName() const { return testName; }
string Test::GetTestDate() const { return testDate; }
int Test::GetTestSize() const { return test.size(); }
vector<Question*> Test::GetVectorQuestions() { return test; }

Question* Test::FindQuestion(const string quest) const
{
	for (auto q : test) 
		if (q->GetQuestion() == quest) return q;
	return NULL;
}
Question* Test::FindQuestion(const int i) const
{
	if (i >= test.size() || i <= 0) return NULL;
	return test.at(i-1);
}

vector<Question*>::iterator Test::FindQuestIterator(const string quest)
{
	vector<Question*>::iterator it = test.begin();
	while (it != test.end()) {
		if ((*it)->GetQuestion() == quest) return it;
		it++;
	}
	return it;
}

void Test::AddQuestion(Question* q) { test.push_back(q); }
void Test::DeleteQuestion(int i) 
{
	auto it = test.begin() + i;
	delete* it;
	test.erase(it);
}

void Test::SaveToFstream(ofstream& fout) 
{
	fout << "$Test\n" << categoryName << "\n"
		<< testName << "\n" << testDate << "\n";
	for (auto q : test) q->SaveQuestionToFstream(fout);
	fout << "#Test\n";
}

void Test::ReadFromFstream(ifstream& fin) 
{
	string s;
	getline(fin, s);
	if (s != "#Test") SetCategoryName(s);
	else return;
	getline(fin, s);
	if (s != "#Test") SetTestName(s);
	else return;
	getline(fin, s);
	if (s != "#Test") SetTestDate(s);
	else return;
	test.clear();
	while (s != "#Test") {
		getline(fin, s);
		if (s == "#Test") break;
		if (s == "$Question") {
			Question* tmp = new Question;
			tmp->ReadQuestionFromFstream(fin);
			test.push_back(tmp);
			tmp = NULL;
		}
	}
}

void Test::ExportTest(string path) 
{
	ofstream fout;
	fout.open(path, ios_base::out);
	SaveToFstream(fout);
	fout.close();
}

void Test::ImportTest(string path) 
{
	ifstream fin;
	fin.open(path, ios_base::in);
	if (fin.is_open()) {
		SetCategoryName("none");
		SetTestName("none");
		SetTestDate("0000");
		test.clear();
		string s;
		getline(fin, s);
		if (s == "$Test") ReadFromFstream(fin);
		else cout << "No Test in '" << path << "'\n";
		fin.close();
	}
	else cout << "No such file!\n";
}

void Test::ShowTest() const
{
	cout << "'"<< testName << "' | '" << categoryName << "'\n";
	int i = 0;
	for (auto quest : test) {
		cout << ++i << " ";
		quest->Show();
	}
}