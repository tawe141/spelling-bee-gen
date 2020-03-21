//
// Created by Eric on 3/9/2020.
//

#ifndef SPELLING_BEE_GEN_TRIE_H
#define SPELLING_BEE_GEN_TRIE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

class TrieNode {
private:
    bool is_word;
    std::unordered_map<char, TrieNode*> children;
    static bool satisfies_mandatory(const std::string &word, const std::set<char> &mandatory);
    void search_helper(
            const std::set<char> &mandatory,
            const std::set<char> &auxiliary,
            std::vector<std::string> *storage,
            const uint8_t depth_limit,
            const std::string &word,
            uint8_t depth = 1
    );
public:
    explicit TrieNode(bool is_word = false);
    explicit TrieNode(std::vector<std::string> &v);
    void add(std::string s);
    bool exists(std::string s);
    std::vector<std::string> search(
            const std::set<char> &mandatory,
            const std::set<char> &auxiliary,
            const uint8_t depth_limit = 15
                    );
};


#endif //SPELLING_BEE_GEN_TRIE_H
