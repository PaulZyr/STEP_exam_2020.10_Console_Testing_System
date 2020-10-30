#ifndef TEST_H
#define TEST_H

#include "Question.h"

class Test
{
	string testName;
	string categoryName;
	string testDate;
	vector<Question*> test;
public:
	Test();
	~Test();

	void SetTestName(const string s);
	void SetCategoryName(const string s);
	void SetTestDate(const string s);
	
	string GetTestName() const;
	string GetCategoryName() const;
	string GetTestDate() const;
	int GetTestSize() const;
	vector<Question*> GetVectorQuestions();

	Question* FindQuestion(const string quest) const;
	Question* FindQuestion(const int i) const;
	vector<Question*>::iterator FindQuestIterator(const string quest);

	void AddQuestion(Question* q);
	void DeleteQuestion(int i);

	void SaveToFstream(ofstream& fout);
	void ReadFromFstream(ifstream& fin);

	void ExportTest(string path);
	void ImportTest(string path);

	void ShowTest() const;
};

#endif

