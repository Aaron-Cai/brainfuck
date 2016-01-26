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
		NORMAL, LOOP_END, ERROR
	};

	Interpreter(bool de = false)
	{
		byte = new char[byteSize];
		memset(byte, 0, byteSize*sizeof(char));
		pointer = byte;
		debug = de;
	}
	~Interpreter()
	{
		delete[]byte;
	}

	InterpretingState interpreter(char opr)
	{
		InterpretingState state = NORMAL;
		try
		{
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
				throw exception("Invalid operator");
			}
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
			cout << "$ ";
		}
		return state;
	}

	void ScanCode(string code)
	{
		size_t i = 0;
		try
		{
			while (i < code.size())
			{
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
									throw exception("Syntax error");
							}
						else
							i++;
					}
				}
			}
			if (debug)
			{
				display();
			}
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
		}

	}

	void display() //
	{
		cout << "\n\n";
		for (size_t i = 0; i < 20; i++)
		{
			cout << (int)byte[i] << " ";
		}
		cout << "\n";
		int pos = pointer - byte;
		for (int i = 0; i < pos-1; i++)
		{
			cout << "  ";
		}
		cout << "^\n$ ";
	}

	void SwitchDebugState()
	{
		debug = !debug;
	}

private:
	char* byte;
	char* pointer;
	bool debug = false;
};

int main(int argc, char** argv)
{
	const string version = "0.9.0";
	if (argc == 1)	//interactor mode
	{
		cout << "Brainfuck " << version << ". ";
		cout << "Type \"help\", \"copyright\" for more information.\n";
		cout << "To quit, press CTRL+Z\n";
		cout << "$ ";
		Interpreter in(true);
		string code;
		while (cin >> code)
		{
			if (code == "help")
			{
				string info = "> increment the data pointer (to point to the next cell to the right).\n< decrement the data pointer(to point to the next cell to the left).\n+ increment(increase by one) the byte at the data pointer.\n- decrement(decrease by one) the byte at the data pointer.\n. output the byte at the data pointer.\n, accept one byte of input, storing its value in the byte at the data pointer.\n[ if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching] command.\n] if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.\n";
				cout << info << "$ ";
				continue;
			}
			cout << "$ ";
			in.ScanCode(code);

		}

	}
	else if (argc == 2)
	{
		string arg = argv[1];
		if (arg == "-v")
		{
			cout << "Brainfuck version: " << version << "\n";
		}
		else
		{
			ifstream fin(arg);
			string code;

			Interpreter in;

			while (fin >> code)//todo some bug when exec file
			{
				cout << code << endl;
				in.ScanCode(code);
			}
		}
	}

	return 0;
}