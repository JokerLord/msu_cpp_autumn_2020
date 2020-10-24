#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

class TokenParser
{
public:
	void (*StartCallback)();
	void (*DigitTokenCallback)(string);
	void (*StringTokenCallback)(string);
	void (*EndCallback)();
	vector<string> strings = {};
	vector<string> digits = {};

	TokenParser()
	{
		StartCallback = nullptr;
		DigitTokenCallback = nullptr;
		StringTokenCallback = nullptr;
		EndCallback = nullptr;
	}
	void SetStartCallback(void (*func)())
	{
		StartCallback = func;
	}
	void SetDigitTokenCallback(void (*func)(string))
	{
		DigitTokenCallback = func;
	}
	void SetStringTokenCallback(void (*func)(string))
	{
		StringTokenCallback = func;
	}
	void SetEndCallback(void (*func)())
	{
		EndCallback = func;
	}
	void ParseIt(string str)
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
			if (('0' <= ch) && (ch <= '9')) {
				curr += ch;
			} else if ((ch == ' ') || (ch == '\t') || (ch == '\n')) {
				if (curr.length() != 0) {
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
					curr = "";
					flag = false;
				}
			} else {
				flag = true;
				curr += ch;
			}
		}
		if (curr.length() != 0) {
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

void Digit(string digit)
{
	cout << "It's a digit token: " << digit << endl;
}

void String(string str)
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
	assert(parser.StartCallback != nullptr);
	parser.SetDigitTokenCallback(Digit);
	assert(parser.DigitTokenCallback != nullptr);
	parser.SetStringTokenCallback(String);
	assert(parser.StringTokenCallback != nullptr);
	parser.SetEndCallback(End);
	assert(parser.EndCallback != nullptr);
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
	assert(parser.StartCallback == nullptr);
	parser.SetDigitTokenCallback(Digit);
	parser.SetStringTokenCallback(String);
	assert(parser.EndCallback == nullptr);
	string str = "\nf8312  8979r879 	03 38490923  \n sdf3efwf0  89787";
	parser.ParseIt(str);
}

void NoDigitFuncTest()
{
	TokenParser parser;
	parser.SetStartCallback(Start);
	assert(parser.DigitTokenCallback == nullptr);
	parser.SetStringTokenCallback(String);
	parser.SetEndCallback(End);
	string str = "\nf8312  8979r879 	03 38490923  \n sdf3efwf0  89787";
	parser.ParseIt(str);
}

void NoDigitStringFuncTest()
{
	TokenParser parser;
	parser.SetStartCallback(Start);
	assert(parser.DigitTokenCallback == nullptr);
	assert(parser.StringTokenCallback == nullptr);
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
