#include <bits/stdc++.h>
#include <regex>
using namespace std;

regex keywordRegex(R"((auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|using|unsigned|void|namespace|while|main|include)\b)");
regex operatorRegex(R"(\+\+|--|\+=|-=|=|/=|%=|==|!=|>=|<=|&&|\|\||!|=|\+|-|\|/|%)");
regex symbolRegex(R"([(){}\[\];,<>:.'"#\\])");
regex nameRegex(R"([a-zA-Z_][a-zA-Z0-9_]*)");
regex textRegex(R"(".*?")");
regex commentRegex(R"(//.*)");

map<string, pair<int, string>> tokenRegistry;
int uniqueID = 1;

void storeToken(const string &token, const string &category) {
    if (tokenRegistry.find(token) == tokenRegistry.end()) {
        tokenRegistry[token] = {uniqueID++, category};
    }
}

void analyzeCode(string source) {
    smatch found;
    string temp = source;
    
    cout << "Strings: ";
    while (regex_search(temp, found, textRegex)) {
        cout << found.str() << " ";
        storeToken(found.str(), "String");
        temp = found.suffix();
    }
    cout << endl;

    temp = source;
    cout << "Keywords: ";
    while (regex_search(temp, found, keywordRegex)) {
        cout << found.str() << " ";
        storeToken(found.str(), "Keyword");
        temp = found.suffix();
    }
    cout << endl;

    temp = source;
    cout << "Operators: ";
    while (regex_search(temp, found, operatorRegex)) {
        cout << found.str() << " ";
        storeToken(found.str(), "Operator");
        temp = found.suffix();
    }
    cout << endl;

    temp = source;
    cout << "Special Symbols: ";
    while (regex_search(temp, found, symbolRegex)) {
        cout << found.str() << " ";
        storeToken(found.str(), "Special Symbol");
        temp = found.suffix();
    }
    cout << endl;

    temp = source;
    cout << "Identifiers: ";
    while (regex_search(temp, found, nameRegex)) {
        if (!regex_match(found.str(), keywordRegex)) {
            cout << found.str() << " ";
            storeToken(found.str(), "Identifier");
        }
        temp = found.suffix();
    }
    cout << endl;

    cout << "\nSymbol Table:\n";
    cout << "| Symbol               | Type            | ID  |\n";
    for (const auto &entry : tokenRegistry) {
        cout << "| " << setw(20) << entry.first << " | " << setw(15) << entry.second.second << " | " << setw(3) << entry.second.first << " |\n";
    }
}

int main() {
    string filePath = "C:/Users/Dell/OneDrive - Aakash Educational Services Ltd/Desktop/6th SEM/prc7.cpp";
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Could not open file: " << filePath << endl;
        return 1;
    }
    string codeData, codeLine;
    while (getline(inputFile, codeLine))
        codeData += codeLine + " ";
    inputFile.close();
    analyzeCode(codeData);
    return 0;
}
