#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void printMessage();
void interactiveMode();
void modifyPointer(string c);
void printTape();
void compileCPlusPlus(string s);
void runCrazyProgram(string s);
const int SIZE = 1000;
int tape[SIZE] = {0};
int *dp = &tape[0];
int index = 0;

int main(int argc, char *argv[]) {
	string arg;
	string arg2;
	if(argc == 3) {
		arg = argv[1];
		arg2 = argv[2];
		if(arg == "-e") {
			runCrazyProgram(arg2);
		} else if(arg == "-c") {
			compileCPlusPlus(arg2);
		}
	} else {
		interactiveMode();
	}

	return 0;
}

void compileCPlusPlus(string s) {

    ofstream fout(s);

    fout << "#include <iostream>" << "\n";
    fout << "const int SIZE = 1000;" << "\n";
    fout << "int tape[SIZE] = {0};" << "\n";
    fout << "int *dp = &tape[0];" << "\n";
    fout << "int index = 0;" << "\n\n";
    fout << "int main() {" << "\n";

    fstream f("fact.cz", fstream::in);
    string contents;
    getline(f,contents,'\0');

    for(int i = 0; i < contents.length(); i++) {
    	char c = contents[i];

        if(c == '+') {
            fout << "   *dp = *dp + 1;" << "\n";
        } else if(c == '-') {
            fout << "   *dp = *dp - 1;" << "\n";
        } else if(c == '>') {
            fout << "   index = index + 1;" << "\n";
            fout << "   dp = &tape[index];" << "\n";
        } else if(c == '<') {
            fout << "   index = index - 1;" << "\n";
            fout << "   dp = &tape[index];" << "\n";
        } else if(c == ':') {
            fout << "   std::cout << \"Int Value:\" << *dp << \"\\n\";" << "\n";
        } else if(c == '.') {
            fout << "   std::cout << \"Int Char:\" << (char)*dp << \"\\n\";"
	    	<< "\n";
        } else if(c == '{') {
            fout << "   while(*dp != 0) {" << "\n";
        } else {
            //Symbol must be '}'
            //Ensures the for loop runs with the closed bracket.
            fout << "   }" << "\n";
        }
    }

    fout << "   return 0;" << "\n";
    fout << "}";

    cout << "\nWritten to file successful!" << "\n";
}

void runCrazyProgram(string s) {

    fstream f(s.c_str());
    string contents;
    getline(f,contents,'\0');

    modifyPointer(contents);
}

void printMessage() {

    cout << "Enter Crazy Character(s): " << "\n"
        << "+ - > < : . { }" << "\n";

}

void interactiveMode() {

    string firstSymbol;
    printMessage();
    cin >> firstSymbol;
    cout << "\n";

    while(firstSymbol[0] == '+' || firstSymbol[0] == '-' || firstSymbol[0] == '>'||
        firstSymbol[0] == '<' || firstSymbol[0] == ':' ||
        firstSymbol[0] == '.' || firstSymbol[0] == '{' ||
        firstSymbol[0] == '}') {

        modifyPointer(firstSymbol);
        printTape();

        cin >> firstSymbol;
        cout << "\n";
    }
}

void modifyPointer(string str) {

    int depth = 0;

    for(int i = 0; i < str.length(); i++) {

        if(str[i] == '+') {

            *dp = *dp + 1;

        } else if(str[i] == '-') {

            *dp = *dp - 1;

        } else if(str[i] == '>') {

            index = index + 1;

            if(index > 1000) {
                index == 1000;
            }

            dp = &tape[index];

        } else if(str[i] == '<') {

            index = index - 1;

            if(index < 0) {
                index == 0;
            }

            dp = &tape[index];

        } else if(str[i] == ':') {

            cout << "Int Value: " << *dp << "\n\n";

        } else if(str[i] == '.') {

            cout << "Int Char: " << (char)*dp << "\n\n";

        } else if(str[i] == '{') {

            //must be 0
            if(*dp == 0) {
                i++;
                while(depth > 0 || str[i] != '}') {
                    if(str[i] == '{') {
                        depth++;
                    }
                    if(str[i] == '}') {
                        depth--;
                    }
                    i++;
                }
            }

        } else if(str[i] == '}') {
            //if zero, do not go back to corresponding brace
            if(*dp != 0) {
                i--;
                while(depth > 0 || str[i] != '{') {
                    if(str[i] == '}') {
                        depth++;
                    }
                    if(str[i] == '{') {
                        depth--;
                    }
                    i--;
                }
            }

        }
    }
}

void printTape() {

    int start = 0;
    int endLoop = 1000;

    if(index <= 8) {
        start = 0;
    } else {
        start = index;
    }

    if(index >= 992) {
        start = 992;
    }

    for(int i = start; i <= endLoop; i++) {
       if(i <= start + 8) {
            cout << setw(5) << i;
       }
    }

    cout << "\n";

    for(int i = start; i <= endLoop; i++) {
        if(i <= start + 8) {
            cout << setw(5) << *(tape + i);
        }
    }

    cout << "\n";

    int count = 0;

    for(int i = start; i <= endLoop; i++) {
        if(i <= start + 8) {
            count++;
            if(&tape[i] == dp) {
                int w;
                if(i == 0) {
                    w = 5;
                } else {
                    w = count * 5;
                }
                cout << setw(w) << "^";
            } else {
                cout << setw(5);
            }
        }
    }

    cout << "\n";
}
