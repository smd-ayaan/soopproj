#include<iostream>

#include"RingBuffer.hpp"

int main()
{
	RingBuffer<int> ring = RingBuffer<int>(10);
	ring.push(55);
	//ring.test();

	return 0;
}
