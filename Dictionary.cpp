// Dictionary.cpp

// This was a correct but horribly inefficient implementation of Dictionary
// functionality.  My job was to change DictionaryImpl to a more efficient
// correct implementation.  I was able to change it any way I'd like to, subject to
// restrictions in the spec (e.g., that the only C++ library container I was
// allowed to use was vector, list, stack, and queue (and string); if I
// want anything fancier, implement it).

//#include <iostream>

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <vector> //can use this according to specs
#include <algorithm>  // for swap
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl() {}
    ~DictionaryImpl() {}
	unsigned long hash(string word);
	unsigned long letterToPrime(char letter);
    void insert(string word);
	void lookup(string letters, void callback(string));// const;
  private:
	//vector< list<unsigned long> > m_words; //array of linked lists
	//array of lists
	//each list has key and word string

	list<string> table[49999];
};

unsigned long DictionaryImpl::letterToPrime(char letter)
{
	//Frequently occurring letters get assigned smaller prime numbers
	switch (letter)
	{
	case 'e':
		return 2;
		break;
	case 't':
		return 3;
		break;
	case 'a':
		return	5;
		break;
	case 'o':
		return 7;
		break;
	case 'i':
		return 11;
		break;
	case 'n':
		return 13;
		break;
	case 's':
		return 17;
		break;
	case 'h':
		return 19;
		break;
	case 'r':
		return 23;
		break;
	case 'd':
		return 29;
		break;
	case 'l':
		return 31;
		break;
	case 'c':
		return 37;
		break;
	case 'u':
		return 41;
		break;
	case 'm':
		return 43;
		break;
	case 'w':
		return 47;
		break;
	case 'f':
		return 53;
		break;
	case 'g':
		return 59;
		break;
	case 'y':
		return 61;
		break;
	case 'p':
		return 67;
		break;
	case 'b':
		return 71;
		break;
	case 'v':
		return 73;
		break;
	case 'k':
		return 79;
		break;
	case 'j':
		return 83;
		break;
	case 'x':
		return 89;
		break;
	case 'q':
		return 97;
		break;
	case 'z':
		return 101;
		break;
	default:
		return 1;
	}
}

unsigned long DictionaryImpl::hash(string word)
{
	//Primes are multiplicatively unique
	//unsigned long temp;
	unsigned long oldKey = 7919;
	//unsigned long newKey = 1;

	for (int i = 0; i < word.length(); i++)
	{
		oldKey *= letterToPrime(word[i]);
	}
	oldKey *= 104743;
	return oldKey % 49999; //mod by 49999 old key to get new key
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
	if (!word.empty())
	{
		unsigned long key = hash(word);
		//each array bucket points to a linked list with that key
		table[key].push_back(word);
	}
}

void DictionaryImpl::lookup(string letters, void callback(string)) //const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

	unsigned long key = hash(letters);
  
		for (list<string>::const_iterator wordp = table[key].begin(); wordp != table[key].end(); wordp++)
        {   
			string sortedWord = letters;
			sort(sortedWord.begin(), sortedWord.end());
			string sortedWord2 = (*wordp);
			sort(sortedWord2.begin(), sortedWord2.end());
			//if (letters.length() == (*wordp).length())
			if (sortedWord == sortedWord2)
			{
				callback(*wordp);
			}
        }
}
    
void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop off everything from "to" to end.
} 

  // Each successive call to this function generates the next permutation of the
  // characters in the parameter.  For example,
  //    string s = "eel";
  //    generateNextPermutation(s);  // now s == "ele"
  //    generateNextPermutation(s);  // now s == "lee"
  //    generateNextPermutation(s);  // now s == "eel"
  // You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code.

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}