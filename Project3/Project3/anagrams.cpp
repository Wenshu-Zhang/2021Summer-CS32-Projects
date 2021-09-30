//
//  anagrams.cpp
//  Project3
//
//  Created by Claire Z on 2021/7/24.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

int loadDictionary(istream& dictfile, string dict[], int count);
int makeDictionary(istream &dictfile, string dict[]);
bool isAnagram(string& word, string& dictWord, int count);
bool isResult(string word, string dictWord);
int howManyResults(string& word, const string dict[], int size, string results[], int numResult);
int shuffleChars(string word, const string dict[], int size, string results[]);
void revealOutcomes(const string results[], int size);

//load words one by one recursively and retunr the number loaded
int loadDictionary(istream& dictfile, string dict[], int count){
    if(count == MAXDICTWORDS)               //if MAX number of words are loaded
        return count;                       //stop and return the count
    string line;                            //for storing the word temporarily
    if(getline(dictfile, line)){            //if the line contains a word, get it
        *dict = line;                       //and store it in dict[]
        return loadDictionary(dictfile, dict+1, count+1);
    }
    else
        return count;                       //if there's no more word, return the count
}


//create an int variable and pass it into loadDictionary to keep track of
//the number of words loaded
//then, return the number of words loaded by loadDictionary
int makeDictionary(istream &dictfile, string dict[]){
    int count = 0;
    return loadDictionary(dictfile, dict, count);
}

//check if two words of the same length are anagrams
//also pass in times, which is the max number of times of rotating the dictionary word
//add a count parameter, which keeps track of times of rotating a word
bool isAnagram(string& word, string& dictWord, int count){
    if(count > word.size())
        return false;
    if(word.size() == 0)//if all letters are the same
        return true;                        //the dictionary word is anagram, return true
    if(word[0] == dictWord[0]){             //if the letters are the same
        //cut the char off both words and check the next letter
        count = 0;
        word = word.substr(1,word.size()-1);
        dictWord = dictWord.substr(1,dictWord.size()-1);
        isAnagram(word, dictWord, count);
    }
    else{
        //otherwise, rotate the dictionary word once to the left
        //the first letter is appended the end of the word
        dictWord = dictWord.substr(1,dictWord.size()-1)+dictWord[0];
        count++;
    }
    //check the first letter of the rotated word
    return isAnagram(word, dictWord, count);
}


bool isResult(string word, string dictWord){
    if(word.size() != dictWord.size())      //if the sizes don't match, not anagrams
        return false;                       //so, return false
    else                                    //otherwise, check the two words
        return isAnagram(word, dictWord, 0);
}

//check the words in the dictionary recursively
//if it is a result, store it in result[] and add 1 to numResult
//stop when all words are visited
int howManyResults(string& word, const string dict[], int size, string results[], int numResult){
    if(numResult == MAXRESULTS)
        return numResult;
    if(size == 0)                           //if all words are examined
        return numResult;                   //stop and return numResult
    if(isResult(word, *dict)){              //if it is a result
        *results = *dict;                   //store it in result[]
        //check the next one in the dictionary,
        //also move to the next position in results[]
        results++;
        numResult++; //add 1 to numResult
    }
    return howManyResults(word, dict+1, size-1,results, numResult);
}


//return howManyResults
int shuffleChars(string word, const string dict[], int size, string results[]){
    return howManyResults(word, dict, size, results, 0);
}



void revealOutcomes(const string results[], int size){
    if(size == 0)                           //stop when all results are printed
        return;
    cout << results[size-1] << endl;        //print the results from the last position
    revealOutcomes(results, size-1);        //recursively
}


