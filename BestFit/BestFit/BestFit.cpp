#include<iostream>
#include<string>

using namespace std;

void BestFit(struct partition *, struct job *, int);

struct job
{
	string name;
	int job_size;
	bool status = true;  // run is flase, wait is true;
	int partition_number;
};

struct partition {
public:
	int partition_size;
	bool partition_status = true; //not busy is true, busy is false;
	int unused;
};
int getmemorysize() {
	int memory_size;
	cout << "Please input memory size you want: ";
	cin >> memory_size;
	return memory_size;
}
void getEveryPartitionSize(struct partition *partitions, int jobnumber, int restmemory)
{
	cout << "Please input every partition size:" << endl;
	for (int i = 0; i < jobnumber; i++) {
		if (restmemory == 0)
		{
			cout << "No." << i + 1 << ": " << restmemory << endl;
			continue;
		}
		cout << "No." << i + 1 << ": ";
		cin >> partitions[i].partition_size;
		if (partitions[i].partition_size > restmemory) {
			cout << "The partition size cannot bigger than the rest memory size." << endl;
			cout << "No." << i + 1 << ": ";
			cin >> partitions[i].partition_size;
		}
		restmemory -= partitions[i].partition_size;
		cout << "The rest memory size is: " << restmemory << endl;
	}
}
void getEveryJobNameandSize(struct job *jobs, int jobnumber)
{
	cout << "Please input every job name and size:" << endl;
	for (int i = 0; i < jobnumber; i++) {
		cout << "Job " << i + 1 << ": ";
		cin >> jobs[i].name >> jobs[i].job_size;
	}
}

int main()
{
	partition *partitions;
	job *jobs;
	int partition_job_number;
	int the_rest_memory_size;

	the_rest_memory_size = getmemorysize();

	cout << "Please input partition&job number you want(not bigger than 5): ";
	cin >> partition_job_number;

	partitions = new partition[partition_job_number];
	jobs = new job[partition_job_number];

	getEveryPartitionSize(partitions, partition_job_number, the_rest_memory_size);

	getEveryJobNameandSize(jobs, partition_job_number);

	BestFit(partitions, jobs, partition_job_number);

	delete[] jobs;
	delete[] partitions;

	return 0;
}



void BestFit(struct partition *partitions, struct job *jobs, int number) {
	int total_waste = 0;
	for (int i = 0; i < number; i++)
	{
		int bestindex = -1;

		for (int j = 0; j < number; j++)
		{
			if (!partitions[j].partition_status || partitions[j].partition_size < jobs[i].job_size)
				continue;
			if (bestindex == -1)
				bestindex = j;
			else if (partitions[j].partition_size < partitions[bestindex].partition_size)
				bestindex = j;
		}
		if (bestindex != -1)
		{
			jobs[i].status = false;
			partitions[bestindex].partition_status = false;
			jobs[i].partition_number = bestindex + 1;
			partitions[bestindex].unused = partitions[bestindex].partition_size - jobs[i].job_size;
			total_waste += partitions[bestindex].unused;
			cout << jobs[i].name << " is running in partition " << bestindex + 1 << "   " << "waste: " << partitions[bestindex].unused << endl;
		}

		for (int q = 0; q < number; q++)
		{
			if (!jobs[i].status)
				break;
			else if ((!partitions[q].partition_status) && (partitions[q].partition_size >= jobs[i].job_size) && jobs[i].status) {
				cout << jobs[i].name << " have to wait." << endl;
				break;
			}
			else if ((jobs[i].status) && (q == number - 1))
				cout << jobs[i].name << " could not be allocated." << endl;
		}


	}
	for (int x = 0; x < number; x++)
	{
		if (partitions[x].partition_status)
			total_waste += partitions[x].partition_size;
	}
	cout << "Total memory waste is: " << total_waste << endl;
}


/*OUTPUT
Please input memory size you want: 1000
Please input partition&job number you want(not bigger than 5): 4
Please input every partition size:
No.1: 300
The rest memory size is: 700
No.2: 200
The rest memory size is: 500
No.3: 400
The rest memory size is: 100
No.4: 100
The rest memory size is: 0
Please input every job name and size:
Job 1: J1 200
Job 2: J2 300
Job 3: J3 100
Job 4: J4 200
J1 is running in partition 2   wSaste: 0
J2 is running in partition 1   waste: 0
J3 is running in partition 4   waste: 0
J4 is running in partition 3   waste: 200
Total memory waste is: 200
Press any key to continue . . .

*/

