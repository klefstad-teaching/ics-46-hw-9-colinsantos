#include "ladder.h"

void error(string word1, string word2, string msg) {
    std::cout << "Error: Words " << word1 << ", " << word2 << ": " << msg << std::endl;
}

bool is_adjacent(const string& word1, const string& word2) {
    int diff = 0;
    int word1len = word1.length();
    int word2len = word2.length();

    if (word1 == word2 || word1len > word2len + 1 || word2len > word1len + 1) {
        return false;
    }

    if (word1len == word2len) {
        for (int i = 0; i < word1len; ++i) {
            if (word1[i] != word2[i]) {
                ++diff;

                if (diff > 1) {
                    return false;
                }
            }
        }
    } else {
        int i = 0;
        int j = 0;

        while (i < word1len && j < word2len) {
            if (word1[i] != word2[j]) {
                ++diff;

                if (diff > 1) {
                    return false;
                }

                if (word1len > word2len) {
                    ++i;
                } else if (word1len < word2len) {
                    ++j;
                }
            } else {
                ++i;
                ++j;
            }
        }

        if (i < word1len || j < word2len) {
            ++diff;
        }
    }

    return diff == 1;
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    std::queue<vector<string>> ladder_queue;

    std::vector<string> v;
    v.push_back(begin_word);

    ladder_queue.push(v);

    std::set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        std::vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        std::string last_word = ladder.back();

        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    std::vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    return std::vector<string>();
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);

    for (string word; (in >> word);) {
        word_list.insert(word);
    }

    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (string s : ladder) {
        std::cout << s << endl;
    }
}