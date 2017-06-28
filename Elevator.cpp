#include "stdafx.h"
#include "Elevator.h"
#include "PriorityQueue.h"
#include "Queue.h"
#include <iostream>
#include <fstream>
using namespace std;

const int FLOOR_TIME = 5;

PriorityQueue<int> p_queue;

Elevator::Elevator()
{
	time_elapsed = 0;
	current_floor = 1;
}


Elevator::~Elevator()
{
}

void Elevator::ReadInput(char* file_name)
{
	ifstream file(file_name, ios::binary | ios::ate);
	if (!file)
	{
		cerr << "Error with the file with the input" << endl;;
	}
	unsigned int filesize = (unsigned int)file.tellg();
	file.seekg(0, ios::beg);
	char* file_buffer = new char[filesize + 2];
	file.read(file_buffer, filesize);
	file.close();
	file_buffer[filesize] = '\n';
	file_buffer[filesize + 1] = 0;
	char floors[32];
	char requests[32];
	int i = 0;
	while (*file_buffer != ' ')
	{
		floors[i] = *file_buffer;
		*file_buffer++;
		i++;
	}
	*file_buffer++;
	floors_num = atoi(floors);
	int k = 0;
	while (*file_buffer != '\n')
	{
		requests[k] = *file_buffer;
		k++;
		*file_buffer++;
	}
	*file_buffer++;
	requests_num = atoi(requests);
	ParseRequests(file_buffer);
}


void Elevator::ParseRequests(char* file_buffer)
{
	char direction[5];
	char* floor = new char[8];
	char time[8];
	for (int count = 0; count < requests_num; count++)
	{
		char* command = new char[8];
		int i = 0;
		while (*file_buffer != ' ' && *file_buffer != '\n')
		{
			command[i] = file_buffer[0];
			i++;
			*file_buffer++;
		}
		command[i] = '\0';
		*file_buffer++;
		if (strcmp(command, "call") == 0)
		{
			int k = 0;
			while (*file_buffer != ' ' && *file_buffer != '\n')
			{
				direction[k] = file_buffer[0];
				k++;
				*file_buffer++;
			}
			direction[k] = '\0';
			*file_buffer++;
			int z = 0;
			while (*file_buffer != ' ' && *file_buffer != '\n')
			{
				floor[z] = file_buffer[0];
				z++;
				*file_buffer++;
			}
			floor[z] = '\0';
			*file_buffer++;
			int j = 0;
			while (*file_buffer != ' ' && *file_buffer != '\n' && file_buffer != NULL)
			{
				time[j] = file_buffer[0];
				j++;
				*file_buffer++;;
			}
			time[j] = '\0';
			*file_buffer++;
			int floor_ = atoi(floor);
			int time_ = atoi(time);
			i++;
			p_queue.Insert(floor_, time_);
		}
		else if (strcmp(command, "go") == 0)
		{
			int p = 0;
			while (*file_buffer != ' ' && *file_buffer != '\n')
			{
				floor[p] = file_buffer[0];
				p++;
				*file_buffer++;
			}
			floor[p] = '\0';
			*file_buffer++;
			int q = 0;
			while (*file_buffer != ' ' && *file_buffer != '\n')
			{
				time[q] = file_buffer[0];
				q++;
				*file_buffer++;;
			}
			time[q] = '\0';
			*file_buffer++;
			int floor_ = atoi(floor);
			int time_ = atoi(time);
			p_queue.Insert(floor_, time_);
		}
	}
	SortRequests();
	//delete[] file_buffer;
}


void Elevator::SortRequests()
{
	if (floors_num == 1)
	{
		while (!p_queue.IsEmpty())
		{
			int temp_priority = p_queue.FrontPriority();
			cout << temp_priority + 1<< " 1 down" << endl;
			p_queue.Peek();
		}
	}
	int i = 0;
	int last_time_elapsed = 0;
	PriorityQueue<int> temp_queue;
	Queue<int> result;
	int length = p_queue.Length();
	int result_length = 0;
	while (result_length != length)
	{
		int go_to_floor = p_queue.FrontData();
		time_elapsed += abs((current_floor - go_to_floor) * 5);
		PriorityQueue<int> queue1;
		while (!p_queue.IsEmpty())
		{
			if (temp_queue.IsEmpty())
			{
				int temp_data = p_queue.Peek();
				temp_queue.Insert(temp_data, temp_data);
			}
			else
			{
				if (current_floor - go_to_floor < 0)
				{
					if (time_elapsed > p_queue.FrontPriority() &&
						(abs(p_queue.FrontData() - current_floor) * 5 + last_time_elapsed) > p_queue.FrontPriority() &&
						p_queue.FrontData() >= current_floor &&
						p_queue.FrontData() <= go_to_floor)
					{
						int temp_data = p_queue.Peek();
						temp_queue.Insert(temp_data, temp_data);
					}
					else
					{
						int temp_priority = p_queue.FrontPriority();
						queue1.Insert(p_queue.Peek(), temp_priority);
					}
				}
				else if (current_floor - go_to_floor > 0)
				{
					if (time_elapsed > p_queue.FrontPriority() &&
						(abs(p_queue.FrontData() - current_floor) * 5 + last_time_elapsed) > p_queue.FrontPriority() &&
						p_queue.FrontData() <= current_floor &&
						p_queue.FrontData() >= go_to_floor)
					{
						int temp_data = p_queue.Peek();
						temp_queue.Insert(temp_data, temp_data);
					}
					else
					{
						int temp_priority = p_queue.FrontPriority();
						queue1.Insert(p_queue.Peek(), temp_priority);
					}
				}
			}
		}
		while (!temp_queue.IsEmpty())
		{
			if (current_floor > go_to_floor)
			{
				result.Insert(temp_queue.PeekEnd());
				result_length++;
			}
			else
			{
				result.Insert(temp_queue.Peek());
				result_length++;
			}
		}
		current_floor = result.LastData();
		i++;
		last_time_elapsed = time_elapsed;
		p_queue = queue1;
	}
	int time = 1;
	int cur_floor = 1;
	int* printed_floors = new int[requests_num + 1];
	int counter = 0;
	while (!result.IsEmpty())
	{
		bool check = true;
		int last_floor = result.Peek();
		time += abs((last_floor - cur_floor)*5);
		printed_floors[counter] = last_floor;
		if (last_floor == printed_floors[counter - 1])
		{
			check = false;
		}
		if (check == true)
		{
			if (last_floor > cur_floor)
			{
				cout << time << " " << last_floor << " up" << endl;
			}
			else cout << time << " " << last_floor << " down" << endl;
		}
		cur_floor = last_floor;
		counter++;
	}
}



