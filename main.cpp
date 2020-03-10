//
// Created by Eric on 3/9/2020.
//

#include "trie.h"
#include <iostream>
#include <fstream>
#include <string>


int main() {
    TrieNode root;

    std::string tmp;
    std::ifstream in("../english-words/words_alpha.txt");
    while (std::getline(in, tmp)) {
        // pop_back once to get rid of '\r'
        tmp.pop_back();
        root.add(tmp);
    }
    if (root.exists("truck")) {
        std::cout << "Found truck" << std::endl;
    }
    else {
        std::cout << "truck not found" << std::endl;
    }
}
