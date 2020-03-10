//
// Created by Eric on 3/9/2020.
//

#ifndef SPELLING_BEE_GEN_TRIE_H
#define SPELLING_BEE_GEN_TRIE_H

#include <unordered_map>
#include <string>

class TrieNode {
public:
    bool is_word;
    std::unordered_map<char, TrieNode*> children;

    explicit TrieNode(bool is_word = false);
    void add(std::string s);
    bool exists(std::string s);
};

class Trie {
private:
    TrieNode root;

public:
    Trie();
};


#endif //SPELLING_BEE_GEN_TRIE_H
