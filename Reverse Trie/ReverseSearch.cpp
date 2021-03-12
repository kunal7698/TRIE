#include<bits/stdc++.h>
using namespace std;

class TrieNode{
public:
    bool isValidWord;
    int Id, freqOfWord;
    unordered_map<char, TrieNode*> children;
    TrieNode(){
        isValidWord = false;
        Id = -1;
        freqOfWord = 0;
    }
};

class TrieDS{
private:
    TrieNode* root;
    int totalWords;
    int ID;

public:
// constructors to instantiate TRIE
    // Constructing an empty TRIE
    TrieDS(){
        root = new TrieNode();ID=0;
    }
    // Constructing TRIE from TEST DATA
    TrieDS(const vector<pair<string,int>>& words){
        root = new TrieNode();ID=0;
        for(pair<string,int> word : words){
            insertWord(word);
        }
    }
// used to insert a word in the TRIE.
    void insertWord(pair<string,int> &word){
        TrieNode* currNode = root;
        for(int i=0;i<word.first.length();i++){
            unordered_map<char, TrieNode*>& childMap = (currNode->children);
            if(childMap.find(word.first[i]) == childMap.end()){
                currNode = new TrieNode();
                childMap[word.first[i]] = currNode;
            }
            else{
                currNode = childMap[word.first[i]];
            }
        }
        currNode->isValidWord = true;
        currNode->freqOfWord = word.second;
        currNode->Id = ++ID;
    }

// check if a word is in the TRIE
    // Using backTracking to find the node corresponding to id.
    string DFS(TrieNode* currNode, int val, string prefix){
        if(currNode->isValidWord==true && currNode->Id==val){
            return prefix;
        }
        for(auto child: currNode->children){
            prefix.push_back(child.first);
            string res = DFS(child.second, val, prefix);
            if(res != "-"){return res;}
            prefix.pop_back();
        }
        return "-";
    }
    // helper function to use DFS by User.
    string searchWord(int val){
        string temp = "";
        string result = DFS(root, val, temp);
        return result;
    }
};

// function to use CSV file to build TRIE.
vector<pair<string,int>> readRecordFromFile(string fileName){
    vector<pair<string,int>> record;
    ifstream file;
    file.open(fileName);
    string field1, field2;
    while(getline(file, field1, ',')){
        getline(file, field2, '\n');
        record.push_back({field1, stoi(field2)});
    }
    return record;
}

int main()
{
    /**** using source file to build trie ********/
    // Source data file
    string fileName = "EnglishDictionary.csv";
    // building trie from source file
    vector<pair<string,int>> input = readRecordFromFile(fileName);
    TrieDS *myTrie = new TrieDS(input);
    // input based searching to check the availability of a string with
    // certain fixed ID.
 	int x;
 	while(cin>>x){
        int ID;
        cin>>ID;
        cout<<myTrie->searchWord(ID)<<endl;
 	}
    return 0;
}
