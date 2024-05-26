/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    vector<string> dict;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            dict.push_back(word);
        }
    }
    for (unsigned i = 0; i < dict.size(); i++) {
        string og = dict.at(i);
        string og1 = dict.at(i);
        string og2 = dict.at(i);
        string first_removed = og1.erase(0, 1);
        string second_removed = og2.erase(1, 1);
        if (d.homophones(og ,first_removed) && d.homophones(og, second_removed)) ret.push_back({og, first_removed, second_removed});
    }
    return ret;
}
