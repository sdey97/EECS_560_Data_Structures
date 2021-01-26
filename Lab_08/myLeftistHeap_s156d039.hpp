# include <iostream>
# include <vector>
# include <fstream>
# include <string>
#include <stdexcept>

template <typename Comparable>
class myLeftistHeap
{
    public:
        myLeftistHeap( )
        :   root{nullptr}
        {

        }

        myLeftistHeap( const myLeftistHeap & rhs )
        :   root{nullptr}
        {
            root = clone( rhs.root );
        }

        myLeftistHeap( myLeftistHeap && rhs )
        :   root{rhs.root}
        {
            rhs.root = nullptr;
        }

        ~myLeftistHeap( )
        {
            makeEmpty();
        }

        myLeftistHeap & operator=( const myLeftistHeap & rhs )
        {
            myLeftistHeap copy = rhs;
            std::swap( *this, copy );
            return *this;
        }
        myLeftistHeap & operator=( myLeftistHeap && rhs )
        {
            std::swap( root, rhs.root );       
            return *this;
        }

        bool isEmpty( ) const
        {
            return root == nullptr;
        }

        const Comparable & findMin( ) const
        {
            return root->element;
        }

        void insert( const Comparable & x )
        {
            root = merge( new LeftistNode{ x }, root );
        }

        void insert( Comparable && x )
        {
            root = merge(new LeftistNode{ x }, root);
        }

        void deleteMin( )
        {
            if( isEmpty( ) )
                return;

            LeftistNode *oldRoot = root;
            root = merge( root->left, root->right );
            delete oldRoot;
        }

        void deleteMin( Comparable & minItem )
        {
            minItem = findMin( );
            deleteMin( );
        }

        void makeEmpty( )
        {
            reclaimMemory(root); 
            root = nullptr; 
        }

        void merge( myLeftistHeap & rhs )
        {
            if( this == &rhs ) 
                return;

            root = merge( root, rhs.root );
            rhs.root = nullptr;
        }

        void printInOrder()
        {
            printInOrder(root);
        }

        void printLevelOrder()
        {
            printLevelOrder(root);
        }

    private:
        struct LeftistNode
        {
            Comparable element;
            LeftistNode *left;
            LeftistNode *right;
            int npl;

            LeftistNode( const Comparable & e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np=0)
            : element{ e }, left{ lt }, right{ rt }, npl{ np}{}

            LeftistNode( Comparable && e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np=0)
            : element{ std::move( e ) }, left{ lt }, right{ rt }, npl{ np}{}
        };

        LeftistNode *root;

        LeftistNode * merge( LeftistNode *h1, LeftistNode *h2 )
        {
            if( h1 == nullptr )
                return h2;
            if( h2 == nullptr )
                return h1;
            if( h1->element < h2->element )
                return merge1( h1, h2 );
            else
                return merge1( h2, h1 );
        }

        LeftistNode * merge1( LeftistNode *h1, LeftistNode *h2 )
        {

            if( h1->left == nullptr )
                h1->left = h2; 
            else
            {
                h1->right = merge( h1->right, h2 );
                if( h1->left->npl < h1->right->npl )
                    swapChildren( h1 );
                h1->npl = h1->right->npl + 1;
            }
            return h1;
        }

        void printInOrder( LeftistNode *t, std::ostream & out = std::cout )
        {
            if( t != nullptr )
            {
                printInOrder( t->left, out );
                out << t->element << std::endl;
                printInOrder( t->right, out );
            }
        }

        void printLevelOrder( LeftistNode *t)  
        {  
            int h = level(t);
            int i;  
            for (i = 1; i <= h; i++)  
                printLevelOrder(t, i);  
        }

        void printLevelOrder( LeftistNode *t, int level)  
        {  
            if (t == nullptr)  
                return;  
            if (level == 1)  
                std::cout << t->element << std::endl;  
            else if (level > 1)  
            {  
                printLevelOrder(t->left, level-1);  
                printLevelOrder(t->right, level-1);  
            }  
        }

        int level(LeftistNode* t)  
        {  
            if (t == nullptr)  
                return 0;  
            else
            {  
                int lh, rh;
                lh = level(t->left);  
                rh = level(t->right);  
        
                if (lh > rh)  
                    return(lh + 1);  
                else return(rh + 1);  
            }  
        } 

        void swapChildren( LeftistNode *t )
        {
            LeftistNode *temp;
            temp = t->left;
            t->left = t->right;
            t->right = temp;
        }

        void reclaimMemory( LeftistNode *t )
        {
            if (t != nullptr) 
            { 
                reclaimMemory(t->left); 
                reclaimMemory(t->right); 
                delete t; 
            } 
        }

        LeftistNode * clone( LeftistNode *t ) const
        {
            if (t == nullptr) 
                return nullptr; 
            else
                return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
        }
};