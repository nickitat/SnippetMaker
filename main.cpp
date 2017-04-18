#include "SnippetMaker/SnippetMaker.h"

using namespace SnippetMakerNamespace;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Path to the input file was not specified." << endl;
        return 1;
    }
    std::string path = argv[1];

    setlocale(0, "");
    wcout << std::fixed << std::setprecision(3);

    wifstream inputFile(path);
    if (inputFile.is_open()) {
        auto start = clock();
        SnippetMaker snippetMaker(inputFile);
        auto end = clock();
        wcout << "SnippetMaker() time: " << (double) (end - start) / (double) CLOCKS_PER_SEC << endl;
        while (true) {
            wstring query;
            getline(wcin, query, (wchar_t) '\n');
            if (!query.empty()) {
                start = clock();
                auto response = snippetMaker.handleQuery(query);
                end = clock();
                wcout << "SnippetMaker::handleQuery() time: " << (double) (end - start) / (double) CLOCKS_PER_SEC
                      << endl;
                wcout << "Response: " << endl;
                for (auto sentence : response) {
                    for (auto word : sentence) {
                        wcout << word << " ";
                    }
                    wcout << endl;
                }
            }
            else {
                return 0;
            }
        }
        inputFile.close();
    }
    else {
        cerr << "Incorrect path to the file" << endl;
        return 1;
    }
    return 0;
}