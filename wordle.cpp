#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <limits.h>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wordle_helper(const std::set<std::string>& dict, std::string floating, size_t index, std::set<std::string>& matches, std::string temp);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> found_words;

    wordle_helper(dict, floating, 0, found_words, in);
    return found_words;


}

// Define any helper functions here
void wordle_helper(const std::set<std::string>& dict, std::string floating, size_t index, std::set<std::string>& matches, std::string temp) {
    if (index == temp.size()) {
        if (floating.empty()) {
            if (dict.find(temp) != dict.end()) {
                matches.insert(temp);
            }
            return;
        }
    } else {
        int numDashes = 0;
        if (temp[index] != '-') {
            wordle_helper(dict, floating, index + 1, matches, temp);
            return;
        }
        for (size_t i = 0; i < temp.size(); i++) {
            switch(temp[i]) {
                case '-':
                    numDashes++;
                    break;
                default:
                    break;
            }
        }
        string temp2 = floating;
        int temp2_size = static_cast<int>(temp2.size());
        if (numDashes > temp2_size) {
            for (char c = 'a'; c <= 'z'; c++) {
                switch(temp2.find(c)) {
                    case string::npos:
                        temp[index] = c;
                        wordle_helper(dict, temp2, index + 1, matches, temp);
                        break;
                    default:
                        temp[index] = c;
                        string temp3 = temp2;
                        temp3.erase(temp2.find(c), 1);
                        wordle_helper(dict, temp3, index + 1, matches, temp);
                        break;
                }
            }
        } else if (numDashes == temp2_size) {
            for (size_t i = 0; i < temp2.size(); i++) {
                temp[index] = temp2[i];
                string temp3 = temp2;
                temp3.erase(i, 1);
                wordle_helper(dict, temp3, index + 1, matches, temp);
            }
        }
    }
}