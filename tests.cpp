#include <iostream>
#include <fstream>
#include <assert.h>
#include "aes128_constants.h"
#include <array>

using namespace std;

//@param: a string of length = 2 corresponding to a hex byte e.g. 1F
//@return: an unsigned char corresponding to the passed string e.g. 0x1F
unsigned char str_to_byte(string str)
{
    assert(str.length() == 2);
    unsigned char result = 0x00;
    char firstchar = str[0];
    char lastchar = str[1];

    if(isdigit(firstchar))
    {
        result += (firstchar - 48) * 16;
    }
    else if(isalpha(firstchar))
    {
        firstchar = tolower(firstchar);
        assert(firstchar <= 'f');
        result += (firstchar - 87) * 16;
    }
    else return -1;

    if(isdigit(lastchar))
    {
        result += (lastchar - 48);
    }
    else if(isalpha(lastchar))
    {
        lastchar = tolower(lastchar);
        assert(lastchar <= 'f');
        result += (lastchar - 87);
    }
    else return -1;

    return result;
}

//@param a string representing 16 bytes in hex, can accept strings with whitespace, lowercase and uppercase 
//  e.g. ff 09 a0 f0 f1 FA 01 10 ff 09 a0 F0 f1 ff 01 10
//@return: a pointer to an array of unsigned chars corresponding to the passed string
unsigned char* hexstr_to_uchar(string str)
{
    const int SIZE = 16;
    static unsigned char uchar_array[SIZE];

    int i = 0;
    for(int j = 0; j < SIZE; j++)
    {
        string byte_str = "";
        
        while(byte_str.length() < 2)
        {
            if(isalnum(str[i]))
            {
                byte_str += str[i];
            }
            i++;
        }
        uchar_array[j] = str_to_byte(byte_str);
    }

    return uchar_array;
}

//performs the g function of AES on an array of 4 unsigned chars
//@param: inputBytes: the input array of of 4 unsigned chars
//@param: roundNum: the current round of transformation in the AES 
//@return: the result of the g function on inputBytes as an array of 4 unsigned chars
array<unsigned char, 4> g(array<unsigned char, 4> inputBytes, int roundNum)
{
    array<unsigned char, 4> outputBytes;
    outputBytes[0] = inputBytes[1];
    outputBytes[1] = inputBytes[2];
    outputBytes[2] = inputBytes[3];
    outputBytes[3] = inputBytes[0];

    for(int i = 0; i < 4; i++)
    {
        outputBytes[i] = sbox[(int)outputBytes[i]];
    }

    outputBytes[0] = outputBytes[0] ^ rcon[roundNum];
    return outputBytes;
}

//TODO fix me 
//performs a transform on a round key
//@param: inputKey: the previous round key
//@param: roundNum: the round number (0-11)
//@return: an array of unsigned char corresponding to the round key
array<unsigned char, 16> transform(array<unsigned char, 16> inputKey , int roundNum)
{
    //pass the last 4 bytes through the g function and xor with the first 4 bytes
    array<unsigned char, 4> lastBytes;
    for(int i = 0; i < 4; i++)
    {
        lastBytes[i] = inputKey[i+11];
    }
    lastBytes = g(lastBytes, roundNum);
    for(int i = 0; i < 4; i++)
    {
        inputKey[i] = inputKey[i] ^ lastBytes[i];
    }

    //xor bytes 4 - 15 with bytes 0-11 respectively
    for(int i = 1; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int index = (i*4) +j;
            int lastIndex = (i-1) * 4 + j;
            inputKey[index] = inputKey[index] ^ inputKey[lastIndex];
        }
    }
}

array<array<unsigned char, 16>,11> get_key_schedule(string str)
{
    unsigned char* currentKey = hexstr_to_uchar(str);
    array<array<unsigned char, 16>,11> keySchedule;
    
    for(int i = 0; i < 11; i++)
    {
        unsigned char roundKey[16];
        //transform
    }

}
array<int, 2> getarr()
{
    array<int, 2> arr = {1,2};
    return arr;
}
int main()
{
    //get_key_schedule("ff 09 a0 f0 f1 ff 01 10 ff 09 a0 f0 f1 ff 01 10");
     array<unsigned char,4> in = {0x00, 0x01, 0x10, 0xFF};
    array<unsigned char,4> o = g(in, 0);
    for(int i = 0; i < 4; i++)
    {
        cout << (int)o[i] << " ";
    }

    cout << endl;

     array<unsigned char,16 > in1 = 
    {0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x10, 0xFF};
    array<unsigned char,16> o1 = transform(in1, 0);
    for(int i = 0; i < 16; i++)
    {
        cout << (int)o1[i] << " ";
    }
    return 0;
}