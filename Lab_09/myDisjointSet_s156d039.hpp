# include <iostream>
# include <vector>
# include <fstream>
# include <string>

class myDisjointSet
{
    public:
        explicit myDisjointSet( int numElements ) : s( numElements, -1 )
        {
            numElem = numElements;
        }

        int find( int x ) const
        {
            if( s[ x ] < 0 )
                return x;
            else
                return find( s[ x ] );
        }

        int find( int x )
        {
            if( s[ x ] < 0 )
                return x;
            else
                return s[x]= find( s[ x ] );
        }

        void unionSets( int root1, int root2 )
        {
            int x = find(root1);
            int y = find(root2);
            if(s[x] <= s[y])
            {
                s[x] = s[x] + s[y];
                s[y] = x;
            }
            else
            {
                s[y] = s[x] + s[y];
                s[x] = y;
            }     
        }

        int getNumberElements() const
        {
            return numElem;
        }

        int getSetSize( int i ) const
        {
            int x = find(i);
            int y = -s[x];
            return y;
        }

        void print(int i)
        {
            std::cout << i << std::endl;
            if(s[i] >= 0)
            {
                print(s[i]);
            }
            return;
        }

    private:
        std::vector<int> s;
        int numElem;
};