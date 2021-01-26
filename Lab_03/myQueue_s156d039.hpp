#include <iostream>

template <typename Obj>
class myQueue
{
    public:
        myQueue(void)
        :   m_size{0}, m_capacity{10}, m_front{0}, m_rear{-1}
        {
            elements = new Obj[m_capacity];
        }

        ~myQueue()
        {
            if(empty() == 0)
            {
                clear();
            }
        }

        //move constructor
        myQueue( myQueue && rhs ) 
        :   m_size{rhs.m_size}, m_capacity{rhs.m_capacity}, m_front{rhs.m_front}, m_rear{rhs.m_rear}, elements{rhs.elements}
        {
            rhs.elements = nullptr;
            rhs.m_size = 0;
            rhs.m_capacity = 0;
            rhs.m_rear = -1;
            rhs.m_front = 0;

        }

        //move overload
        myQueue & operator= (myQueue && rhs)
        {
            std::swap( m_size, rhs.m_size );
            std::swap( m_capacity, rhs.m_capacity );
            std::swap( elements, rhs.elements );
            std::swap( m_front, rhs.m_front );
            std::swap( m_rear, rhs.m_rear );
            return *this;
        }

        //copy constructor
        myQueue(const myQueue<Obj>& rhs)
        {
            m_size = rhs.m_size;
            m_capacity = rhs.m_capacity;
            m_front = rhs.m_front;
            m_rear = rhs.m_rear;
            elements = new Obj[m_capacity];
            for(int i = 0; i < rhs.m_size; ++i)
            {
                this->elements[i] = rhs.elements[i];
            }
        }

        //copy overload
        myQueue & operator= (const myQueue & rhs)
        {
            myQueue temp = rhs;
            std::swap( *this, temp );
            return *this;
        }

        void enqueue(Obj data) 
        { 
            // check queue is full or not 
            if (isFull()) { 
                resize(); 
            }
            m_rear = (m_rear + 1) % m_capacity;
            elements[m_rear] = data;
            m_size++;
        }

        Obj dequeue() 
        {  
            Obj temp = elements[m_front];
            if (empty() == 0) { 
                m_front = (m_front + 1) % m_capacity;
                m_size--;
               
                return temp; 
            }
            
        }

        Obj front()
        {
            if(empty() == 0)
            {
                return elements[m_front];
            }
        }

        void clear()
        {
           while(!empty())
           {
               dequeue();
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
            for(int i = m_front; i < size() + m_front; i++)
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
        int m_front;
        int m_rear;
        Obj *elements;
};