#ifndef VEHICLE_H
#define VEHICLE_H
class Vehicle
{
public:
    Vehicle(int mass, int max_velocity) : _mass(mass),
    _max_velocity(max_velocity);

    int getMass(){return _mass;}
    int getMaxVelocity(){return _max_velocity;}

private:
    int _mass;
    int _max_velocity;
};
#endif