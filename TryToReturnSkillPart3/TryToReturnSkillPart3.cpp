#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

class Lexem {

public:

    Lexem() {
        this->word = "";
        this->count = 0;
    }

    Lexem(std::string word) {
        this->word = word;
        this->count = 1;
    }

    void addCount() {
        ++this->count;
    }

    std::string getWord() {
        return word;
    }

    std::string getContent() {
        std::stringstream ss;
        ss << count;
        return word + " counts " + ss.str() + " times\n";
    }

    bool operator< (const Lexem& other) const {
        if (this->word < other.word) {
            return true;
        }
        return false;
    }

private:
    std::string word;
    int count;
};

void check_repeat_string_file() {
    std::ifstream fin;
    std::ofstream fon;
    std::vector<Lexem> vecLex;

    fin.open("input.txt");
    if (fin.is_open()) {
        std::string a;
        while (fin >> a) {
            auto iter = vecLex.begin();
            int count = 0;
            while (iter != vecLex.end())
            {
                Lexem& lex = *iter;
                if (lex.getWord() == a) {
                   lex.addCount();
                    break;
                }
                ++iter;
            }
            if (iter == vecLex.end()) {
                vecLex.push_back(a);
            }
        }
        std::sort(vecLex.begin(), vecLex.end(), [](const Lexem& a, const Lexem& b) {
            return a < b; });
        fin.close();
    }

    fon.open("output.txt");
    if (fon.is_open()) {
        auto iter = vecLex.begin();
        while (iter != vecLex.end()) {
            Lexem lex = *iter;
            fon << lex.getContent();
            ++iter;
        }
        fon.close();
    }
}


int main()
{
    check_repeat_string_file();
    return 0;
}