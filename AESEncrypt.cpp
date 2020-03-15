#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

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