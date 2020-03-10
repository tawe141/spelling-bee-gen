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
//    if (root.exists("truck")) {
//        std::cout << "Found truck" << std::endl;
//    }
//    else {
//        std::cout << "truck not found" << std::endl;
//    }
    // March 10, 2020 game has a mandatory letter L and auxiliary letters D, T, Y, I, Q, and U
    std::set<char> mandatory = {'l'};
    std::set<char> auxiliary = {'d', 't', 'y', 'i', 'q', 'u'};
    std::vector<std::string> search_results = root.search(mandatory, auxiliary);
    for (std::string &s : search_results) {
        std::cout << s << std::endl;
    }
}
