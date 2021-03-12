#include<bits/stdc++.h>
using namespace std;

class TrieNode{
public:
    bool isValidWord;
    int freqOfWord;
    unordered_map<char, TrieNode*> children;
    TrieNode(){
        isValidWord = false;
        freqOfWord = 0;
    }
};

// TRIE
class TrieDS{
private:
    TrieNode* root;
    int totalWords;

    //Function to convert given TRIE into a serial TRIE
       void buildSerialTrie(TrieNode *root, string &serialTrie)
       {
           if(root->isValidWord){
              serialTrie.push_back(']');
              serialTrie += to_string(root->freqOfWord);
           }
           unordered_map<char, TrieNode*> &children = root->children;
           for(auto child : children)
           {
               serialTrie.push_back(child.first);
               buildSerialTrie(child.second, serialTrie);
           }
           serialTrie.push_back('>');
       }

       //Function to re-create TRIE from serial TRIE
       int stringToTrie(TrieNode *node, string &serialTrie, int &read)
       {
            int wordSeen = 0;
            if(serialTrie[read] == ']')
            {
               node->isValidWord = 1;
               wordSeen++;
               read++;
               int frequency = 0,val = (serialTrie[read]-'0');
               while(val >= 0 && val <= 9){
                    frequency = frequency*10 + val;
                    read++;val = (serialTrie[read]-'0');
               }
               node->freqOfWord = frequency;
            }
            else{
                node->isValidWord = 0;
            }

            unordered_map<char, TrieNode*> &childMap = node->children;
            while(serialTrie[read] != '>')
            {
                while(1){
                    int val = (serialTrie[read]-'0');
                    if(val>=0 && val<=9){read++;}
                    else{break;}
                }
                char ch = serialTrie[read++];
                childMap[ch] = new TrieNode();
                wordSeen += stringToTrie(childMap[ch], serialTrie, read);
            }
            read++;
            return wordSeen;
       }

public:
// constructors to instantiate TRIE
    // Constructing an empty TRIE
    TrieDS(){
        root = new TrieNode();
    }
    // Constructing TRIE from TEST DATA
    TrieDS(const vector<pair<string,int>>& words){
        root = new TrieNode();
        for(pair<string,int> word : words){
            insertWord(word);
        }
    }
    // Constructing a TRIE using a serial TRIE.
    TrieDS(string &serialTrie){
        root = new TrieNode();
        int read = 0;
        totalWords = stringToTrie(root, serialTrie, read);
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
    }

// check if a word is in the TRIE
    pair<bool,int> findWord(const string word){
        TrieNode* currNode = root;
        for(int i=0;i<word.length();i++){
            unordered_map<char, TrieNode*>& childMap = (currNode->children);
            if(childMap.find(word[i]) == childMap.end()){
                return {false,0};
            }
            else{
                currNode = childMap[word[i]];
            }
        }
        if(currNode->isValidWord){
            return {true,currNode->freqOfWord};
        }
        return {false,0};
    }

// Converts current TRIE into Serialized TRIE.
    string trieToString(){
       string serializedTrie;
       buildSerialTrie(root, serializedTrie);
       return serializedTrie;
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
    vector<pair<string,int>> input1 = readRecordFromFile(fileName);
    TrieDS *myTrie1 = new TrieDS(input1);
    // file where serialized format is stored
    freopen ("SERIAL_FORM.txt", "w", stdout);
 	cout<<myTrie1->trieToString()<<endl;
 	/**********************************************/


 	/******** To use Serialized format ******/
 	//freopen ("SERIAL_FORM.txt", "r", stdout);
 	//string input2;cin>>input2;
 	//TrieDS *myTrie2 = new TrieDS(input2);
 	/****************************************/

 	/******* to check if some word is present in trie ***/
 	// enter the word to be searched
 	string text;cin>>text;
 	pair<bool,int> ans = myTrie1->findWord(text);
 	if(ans.first){
        cout<<"YES "<<ans.second<<endl;
 	}
 	else{
        cout<<"NO"<<endl;
 	}
 	/****************************************************/

 	return 0;

}

