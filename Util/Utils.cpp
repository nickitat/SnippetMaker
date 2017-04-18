#include "Utils.h"

#include <set>

using std::set;

bool isAlpha(wchar_t symbol) {
    static const std::locale loc("C");
    return std::isalpha(symbol, loc);
}

void toLowerCase(wchar_t &symbol) {
    static const std::locale loc("C");
    if (isAlpha(symbol)) {
        symbol = tolower(symbol, loc);
    }
}

bool isEndOfSentence(wstring &word) {
    return word.back() == '.' || word.back() == '!' || word.back() == '?';
}

int getPrefWithoutPunctuationMarks(const wstring &word) {
    int last = (int) word.length() - 1;
    while (last >= 0 && !isAlpha(word[last])) {
        --last;
    }
    return last;
}

vector<int> chooseTopK(unordered_map<int, int> &sentWeights, const int K) {
    set<pair<int, int>> best;
    for (auto entry : sentWeights) {
        best.insert(std::make_pair(entry.second, entry.first));
        if (best.size() > K) {
            best.erase(--best.end());
        }
    }
    vector<int> res;
    for (auto entry : best) {
        res.push_back(entry.second);
    }
    return res;
}

void toLowerCase(wstring &str) {
    for (auto &ch : str) {
        toLowerCase(ch);
    }
}