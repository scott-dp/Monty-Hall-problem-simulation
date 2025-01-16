#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class MontyHallSimulation {
private:
    bool doors[3]; // false means goat, true means car behind door i
public:
    void setDoors(bool door1, bool door2, bool door3) {
        doors[0] = door1;
        doors[1] = door2;
        doors[2] = door3;
    }

    bool* getDoors() {
        return doors;
    }

    bool simulateWithDoorSwitch() {
        //return true means car is won, false means you got a goat
        int carIndex= rand() % 3;
        if (carIndex == 0) setDoors(true, false, false); //bilen er i første dør
        else if (carIndex == 1) setDoors(false, true, false);//andre dør
        else if (carIndex == 2) setDoors(false, false, true);//Tredje dør

        int firstPickIndex = rand() % 3; //Contestant first choice

        //Now host opens a door with goat inside
        int hostDoorPickIndex;
        while (true) {
            //After this loop the hostDoorPickIndex will be a door with a goat and not the door that the contestant chose
            hostDoorPickIndex = rand() % 3;
            if (hostDoorPickIndex == firstPickIndex || getDoors()[hostDoorPickIndex]) continue;
            break;
        }

        //Now contestant must switch door
        int switchedDoorIndex;
        for (int i = 0; i < 3; ++i) {
            if (i != firstPickIndex && i != hostDoorPickIndex) switchedDoorIndex = i;
        }

        return getDoors()[switchedDoorIndex]; //Returns true if the contestant switched to car, false if goat
    }

    bool simulateWithoutDoorSwitch() {
        //return true means car is won, false means you got a goat
        int carIndex= rand() % 3;
        if (carIndex == 0) setDoors(true, false, false); //bilen er i første dør
        else if (carIndex == 1) setDoors(false, true, false);//andre dør
        else if (carIndex == 2) setDoors(false, false, true);//Tredje dør

        int firstPickIndex = rand() % 3; //Contestant first choice
        return getDoors()[firstPickIndex];
    }

    double simulateAndGetSuccessRate(int numSimulations, bool switchDoor) {
        if (switchDoor) {
            int numSuccesses = 0;
            for (int i = 0; i < numSimulations; ++i) {
                if (simulateWithDoorSwitch()) numSuccesses++;
            }
            return ((double) numSuccesses) / ((double) numSimulations);
        } else {
            int numSuccesses = 0;
            for (int i = 0; i < numSimulations; ++i) {
                if (simulateWithoutDoorSwitch()) numSuccesses++;
            }
            return ((double) numSuccesses) / ((double) numSimulations);
        }
    }
};

int main() {
    srand(time(nullptr));
    MontyHallSimulation simulator;
    cout << "Success rate with door switch: " << endl;
    cout << simulator.simulateAndGetSuccessRate(10000, true) << endl;

    cout << "Success rate without door switch: " << endl;
    cout << simulator.simulateAndGetSuccessRate(10000, false) << endl;
    return 0;
}
