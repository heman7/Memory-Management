#include<iostream>
#include<string>

using namespace std;

struct process {
	string name;
	int arrival_time;
	int CPUtime;
	int start_time;
	int terminate_time;
	int turnaround_time;
	bool status;
	int priority;
};


void Priority_Algorithms(struct process *, int);


void getArrivalTime_and_CPUTime(struct process *processes, int number) {
	cout << "Please input every process arrival time and CPUtime:" << endl;
	for (int i = 0; i < number; i++) {
		cout << "No." << i + 1 << ": ";
		cin >> processes[i].arrival_time >> processes[i].CPUtime;

		if (processes[i].arrival_time <= -1 || processes[i].CPUtime <= -1) {
			cout << "The arrival time or CPUtime cannot less than 0." << endl;
			cout << "No." << i + 1 << ": ";
			cin >> processes[i].arrival_time >> processes[i].CPUtime;
		}
	}
}

void getPriority(struct process *processes, int number) {
	cout << "Please input every process priority:" << endl;
	for (int i = 0; i<number; i++) {
		cout << "No." << i + 1 << ": ";
		cin >> processes[i].priority;
		if (processes[i].priority <= 0) {
			cout << "The priority cannot less than 1." << endl;
			cout << "No." << i + 1 << ": ";
			cin >> processes[i].priority;
		}
	}
}

void allfalse(struct process *processes, int number) {
	for (int i = 0; i < number; i++) {
		processes[i].status = false;
	}
}


int main() {
	process *processforPri;
	int process_number;

	cout << "Please input processes number you want(not bigger than 5): ";
	cin >> process_number;

	processforPri = new process[process_number];

	getArrivalTime_and_CPUTime(processforPri, process_number);




	Priority_Algorithms(processforPri, process_number);





	return 0;
}



void Priority_Algorithms(struct process *processes, int number) {

	int current_time = 0;
	double average_turnaround_time;
	int total_time = 0;
	bool all_status = false;
	int mini_arrival_time_index;
	int smallest_priority_index;
	getPriority(processes, number);
	allfalse(processes, number);

	while (!all_status) {
		mini_arrival_time_index = -1;
		smallest_priority_index = -1;
		for (int i = 0; i < number; i++) {
			if (processes[i].status)
				continue;
			if (mini_arrival_time_index == -1)
				mini_arrival_time_index = i;
			else if (processes[i].arrival_time < processes[mini_arrival_time_index].arrival_time)
				mini_arrival_time_index = i;
			if (processes[i].arrival_time == processes[mini_arrival_time_index].arrival_time&&processes[i].priority < processes[mini_arrival_time_index].priority)
				mini_arrival_time_index = i;
		}

		for (int q = 0; q < number; q++) {
			if (processes[q].status)
				continue;
			if (smallest_priority_index == -1)
				smallest_priority_index = q;
			if (processes[q].priority < processes[smallest_priority_index].priority)
				smallest_priority_index = q;
		}
		if ((smallest_priority_index != -1) && (current_time >= processes[smallest_priority_index].arrival_time)) {

			processes[smallest_priority_index].start_time = current_time;
			processes[smallest_priority_index].terminate_time = processes[smallest_priority_index].start_time + processes[smallest_priority_index].CPUtime;
			processes[smallest_priority_index].turnaround_time = processes[smallest_priority_index].terminate_time - processes[smallest_priority_index].arrival_time;
			processes[smallest_priority_index].status = true;
			current_time = processes[smallest_priority_index].terminate_time;


		}
		else if ((current_time < processes[smallest_priority_index].arrival_time) && (processes[mini_arrival_time_index].arrival_time >= current_time)) {

			processes[mini_arrival_time_index].start_time = processes[mini_arrival_time_index].arrival_time;
			processes[mini_arrival_time_index].terminate_time = processes[mini_arrival_time_index].start_time + processes[mini_arrival_time_index].CPUtime;
			processes[mini_arrival_time_index].turnaround_time = processes[mini_arrival_time_index].terminate_time - processes[mini_arrival_time_index].arrival_time;
			processes[mini_arrival_time_index].status = true;
			current_time = processes[mini_arrival_time_index].terminate_time;
		}



		else if ((current_time < processes[smallest_priority_index].arrival_time) && (processes[mini_arrival_time_index].arrival_time < current_time)) {

			processes[mini_arrival_time_index].start_time = current_time;
			processes[mini_arrival_time_index].terminate_time = processes[mini_arrival_time_index].start_time + processes[mini_arrival_time_index].CPUtime;
			processes[mini_arrival_time_index].turnaround_time = processes[mini_arrival_time_index].terminate_time - processes[mini_arrival_time_index].arrival_time;
			processes[mini_arrival_time_index].status = true;
			current_time = processes[mini_arrival_time_index].terminate_time;


		}
		for (int a = 0; a < number; a++) {
			if (!processes[a].status)
				break;
			if (a == number - 1)
				all_status = true;
		}
	}
	for (int b = 0; b < number; b++) {
		cout << "Process " << b + 1 << " :" << endl;
		cout << "Starting Time: " << processes[b].start_time << endl;
		cout << "Terminating Time: " << processes[b].terminate_time << endl;
		cout << "Turnaround Time: " << processes[b].turnaround_time << endl;
	}

	for (int x = 0; x < number; x++)
		total_time += processes[x].turnaround_time;
	average_turnaround_time = total_time*1.0 / number;
	cout << "The average turnaround time: " << average_turnaround_time << endl;
}

/*OUTPUT
Please input processes number you want(not bigger than 5): 4
Please input every process arrival time and CPUtime:
No.1: 0 10
No.2: 5 5
No.3: 10 5
No.4: 15 2
Please input every process priority:
No.1: 4
No.2: 2
No.3: 1
No.4: 3
Process 1 :
Starting Time: 0
Terminating Time: 10
Turnaround Time: 10
Process 2 :
Starting Time: 15
Terminating Time: 20
Turnaround Time: 15
Process 3 :
Starting Time: 10
Terminating Time: 15
Turnaround Time: 5
Process 4 :
Starting Time: 20
Terminating Time: 22
Turnaround Time: 7
The average turnaround time: 9.25
Press any key to continue . . .
*/