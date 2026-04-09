#include<cassert>

template<typename T>
class RingBuffer
{
	private:
		int max_size;
		T *buffer;
		int size;
		int head, tail;

	public:
		RingBuffer() = delete;

		RingBuffer(int max_size)
		{
			this->max_size = max_size;
			buffer = new T[max_size];
			size = head = tail = 0;
		}

		~RingBuffer()
		{
			delete[] buffer;
		}



		void push(T data)
		{
			if(size!=max_size)
			{
				buffer[head] = data;
				head = (head+1)%max_size;
				size++;
			}
		}



		void pop()
		{
			if(size!=0)
			{
				tail = (tail+1)%max_size;
				size--;
			}
		}

		T at(int index)
		{
			//assert(index<size && "index out of bounds");
			return buffer[((tail+index)%max_size)];
			
			//throw std::out_of_range("index out of bounds");
		}
		
		
		int getSize(){return size;}


		bool isEmpty(){return size==0;}

	
		void test()
		{
			std::cout<< "SIZE: " << size <<"\n";
			std::cout<<"DATA:  ";
			
			for(int i=0;i<size;i++)
			{
				std::cout<< buffer[i] <<"  ";
			}
			std::cout<<"\n";
		}


};








//Changes:
//--use size_t instead of int
//--proper error handling-----do bool push() instead of void push()
//--etc
