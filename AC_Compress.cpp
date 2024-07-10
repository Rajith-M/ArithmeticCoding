#include <iostream>
#include <array>
#include <string>
#include <cassert>
#include <cstdint>
#include "opstream.hpp"

const u32 EOS_SYMBOL = 256;

int main(int argc, char** argv){

    OutputBitStream stream{std::cout};

    //Creating the frequency table
    std::array<u32, EOF_SYMBOL+1> frequencies {};
    //If a symbol has zero frequency, it would have zero probability in the model, so we fill the array with 1s
    frequencies.fill(1);

    //Set the frequencies of letters (65 - 122) to 2 
    for(unsigned int i = 65; i <= 122; i++)
        frequencies.at(i) = 2;
    
    //Now set the frequencies of uppercase/lowercase vowels to 4 
    std::string vowels{"AEIOUaeiou"};
    for(unsigned char c: vowels)
        frequencies.at(c) = 4;

    /*What we've done above is create a static probability distribution with no prior knowledge of incoming data. 1 for all ASCII symbols, 2 for the letters(both uppercase and lowercase)
    4 for vowels since they're more likely to appear than consonants*/

    //Now compute cumulative frequencies for each symbol.
    //We actually want the range [CF_low,CF_high] for each symbol,
    //but since CF_low(i) = CF_high(i-1), we only really have to compute
    //the array of lower bounds.

    //The cumulative frequency range for each symbol i will be 
    //[ CF_low.at(i), CF_low.at(i+1) ) 
    //(note that it's a half-open interval)
    //This array also needs to be u64 to account for overflow as mentioned in the readme file
    std::array<u64, EOF_SYMBOL+2> CF_low {};
    CF_low.at(0) = 0;
    for (unsigned int i = 1; i < EOF_SYMBOL+2; i++){
        CF_low.at(i) = CF_low.at(i-1) + frequencies.at(i-1); 
    }
    /*Lemme demonstrate this cumulative function at action with a simple example
    Frequencies: [1,1,2,2,4,4]
    CF_low: [0,1,2,4,6,10,14]*/

    /*In BillBird's videos, he mentions having the cumulative probabilites remain as fractions like 7/11 rather than its floating point value 0.6363... because that way
    we don't lose precision by truncation*/

    //We also need to know the global cumulative frequency (of all 
    //symbols), which will be the denominator of a formula below.
    //It turns out this value is already stored as CF_low.at(max_symbol+1)
    u64 global_cumulative_frequency = CF_low.at(EOF_SYMBOL+1);

    
    assert(global_cumulative_frequency <= 0xffffffff); //If this fails, frequencies must be scaled down

    u32 lower_bound = 0;  //Bit sequence of all zeros
    u32 upper_bound = ~0; //Bit sequence of all ones
    //Remember that our range is [low,high+1)

    int underflow_counter = 0;
    //Below is the while true loop for encoding
    while(1){
        
    }

}