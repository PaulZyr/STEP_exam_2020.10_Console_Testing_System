#include "Question.h"
#include "Header.h"

using namespace std;

Question::Question() : question("none") {}
Question::~Question() {
	for (auto a : answers) delete a;
}

void Question::SetQuestion(const string s) { question = s; }
string Question::GetQuestion() const { return question; }

vector<Answer*> Question::GetAnswers() const { return answers; }

void Question::AddAnswer(const string s, const bool b)
{ 
	Answer* tmp = new Answer;
	tmp->SetAnswer(s);
	tmp->SetRight(b);
	answers.push_back(tmp);
	tmp = NULL;
}

void Question::ChangeAnswer(const string s, const bool b, const int n)
{
	answers.at(n - 1)->SetAnswer(s);
	answers.at(n - 1)->SetRight(b);
}

void Question::DeleteAnswer(const int i) 
{
	auto it = answers.begin() + i;
	delete (*it);
	answers.erase(it);
}

bool Question::CheckRightAnswer(const int i) const
{
	if (i >= answers.size() || i < 0) return false;
	else
	{
		if (answers[i]->GetRight()) return true;
		else return false;
	}
}
void Question::Show() const
{
	cout << "Question: " << question << endl
		<< "Answers: " << endl;
	int i = 0;
	for (auto a : answers)
	{
		cout << ++i << ": " << a->GetAnswer() << endl;
	}
}

void Question::SaveQuestionToFstream(ofstream& fout) 
{
	fout << "$Question\n" << question << "\n";
	for (auto a : answers)
		fout << a->GetAnswer() << "\n" << a->GetRight() << "\n";
	fout << "#Question\n";
}

void Question::ReadQuestionFromFstream(ifstream& fin) 
{
	string s;
	bool b;
	getline(fin, s);
	if (s != "#Question") SetQuestion(s);
	else return;
	while (s != "#Question") {
		getline(fin, s);
		if (s == "#Question") break;
		Answer* tmp = new Answer;
		tmp->SetAnswer(s);
		fin >> b; fin.ignore();
		tmp->SetRight(b);
		answers.push_back(tmp);
		tmp = NULL;
	}
}


