#include "SnippetMaker.h"
#include "../Util/Utils.h"

SnippetMaker::SnippetMaker(wifstream &input, int _MAX_SENTENCES_COUNT_FOR_OUTPUT) : MAX_SENTENCES_COUNT_FOR_OUTPUT(
        _MAX_SENTENCES_COUNT_FOR_OUTPUT) {
    DataPreparator dataPreparator(input);
    frequency = dataPreparator.getFrequency();
    sentencesWithThisWord = dataPreparator.getSentWithThisWord();
    sentences = dataPreparator.getSentences();
}

vector<vector<wstring>> SnippetMaker::handleQuery(wstring query) const {
    vector<wstring> words = parseQuery(query);
    unordered_map<int, int> sentWeights;
    for (auto word : words) {
        if (!sentencesWithThisWord.count(word)) continue;
        for (auto sent : sentencesWithThisWord.at(word)) {
            if (!frequency.count(word)) continue;
            sentWeights[sent] += frequency.at(word);
        }
    }
    vector<int> chosenSent = chooseTopK(sentWeights, MAX_SENTENCES_COUNT_FOR_OUTPUT);
    vector<vector<wstring>> response;
    for (auto sent : chosenSent) {
        response.push_back(sentences[sent]);
    }
    return response;
}

vector<wstring> SnippetMaker::parseQuery(wstring query) const {
    vector<wstring> words;
    int spacePos = -1;
    while ((spacePos = query.find(' ')) != wstring::npos) {
        words.push_back(query.substr(0, spacePos));
        while (words.back().length() > 0 && !isAlpha(words.back().back())) {
            words.back().pop_back();
        }
        if (words.back().empty()) words.pop_back();
        query.erase(0, spacePos);
        if (query.length() && query[0] == ' ') query.erase(0, 1);
    }
    if (query.length()) words.push_back(query);
    for (auto &word : words) {
        toLowerCase(word);
    }
    return words;
}