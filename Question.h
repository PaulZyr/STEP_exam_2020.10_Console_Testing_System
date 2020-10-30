#ifndef QUESTION_H
#define QUESTION_H

#include "Answer.h"
#include <vector>
#include <fstream>

class Question
{
	string question;
	vector<Answer*> answers;
public:
	Question();
	~Question();

	void SetQuestion(const string s);
	string GetQuestion() const;
	vector<Answer*> GetAnswers() const;

	void AddAnswer(const string s, const bool b);
	void ChangeAnswer(const string s, const bool b, const int n);
	void DeleteAnswer(const int i);

	bool CheckRightAnswer(const int n) const;
	void Show() const;

	void SaveQuestionToFstream(ofstream& fout);
	void ReadQuestionFromFstream(ifstream& fin);
};

#endif // !QUESTION_H