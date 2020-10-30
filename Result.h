#ifndef _RESULT_H
#define RESULT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Result
{
	string testName;
	bool testDone;
	string testDate;
	int testMark;
	vector<bool> question_marks; // like 01100110
public:
	Result() :testName("none"), testDone(false),
		testDate("0"), testMark(0) {}

	void SetTestName(string s) { testName = s; }
	void SetTestDone(bool b) { testDone = b; }
	void SetTestDate(string s) { testDate = s; }
	void SetMark(int n) { testMark = n; }

	string GetTestName() { return testName; }
	bool GetTestDone() { return testDone; }
	string GetTestDate() { return testDate; }
	int GetCurrent() { return question_marks.size(); }
	int GetMark()
	{ 
		if (testDone) return testMark;
		else return 0;
	}

	void AddQuestionMark(bool b)
	{
		question_marks.push_back(b);
	}

	void Clear()
	{
		question_marks.clear();
	}

	void CountResult()
	{
		if (testDone)
		{
			int n = 0;
			for (auto b : question_marks) n += b;
			int w = (n * 100) / question_marks.size();
			if (w >= 97) testMark = 12;
			else if (w >= 94) testMark = 11;
			else if (w >= 90) testMark = 10;
			else if (w >= 87) testMark = 9;
			else if (w >= 84) testMark = 8;
			else if (w >= 80) testMark = 7;
			else if (w >= 77) testMark = 6;
			else if (w >= 74) testMark = 5;
			else if (w >= 70) testMark = 4;
			else if (w >= 68) testMark = 3;
			else if (w >= 66) testMark = 2;
			else if (w >= 65) testMark = 1;
			else testMark = 0;

		}
		else cout << "Test NOT Done yet!\n";
	}

	void ShowResult() const 
	{
		cout << "'" << testName << "'\n    Status: ";
		if (testDone)
			cout << "DONE\n    Mark = " << testMark << "\n";
		else
		{
			cout << "NOT done yet\n"
				<< "    Current question: " << question_marks.size() << "\n";
				
		}
		cout << "    Right answered Questions: ";
		int i = 0;
		for (auto b : question_marks)
			if (b == 1) i++;
		cout << i << " from " << question_marks.size() << "\n";
		cout << endl;
	}

	void SaveResultToFstream(ofstream& fout) 
	{
		fout << "$Result\n" << testName << "\n"
			<< testDone << "\n" << testDate << "\n" 
			<< testMark << "\n";
		fout << "$";
		for (auto b : question_marks) fout << b;
		fout << "#\n";
		fout << "#Result\n";
	}

	void ReadResultFromFstream(ifstream& fin) 
	{
		string s;

		getline(fin, s);
		if (s != "#Result") SetTestName(s);

		getline(fin, s);
		if (s != "#Result") {
			if (s == "1") SetTestDone(true);
			else SetTestDone(false);
		}
		else return;

		getline(fin, s);
		if (s != "#Result") SetTestDate(s);
		else return;
			
		int n;
		fin >> n; SetMark(n);
		fin.ignore();
			
		getline(fin, s);
		question_marks.clear();
		if (s != "#Result") {
			for (auto c : s) {
				if (c == '1') question_marks.push_back(true);
				else if (c == '0')question_marks.push_back(false);
			}
		}
		else return;
		getline(fin, s);
	}
};
#endif // !_RESULT_H