//
// Created by Eric on 3/9/2020.
//

#include "trie.h"
#include <iostream>


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

bool TrieNode::satisfies_mandatory(const std::string &word, const std::set<char> &mandatory) {
    for (const char &i : mandatory) {
        if (word.find(i) == std::string::npos) {
            return false;
        }
    }
    return true;
}

void TrieNode::search_helper(
        const std::set<char> &mandatory,
        const std::set<char> &auxiliary,
        std::vector<std::string> *storage,
        const uint8_t depth_limit,
        const std::string &word,
        uint8_t depth
) {
//    std::cout << word << std::endl;

    if (depth <= depth_limit) {
        if (this->is_word && this->satisfies_mandatory(word, mandatory)) {
            storage->push_back(word);
        }
        // ugly; should really be only one for loop, but why waste time and memory combining two sets?
        for (const char &i : mandatory) {
            if (this->children.find(i) != this->children.end()) {
                std::string new_word = word;
                new_word.push_back(i);
                this->children[i]->search_helper(mandatory, auxiliary, storage, depth_limit, new_word, depth + 1);
            }
        }
        for (const char &i : auxiliary) {
            if (this->children.find(i) != this->children.end()) {
                std::string new_word = word;
                new_word.push_back(i);
                this->children[i]->search_helper(mandatory, auxiliary, storage, depth_limit, new_word, depth + 1);
            }
        }
    }
}

std::vector<std::string> TrieNode::search(
        const std::set<char> &mandatory,
        const std::set<char> &auxiliary,
        const uint8_t depth_limit
        ) {
    std::vector<char> common;
    std::set_intersection(mandatory.begin(), mandatory.end(), auxiliary.begin(), auxiliary.end(), std::back_inserter(common));
    if (!common.empty()) {
        throw std::invalid_argument("Mandatory and auxiliary letters share common letters.");
    }

    std::vector<std::string> storage;
    std::string word_init;

    this->search_helper(mandatory, auxiliary, &storage, depth_limit, word_init);

    return storage;
}
