#include "ladder.h"

void error(string word1, string word2, string msg) {
    std::cout << "Error: Words " << word1 << ", " << word2 << ": " << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int diff = 0;
    int word1len = str1.length();
    int word2len = str2.length();

    if (abs(word1len - word2len) > d) {
        return false;
    }

    if (str1 == str2) {
        return true;
    }

    if (word1len == word2len) {
        for (int i = 0; i < word1len; ++i) {
            if (str1[i] != str2[i]) {
                ++diff;

                if (diff > d) {
                    return false;
                }
            }
        }
    } else {
        int i = 0;
        int j = 0;

        while (i < word1len && j < word2len) {
            if (str1[i] != str2[j]) {
                ++diff;

                if (diff > d) {
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

    return diff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Cannot be the same words");
        return std::vector<string>();
    }

    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "Cannot find second word in dictionary");
        return std::vector<string>();
    }

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
        std::cout << s << " ";
    }

    std::cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}