int main(){
//    string results[MAXRESULTS];
//    string dict[MAXDICTWORDS];
//    ifstream dictfile;         // file containing the list of words
//    int nwords;                // number of words read from dictionary
//    string word;
//
//    //check if the dictfile can be read in and examined word by word
//    //check the number of dictionary words loaded
//    //let the user enter a word for check
//    //find all results and the number of results
//    //reveal the results using the function revealOutcomes
//    dictfile.open("/Users/clairez/Desktop/words.txt");
//    if (!dictfile) {
//        cout << "File not found!" << endl;
//        return (1);
//    }
//
//    nwords = makeDictionary(dictfile, dict);
//    cout << nwords << endl;
//
//    cout << "Please enter a string for an anagram: ";
//    cin >> word;
//
//    int numMatches = shuffleChars(word, dict, nwords, results);
//    if (!numMatches)
//        cout << "No matches found" << endl;
//    else
//        revealOutcomes(results, numMatches);
//
//    //make the dictionary bigger than MAXDICTWORDS = 30000
//    //check the number of dictionary words loaded(should not be greater than 30000
//    //let the user enter a word for check
//    //find all results and the number of results
//    //reveal the results using the function revealOutcomes
//    dictfile.open("/Users/clairez/Desktop/dictionary.txt");
//    if (!dictfile) {
//        cout << "File not found!" << endl;
//        return (1);
//    }
//
//    nwords = makeDictionary(dictfile, dict);
//    cout << nwords << endl;
//
//    cout << "Please enter a string for an anagram: ";
//    cin >> word;
//
//    int numMatches = shuffleChars(word, dict, nwords, results);
//    if (!numMatches)
//        cout << "No matches found" << endl;
//    else
//        revealOutcomes(results, numMatches);
//
////
//
//    //regular test consisting of 3 anagrams
//    //reveal the results using the function revealOutcomes
//    string results1[MAXRESULTS];
//    string exampleDict[] = { "art", "tar", "rat"};
//    int numResults = shuffleChars("art", exampleDict, 3, results1);
//    assert(numResults == 3 && results1[0] == "art");
//    revealOutcomes(results1, numResults);
//
//    //test consisting of words of different sizes
//    //no anagrams are included, so numResults should be 0
//    //no need to reveal the results
//    string results2[MAXRESULTS];
//    string exampleDict2[] = { "abcd", "efgh", "ijkl","mno"};
//    numResults = shuffleChars("abc", exampleDict2, 4, results2);
//    assert(numResults == 0);
//    numResults = shuffleChars("", exampleDict2, 4, results2);
//    assert(numResults == 0);
//
//    //test consisting of longer anagrams
//    //all words should end up in the results array
//    //reveal the results using the function revealOutcomes
//    string results3[MAXRESULTS];
//    string exampleDict3[] = { "abcdefg", "gfedcba", "cbadgfe","agbfced"};
//    numResults = shuffleChars("gedfbca", exampleDict3, 4, results3);
//    assert(numResults == 4);
//    revealOutcomes(results3, numResults);
//
//    //test consisting of very long anagrams
//    //all words should end up in the results array
//    //reveal the results using the function revealOutcomes
//    string results4[MAXRESULTS];
//    string exampleDict4[] = { "abcdefghijk", "kgfiejdcbah", "hcibadkgfej","jkaighbfced","ghakbcfdeij"};
//    numResults = shuffleChars("gekdfjbcahi", exampleDict4, 5, results4);
//    assert(numResults == 5);
//    revealOutcomes(results4, numResults);
//
//    //test consisting of many anagrams
//    //numResults should not exceed MAXRESULTS
//    //reveal the results using the function revealOutcomes
//    string results5[MAXRESULTS];
//    string exampleDict5[] = { "abcd","abdc","acbd","acdb","adbc","adcb","bacd","badc","bcad","bcda","bdac","bdca","cabd","cadb","cbad","cbda","cdab","cdba","dabc","dacb","dbac"};
//    numResults = shuffleChars("abcd", exampleDict5, 21, results5);
//    assert(numResults == MAXRESULTS);
//    revealOutcomes(results5, numResults);
//
//    //test consisting of one letter anagrams
//    //reveal the results using the function revealOutcomes
//    string results6[MAXRESULTS];
//    string exampleDict6[] = { "a", "a", "a"};
//    numResults = shuffleChars("a", exampleDict6, 3, results6);
//    assert(numResults == 3);
//    revealOutcomes(results6, numResults);
//
//    //test consisting of words of the same length
//    //no matching words
//    //reveal the results using the function revealOutcomes (prints nothing)
//    string results7[MAXRESULTS];
//    string exampleDict7[] = { "yes", "how", "tub", "why"};
//    numResults = shuffleChars("ooh", exampleDict7, 4, results7);
//    assert(numResults == 0);
//    revealOutcomes(results7, numResults);
//
//    //test consisting of words of the same length
//    //some are matching words, and some are not
//    //reveal the results using the function revealOutcomes(should print nothing)
//    string results8[MAXRESULTS];
//    string exampleDict8[] = { "buy", "but", "tub", "rub"};
//    numResults = shuffleChars("ubt", exampleDict8, 4, results8);
//    assert(numResults == 2);
//    revealOutcomes(results8, numResults);
//
//    //test consisting of very long words
//    //some are matching words, and some are not
//    //reveal the results using the function revealOutcomes
//    string results9[MAXRESULTS];
//    string exampleDict9[] = { "abcdefghijk","kgfieudcbah","hcibadkgfej","jkaighbtced","ghakbcfdeij"};
//    numResults = shuffleChars("gekdfjbcahi", exampleDict9, 5, results9);
//    assert(numResults == 3);
//    revealOutcomes(results9, numResults);
//
//    //test consisting of empty strings
//    //no words are matching
//    //reveal the results using the function revealOutcomes(should print nothing)
//    string results10[MAXRESULTS];
//    string exampleDict10[] = { "","","","",""};
//    numResults = shuffleChars("hi", exampleDict10, 5, results10);
//    assert(numResults == 0);
//    revealOutcomes(results10, numResults);
//
//    cout << "all tests passed" << endl;
    
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile; // file containing the list of words
    int nwords; // number of words read from dictionary
    string word;
    dictfile.open("/Users/clairez/Desktop/words.txt");
    if (!dictfile) {
    cout << "File not found!" << endl;
    return (1);
    }
    nwords = makeDictionary(dictfile, dict);
//    #ifdef TEST1
//    word = "rat";
//    #endif
//    #ifdef TEST2
//    word = "babe";
//    #endif
//    #ifdef TEST3
//    word = "plane";
//    #endif
//    #ifdef TEST4
//    word = "maiden";
//    #endif
//    #ifdef TEST5
//    word = "arrogant";
//    #endif
    int numMatches = shuffleChars("arrogant", dict, nwords, results);
    if (!numMatches)
    cout << "No matches found" << endl;
    else
    revealOutcomes(results, numMatches);
//    #ifdef TEST1
//    assert(numMatches == 3 && (results[0] == "rat" ||
//    results[0] == "art"
//    || results[0] == "tar"));
//    #endif
//    #ifdef TEST2
//    assert(numMatches == 2 && (results[0] == "abbe" ||
//    results[0] == "babe"));
//    #endif
//    #ifdef TEST3
//    assert(numMatches == 3 && (results[0] == "plane" ||
//    results[0] == "panel"
//    || results[0] == "penal"));
//    #endif
//    #ifdef TEST4
//    assert(numMatches == 2 && (results[0] == "maiden" ||
//    results[0] == "median"));
//    #endif
//    #ifdef TEST5
    assert(numMatches == 2 && (results[0] == "arrogant" ||
    results[0] == "tarragon"));
//    #endif
    return 0;
}

