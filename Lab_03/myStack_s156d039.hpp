#include <iostream>

template <typename Obj>
class myStack
{
    public:
        myStack(void)
        :   m_size{0}, m_capacity{10}, m_top{-1}
        {
            elements = new Obj[m_capacity];
        }

        ~myStack()
        {
            if(empty() == 0)
            {
                clear();
            }
        }

        //move constructor
        myStack( myStack && rhs ) 
        :   m_size{rhs.m_size}, m_capacity{rhs.m_capacity}, m_top{rhs.m_top}, elements{rhs.elements}
        {
            rhs.elements = nullptr;
            rhs.m_size = 0;
            rhs.m_capacity = 0;
            rhs.m_top = -1;

        }

        //move overload
        myStack & operator= (myStack && rhs)
        {
            std::swap( m_size, rhs.m_size );
            std::swap( m_capacity, rhs.m_capacity );
            std::swap( elements, rhs.elements );
            std::swap( m_top, rhs.m_top );
            return *this;
        }

        //copy constructor
        myStack(const myStack<Obj>& rhs)
        {
            m_size = rhs.m_size;
            m_capacity = rhs.m_capacity;
            m_top = rhs.m_top;
            elements = new Obj[m_capacity];
            for(int i = 0; i < rhs.m_size; ++i)
            {
                this->elements[i] = rhs.elements[i];
            }
        }

        //copy overload
        myStack & operator= (const myStack & rhs)
        {
            myStack temp = rhs;
            std::swap( *this, temp );
            return *this;
        }

        void push(Obj x)
        {
            if(isFull())
            {
                resize();
            }
            m_size++;
            elements[++m_top] = x;
        }

        Obj pop()
        {
            if(empty() == 0)
            {
                m_size--;
                return elements[m_top--];
            }
        }

        Obj top()
        {
            if(empty() == 0)
            {
                return elements[m_top];
            }
        }

        void clear()
        {
           while(!empty())
           {
               pop();
           }
        }

        bool isFull()
        {
            if(size() == m_capacity)
            {
                return true;
            }
            return false;
        }

        void resize()
        {
            this->m_capacity *= 2;
            Obj *temp = new Obj[m_capacity];
            for(int i = 0; i < size(); i++)
            {
                temp[i] = elements[i];
            }
            elements = temp;
            temp = nullptr;
        }

        int empty()
        {
            if(size() == 0)
            {
                return 1;
            }
            return 0;
        }

        int size() const
        {
            return m_size;
        }


    private:
        int m_size;
        int m_capacity;
        int m_top;
        Obj *elements;
};