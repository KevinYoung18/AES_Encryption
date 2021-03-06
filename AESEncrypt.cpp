#include <iostream>
#include <fstream>
#include <assert.h>
#include <array>
#include "aes128_constants.h"

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
array<unsigned char,4> g(array<unsigned char, 4> inputBytes, int roundNum)
{
    array<unsigned char,4> outputBytes;
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


unsigned char* get_round_key(string str)
{
    unsigned char* key = hexstr_to_uchar(str);
    cout << (int)key[0];

}

int main()
{

    string fileName;
    string key;
    ifstream input;

    cout << "Enter file name: " << endl;
    cin >> fileName;
    cout << "Enter encryption key: " << endl;
    cin >> key;
    
    input.open(fileName);

   
    input.close();
    return 0;
}