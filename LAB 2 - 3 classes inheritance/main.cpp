#include <iostream>
using namespace std;

class building{
public:
    void enter(){
        if (population<population_cup){
            cout<<"You entered building on "<<adress<<endl;
            population+=1;
        }else{
            cout<<"Building on "<<adress<<" is full."<<endl;
        }
    }
    void get_out(){
        if (population>0){
            population -=1;
            cout<<"Someone got out of building on "<<adress<<endl;
        }
        else{
            cout<<"There's no one in building on "<<adress<<endl;
        }
    }
    building(string adr, int floor){
        adress = adr;
        population = 0;
        floors = floor;
        population_cup=7;
    }
    int floors;
    string adress;
    int population;
    int population_cup;
};

class house: public building{
public:
    void turnTheLightsOff(){
        lights = false;
        cout<<"You turned the lights off in house on "<<adress<<endl;
    }
    void turnTheLightsOn(){
        lights = true;
        cout<<"You turned the lights on in house on "<<adress<<endl;
    }

    house( string adr, int floor) :building(adr,floor) {
        adress = adr;
        population = 0;
        floors = floor;
        population_cup=5;
        lights = false;
    }

protected:
    bool lights;

};

class townhouse: public house{
public:
    townhouse( string adr, int flor) : house( adr, flor) {
        adress = adr;
        floors = flor;
        population_cup=3;
        lights = false;
        opened = true;
    }

    void closeDoor(){
        opened = false;
    }
    void openDoor(){
        opened = true;
    }

    void Honest_enter(){
        if(opened){
            enter();
        } else{
            cout<<"Sorry, door  on "<<adress<<" is closed, you can't enter."<<endl;
        }
    }
private:
    bool opened;
};


int main() {
    building build1("221B Baker St.",3);
    for(int i=1;i<=8;i++){
        build1.enter();
    }
    for(int i=8;i>=0;i--){
        build1.get_out();
    }

    house house1("38 Petrovka St.",3);
    for(int i=1;i<=6;i++){
        house1.enter();
    }
    for(int i=6;i>=0;i--){
        house1.get_out();
    }
    house1.turnTheLightsOff();
    house1.turnTheLightsOn();

    townhouse town1("1 MyOwn St.", 2);
    for(int i=1;i<=4;i++){
        town1.enter();
    }
    for(int i=4;i>=0;i--){
        town1.get_out();
    }
    town1.turnTheLightsOff();
    town1.turnTheLightsOn();
    town1.closeDoor();
    town1.Honest_enter();
    town1.openDoor();
    town1.Honest_enter();

    return 0;
}
