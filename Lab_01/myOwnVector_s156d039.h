#include <algorithm>
#include <vector>
#include <iostream>

template <typename Vec>
class myOwnVector
{
    public:
        //constructor
        explicit myOwnVector( int init = 0) 
        :   m_size{init}, m_capacity{init + SPARE_CAPACITY}
        {
            vecs = new Vec[m_capacity];
        }

        //copy contructor
        myOwnVector( const myOwnVector & rhs ) 
        :   m_size{rhs.m_size}, m_capacity{rhs.m_capacity}, vecs{nullptr}
        {
            vecs = new Vec[m_capacity];
            for(int i = 0; i < m_size; ++i)
            {
                vecs[i] = rhs.vecs[i];
            }
        }

        //move constructor -- moves rhs to new vector
        //and depopulates the rhs
        myOwnVector( myOwnVector && rhs ) 
        :   m_size{rhs.m_size}, m_capacity{rhs.m_capacity}, vecs{rhs.vecs}
        {
            rhs.vecs = nullptr;
            rhs.m_size = 0;
            rhs.m_capacity = 0;
        }

        //copy constructor using STL init
        myOwnVector(const std::vector<Vec>& data)
        {
            m_size = data.m_size;
            m_capacity = data.m_capacity;
            for(int i = 0; i < data.m_size; ++i)
            {
                this->vecs[i] = data.vecs[i];
            }
        }

        //operator overload -- copy lhs
        myOwnVector & operator= (const myOwnVector & rhs)
        {
            myOwnVector temp = rhs;
            std::swap( *this, temp );
            return *this;
        }

        //operator overload -- swap lhs and rhs
        myOwnVector & operator= (myOwnVector && rhs)
        {
            std::swap( m_size, rhs.m_size );
            std::swap( m_capacity, rhs.m_capacity );
            std::swap( vecs, rhs.vecs );
            return *this;
        }

        Vec & operator[] (int idx)
        {
            return vecs[idx];
        }
        
        const Vec & operator[] (int idx) const
        {
            return vecs[idx];
        }
        
        int size() const
        {
            return m_size;
        }

        bool empty() const
        {
            return size() == 0;
        }

        int capacity() const
        {
            return m_capacity;
        }

        //resize
        void resize(int newSize)
        {
            if( newSize > m_capacity )
                freeSpace( newSize * 2 );
            m_size = newSize;
        }

        //reserve
        void freeSpace(int newCapacity)
        {
            if(newCapacity < m_size)
            {
                return;
            }

            Vec *newVecs = new Vec[newCapacity];
            for(int i = 0; i < m_size; ++i) //++i
                newVecs[i] = std::move( vecs[i] );
            
            m_capacity = newCapacity;
            std::swap( vecs, newVecs );
            delete [ ] newVecs;
        }

        //push_back
        void push_back( const Vec & val)
        {
            if(m_size == m_capacity)
                freeSpace( 2 * m_size + 1);
            
            vecs[m_size++] = val;
        }

        //push_back
        void push_back( Vec && val)
        {
            if(m_size == m_capacity)
                freeSpace( 2 * m_size + 1);
            
            vecs[m_size++] = std::move(val);
        }

        //remove last element
        void pop_back()
        {
            m_size--;
        }

        //print last element
        const Vec & back ( ) const
        {
            return vecs[ m_size - 1 ];
        }

        typedef Vec * iterator;
        typedef const Vec * const_iterator;

        iterator begin( )
        { 
            return &vecs[ 0 ]; 
        }
        const_iterator begin( ) const
        { 
            return &vecs[ 0 ]; 
        }
        iterator end( )
        { 
            return &vecs[ size( ) ];  
        }
        const_iterator end( ) const
        { 
            return &vecs[ size( ) ]; 
        }

        myOwnVector<Vec>& append(const myOwnVector<Vec>& data)
        {
            int original_size = m_size;
            for(int i = 0; i < data.m_size; ++i)
            {
                this->push_back(data.vecs[i]);
            }
            return *this;
        }

        static const int SPARE_CAPACITY = 16;

    private:
        int m_size;
        int m_capacity;
        Vec *vecs;
};