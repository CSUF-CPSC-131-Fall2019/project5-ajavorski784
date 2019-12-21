#include "WordFrequency.h"
#include "sanitize.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

WordFrequency::WordFrequency() {} // default constructor
void WordFrequency::readIn(const string &filename) {
  std::ifstream file(filename);
  std::string line; // variable to allow for reading a whole line in to process
  std::string currentWord; // Word holder for placing into hash table

  while (!file.eof()) {
    getline(file, line); // Reads line in from text
    std::stringstream currentLine(line);
    while (!currentLine.eof()) {
      getline(currentLine, currentWord, ' '); // Reads a word from the stream
      // Removal of end punctuation characters
      currentWord.erase(
          std::remove(currentWord.begin(), currentWord.end(), '.'),
          currentWord.end());
      currentWord.erase(
          std::remove(currentWord.begin(), currentWord.end(), '?'),
          currentWord.end());
      currentWord.erase(
          std::remove(currentWord.begin(), currentWord.end(), '!'),
          currentWord.end());

      sanitize(currentWord); // Sanitizes un needed characters in string

      if (currentWord == "") { // Just checks if any string is an empty string
        continue;              // Don't put empty strings into Frequency table
      } else {
        frequencyTable[currentWord]++; // Add word to Frequency table
      }
    }
  }
} // add words from file to hash table
size_t WordFrequency::numberOfWords() {
  return frequencyTable.size();
} // return the number of unique words
size_t WordFrequency::wordCount(const string &word) {
  return frequencyTable[word];

} // return the number of occurrences of the given word
string WordFrequency::mostFrequentWord() {
  std::string word;
  int freqWord = 0;
  std::unordered_map<string, int>::iterator itr;
  for (itr = frequencyTable.begin(); itr != frequencyTable.end(); itr++) {
    if (itr == frequencyTable.begin()) {
      word = itr->first;
      freqWord = itr->second;
    }
    if (freqWord < itr->second) {
      word = itr->first;
      freqWord = itr->second;
    }
  }
  return word;
} // return the most frequent word
size_t WordFrequency::maxBucketSize() {
  int bigBucket =
      frequencyTable.bucket_size(0); // Variable storing largest bucket size
  for (int i = 0; i < frequencyTable.bucket_count(); i++) {
    if (bigBucket < frequencyTable.bucket_size(i)) {
      bigBucket = frequencyTable.bucket_size(i);
    }
  }
  return bigBucket;
} // return the size of the largest bucket
  // in the hash table
