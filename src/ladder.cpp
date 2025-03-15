#include "ladder.h"
#include <fstream>

void error(string word1, string word2, string msg) {std::cerr << word1 << ' ' << word2 << ": " << msg << std::endl;}

int diff_chars(const std::string& str1, const std::string& str2, int n) {
    int cnt = 0;
    for (int i=0; i < n; ++i) {
        if (str1[i] != str2[i]) ++cnt;
    }
    return cnt;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int m = str1.size();
    int n = str2.size();

    if (abs(n-m) > d) return false;
    if (n == m) return diff_chars(str1, str2, n) <= d;
    
    int prev; 
    vector<int> curr(n + 1, 0); 

    for (int j = 0; j <= n; j++)
        curr[j] = j;
  
    for (int i = 1; i <= m; i++) {
        prev = curr[0]; 
        curr[0] = i;
        for (int j = 1; j <= n; j++) {
            int temp = curr[j];
            if (str1[i - 1] == str2[j - 1])
                curr[j] = prev;
            else
                curr[j] = 1 + min({curr[j - 1], prev, curr[j]});
            prev = temp;
        }
    }
    
    return curr[n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {return edit_distance_within(word1, word2, 1);}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // if target word not a word in dict or target word = input word, return empty ladder
    if (begin_word == end_word) return {};
    if (word_list.find(end_word) == word_list.end()) return {};

    std::queue<std::vector<std::string>> ladder_queue;
    ladder_queue.push({begin_word});
    std::set<std::string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        std::vector<std::string> ladder = ladder_queue.front();
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