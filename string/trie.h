class TrieNode {
public:
    bool end;
    TrieNode* children[26];

    TrieNode() {
        end = false;
        memset(children, 0, sizeof children);
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for(auto ch : word) {
            int i = ch - 'a';
            if(!node->children[i]) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->end = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for(auto ch : word) {
            int i = ch - 'a';
            if(!node->children[i]) return false;
            node = node->children[i];
        }
        return node->end;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for(auto ch : prefix) {
            int i = ch - 'a';
            if(!node->children[i]) return false;
            node = node->children[i];
        }
        return true;
    }
};
