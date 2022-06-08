#ifndef library_H
#define library_H
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>
using namespace std;

class library
{
private:
	int lock = 0;
public:
	void print(vector<string>, int);
	void EnterBook();
	void ShowBook();
	void EnterMember();
	void ShowMember();
	void BorrowBooks();
	void ReturnBooks();
};
#endif
