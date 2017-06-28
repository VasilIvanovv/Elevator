#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
#include "Elevator.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;



int main(int argc, char* argv[])
{
	char* file_name = argv[1];
	Elevator elevator;
	elevator.ReadInput(file_name);
	system("pause");
	return 0;
}

