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
	int turnAroundTime;
	int waitTime;
	int numPieces;
	int totalAddressSpace;
	bool complete;
};

int main()
{
	long memSize = 0;
	long pageSize = 0;
	Process* processArray;
	int memPiece = 0;
	int time = 0;
	int frameSize;
	int totalTurnAroundTime = 0;
	float averageTurnAroundTime = 0.;
	int completeCounter = 0;
	bool chainComplete = false;
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

	// Create the simulated memory array[memSize/pageSize]
	frameSize = memSize / pageSize;
	Process memory[frameSize];

	//Prompt user for the input file
	std::cin.ignore();
	std::cout << "Enter the input file name (including file extension): ";
	std::getline(std::cin,fileName);

	//Begin reading the input file
	input.open(fileName.c_str(), std::ifstream::in);

	//Grab first char to determine how many processes
	int numOfProcesses;
	input >> numOfProcesses;
	int counter = 0;
	processArray = new Process[numOfProcesses];

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
		processArray[counter].waitTime = 0;
		counter++;
	}

	// Main part of the memory manager
	do
	{
		// Place process on the queue
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

		for(int i = 0; i < memSize/pageSize; i++)
		{
			// Process Complete
			if(memory[i].completionTime + memory[i].waitTime == time)
			{
				memory[i].complete = true;
				memory[i].turnAroundTime = (memory[i].completionTime + memory[i].waitTime) - memory[i].arrivalTime;
				totalTurnAroundTime += memory[i].turnAroundTime;
				completeCounter++;
			}
			// Process in queue
			if(!processQueue.empty())
			{
				for(int i = 0; i < processQueue.size() - 1; i++)
				{
					if(/* there is enough frames */)
					{
						// map to memory
						// print out memory map
					}
					else
						processQueue[i].waitTime++;
				}
			}
		}

		// Full completion
		if(completeCounter == numOfProcesses)
		{
			chainComplete = true;
			//calculate average turn around
			averageTurnAroundTime = float(totalTurnAroundTime) / numOfProcesses;
			std::cout << "Average Turn Around Time: " << averageTurnAroundTime << std::endl;
		}

		time++;
	}while(time < memSize); // Will use the chainComplete variable later on to take advantage of the process complete fields.

	delete[] processArray;
	return 0;
}

void MemoryManager()
{
}
