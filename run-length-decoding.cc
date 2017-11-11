/*
    Run-Length Encoding
    (c) Afaan Bilal

    DECODER
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

int to_int(string t) 
{
    return atoi(t.c_str());
}

int main()
{
    ifstream in;

    string filename;
    string outputfile;

    cout << "Run-Length Encoding" << endl;
    cout << "https://github.com/AfaanBilal/run-length-encoding" << endl << endl;
    cout << "DECODER" << endl;
    cout << "Enter input filename : ";
    cin  >> filename;
    cout << "Enter output filename: ";
    cin  >> outputfile;

    in.open(filename, ios::in | ios::binary);
    
    if(in.is_open())
    {
        streampos start = in.tellg();
        in.seekg(0, ios::end);
        streampos end = in.tellg();

        in.seekg(0, ios::beg);

        std::vector<char> contents;
        contents.resize(static_cast<size_t>(end - start));

        in.read(&contents[0], contents.size());

        std::vector<char> decompressed;

        char ch = 0;
        string countStr;

        for(const char& c : contents)
        {
            if (isalpha(c))
            {
                if (ch != 0)
                {
                    int cCount = to_int(countStr);
                    countStr = "";
                    for (int i = 0; i < cCount; i++)
                        decompressed.push_back(ch);
                }

                ch = c;
            }
            else
            {
                countStr.push_back(c);
            }
        }

        int cCount = to_int(countStr);
        countStr = "";
        for (int i = 0; i < cCount; i++)
            decompressed.push_back(ch);

        std::string original_str(contents.begin(), contents.end());
        std::string decompressed_str(decompressed.begin(), decompressed.end());

        ofstream outf(outputfile, ios::out | ios::binary);
        if (outf.is_open())
            outf << decompressed_str;
        else
            cout << "Error: could not open output file: " << outputfile;

        int comp_ratio = (float)original_str.length() / decompressed_str.length() * 100;

        cout << endl;
        cout << "Original    : "  << original_str << endl;
        cout << "Decompressed: " << decompressed_str << endl;
        cout << "Compression ratio: " << comp_ratio << "%" << endl;
    }
    else
    {
        cout << "Error: could not open file: " << filename;
    }
}