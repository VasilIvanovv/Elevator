#pragma once
class Elevator
{
public:
	Elevator();
	~Elevator();
	void ReadInput(char*);
	void ParseRequests(char*);
	void SortRequests();
private:
	int current_floor;
	int floors_num;
	int requests_num;
	int time_elapsed;
	char direction[5];
};

