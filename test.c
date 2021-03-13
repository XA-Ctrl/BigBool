#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BigBool.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

int test_converting_from_str();
int test_converting_from_uint64();
int test_inversion();
int test_conjunction();
int test_disjunction();
int test_xor();
int test_left_shift();
int test_right_shift();
int test_left_circular_shift();
int test_right_circular_shift();


int main(int argc, char const *argv[])
{
    int failCounter = 0;

    failCounter += test_converting_from_str();
    failCounter += test_converting_from_uint64();
    failCounter += test_inversion();
    failCounter += test_conjunction();
    failCounter += test_disjunction();
    failCounter += test_xor();
    failCounter += test_left_shift();
    failCounter += test_right_shift();
    failCounter += test_left_circular_shift();
    failCounter += test_right_circular_shift();


    printf(COLOR_CYAN "\nFails collected: %d\n" COLOR_RESET, failCounter);
    return 0;
}

int test_converting_from_str() {
    printf(COLOR_CYAN "\n\nConverting BigBool from str test:\n" COLOR_RESET);
    int failCounter = 0;

    BigBool* vec = BigBool_from_str("0000");
    char* vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "0")) {
        ++failCounter;
        printf("\t-Zero vector creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else { 
        printf("\t-Zero vector creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);
    
    vec = BigBool_from_str("10111010");
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "10111010")) {
        ++failCounter;
        printf("\t-8 bit vector creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else { 
        printf("\t-8 bit vector creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_str("11100011001");
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11100011001")) {
        ++failCounter;
        printf("\t-Vector of length non-multiple of eight creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Vector of length non-multiple of eight creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    vec = BigBool_from_str("1101100000111101110110000011110111011000001111011101100000111101");
    vecStr = BigBool_to_str(vec);
    
    if(strcmp(vecStr, "1101100000111101110110000011110111011000001111011101100000111101")) {
        ++failCounter;
        printf("\t-64-bit vector creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-64 bit vector creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);


    vec = BigBool_from_str("110110000011110111111111111111111111111110110000011110111011000001111011101100000111101");
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "110110000011110111111111111111111111111110110000011110111011000001111011101100000111101")) {
        ++failCounter;
        printf("\t-Over 64 bit vector creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else { 
        printf("\t-Over 64 bit vector creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);


    vec = BigBool_from_str("000011110001");
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "11110001")) {
        ++failCounter;
        printf("\t-Removing leading zeros of vector: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Removing leading zeros of vector: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    return failCounter;
}

int test_converting_from_uint64() {
    printf(COLOR_CYAN "\n\nConverting BigBool from uint64 test:\n" COLOR_RESET);
    int failCounter = 0;

    BigBool* vec = BigBool_from_uint64(0b0000);
    char* vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "0")) {
        ++failCounter;
        printf("\t-Zero vector creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Zero vector creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);


    vec = BigBool_from_uint64(0b001011010);
    vecStr = BigBool_to_str(vec);


    if(strcmp(vecStr, "1011010")) {
        ++failCounter;
        printf("\t-One byte vector creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-One byte vector creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);


    vec = BigBool_from_uint64(0b11100011001);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11100011001")) {
        ++failCounter;
        printf("\t-Vector of length non-multiple of eight creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Vector of length non-multiple of eight creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    vec = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    vecStr = BigBool_to_str(vec);
    
    if(strcmp(vecStr, "1101100000111101110110000011110111011000001111011101100000111101")) {
        ++failCounter;
        printf("\t-64-bit vector creation: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-64 bit vector creation: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }
    
    free(vec);
    free(vecStr);

    return failCounter;
}

int test_inversion() {
    printf(COLOR_CYAN"\n\nInversion test:\n"COLOR_RESET);
    int failCounter = 0;

    BigBool* vec = BigBool_from_uint64(0b10101010);
    inversion(vec);
    char* vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "01010101")) {
        ++failCounter;
        printf("\t-8 bit vector invesrion: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-8 bit vector invesrion: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);


    vec = BigBool_from_uint64(0b11010101010);
    inversion(vec);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "00101010101")) {
        ++failCounter;
        printf("\t-Inversion of vector of length non-multiple of eight: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Inversion of vector of length non-multiple of eight: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);


    vec = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    inversion(vec);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "0010011111000010001001111100001000100111110000100010011111000010")) {
        ++failCounter;
        printf("\t-64 bit vector inversion: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-64 bit vector inversion: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);    


    vec = BigBool_from_str("1111101100000111101110110000011110111011000001111011101100000111101");
    inversion(vec);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "0000010011111000010001001111100001000100111110000100010011111000010")) {
        ++failCounter;
        printf("\t-Over 64 bit vector inversion: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vector inversion: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);  


    return failCounter;
}

int test_conjunction() {
    printf(COLOR_CYAN "\n\nConjunction test:\n" COLOR_RESET);
    int failCounter = 0;

    BigBool* vec0 = BigBool_from_uint64(0b0);
    BigBool* vec1 = BigBool_from_uint64(0b11001101010111);
    BigBool* vec2 = BigBool_from_uint64(0b10010101);
    BigBool* vec3 = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    BigBool* vec4 = BigBool_from_uint64(0b1111110000000011001010010101010001110010101111100001100110011000);
                                        
    BigBool* res;
    char* vecStr;

    res = conjunction(vec0, vec1);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "0")) {
        ++failCounter;
        printf("\t-Zero vector and non-zero vector conjunction: " COLOR_RED "FAIL\n" COLOR_RESET);    
    }
    else {
        printf("\t-Zero vector and non-zero vector conjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET); 
    }

    free(res);
    free(vecStr);


    res = conjunction(vec1, vec2);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "10101")) {
        ++failCounter;
        printf("\t-Different legths vectors conjunction: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Different legths vector conjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);

    free(vec0);
    free(vec1);
    free(vec2);


    res = conjunction(vec3, vec4);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "1101100000000001000010000001010001010000001111000001100000011000")) {
        ++failCounter;
        printf("\t-64 bit vectors conjunction: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-64 bit vectors conjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);

    free(vec3);
    free(vec4);

    
    vec3 = BigBool_from_str("11011000001111011101100000111101110110000011110111011000001111011001");
    vec4 = BigBool_from_str("11111100000000110010100101010100011100101011111000011001100110001111");
    res = conjunction(vec3, vec4);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "11011000000000010000100000010100010100000011110000011000000110001001")) {
        ++failCounter;
        printf("\t-Over 64 bit vectors conjunction: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vectors conjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);

    free(vec3);
    free(vec4);

    return failCounter;
}

int test_disjunction() {
    printf(COLOR_CYAN "\n\nDisjunction test:\n" COLOR_RESET);
    int failCounter = 0;

    BigBool* vec0 = BigBool_from_uint64(0b0);
    BigBool* vec1 = BigBool_from_uint64(0b11001101010111);
    BigBool* vec2 = BigBool_from_uint64(0b10010101);
    BigBool* vec3 = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    BigBool* vec4 = BigBool_from_uint64(0b1111110000000011001010010101010001110010101111100001100110011000);

    BigBool* res;
    char* vecStr;

    res = disjunction(vec0, vec1);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "11001101010111")) {
        ++failCounter;
        printf("\t-Zero vector and non-zero vector disjunction: " COLOR_RED "FAIL\n" COLOR_RESET);    
    }
    else {
        printf("\t-Zero vector and non-zero vector disjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET); 
    }

    free(res);
    free(vecStr);


    res = disjunction(vec1, vec2);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "11001111010111")) {
        ++failCounter;
        printf("\t-Different legths vectors disjunction: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Different legths vector disjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);

    free(vec0);
    free(vec1);
    free(vec2);


    res = disjunction(vec3, vec4);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "1111110000111111111110010111110111111010101111111101100110111101")) {
        ++failCounter;
        printf("\t-64 bit vectors disjunction: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-64 bit vectors disjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);

    free(vec3);
    free(vec4);

    
    vec3 = BigBool_from_str("11011000001111011101100000111101110110000011110111011000001111011001");
    vec4 = BigBool_from_str("11111100000000110010100101010100011100101011111000011001100110001111");
    res = disjunction(vec3, vec4);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "11111100001111111111100101111101111110101011111111011001101111011111")) {
        ++failCounter;
        printf("\t-Over 64 bit vectors disjunction: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vectors disjunction: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);

    free(vec3);
    free(vec4);

    return failCounter;
}

int test_xor() {
    printf(COLOR_CYAN "\n\nTest XOR:\n" COLOR_RESET);
    int failCounter = 0;

    BigBool* vec0 = BigBool_from_uint64(0b0);
    BigBool* vec1 = BigBool_from_uint64(0b11001101010111);
    BigBool* vec2 = BigBool_from_uint64(0b10010101);
    BigBool* vec3 = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    BigBool* vec4 = BigBool_from_uint64(0b1111110000000011001010010101010001110010101111100001100110011000); 

    BigBool* res;
    char* vecStr;

    res = xor(vec0, vec1);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "11001101010111")) {
        ++failCounter;
        printf("\t-Zero vector and non-zero vector XOR: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Zero vector and non-zero vector XOR: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);


    res = xor(vec1, vec2);
    vecStr = BigBool_to_str(res);
    if(strcmp(vecStr, "11001111000010")) {
        ++failCounter;
        printf("\t-Different length vectors XOR: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Different length vectors XOR: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);


    res = xor(vec3, vec4);
    vecStr = BigBool_to_str(res);
    
    if(strcmp(vecStr, "0010010000111110111100010110100110101010100000111100000110100101")) {
        ++failCounter;
        printf("\t-64 bit vectors XOR: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-64 bit vectors XOR: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);
    free(vec3);
    free(vec4);

    
    vec3 = BigBool_from_str("1111101100000111101110110000011110111011000001111011101100000111101");
    vec4 = BigBool_from_str("1011111110000000011001010010101010001110010101111100001100110011000");
    res = xor(vec3, vec4);
    vecStr = BigBool_to_str(res);

    if(strcmp(vecStr, "0100010010000111110111100010110100110101010100000111100000110100101")) {
        ++failCounter;
        printf("\t-Over 64 bit vectors XOR: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vectors XOR: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(res);
    free(vecStr);
    free(vec3);
    free(vec4);
    
    return failCounter;
}

int test_left_shift() {
    printf(COLOR_CYAN "\n\nLeft shift test:\n" COLOR_RESET);
    int failCounter = 0;
    int shift = 3;

    BigBool* vec = BigBool_from_uint64(0b11010101);
    left_shift(vec, shift);
    char* vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "10101000")) {
        ++failCounter;
        printf("\t-8 bit vector left shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-8 bit vector left shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b10111010101);
    left_shift(vec, shift);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11010101000")) {
        ++failCounter;
        printf("\t-Left shift of vector of length non-multiple of eight: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Left shift of vector of length non-multiple of eight: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    left_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "1100000111101110110000011110111011000001111011101100000111101000")) {
        ++failCounter;
        printf("\t-64 bit vector left shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }    
    else {
        printf("\t-64 bit vector left shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_str("1101101100000111101110110000011110111011000001111011101100000111101");
    left_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "1101100000111101110110000011110111011000001111011101100000111101000")) {
        ++failCounter;
        printf("\t-Over 64 bit vector left shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vector left shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    return failCounter;
}

int test_right_shift() {
    printf(COLOR_CYAN "\n\nRight shift test:\n" COLOR_RESET);
    int failCounter = 0;
    int shift = 3;

    BigBool* vec = BigBool_from_uint64(0b11010101);
    right_shift(vec, shift);
    char* vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "00011010")) {
        ++failCounter;
        printf("\t-8 bit vector left shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-8 bit vector left shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b10111010101);
    right_shift(vec, shift);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "00010111010")) {
        ++failCounter;
        printf("\t-Left shift of vector of length non-multiple of eight: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Left shift of vector of length non-multiple of eight: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    right_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "0001101100000111101110110000011110111011000001111011101100000111")) {
        ++failCounter;
        printf("\t-64 bit vector left shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }    
    else {
        printf("\t-64 bit vector left shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_str("1101101100000111101110110000011110111011000001111011101100000111101");
    right_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "0001101101100000111101110110000011110111011000001111011101100000111")) {
        ++failCounter;
        printf("\t-Over 64 bit vector left shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vector left shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b11010101);
    left_shift(vec, 0);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11010101")) {
        ++failCounter;
        printf("\t-Zero shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Zero shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    return failCounter;
}

int test_left_circular_shift() {
    printf(COLOR_CYAN "\n\nLeft circular shift test:\n" COLOR_RESET);
    int failCounter = 0;
    int shift = 3;

    BigBool* vec = BigBool_from_uint64(0b11010101);
    left_circular_shift(vec, shift);
    char* vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "10101110")) {
        ++failCounter;
        printf("\t-8 bit vector left circular shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-8 bit vector left circular shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b10111010101);
    left_circular_shift(vec, shift);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11010101101")) {
        ++failCounter;
        printf("\t-Left circular shift of vector of length non-multiple of eight: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Left circular shift of vector of length non-multiple of eight: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    left_circular_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "1100000111101110110000011110111011000001111011101100000111101110")) {
        ++failCounter;
        printf("\t-64 bit vector left circular shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }    
    else {
        printf("\t-64 bit vector left circular shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_str("1101101100000111101110110000011110111011000001111011101100000111101");
    left_circular_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "1101100000111101110110000011110111011000001111011101100000111101110")) {
        ++failCounter;
        printf("\t-Over 64 bit vector left circular shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vector left circular shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b11010101);
    left_circular_shift(vec, 0);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11010101")) {
        ++failCounter;
        printf("\t-Zero shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Zero shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b11010101);
    right_shift(vec, 0);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11010101")) {
        ++failCounter;
        printf("\t-Zero shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Zero shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    return failCounter;
}

int test_right_circular_shift() {
    printf(COLOR_CYAN "\n\nRight circular shift test:\n" COLOR_RESET);
    int failCounter;

    int shift = 3;
    BigBool* vec = BigBool_from_uint64(0b11010101);
    right_circular_shift(vec, shift);
    char* vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "10111010")) {
        ++failCounter;
        printf("\t-8 bit vector right circular shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-8 bit vector right circular shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b10111010101);
    right_circular_shift(vec, shift);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "10110111010")) {
        ++failCounter;
        printf("\t-Right circular shift of vector of length non-multiple of eight: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Right circular shift of vector of length non-multiple of eight: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b1101100000111101110110000011110111011000001111011101100000111101);
    right_circular_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "1011101100000111101110110000011110111011000001111011101100000111")) {
        ++failCounter;
        printf("\t-64 bit vector right circular shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }    
    else {
        printf("\t-64 bit vector right circular shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_str("1101101100000111101110110000011110111011000001111011101100000111101");
    right_circular_shift(vec, shift);
    vecStr = BigBool_to_str(vec);
    if(strcmp(vecStr, "1011101101100000111101110110000011110111011000001111011101100000111")) {
        ++failCounter;
        printf("\t-Over 64 bit vector right circular shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Over 64 bit vector right circular shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    vec = BigBool_from_uint64(0b11010101);
    right_circular_shift(vec, 0);
    vecStr = BigBool_to_str(vec);

    if(strcmp(vecStr, "11010101")) {
        ++failCounter;
        printf("\t-Zero shift: " COLOR_RED "FAIL\n" COLOR_RESET);
    }
    else {
        printf("\t-Zero shift: " COLOR_GREEN "SUCCESS\n" COLOR_RESET);
    }

    free(vec);
    free(vecStr);

    return failCounter;
}