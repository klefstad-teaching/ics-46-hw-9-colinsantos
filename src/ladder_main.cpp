#include "ladder.h"

int main() {
    string word1;
    string word2;

    std::cout << "First: ";
    std::cin >> word1;
    
    std::cout << "Second: ";
    std::cin >> word2;

    if (word1 == word2) {
        error(word1, word2, "Cannot be the same words");
        return 0;
    }

    set<string> word_list;

    load_words(word_list, "words.txt");

    if (word_list.find(word2) == word_list.end()) {
        error(word1, word2, "Cannot find second word in dictionary");
        return 0;
    }

    vector<string> ladder = generate_word_ladder(word1, word2, word_list);

    print_word_ladder(ladder);

    return 0;
}