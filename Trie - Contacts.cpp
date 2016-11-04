//
//  Tries - Contacts.cpp
//  HackerRank
//
//  Created by Zhao Wei on 11/3/16.
//  Copyright © 2016 UCI. All rights reserved.
//

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    int cnt;
    
    TrieNode() : cnt(0) {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void add(const string& name) {
        TrieNode* node = root;
        for (int i = 0; i < name.size(); i ++) {
            if (node->children[name[i] - 'a'] == nullptr)   node->children[name[i] - 'a'] = new TrieNode();
            
            node->children[name[i] - 'a']->cnt++;
            node = node->children[name[i] - 'a'];
        }
    }
    
    int find(const string& partial) {
        TrieNode* node = root;
        for (int i = 0; i < partial.size(); i++) {
            if (node->children[partial[i] - 'a'] == nullptr)   return 0;
            node = node->children[partial[i] - 'a'];
        }
        return node->cnt;
    }
};

int main(){
    Trie trie;
    string op[4] = {"add", "add", "add", "find"};
    string contact[4] = {"apple", "abam", "apyan", "zillot"};
    for (int i = 0; i < 4; i++) {
        if (op[i] == "add") {
            trie.add(contact[i]);
        }
        if (op[i] == "find") {
            int cnt = trie.find("ap");
            cout << cnt << endl;
        }
    }
    return 0;
}
