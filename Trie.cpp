#include "Trie.hpp"

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    TrieNode* cur = root;
    for (char c : word) {
        if (!cur->next[c])
            cur->next[c] = new TrieNode();
        cur = cur->next[c];
    }
    cur->isEnd = true;
}

void Trie::dfs(TrieNode* node, std::string path, std::vector<std::string>& res) {
    if (node->isEnd) res.push_back(path);
    for (auto& p : node->next)
        dfs(p.second, path + p.first, res);
}

std::vector<std::string> Trie::searchPrefix(const std::string& prefix) {
    TrieNode* cur = root;
    for (char c : prefix) {
        if (!cur->next.count(c)) return {};
        cur = cur->next[c];
    }
    std::vector<std::string> result;
    dfs(cur, prefix, result);
    return result;
}
