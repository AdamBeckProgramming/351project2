#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

void MemoryManager();
struct Process
{
	int id;
	int arrivalTime;
	int completionTime;
	int numPieces;
	int totalAddressSpace;
	bool complete;
};

int main()
{
	long memSize = 0;
	int pageSize = 0;
	Process* processArray;
	int memPiece = 0;
	int time = 0;
	std::string fileName;
	std::ifstream input;
	std::ofstream output;
	std::vector<Process> processQueue;

	//Prompt user for both the memory size and page size
	std::cout << "Enter the memory size (kB): ";
	std::cin >> memSize;
	std::cout << "Enter the page size (kB): ";
	std::cin >> pageSize;

	if(pageSize > memSize)
	{
		std::cout << "Page size cannot be larger than the memory size. Restart the program.\n";
		exit(EXIT_FAILURE);
	}

	// array[memSize/pageSize]

	//Prompt user for the input file
	std::cin.ignore();
	std::cout << "Enter the input file name (including file extension): ";
	std::getline(std::cin,fileName);

	//Begin reading the input file
	input.open(fileName.c_str(), std::ifstream::in);

	//Grab first char to determine how many processes
	int b;
	input >> b;
	int counter = 0;
	processArray = new Process[b];

	while(!input.eof())
	{
		input >> processArray[counter].id;
		input >> processArray[counter].arrivalTime >>
			processArray[counter].completionTime;
		input >> processArray[counter].numPieces;
		for(int i = 0; i < processArray[counter].numPieces; i++)
		{
			input >> memPiece;
			processArray[counter].totalAddressSpace += memPiece;
		}
		processArray[counter].complete = false;
		counter++;
	}
	/*for(int i = 0; i < b; i++)
	{
		std::cout << "ProcessID: " << processArray[i].id <<std:: endl;
		std::cout << "Arrival Time: " << processArray[i].arrivalTime <<std::endl;
		std::cout << "Completion Time: " << processArray[i].completionTime << std::endl;
		std::cout << "Total Address Space: " << processArray[i].totalAddressSpace << std::endl;
	}*/

	do
	{
		for(int i = 0; i < b; i++)
			if(processArray[i].arrivalTime == time)
			{
				std::cout << "Process " << i+1 << " has arrived at time " << time << std::endl;
				processQueue.push_back(processArray[i]);
				std::cout << "Input Queue: [";
				for(int j = 0; j < processQueue.size(); j++)
					std::cout << processQueue[j].id << " ";
				std::cout << "]" << std::endl;
			}
		time++;
	}while(time < memSize);

	delete[] processArray;
	return 0;
}

void MemoryManager()
{
}
