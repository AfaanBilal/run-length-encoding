/*
    Run-Length Encoding
    (c) Afaan Bilal
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

string to_string(int t) 
{
    ostringstream os;
    os << t;
    return os.str();
}

int main()
{
    ifstream in;

    string filename;
    string outputfile;

    cout << "Run-Length Encoding" << endl;
    cout << "https://github.com/AfaanBilal/run-length-encoding" << endl << endl;
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

        std::vector<char> compressed;

        int cCount = 1;
        char prevChar = 0;

        for(const char& c : contents)
        {
            if (c == prevChar)
                cCount++;
            else if (prevChar != 0)
            {
                compressed.push_back(prevChar);

                string count_str = to_string(cCount);
                for(const char& cc : count_str)
                    compressed.push_back(cc);

                cCount = 1;
            }

            prevChar = c;
        }

        compressed.push_back(prevChar);

        string count_str = to_string(cCount);
        for(const char& cc : count_str)
            compressed.push_back(cc);

        std::string original_str(contents.begin(), contents.end());
        std::string compressed_str(compressed.begin(), compressed.end());

        ofstream outf(outputfile, ios::out | ios::binary);
        if (outf.is_open())
            outf << compressed_str;
        else
            cout << "Error: could not open output file: " << outputfile;

        int comp_ratio = (float)compressed_str.length() / original_str.length() * 100;

        cout << endl;
        cout << "Original  : "  << original_str << endl;
        cout << "Compressed: " << compressed_str << endl;
        cout << "Compression ratio: " << comp_ratio << "%" << endl;
    }
    else
    {
        cout << "Error: could not open file: " << filename;
    }
}