// multiple rider case attempt
/*
Passenger List: elevator maintains list of passengers (pairs of person_id and destination floor)
Batch Processing: elevator picks up as many passengers as possible from the queue if they are on the same floor, respecting the maximum occupancy
Route Management: elevator manages passengers' routes, moving to each passenger's destination floor and logging the necessary information
Complete Logging: detailed logs for each step including entering and exiting the elevator are added to provide comprehensive traceability
also
Occupancy Declaration: occupancy variable initialized to 0 at the start of the elevator function
Occupancy Management: increment occupancy each time a passenger enters the elevator and decrement each time a passenger exits.
*/

#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <random>
#include <atomic>
#include <vector>
#include <condition_variable>
#include <tuple>
#include <unordered_map>

using namespace std;

const int NUM_FLOORS = 50;
const int NUM_ELEVATORS = 6;
const int MAX_OCCUPANCY = 5;
const int MAX_WAIT_TIME = 5000; // milliseconds

mutex cout_mtx;
mutex queue_mtx;
condition_variable cv;
queue<tuple<int, int, int>> global_queue; // person_id, start_floor, dest_floor
vector<int> elevator_positions(NUM_ELEVATORS, 0);
atomic<int> num_people_serviced(0);
vector<int> global_passengers_serviced(NUM_ELEVATORS, 0);
int npeople;

void elevator(int id) {
    int occupancy = 0; // Initialize occupancy for each elevator
    vector<pair<int, int>> passengers; // pairs of (person_id, dest_floor)

    // please complete the code segment

    {
        lock_guard<mutex> lock(cout_mtx);
        cout << "Elevator " << id << " has finished servicing all people." << endl;
        cout << "Elevator " << id << " serviced " << global_passengers_serviced[id] << " passengers." << endl;
    }
}

void person(int id) {
    int curr_floor = rand() % NUM_FLOORS;
    int dest_floor = rand() % NUM_FLOORS;
    while (dest_floor == curr_floor) {
        dest_floor = rand() % NUM_FLOORS;
    }

    {
        lock_guard<mutex> lock(cout_mtx);
        cout << "Person " << id << " wants to go from floor " << curr_floor << " to floor " << dest_floor << endl;
    }
    // please complete the code segment 
}

#endif // ELEVATOR_HPP

