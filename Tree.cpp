#pragma once
#include <unordered_map>
#include <string>
#include <vector>

struct TrieNode {
    bool isEnd = false;
    std::unordered_map<char, TrieNode*> next;
};

class Trie {
public:
    Trie();
    void insert(const std::string& word);
    std::vector<std::string> searchPrefix(const std::string& prefix);

private:
    TrieNode* root;
    void dfs(TrieNode* node, std::string path, std::vector<std::string>& results);
};
