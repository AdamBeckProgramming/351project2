#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

struct Process
{
	int id;
	int arrivalTime;
	int completionTime;
	int turnAroundTime;
  int framesRequired;
	int waitTime;
	int numPieces;
	int totalAddressSpace;
	bool complete;
	bool filled;
};
void InitializeMemory(Process*, int);
void MemoryManager();

int main()
{
	long memSize = 0;
	long pageSize = 0;
	Process* processArray;
	Process* memory;
	int memPiece = 0;
	int time = 0;
	int frameCnt;
	int emptyCnt;
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
	frameCnt = memSize / pageSize;
	memory = new Process[frameCnt];
	InitializeMemory(memory, frameCnt);
	emptyCnt = frameCnt;

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
		processArray[counter].framesRequired = int(ceil(processArray[counter].totalAddressSpace / double(pageSize)));
		processArray[counter].filled = true;
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

		// Process Arrives and needs to be mapped
		if(!processQueue.empty())
		{
			for(int i = 0; i < processQueue.size(); i++)
			{
				if(processQueue[i].framesRequired <= emptyCnt)
				{
					// Map to memory
					int frame = processQueue[i].framesRequired;
					for(int j = 0; j < frameCnt; j++)
					{
						if(frame > 0 && memory[j].filled == false)
						{
							// transfer info over to memory
							memory[j].id = processQueue[i].id;
							memory[j].arrivalTime = processQueue[i].arrivalTime;
							memory[j].completionTime = processQueue[i].completionTime;
							memory[j].framesRequired = processQueue[i].framesRequired;
							memory[j].waitTime = processQueue[i].waitTime;
							memory[j].numPieces = processQueue[i].numPieces;
							memory[j].totalAddressSpace = processQueue[i].totalAddressSpace;
							memory[j].complete = processQueue[i].complete;
							memory[j].filled = true;
							frame--;
						}
						else
							break;
					}
					// Print out memory map
					for(int j = 0; j < frameCnt; j++)
					{
						if(memory[j].filled == true)
						{
						}
						else
						{
						}
					}
				}
				else
					processQueue[i].waitTime++;
			}
		}

		// Process Completes and needs to be removed
		for(int i = 0; i < memSize/pageSize; i++)
		{
			if(memory[i].completionTime + memory[i].waitTime == time)
			{
				memory[i].complete = true;
				memory[i].turnAroundTime = (memory[i].completionTime + memory[i].waitTime) - memory[i].arrivalTime;
				totalTurnAroundTime += memory[i].turnAroundTime;
				memory[i].filled = false;
				emptyCnt++;
				completeCounter++;
				std::cout << "Process " << memory[i].id << " completes\n";
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
	}while(chainComplete = false);

	delete[] processArray;
	delete[] memory;
	return 0;
}

void MemoryManager()
{
}

void InitializeMemory(Process* mem, int frameCnt)
{
	for(int i = 0; i < frameCnt; i++)
	{
		mem[i].id = -1;
		mem[i].arrivalTime = -1;
		mem[i].completionTime = -1;
		mem[i].turnAroundTime = -1;
		mem[i].framesRequired = -1;
		mem[i].waitTime = -1;
		mem[i].numPieces = -1;
		mem[i].totalAddressSpace = -1;
		mem[i].complete = false;
		mem[i].filled = false;
	}
}
