#ifndef HEADER_H
#define HEADER_H

#include "Database.h"
#include "Administrator.h"

using namespace std;

// Source.cpp
void FirstTimeRunMenu(Administrator* admin);
void Welcome();
void StartMenu(Administrator* admin, Database* base);
void NewUser(Database* base);
bool CheckFile(string path);
int IntFromString(string str);

// UserMode.cpp
void UserLogin(Database* base);
void TestingMenu(Database* base, User* user);
void TakeNewTest(Database* base, User* user);
void ContinueTest(Database* base, User* user);
void PassTest(Test* test, Result* res_test);

// AdminMode.cpp
void AdminMode(Administrator* admin, Database* base);

void WorkWithTest(Database* base);
void NewTest(Database* base);
void DeleteTest(Database* base);
void ChangeQuestion(Test* test_tmp);
void ChangeTest(Database* base);
void ChangeAnswer(Question* quest_tmp);
void ImportTest(Database* base);
void ExportTest(Database* base);
void ChangeCategories(Database* base);
void InitQuestion(Question* quest_tmp);

void WorkWithUsers(Database* base);
void DeleteUser(Database* base);
void ChangeUser(Database* base);
void ChangeUserID(User* tmp);
void ChangeUserLogin(User* tmp);
void ChangeUserName(User* tmp);
void ChangeUserPhone(User* tmp);
void ChangeUserAddress(User* tmp);
void ImportUser(Database* base);
void ExportUser(Database* base);

#endif // !HEADER_H

