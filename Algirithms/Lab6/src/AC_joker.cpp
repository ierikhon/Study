#include "AC_joker.h"

Bor makeBor(int parentN, char sym)
{
    Bor borS;
    for(int i=0; i<52; i++)
        borS.next[i] = borS.auto_move[i] = -1;
    borS.isStr = false;
    borS.suffixL = -1;
    borS.parent = parentN;
    borS.symbol = sym;
    borS.CompressedSuffixL = -1;
    return borS;
}

void addtoBor(string s,  vector<Bor> bor, vector<string>& patterns)
{
    int number = 0;
    for (size_t i=0; i<s.length(); i++)
    {
        char sym = s[i] - 'A';
        if (bor[number].next[sym] == -1)
        {
            bor.push_back(makeBor(number, sym));
            bor[number].next[sym] = bor.size() - 1;
        }
        number = bor[number].next[sym];
    }
    bor[number].isStr = true;
    patterns.push_back(s);
    bor[number].patternNumber.push_back(patterns.size() - 1);
}

int getLink(int node, vector<Bor> bor)
{
    if (bor[node].suffixL == -1)
        if (node == 0 || bor[node].parent == 0)
            bor[node].suffixL = 0;
        else
            bor[node].suffixL = getAM(getLink(bor[node].parent, bor), bor[node].symbol, bor);
    return bor[node].suffixL;
}

int getAM(int node, char sym, vector<Bor> bor)
{
    if (bor[node].auto_move[sym] == -1)
        if (bor[node].next[sym] != -1)
            bor[node].auto_move[sym] = bor[node].next[sym];
        else
        {
            if (node == 0)
                bor[node].auto_move[sym] = 0;
            else
                bor[node].auto_move[sym] = getAM(getLink(node, bor), sym, bor);
        }
    return bor[node].auto_move[sym];
}

int getCompressedLink(int node, vector<Bor> bor)
{
    if (bor[node].CompressedSuffixL == -1)
    {
        int link = getLink(node, bor);
        if (link == 0)
            bor[node].CompressedSuffixL = 0;
        else
        {
            if (bor[link].isStr)
                bor[node].CompressedSuffixL = link;
            else bor[node].CompressedSuffixL = getCompressedLink(link, bor);
        }
    }
    return bor[node].CompressedSuffixL;
}

void AC(const string& s,vector<int>& count,const vector<int>& lenght, vector<Bor> bor, vector<string> patterns)
{
    int u = 0;
    for(size_t i = 0; i < s.length(); i++)
    {
        u = getAM(u, s[i] - 'A', bor);
        for(int j = u; j != 0; j = getCompressedLink(j, bor))
            if (bor[j].isStr)
                for(const auto& current: bor[j].patternNumber)
                    if(i+1-lenght[current]<count.size())
                        count[i+1-lenght[current]]++;
    }
}