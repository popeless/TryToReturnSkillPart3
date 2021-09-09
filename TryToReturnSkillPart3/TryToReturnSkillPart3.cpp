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
        return this->word < other.word;
    }

    bool operator< (const std::string& other) const {
        return this->word < other;
    }

    bool operator> (const Lexem& other) const {
        return this->word > other.word;
    }

    bool operator== (const Lexem& other) const {
        return this->word == other.word;
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
            auto it = std::lower_bound(
                vecLex.begin(),
                vecLex.end(),
                a,
                [](const Lexem& l, const std::string& r) { return l < r; });
            if (it != vecLex.end() && *it == a) {
                it->addCount();
            }
            else {
                vecLex.insert(it, a);
            }
        }
        fin.close();
    }

    fon.open("output.txt");
    if (fon.is_open()) {
        auto iter = vecLex.begin();
        while (iter != vecLex.end()) {
            fon << iter->getContent();
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