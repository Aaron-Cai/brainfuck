#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;

const unsigned byteSize = 30000;

class Interpreter
{
public:
	enum InterpretingState
	{
		NORMAL,LOOP_END,ERROR
	};
	
	Interpreter() 
	{
		byte = new char[byteSize];
		memset(byte, 0, byteSize*sizeof(char));
		pointer = byte;
	}
	~Interpreter() 
	{
		delete []byte;
	}
	
	InterpretingState interpreter(char opr)
	{
		InterpretingState state = NORMAL;
		switch (opr)
		{
		case '>':
			if (pointer < byte + byteSize)
			{
				pointer++;
			}
			break;
		case '<':
			if (pointer > byte)
			{
				pointer--;
			}
			else
			{
				throw("error");
			}
			break;
		case '+':
			(*pointer)++;
			break;
		case '-':
			(*pointer)--;
			break;
		case '.':
			cout << (*pointer);
			break;
		case ',':
			cout << "Please input a value... ";
			cin >> (*pointer);
			break;
		default:
			break;
		}
		//cout << opr << "\t";
		//display();
		return state;
	}

	void ScanCode(string code)
	{
		size_t i = 0;
		while(i < code.size())
		{
			//cout << i << ":   ";
			if (code[i] != '[' && code[i] != ']') 
			{
				interpreter(code[i]);
				i++;
			}
			else
			{
				if (*pointer == 0)
				{
					if (code[i] == ']')
						i++;
					else
					{
						while (code[i] != ']')i++;
						i++;
					}
				}
				else
				{
					if (code[i] == ']')
						while (code[i] != '[')
						{
							i--;
							if (i < 0)
								throw("syntax error");
						}
					else
						i++;
				}
			}
		}
	}

	void display()
	{
		for (size_t i = 0; i < 20; i++)
		{
			cout << (int)byte[i] << " ";
		}
		cout << "\t" << pointer - byte << endl;
	}


private:
	char* byte;
	char* pointer;
};


int main(int argc, char** argv)
{
	Interpreter in;
	string code = "++++++++++[>+++>++++>+++++++>++++++++++>+++++++++++<<<<<-]>>>++.>---.>++..+++++++++.<<<<++.>>>>-----------.---------.++++++++++++++++++.<<<<.>>>>++.<++++.----.>-------.<<<++++.<.>>>++++++.>---.<---.>++++.<<<<.>>>--.++++++++++.-------.>..<<<<.>>>>+.<+++.---.<<<.>>+++.>>+++.<<<+++++++..>>>---------.<<<<+.";
	try
	{
		in.ScanCode(code);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}