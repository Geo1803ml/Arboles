#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

    //  Función privada auxiliar:
    // Una vez que llegamos al prefijo, bajamos recursivamente para encontrar todas las terminaciones posibles
    void collectWords(TrieNode* node, std::string currentPrefix, std::vector<std::string>& results) {
        if (node->isEndOfWord) {
            results.push_back(currentPrefix);
        }
        for (auto const& [key, val] : node->children) {
            collectWords(val, currentPrefix + key, results);
        }
    }

public:
    Trie() { root = new TrieNode(); }

    // Insertar (Día 5)
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

    //  Buscar por Prefijo (Día 6)
    std::vector<std::string> getWordsStartingWith(const std::string& prefix) {
        TrieNode* current = root;
        std::vector<std::string> results;

        // 1. Navegar hasta el final del prefijo (ej: si busco "do", camino 'd' -> 'o')
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return results; // Si el prefijo no existe, devolvemos lista vacía
            }
            current = current->children[ch];
        }

        // 2. Desde ese punto, recolectar todo lo que haya abajo ("docs", "documento", "domingo")
        collectWords(current, prefix, results);
        return results;
    }
};