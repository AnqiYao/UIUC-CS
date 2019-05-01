/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

#include "pronounce_dict.h"

#include <string>
using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
  vector<StringTriple> endvec;
  ifstream wordsFile(word_list_fname);
  string word;
if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
      
     if (word.length()==5){
        string word1 = word.substr(1);
        string word2 = word.substr(0,1);
        word2+=word.substr(2); 
        if( d.homophones(word,word1) &&  d.homophones(word,word2) &&  d.homophones(word2,word1)){
     StringTriple result ;
     std::get<0>(result) = word;
      std::get<1>(result)= word1;
      std::get<2>(result)= word2;
       endvec.push_back(result);
  

      }
   }      
 }
}
/* Your code goes here! */
    return endvec;
}
