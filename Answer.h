#ifndef ANSWER_H
#define ANSWER_H

#include <iostream>
#include <string>
using namespace std;

class Answer
{
	string answer;
	bool right;
public:
	Answer() :answer("none"), right(false) {}

	void SetAnswer(const string s) { answer = s; }
	void SetRight(const bool b) { right = b; }

	string GetAnswer() const { return answer; }
	bool GetRight() const { return right; }
};
#endif // !ANSWER_H