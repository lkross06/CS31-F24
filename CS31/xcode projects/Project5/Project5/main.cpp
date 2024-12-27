#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;

const char WORDS_FILENAME[35] = "/Users/lkross/Desktop/words.txt";
const int MAX_NUM_WORDS = 8000;
const int NUM_WORDS = 7264; //7264 = number of words in the provided word file
const int MAX_TRIAL_WORD_LENGTH = 100;

int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum){
    if (nWords < 0 || wordnum < 0 || wordnum >= nWords) return -1; //bad arguments
    
    //get the chosen word
    char chosen_word[MAXWORDLEN + 1];
    strcpy(chosen_word, words[wordnum]);
    
    int score = 0;
    
    for (;;){
        int num_stars = 0;
        int num_planets = 0;
        
        char trial_word[MAXWORDLEN + 1];
        cout << "Trial word: ";
        cin.getline(trial_word, MAX_TRIAL_WORD_LENGTH);
        int trial_word_length = strlen(trial_word);
        
        //check for invalid trial word
        bool invalid = false;
        if (trial_word_length > MAXWORDLEN || trial_word_length < MINWORDLEN) invalid = true;
        
        for (int i = 0; i < trial_word_length; i++){
            if (!islower(trial_word[i])){
                invalid = true;
                break;
            }
        }
        
        //check for unknown word
        bool unknown = true;
        for (int i = 0; i < nWords; i++){
            if (strcmp(words[i], trial_word) == 0){
                unknown = false;
                break;
            }
        }
        
        if (invalid){
            //get a new trial word
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        } else if (unknown){
            //get a new trial word
            cout << "I don't know that word." << endl;
            continue;
        } else {
            //since a valid trial word was entered we can increase the score
            score += 1;
        }
        
        //check to see if the trial word IS the chosen word
        if (strcmp(trial_word, chosen_word) == 0) break;
        
        //keep track of which letters "match" (s/p) in the trial
        //word and chosen word to prevent double-counting for planets
        //notice that 'X' will never appear in the chosen word and is caught by uppercase check
        char temp_trial_word[MAXWORDLEN + 1];
        strcpy(temp_trial_word, trial_word);
        char temp_chosen_word[MAXWORDLEN + 1];
        strcpy(temp_chosen_word, chosen_word);
        
        //check for stars
        for (int i = 0; i < trial_word_length; i++){
            if (chosen_word[i] == trial_word[i]){
                num_stars++;
                temp_trial_word[i] = 'X';
                temp_chosen_word[i] = 'X';
            }
        }

        //check for planets
        for (int i = 0; i < trial_word_length; i++){
            //c is a pointer to the character in chosen word
            //notice that we compare the actual trial word to the temporary chosen word.
            //since we know that the actual trial word will never have 'X', we don't have
            //to worry about planets being formed from matching X's
            char* c = strchr(temp_chosen_word, trial_word[i]);
            if (c != nullptr){
                //k is the index of the character in the chosen word (subtract difference in mem addresses)
                int k = &*c - &temp_chosen_word[0];
                
                if (temp_trial_word[i] != 'X' && temp_chosen_word[k] != 'X'){ //no double-counting
                    num_planets++;
                    temp_trial_word[i] = 'X';
                    temp_chosen_word[k] = 'X';
                }
            }
            
        }
        
        //print out the number of stars and planets
        cout << "Stars: " << num_stars << ", Planets: " << num_planets << endl;
    }

    return score;
}

void updateStatistics(int curr_score, int* min, int* max, double* sum, int rounds_played){
    //check to see if it was round 1
    if (*min == -1) *min = curr_score;
    if (*max == -1) *max = curr_score;
    //update stats
    if (curr_score < *min) *min = curr_score;
    if (curr_score > *max) *max = curr_score;
    *sum += curr_score;
    
    //set doubles to 2 decimal points
    cout.setf(ios::fixed);
    cout.precision(2);
    
    //print out new stats
    cout << "Average: " << *sum/rounds_played << ", minimum: " << *min << ", maximum: " << *max << endl;
}

int main() {
    //8000 words, 7 chars max (6-letter word + 1 '\0')
    char word_list[MAX_NUM_WORDS][MAXWORDLEN + 1];
    
    //populate word list
    int download_result = getWords(word_list, NUM_WORDS, WORDS_FILENAME);
    if (download_result < 1){
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    
    int num_rounds;
    
    cout << "How many rounds do you want to play? ";
    cin >> num_rounds;
    if (num_rounds < 0){
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    //clear input buffer
    cin.ignore(10000, '\n');
    
    //these will help up get statistics for each round
    int min = -1; //default to -1 so we know to set it during round 1
    int max = -1;
    double sum = 0.0;
    
    for (int i = 0; i < num_rounds; i++){
        cout << endl << "Round " << i + 1 << endl;
        
        //choose a random word from the list of words
        //the modulo takes the remainder so its always within the bounds
        int chosen_index = randInt(0, NUM_WORDS - 1) % NUM_WORDS;
        
        //get the chosen word
        char secret_word[MAXWORDLEN + 1];
        strcpy(secret_word, word_list[chosen_index]);
        
        cout << "The secret word is " << strlen(secret_word) << " letters long." << endl;
        
        //run the round
        int round_score = runOneRound(word_list, NUM_WORDS, chosen_index);
        
        //check for some error
        if (round_score == -1){
            cout << "The program encountered an unknown error." << endl;
            return 0;
        }
        
        //print their score
        if (round_score == 1) cout << "You got it in 1 try." << endl;
        else cout << "You got it in " << round_score << " tries." << endl;
        
        //update and print out the stats
        updateStatistics(round_score, &min, &max, &sum, i + 1);
    }
    
    return 0;
}
