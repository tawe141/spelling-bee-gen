//
// Created by Eric on 3/9/2020.
//

#include "gtest/gtest.h"
#include "trie.h"


TEST(TrieNode, AddAndSearch) {
    std::vector<std::string> list_of_words = {
            "friend",
            "foe",
            "folk",
            "first",
            "fern",
            "fix",
            "succinct"
    };

    TrieNode root;

    for (const std::string &i : list_of_words) {
        root.add(i);
    }

    for (const std::string &i : list_of_words) {
        EXPECT_TRUE(root.exists(i));
    }
    EXPECT_FALSE(root.exists("succ"));
}
