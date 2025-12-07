// Trie.hpp
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

// Estructura básica que Geovanny debería implementar
class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }
    
    // Función para insertar una palabra
    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }
    
    // (Geovanny agregará búsqueda y autocompletado después)
};