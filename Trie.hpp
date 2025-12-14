#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Nodo del Trie
struct TrieNode {
    unordered_map<char, shared_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    shared_ptr<TrieNode> root;

    // Función auxiliar recursiva para buscar palabras
    void dfs(shared_ptr<TrieNode> node, string currentPrefix, vector<string>& results) {
        if (node->isEndOfWord) {
            results.push_back(currentPrefix);
        }
        for (auto& pair : node->children) {
            dfs(pair.second, currentPrefix + pair.first, results);
        }
    }

public:
    Trie() {
        root = make_shared<TrieNode>();
    }

    // Insertar una palabra
    void insert(const string& word) {
        shared_ptr<TrieNode> current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    
    // Busca todas las palabras que empiecen con 'prefix'
    vector<string> getWordsStartingWith(const string& prefix) {
        shared_ptr<TrieNode> current = root;
        vector<string> results;

        // 1. Navegar hasta el final del prefijo
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return results; // No hay coincidencias
            }
            current = current->children[ch];
        }

        // 2. Desde ahí, recolectar todas las palabras hijas
        dfs(current, prefix, results);
        return results;
    }
};

#endif // TRIE_HPP