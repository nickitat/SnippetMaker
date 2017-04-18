#ifndef SNIPPETMAKER_SNIPPETMAKER_H
#define SNIPPETMAKER_SNIPPETMAKER_H

#include "../Util/Includes.h"
#include "DataPreparator.h"

namespace SnippetMakerNamespace {

    class SnippetMaker {

    public:

        SnippetMaker(wifstream &input, int _MAX_SENTENCES_COUNT_FOR_OUTPUT = 5);

        vector<vector<wstring>> handleQuery(wstring query) const;

        vector<wstring> parseQuery(wstring query) const;

    private:

        const int MAX_SENTENCES_COUNT_FOR_OUTPUT;

        vector<vector<wstring>> sentences;
        unordered_map<wstring, int> frequency;
        unordered_map<wstring, vector<int>> sentencesWithThisWord;

    };

}

#endif //SNIPPETMAKER_SNIPPETMAKER_H