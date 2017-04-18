#ifndef SNIPPETMAKER_DATAPREPARATOR_H
#define SNIPPETMAKER_DATAPREPARATOR_H

#include "../Util/Includes.h"

namespace SnippetMakerNamespace {

    class DataPreparator {

    public:

        DataPreparator(wifstream &input, int _MAX_SENTENCES_COUNT = 50);

        vector<vector<wstring>> getSentences() const;

        unordered_map<wstring, int> getFrequency() const;

        unordered_map<wstring, vector<int>> getSentWithThisWord() const;

    private:

        const int MAX_SENTENCES_COUNT; // just random constant was chosen for simplicity

        vector<vector<wstring>> sentences;
        unordered_map<wstring, int> frequency;
        unordered_map<wstring, vector<int>> sentWithThisWord;

        void buildFrequency();

        void buildSentWithThisWord();

        void parseSentences(wifstream &input);

        void calcSentencesWeights(vector<int> &sentWeights);

    };

}

#endif //SNIPPETMAKER_DATAPREPARATOR_H
