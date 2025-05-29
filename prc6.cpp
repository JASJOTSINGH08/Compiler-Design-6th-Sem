#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <set>
using namespace std;

set<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", 
                        "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", 
                        "struct", "switch", "typedef", "using", "unsigned", "void", "namespace", "while", "main", "include"};
set<string> operators = {"+", "-", "*", "/", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "++", "--", "+=", "-=", "*=", "/=", "%="};
set<char> specialSymbols = {'(', ')', '{', '}', '[', ']', ';', ',', '<', '>', ':', '.', '"', '#', '\'', '\\'};

bool isInteger(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void processLine(const string& line) {
    vector<string> tokens;
    string token = "";
    bool inString = false;

    for (char c : line) {
        if (c == '"' || c == '\'') { 
            if (inString) {
                token += c;
                tokens.push_back(token);
                token = "";
                inString = false;
            } else {
                if (!token.empty()) tokens.push_back(token);
                token = c;
                inString = true;
            }
        } else if (inString) {
            token += c;
        } else if (isspace(c) || specialSymbols.count(c)) {
            if (!token.empty()) tokens.push_back(token);
            token = "";

            if (specialSymbols.count(c)) {
                string special(1, c);
                tokens.push_back(special);
            }
        } else if (ispunct(c)) {
            if (!token.empty()) tokens.push_back(token);
            token = c;
        } else {
            token += c;
        }
    }

    if (!token.empty()) tokens.push_back(token);

    for (const string& tok : tokens) {
        if (keywords.count(tok)) {
            cout << tok << " is a keyword\n";
        } else if (operators.count(tok)) {
            cout << tok << " is an operator\n";
        } else if (specialSymbols.count(tok[0]) && tok.size() == 1) {
            cout << tok << " is a special symbol\n";
        } else if (isInteger(tok)) {
            cout << tok << " is an integer constant\n";
        } else if (tok[0] == '"' || tok[0] == '\'') {
            cout << tok << " is a string constant\n";
        } else {
            cout << tok << " is an identifier\n";
        }
    }
}

int main() {
    ifstream file("C:/Users/Dell/OneDrive - Aakash Educational Services Ltd/Desktop/6th SEM/prc1.cpp"); 
    if (!file.is_open()) {
        cout << "Error: Could not open the file.\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        processLine(liNne);
    }

    file.close();
    return 0;
}
