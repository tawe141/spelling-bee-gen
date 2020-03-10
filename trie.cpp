//
// Created by Eric on 3/9/2020.
//

#include "trie.h"

TrieNode::TrieNode(bool is_word) {
    this->is_word = is_word;
}

void TrieNode::add(std::string s) {
    if (!s.empty()) {
        char x = s[0];
        if (this->children.find(x) == this->children.end()) {
            this->children[x] = new TrieNode();
        }
        s.erase(0, 1);
        this->children[x]->add(s);
    }
    else {
        this->is_word = true;
    }
}

bool TrieNode::exists(std::string s) {
    if (s.empty()) {
        return this->is_word;
    }
    else {
        char x = s[0];
        auto search = this->children.find(x);
        if (search == this->children.end()) {
            return false;
        }
        else {
            s.erase(0, 1);
            return search->second->exists(s);
        }
    }
}
