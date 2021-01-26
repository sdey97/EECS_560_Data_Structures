#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "myDlList_s156d039.hpp"
using namespace std;

template <typename HashedObj>
class myHashTable
{
    public:
        explicit myHashTable( int size = 101 )
        :   theLists( size ), currentSize{0}
        {

        }

        bool contains( const HashedObj & x )
        {
            auto & whichList = theLists[ myhash( x ) ];

            return whichList.find( whichList.begin(), whichList.end(), x ) != whichList.end();
        }

        void makeEmpty( )
        {
            for( auto & thisList : theLists )
                thisList.clear( );
        }

        bool insert( const HashedObj & x )
        {
            auto & whichList = theLists[ myhash( x ) ];
            if( whichList.find( whichList.begin(), whichList.end(), x ) != whichList.end() )
                return false;
            whichList.push_back( x );

            if( ++currentSize > theLists.size( ) )
                rehash( );

            return true;
        }

        bool insert( HashedObj && x )
        {
            auto & whichList = theLists[ myhash( x ) ];
            if( whichList.find( whichList.begin(), whichList.end(), x ) != whichList.end() )
                return false;
            whichList.push_back( x );

            if( ++currentSize > theLists.size( ) )
                rehash( );

            return true;
        }

        bool remove( const HashedObj & x )
        {
            auto & whichList = theLists[ myhash( x ) ];
            auto itr = whichList.find( whichList.begin(), whichList.end(), x );

            if( itr == whichList.end() )
                return false;

            whichList.erase( itr );
            --currentSize;
            return true;
        }

        typename myDlList<HashedObj> ::iterator getiteratorbegin(int index)
        {
            return theLists[index].begin();
        }

        typename myDlList<HashedObj> ::iterator getiteratorend(int index)
        {
            return theLists[index].end();
        }

        int hashsize()
        {
            return theLists.size();
        }

    private:
        vector<myDlList<HashedObj>> theLists; // The array of Lists
        int currentSize;

        void rehash( )
        {
            vector<myDlList<HashedObj>> oldLists = theLists;

            // Create new double-sized, empty table
            theLists.resize( nextPrime( 2 * theLists.size( ) ) );
            for( auto & thisList : theLists )
                thisList.clear( );

            // Copy table over
            currentSize = 0;
            for( auto & thisList : oldLists )
                for( auto & x : thisList )
                    insert( move( x ) );
        }

        size_t myhash( const HashedObj & x ) const
        {
            static hash<HashedObj> hf;
            return hf( x ) % theLists.size( );
        }

        bool isPrime(int x)
        {
            if(x == 1) return false;

            for (int i = 2; i <= x/2; i++)
            {
                if(x % i == 0)
                    return false;
            }
            return true;
        }

        int nextPrime(int n)
        {
            int num = n;
            bool found = false;

            while (!found)
            {
                num++;
                if(isPrime(num))
                    found = true;
            }

            return num;
        }
};

template <typename hashitem>
class hash
{
 public:
  size_t operator()( const hashitem & key )
       {
        size_t hashVal = 0;
        for( char ch : key )
              hashVal = 37 * hashVal + ch;
        return hashVal;
       }
};