#include <functional>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

template <typename Obj, typename Comparator=std::less<Obj>>
class myBinarySearchTree
{
    public:
        //default constructor
        myBinarySearchTree(void)  
        :   m_root{nullptr}
        {

        }
        //copy constructor
        myBinarySearchTree( const myBinarySearchTree & rhs ) : m_root{ nullptr }
        {
            m_root = clone( rhs.root );
        }
        //move constructor
        myBinarySearchTree( myBinarySearchTree && rhs ) : m_root{rhs.m_root}
        {
            rhs.m_root = nullptr;
        }
        //destructor
        ~myBinarySearchTree( )
        {
            makeEmpty( );
        }

        bool contains( const Obj & x ) const
        {
            return contains( x, m_root );
        }

        void insert( const Obj & x )
        {
            insert( x, m_root );
        }

        void insert( Obj && x )
        {
            insert( x, m_root );
        }

        void remove( const Obj & x )
        {
            remove( x, m_root );
        }

        const Obj & findMin( ) const
        {
            findMin(m_root);
        }

        const Obj & findMax( ) const
        {
            findMax(m_root);
        }

        bool isEmpty( ) const
        {
            return m_root == nullptr;
        }
            
        void makeEmpty()
        {
            makeEmpty(m_root);
        }

        void printTree( std::ostream & out = std::cout ) const
        {
            if( !isEmpty( ) )
                printTree( m_root, out );
        }
        //copy overload
        myBinarySearchTree & operator=( const myBinarySearchTree & rhs )
        {
            myBinarySearchTree copy = rhs;
            std::swap( *this, copy );
            return *this;
        }
        
        //move overload
        myBinarySearchTree & operator=( myBinarySearchTree && rhs )
        {
            std::swap( m_root, rhs.root );       
            return *this;
        }
        //public facing traversal functions
        void printTreeInorder( std::ostream & out = std::cout )
        {
            if( !isEmpty( ) )
                printTreeInorder( m_root, out );
        }

        void printTreePreorder( std::ostream & out = std::cout )
        {
            if( !isEmpty( ) )
                printTreePreorder( m_root, out );
        }

        void printTreePostorder( std::ostream & out = std::cout )
        {
            if( !isEmpty( ) )
                printTreePostorder( m_root, out );
        }

    
    private:

        struct BinaryNode
        {
            Obj element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode( const Obj & theElement, BinaryNode *lt, BinaryNode *rt )
            :    element{ theElement }, left{ lt }, right{ rt } { }

            BinaryNode( Obj && theElement, BinaryNode *lt, BinaryNode *rt )
            :    element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
        };

        BinaryNode* m_root;
        Comparator isLessThan;

        BinaryNode * clone( BinaryNode *t ) const
        {
            if( t == nullptr )
                return nullptr;
            else
                return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
        }

        void makeEmpty( BinaryNode * & t )
        {
            if( t != nullptr )
            {
                makeEmpty( t->left );
                makeEmpty( t->right );
                delete t;
            }
            t = nullptr;
        }

        bool contains( const Obj & x, BinaryNode *t ) const
        {
            if( t == nullptr )
                return false;
            else if( isLessThan( x, t->element ) )
                return contains( x, t->left );
            else if( isLessThan( t->element, x ) )
                return contains( x, t->right );
            else
                return true;
        }

        void insert( const Obj & x, BinaryNode *&t)
        {
            if( t == nullptr )
                t = new BinaryNode{ x, nullptr, nullptr };
            else if( x < t->element )
                insert( x, t->left );
            else if( t->element < x )
                insert( x, t->right );
            else
                ;
        }
    
        void insert( Obj && x, BinaryNode *&t)
        {
            if( t == nullptr )
                t = new BinaryNode{ std::move( x ), nullptr, nullptr };
            else if( x < t->element )
                insert( std::move( x ), t->left );
            else if( t->element < x )
                insert( std::move( x ), t->right );
            else
                ;
        }
        //private facing find max and min
        BinaryNode * findMin( BinaryNode *t ) const
        {
            if( t == nullptr )
                return nullptr;
            if( t->left == nullptr )
                return t;
            return findMin( t->left );
        }

        BinaryNode * findMax( BinaryNode *t ) const
        {
            if( t != nullptr )
                while( t->right != nullptr )
                    t = t->right;
            return t;
        }
        //private facing remove
        void remove( const Obj & x, BinaryNode * & t )
        {
            if( t == nullptr )
                return;  
            if( x < t->element )
                remove( x, t->left );
            else if( t->element < x )
                remove( x, t->right );
            else if( t->left != nullptr && t->right != nullptr )
            {
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
            else
            {
                BinaryNode *temp = t;
                t = ( t->left != nullptr ) ? t->left : t->right;
                delete temp;
            }
        }

        void printTree( BinaryNode *t, std::ostream & out ) const
        {
            if( t != nullptr )
            {
                printTree( t->left, out );
                out << t->element << std::endl;
                printTree( t->right, out );
            }
        }
        //private facing traversal functions
        void printTreeInorder( BinaryNode *t, std::ostream & out = std::cout )
        {
            if( t != nullptr )
            {
                printTreeInorder( t->left, out );
                out << t->element << std::endl;
                printTreeInorder( t->right, out );
            }
        }

        void printTreePreorder( BinaryNode *t, std::ostream & out = std::cout )
        {
            if( t != nullptr )
            {
                out << t->element << std::endl;
                printTreePreorder( t->left, out );
                printTreePreorder( t->right, out );
            }
        }

        void printTreePostorder( BinaryNode *t, std::ostream & out = std::cout )
        {
            if( t != nullptr )
            {
                printTreePostorder( t->left, out );
                printTreePostorder( t->right, out );
                out << t->element << std::endl;
            }
        }        
    };