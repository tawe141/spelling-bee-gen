//
// Created by Eric on 3/9/2020.
//

#include "gtest/gtest.h"
#include "trie.h"


class TrieNodeTest : public testing::Test {
protected:
    void SetUp() override {
        this->list_of_words = {
                "friend",
                "foe",
                "folk",
                "first",
                "fern",
                "fix",
                "succinct"
        };

        for (const std::string &i : this->list_of_words) {
            this->root.add(i);
        }
    }
public:
    std::vector<std::string> list_of_words;
    TrieNode root;
};


TEST_F(TrieNodeTest, AddAndExists) {
    for (const std::string &i : this->list_of_words) {
        EXPECT_TRUE(root.exists(i));
    }
    EXPECT_FALSE(root.exists("succ"));
}

TEST_F(TrieNodeTest, Search) {
    std::set<char> mandatory = {'e'};
    std::set<char> auxiliary = {'f', 'o', 'r', 'i', 'n', 'd'};

    std::vector<std::string> search_results = this->root.search(mandatory, auxiliary);
    EXPECT_EQ(search_results.size(), 3);
}
