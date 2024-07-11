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
        bool isEmpty(TrieNode *root) {
	    for (int i = 0; i < root->SIZE; i++) if (root->children[i]) return false;
	    return true;
    }

    void erase(string key) {
        TrieNode* node = root;
        stack<pair<TrieNode*, int>> nodes;
        for(char ch : key) {
            int i = ch - 'a';
            if (!node->children[i]) return; 
            nodes.push({node, i});
            node = node->children[i];
        }
        if(!node->end) return; 
        node->end = false;
        while(!nodes.empty()) {
            auto [parent, index] = nodes.top();
            nodes.pop();
            TrieNode* child = parent->children[index];
            if(!child->end && isEmpty(child)) {
                delete child;
                parent->children[index] = nullptr;
            } else {
                break;
            }
        }
    }
};
