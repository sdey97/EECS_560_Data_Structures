# include <iostream>
# include <vector>
# include <fstream>
# include <string>

template <typename Comparable>
const Comparable & median3( std::vector<Comparable> & a, int left, int right, bool reverse )
{
    if(reverse == false)
    {
        int center = ( left + right ) / 2;

        if( a[ center ] < a[ left ] )
            std::swap( a[ left ], a[ center ] );
        if( a[ right ] < a[ left ] )
            std::swap( a[ left ], a[ right ] );
        if( a[ right ] < a[ center ] )
            std::swap( a[ center ], a[ right ] );

        std::swap( a[ center ], a[ right - 1 ] );
        return a[ right - 1 ];
    }
    else
    {
        int center = ( left + right ) / 2;

        if( a[ center ] > a[ left ] )
            std::swap( a[ left ], a[ center ] );
        if( a[ right ] > a[ left ] )
            std::swap( a[ left ], a[ right ] );
        if( a[ right ] > a[ center ] )
            std::swap( a[ center ], a[ right ] );

        std::swap( a[ center ], a[ right - 1] );
        return a[ right - 1];
    }
    
    
}

template <typename Comparable>
void insertionSort( std::vector<Comparable> & a, int left, int right, bool reverse )
{
    if(reverse == false)
    {
            for( int p = left + 1; p <= right; ++p )
            {
                Comparable tmp = std::move( a[ p ] );
                int j;

                for( j = p; j > left && tmp < a[ j - 1 ]; --j )
                    a[ j ] = std::move( a[ j - 1 ] );
                a[ j ] = std::move( tmp );
            }
    }
    else
    {
        for( int p = left + 1; p <= right; ++p )
            {
                Comparable tmp = std::move( a[ p ] );
                int j;

                for( j = p; j > left && tmp > a[ j - 1 ]; --j )
                    a[ j ] = std::move( a[ j - 1 ] );
                a[ j ] = std::move( tmp );
            }
    }
    
    
}

template <typename Comparable>
void quicksort( std::vector<Comparable> & a, int left, int right, bool reverse)
{
    if(reverse == false)
    {
        if( left + 10 <= right )
        {
            const Comparable & pivot = median3( a, left, right, reverse );
            std::cout << pivot << std::endl;

            int i = left, j = right - 1;
            for( ; ; )
            {
                while( a[ ++i ] < pivot ) { }
                while( pivot < a[ --j ] ) { }
                if( i < j )
                    std::swap( a[ i ], a[ j ] );
                else
                    break;
            }

            std::swap( a[ i ], a[ right - 1 ] ); 

            quicksort( a, left, i - 1, reverse ); 
            quicksort( a, i + 1, right, reverse );
        }
        else
        {
            insertionSort( a, left, right, reverse );
        }
    }
    else
    {
        if( left + 10 <= right )
        {
            const Comparable & pivot = median3( a, left, right, reverse );
            std::cout << pivot << std::endl;


            int i = left, j = right - 1;
            for( ; ; )
            {
                while( a[ ++i ] > pivot ) { }
                while( pivot > a[ --j ] ) { }
                if( i < j )
                    std::swap( a[ i ], a[ j ] );
                else
                    break;
            }

            std::swap( a[ i ], a[ right - 1 ] );

            quicksort( a, left, i - 1, reverse );
            quicksort( a, i + 1, right, reverse );
        }
        else
        {
            insertionSort( a, left, right, reverse );
        }
    }
    
}

template <typename Comparable>
void quickSort( std::vector<Comparable> & a, bool reverse = false)
{
    quicksort( a, 0, a.size( ) - 1, reverse );
}