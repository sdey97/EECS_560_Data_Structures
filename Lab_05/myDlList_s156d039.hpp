#include <algorithm>
#include <vector>
#include <iostream>

template <typename Obj>
class myDlList
{
    private:
        struct Node
        {
            Obj data;
            Node *nxt;
            Node *prv;

            Node( const Obj & d = Obj{}, Node * p = nullptr, Node * n = nullptr)
                : data{ d }, prv{ p }, nxt{ n } { }

            Node( const Obj && d, Node * p = nullptr, Node * n = nullptr)
                : data{ std::move(d) }, prv{ p }, nxt{ n } { }
        };

    public:
        class const_iterator
        {
            public:
                const_iterator() : current{ nullptr }
                { }

                const Obj & operator* ( ) const
                { return retrieve(); }

                const_iterator & operator++ ( )
                {
                    current = current->nxt;
                    return *this;
                }

                const_iterator operator++ ( int )
                {
                    const_iterator old = *this;
                    ++( *this );
                    return old;
                }

                const_iterator & operator-- ( )
                {
                    current = current->prv;
                    return *this;
                }

                const_iterator operator-- ( int )
                {
                    const_iterator old = *this;
                    --( *this );
                    return old;
                }

                bool operator== ( const const_iterator & rhs ) const
                    { return current == rhs.current; }
                bool operator!= ( const const_iterator & rhs ) const
                    { return !( *this == rhs ); }

                protected:
                    Node *current;

                    Obj & retrieve() const
                        { return current->data; }

                    const_iterator( Node *p ) : current{ p }
                        { }

                    friend class myDlList<Obj>;
        };

        class iterator : public const_iterator
        {
            public:
            iterator( )
                { }

            Obj & operator* ( )
                { return const_iterator::retrieve( ); }

            const Obj & operator* ( ) const
                { return const_iterator::operator*( ); }

            iterator & operator++ ( )
            {
                this->current = this->current->nxt;
                return *this;
            }

            iterator operator++ ( int )
            {
                iterator old = *this;
                ++( *this );
                return old;
            }

            iterator & operator-- ( )
            {
                this->current = this->current->prv;
                return *this;
            }

            iterator operator-- ( int )
            {
                iterator old = *this;
                --( *this );
                return old;
            }

            protected:
                iterator( Node *p ) : const_iterator{ p }
                    { }

                friend class myDlList<Obj>;
        };

    public:
        myDlList()
        {
            init();
        }

        ~myDlList()
        {
            // clear();
            delete head;
            delete tail;
        }

        myDlList( const myDlList & rhs )
        {
            init();
            for( auto & val : rhs )
                push_back( val );
        }

        myDlList & operator= ( const myDlList & rhs )
        {
            myDlList copy = rhs;
            std::swap( *this, copy );
            return *this;
        }

        myDlList( myDlList && rhs )
            : m_size{ rhs.m_size }, head{ rhs.head }, tail{ rhs.tail }
        {
            rhs.m_size = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        myDlList & operator= ( myDlList && rhs )
        {
            std::swap( m_size, rhs.m_size );
            std::swap( head, rhs.head );
            std::swap( tail, rhs.tail );

            return *this;
        }

        iterator begin()
            { return { head->nxt }; }
        const_iterator begin() const
            { return { head->nxt }; }
        iterator end()
            { return { tail }; }
        const_iterator end() const
            { return { tail }; }

        int size() const
            { return m_size; }
        bool empty() const
            { return size() == 0; }

        void clear( )
        {
            while( !empty( ) )
            pop_front( );
        }

        Obj & front( )
            { return *begin( ); }
        const Obj & front( ) const
            { return *begin( ); }
        Obj & back( )
            { return *--end( ); }
        const Obj & back( ) const
            { return *--end( ); }
        void push_front( const Obj & val )
            { insert( begin( ), val ); }
        void push_front( Obj && val )
            { insert( begin( ), std::move( val ) ); }

        void push_back( const Obj & val )
            { insert( end( ), val ); }
        void push_back( Obj && val )
            { insert( end( ), std::move( val ) ); }
            
        void pop_front( )
            { erase( begin( ) ); }
        void pop_back( )
            { erase( --end( ) ); }

        void reverselist()
        {
            Node *tmp = NULL;  
            Node *current = head;
            Node *curr_tail = tail;

            while (current != NULL)  
            {  
                tmp = current->prv;  
                current->prv = current->nxt;  
                current->nxt = tmp;              
                current = current->prv; 
            }
            
            if(tmp != NULL ){
                tail = head;
                head = tmp->prv;
            }
            return;
        }

        myDlList<Obj> appendList(myDlList<Obj>& data)
        {
            // std::cout << this->tail->nxt->data << " " << data.head->data << std::endl;
            data.head->nxt->prv = this->tail->prv;
            this->tail->prv->nxt = data.head->nxt;
            this->tail = data.tail;
            return *this;
        }

        typename myDlList<Obj> ::iterator find(typename myDlList<Obj> ::iterator from, typename myDlList<Obj> ::iterator to, const Obj & x )
        {
            iterator itr = from;
            while(itr != to)
            {
                if(itr.retrieve() == x)
                    return itr;
                itr++;
            }
            return to;
        }

        iterator insert( iterator itr, const Obj & val )
        {
            Node *p = itr.current;
            m_size++;
            return { p->prv = p->prv->nxt = new Node{ val, p->prv, p } };
        }

        iterator insert( iterator itr, Obj && val )
        {
            Node *p = itr.current;
            m_size++;
            return { p->prv = p->prv->nxt = new Node{ std::move( val ), p->prv, p } };
        }

        iterator erase( iterator itr )
        {
            Node *p = itr.current;
            iterator retVal{ p->nxt };
            p->prv->nxt = p->nxt;
            p->nxt->prv = p->prv;
            delete p;
            m_size--;
            return retVal;
        }

        iterator erase( iterator from, iterator to )
        {
            for( iterator itr = from; itr != to; )
                itr = erase( itr );

            return to;
        }

    private:
        int m_size;
        Node *head;
        Node *tail;

        void init()
        {
            m_size = 0;
            head = new Node;
            tail = new Node;
            head->nxt = tail;
            tail->prv = head;
        }
};