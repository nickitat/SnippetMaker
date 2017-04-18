#include "DataPreparator.h"
#include "../Util/Utils.h"

DataPreparator::DataPreparator(wifstream &input, int _MAX_SENTENCES_COUNT) : MAX_SENTENCES_COUNT(_MAX_SENTENCES_COUNT) {
    auto start = clock();
    parseSentences(input);
    auto end = clock();
    std::wcout << "Parse sentences time: " << (double) (end - start) / (double) CLOCKS_PER_SEC << std::endl;

    start = clock();
    buildFrequency();
    end = clock();
    std::wcout << "Build frequency time: " << (double) (end - start) / (double) CLOCKS_PER_SEC << std::endl;

    start = clock();
    buildSentWithThisWord();
    end = clock();
    std::wcout << "Build sentWithThisWord time: " << (double) (end - start) / (double) CLOCKS_PER_SEC << std::endl;
}

void DataPreparator::parseSentences(wifstream &input) {
    sentences.push_back(vector<wstring>());
    try {
        wstring word;
        while (input >> word) {
            toLowerCase(word);
            sentences.back().push_back(word);
            if (isEndOfSentence(word)) {
                sentences.push_back(vector<wstring>());
            }
        }
        sentences.pop_back();
    }
    catch (std::exception &e) {
        std::wcout << "We can not read anything from the given file." << std::endl;
        std::wcout << "Exception details: " << e.what() << std::endl;
    }
}

void DataPreparator::buildFrequency() {
    for (auto sent : sentences) {
        for (auto word : sent) {
            int properPref = getPrefWithoutPunctuationMarks(word);
            if (properPref < 0) continue;
            if (properPref != word.length() - 1) { // it's rare case when we works slower
                frequency[word.substr(0, properPref + 1)]++;
            }
            else {
                frequency[word]++;
            }
        }
    }
}

void DataPreparator::buildSentWithThisWord() {
    vector<int> sentWeights;
    calcSentencesWeights(sentWeights);
    for (int i = 0; i < sentences.size(); ++i) {
        for (auto word : sentences[i]) {
            int properPref = getPrefWithoutPunctuationMarks(word);
            if (properPref < 0) continue;
            if (properPref != word.length() - 1) {
                sentWithThisWord[word.substr(0, (size_t) properPref + 1)].push_back(i);
            }
            else {
                sentWithThisWord[word].push_back(i);
            }
            if (sentWithThisWord[word].size() >= 2 * MAX_SENTENCES_COUNT) {
                vector<int> &tmp = sentWithThisWord[word];
                std::sort(tmp.begin(), tmp.end(),
                          [&](int i, int j) -> bool { return sentWeights[i] < sentWeights[j]; });
                tmp.resize(MAX_SENTENCES_COUNT);
            }
        }
    }
}

void DataPreparator::calcSentencesWeights(vector<int> &sentWeights) {
    sentWeights.assign(sentences.size(), 0);
    for (int i = 0; i < sentences.size(); ++i) {
        for (auto word : sentences[i]) {
            int properPref = getPrefWithoutPunctuationMarks(word);
            if (properPref < 0) continue;
            if (properPref != word.length() - 1) { // it's rare case when we works slower
                sentWeights[i] += frequency[word.substr(0, (size_t) properPref + 1)]++;
            }
            else {
                sentWeights[i] += frequency[word]++;
            }
        }
    }
}

unordered_map<wstring, int> DataPreparator::getFrequency() const {
    return frequency;
}

unordered_map<wstring, vector<int>> DataPreparator::getSentWithThisWord() const {
    return sentWithThisWord;
}

vector<vector<wstring>> DataPreparator::getSentences() const {
    return sentences;
}
