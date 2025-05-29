#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <vector>

using namespace std;

const regex keyword_regex(R"(\b(int|float|double|char|bool|void|if|else|switch|case|for|while|do|break|continue|return|class|struct|public|private|protected|namespace|using|virtual|inline|new|delete|try|catch|throw|const|static|volatile|this|friend|operator|sizeof|typedef|enum|union|template|default|goto|register|extern)\b)");
const regex identifier_regex(R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)");

struct Symbol {
    string tokenType;
    string value;
};

unordered_map<string, vector<Symbol>> symbolTable;

void processFile(const string &filename) {
    ifstream file(filename);
    if (!file) return;

    string line;
    while (getline(file, line)) {
        sregex_iterator iter(line.begin(), line.end(), keyword_regex), end;
        while (iter != end) {
            string keyword = iter->str();
            symbolTable[keyword].push_back({"Keyword", keyword});
            ++iter;
        }
        
        iter = sregex_iterator(line.begin(), line.end(), identifier_regex);
        while (iter != end) {
            string identifier = iter->str();
            if (!regex_match(identifier, keyword_regex)) {
                symbolTable[identifier].push_back({"Identifier", identifier});
            }
            ++iter;
        }
    }
    file.close();
}

void ShowSymbolTable() {
    for (const auto &entry : symbolTable) {
        for (const auto &symbol : entry.second) {
            cout << symbol.tokenType << " : " << symbol.value << endl;
        }
    }
}

int main() {
    string filename = "C:/Users/Dell/OneDrive - Aakash Educational Services Ltd/Desktop/6th SEM/prc7.cpp"; 
    processFile(filename);
    ShowSymbolTable();
    return 0;
}
