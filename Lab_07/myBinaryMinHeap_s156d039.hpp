#include <functional>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

template <typename Comparable>
class myBinaryMinHeap
{
    public:
        explicit myBinaryMinHeap(int capacity = 100)
            : heap( capacity ), currentSize{0}
        {

        }

        explicit myBinaryMinHeap( const std::vector<Comparable> & items )
            : heap( items.size( ) + 10 ), currentSize{ items.size( ) }
        {
            for( int i = 0; i < items.size( ); ++i )
                heap[ i+1]= items[ i ];
            buildHeap( );
        }

        bool isEmpty( ) const
        {
            return currentSize == 0;
        }
        const Comparable & findMin( ) const
        {
            if( isEmpty( ) )
                std::cerr << " Error: heap is empty\n";

            return heap[1];
        }

        void insert( const Comparable & x )
        {
            if( currentSize == heap.size( )-1)
                heap.resize( heap.size( ) * 2 );          

             int hole = ++currentSize;
             Comparable copy = x;

             heap[ 0 ] = std::move( copy );
             for( ; x < heap[ hole / 2 ]; hole /= 2 )
                heap[ hole ] = std::move( heap[ hole / 2 ] );
             heap[ hole ] = std::move( heap[ 0 ] );
        }

        void insert( Comparable && x )
        {
            if( currentSize == heap.size( )-1)
                heap.resize( heap.size( ) * 2 );          

             int hole = ++currentSize;

             heap[ 0 ] = std::move( x );
             for( ; x < heap[ hole / 2 ]; hole /= 2 )
                heap[ hole ] = std::move( heap[ hole / 2 ] );
             heap[ hole ] = std::move( heap[ 0 ] );
        }

        void deleteMin( )
        {
            if( isEmpty( ) )
                std::cerr << " Error: heap is empty\n";

            heap[ 1 ] = std::move( heap[ currentSize-- ] );
            percolateDown( 1 );
        }

        void deleteMin( Comparable & minItem )
        {
            if( isEmpty( ) )
                std::cerr << " Error: heap is empty\n";

            minItem = std::move( heap[ 1 ] );
            heap[ 1 ] = std::move( heap[ currentSize-- ] );
            percolateDown( 1 );
        }

        void makeEmpty( )
        {
            while(!isEmpty())
            {
                deleteMin();
            }
        }

        void levelOrder(std::ostream & out)
        {
            for(int i = 1; i <= currentSize; i++)
            {
                out << heap[i] << std::endl;
            }
        }

    private:
        int currentSize;
        std::vector<Comparable> heap;

        void buildHeap( )
        {
            for( int i = currentSize / 2; i > 0; --i )
                percolateDown( i );
        }
        void percolateDown( int hole )
        {
            int child;
            Comparable tmp = std::move( heap[ hole ] );

            for( ; hole * 2 <= currentSize; hole = child )
            {
                child = hole * 2;
                if( child != currentSize && heap[ child +1]< heap[ child ] )
                    ++child;
                if( heap[ child ] < tmp )
                    heap[ hole ] = std::move( heap[ child ] );
                else
                    break;
            }
            heap[ hole ] = std::move( tmp );
        }
 };