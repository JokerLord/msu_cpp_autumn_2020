#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <functional>
#include <ctype.h>
using namespace std;

class TokenParser
{
public:
	function<void()> StartCallback;
	function<void(string&)> DigitTokenCallback;
	function<void(string&)> StringTokenCallback;
	function<void()> EndCallback;
	vector<string> strings = {};
	vector<string> digits = {};
	void SetStartCallback(function<void()> func)
	{
		StartCallback = func;
	}
	void SetDigitTokenCallback(function<void(string&)> func)
	{
		DigitTokenCallback = func;
	}
	void SetStringTokenCallback(function<void(string&)> func)
	{
		StringTokenCallback = func;
	}
	void SetEndCallback(function<void()> func)
	{
		EndCallback = func;
	}
	void EndOfToken(string &curr, bool flag)
	{
		if (flag) {
			strings.push_back(curr);
			if (StringTokenCallback) {
				StringTokenCallback(curr);
			}
		} else {
			digits.push_back(curr);
			if (DigitTokenCallback) {
				DigitTokenCallback(curr);
			}
		}
	}
	void ParseIt(string &str)
	{
		if (StartCallback) {
			StartCallback();
		} else {
			cout << "Please, give me a function first!" << endl;
		}
		if (StringTokenCallback == nullptr) {
			cout << "Where is function for string tokens, moron?" << endl;
		}
		if (DigitTokenCallback == nullptr) {
			cout << "Where is function for digit tokens, moron?" << endl;
		}
		string curr = "";
		bool flag = false;
		for (char ch : str) {
			if (isdigit(ch)) {
				curr += ch;
			} else if (isspace(ch)) {
				if (curr.length() != 0) {
					EndOfToken(curr, flag);
					curr = "";
					flag = false;
				}
			} else {
				flag = true;
				curr += ch;
			}
		}
		if (curr.length() != 0) {
			EndOfToken(curr, flag);
		}
		if (EndCallback) {
			EndCallback();
		} else {
			cout << "That must be some kind of a joke." << endl;
		}
	}
};

void Start()
{
	cout << "Hello! I'm ready to be used as a test" << endl;
}

void Digit(string &digit)
{
	cout << "It's a digit token: " << digit << endl;
}

void String(string &str)
{
	cout << "It's a string token: " << str << endl;
}
 void End()
 {
 	cout << "Okey, I'm done with it" << endl; 
 }


void ParserTest()
{
	TokenParser parser;
	parser.SetStartCallback(Start);
	parser.SetDigitTokenCallback(Digit);
	parser.SetStringTokenCallback(String);
	parser.SetEndCallback(End);
	string str = "\nf8312  8979r879 	03 38490923  \n sdf3efwf0  89787";
	parser.ParseIt(str);
	vector<string> trueDigits = {"03", "38490923", "89787"};
	vector<string> trueStrings = {"f8312", "8979r879", "sdf3efwf0"};
	assert(trueDigits == parser.digits);
	assert(trueStrings == parser.strings);
}

void NoStartEndFuncTest()
{
	TokenParser parser;
	parser.SetDigitTokenCallback(Digit);
	parser.SetStringTokenCallback(String);
	string str = "\nf8312  8979r879 	03 38490923  \n sdf3efwf0  89787";
	parser.ParseIt(str);
}

void NoDigitFuncTest()
{
	TokenParser parser;
	parser.SetStartCallback(Start);
	parser.SetStringTokenCallback(String);
	parser.SetEndCallback(End);
	string str = "\nf8312  8979r879 	03 38490923  \n sdf3efwf0  89787";
	parser.ParseIt(str);
}

void NoDigitStringFuncTest()
{
	TokenParser parser;
	parser.SetStartCallback(Start);
	parser.SetEndCallback(End);
	string str = "\nf8312  8979r879 	03 38490923  \n sdf3efwf0  89787";
	parser.ParseIt(str);
}

int main()
{
	ParserTest();
	NoStartEndFuncTest();
	NoDigitFuncTest();
	NoDigitStringFuncTest();
}
