#ifndef SNIPPETMAKER_UTILS_H
#define SNIPPETMAKER_UTILS_H

#include "Includes.h"

using namespace SnippetMakerNamespace;

bool isAlpha(wchar_t symbol);

bool isEndOfSentence(wstring &word);

int getPrefWithoutPunctuationMarks(const wstring &word);

vector<int> chooseTopK(unordered_map<int, int> &sentWeights, const int K);

void toLowerCase(wstring &str);

#endif //SNIPPETMAKER_UTILS_H
