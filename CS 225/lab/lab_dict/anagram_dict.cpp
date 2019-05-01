/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>
using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
   ifstream wordsFile(filename);
   string word;
if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
        vector<char> list;
        for(size_t i = 0;i<word.size();i++)
            list.push_back(word.at(i));
        sort(list.begin(), list.begin()+word.length());      
        dict[word]=list; 
          
       }
    }
    /* Your code goes here! */
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for(auto& thing: words){  
    auto lookup = dict.find(thing);
    if(lookup == dict.end())
      {
        vector<char> list;
        for(size_t i = 0;i<thing.size();i++)
            list.push_back(thing.at(i));
        sort(list.begin(), list.begin()+thing.length());
        dict[thing] = list;
       }
   }
   /* Your code goes here! */

}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    vector<string> list1;
     list1 = helper(word);
     if(list1.size()>1)
       return list1;
    
 
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector< vector<string>> result;
    for(auto& thing: dict){
        string temp = thing.first;
        vector<string> temp1 = helper(temp);
        if(temp1.size()>1)
            result.push_back(temp1);
    }
   return result;
}
    /* Your code goes here! */

vector<string> AnagramDict::helper(const string& word) const{  
        vector<string> list;
        auto lookup = dict.find(word);
        if(lookup!=dict.end()){
            vector<char> theone = lookup->second;
        for(auto& thing: dict){
           if(thing.second == theone)
                list.push_back(thing.first);
            }
        }
      return list;

}   
