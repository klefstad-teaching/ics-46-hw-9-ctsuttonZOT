#include "ladder.h"
#include <fstream>
#include <unordered_set>

void error(string word1, string word2, string msg) {std::cerr << word1 << ' ' << word2 << ": " << msg << std::endl;}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int m = str1.length();
    int n = str2.length();

    // if diff in length is larger than threshold, must be false
    if (abs(n-m) > d) return false;

    int prev; 
    vector<int> curr(n + 1, 0); 

    for (int j = 0; j <= n; j++)
        curr[j] = j;
  
    for (int i = 1; i <= m; i++) {
        prev = curr[0]; 
        curr[0] = i;
        int min_in_row = curr[0];
        for (int j = 1; j <= n; j++) {
            int temp = curr[j];
            if (str1[i - 1] == str2[j - 1])
                curr[j] = prev;
            else
                curr[j] = 1 + min({curr[j - 1], prev, curr[j]});
            prev = temp;
            min_in_row = min(min_in_row, curr[j]);
        }
        if (min_in_row > d) return false;
    }
    
    return curr[n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {return edit_distance_within(word1, word2, 1);}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    std::queue<std::vector<std::string>> ladder_queue;
    ladder_queue.push({begin_word});
    std::unordered_set<std::string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        auto ladder = ladder_queue.front();
        ladder_queue.pop();
        std::string last_word = ladder.back();
        for (std::string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    auto new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    std::string word;
    while (getline(file, word))
        word_list.insert(word);
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) 
        std::cout << "No word ladder found.\n";
    else {
        std::cout << "Word ladder found: ";
        for (auto word : ladder) std::cout << word << ' ';
        std::cout << std::endl;
    }
}