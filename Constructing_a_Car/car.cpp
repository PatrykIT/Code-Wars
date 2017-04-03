

/* https://www.codewars.com/kata/constructing-a-car-number-1-engine-and-fuel-tank/train/cpp */

class ICar
{
public:

    virtual void EngineStart() = 0;

    virtual void EngineStop() = 0;

    virtual void Refuel(double liters) = 0;

    virtual void RunningIdle() = 0;

    virtual bool getEngineIsRunning() = 0;

};

class IEngine
{
public:

    virtual void Consume(double liters) = 0;

    virtual void Start() = 0;

    virtual void Stop() = 0;

protected:

    bool isRunning = false;
};

class IFuelTank
{
public:

    virtual void Consume(double liters) = 0;

    virtual void Refuel(double liters) = 0;

protected:

    double fillLevel = 0.0;

};

class IFuelTankDisplay
{
protected:

    bool isOnReserve = false;

    bool isComplete = false;

    virtual double getFillLevel() = 0;

    virtual bool getIsComplete() = 0;

    virtual bool getIsOnReserve() = 0;
};


















#include <memory>
#include <cmath>
#include <iostream>
using std::cout;


class FuelTank : public IFuelTank
{
    friend class Car;
    friend class FuelTankDisplay;
    friend class Engine;

    double maximum_size_of_tank = 60.0;
    double reserve_limit = 5.0;

public:

    FuelTank() { fillLevel = 20.0; }
    FuelTank(double fuel_level)
    {
        cout << "Constructor of fuel tank: " << fuel_level << "\n";
        if(fuel_level <= 0.0)
            fillLevel = 0.0;
        else if(fuel_level >= maximum_size_of_tank)
            fillLevel = maximum_size_of_tank;
        else
            fillLevel = fuel_level;
    }

    virtual void Consume(double liters)
    {
        fillLevel -= liters;
        if(fillLevel < 0.0)
            fillLevel = 0.0;
    }

    virtual void Refuel(double liters)
    {
        if(liters >= 0.0)
        {
            fillLevel += liters;
            if(fillLevel > maximum_size_of_tank)
                fillLevel = maximum_size_of_tank;
        }
    }
};


class FuelTankDisplay : public IFuelTankDisplay
{
    friend class Car;
    FuelTank *fuel_tank;

public:
    FuelTankDisplay(FuelTank *fuel) : fuel_tank(fuel) { }

    virtual double getFillLevel()
    {
//        std::cout << "getFillLevel: " << fuel_tank->fillLevel << "\n";
//        std::cout << "Floor advanced: " << std::floor(fuel_tank->fillLevel * std::pow(10, 1)) / std::pow(10, 1) << "\n";
//        cout << "Floor basic: " << std::floor(fuel_tank->fillLevel + 0.5) << "\n";

        if(fuel_tank->fillLevel >= 0.1 && fuel_tank->fillLevel <= 0.2)
            return std::floor(fuel_tank->fillLevel * std::pow(10, 1)) / std::pow(10, 1);
        return std::floor(fuel_tank->fillLevel + 0.5);
    }

    virtual bool getIsComplete()
    {
        return fuel_tank->fillLevel == fuel_tank->maximum_size_of_tank;
    }

    virtual bool getIsOnReserve()
    {
        return fuel_tank->fillLevel <= fuel_tank->reserve_limit;
    }
};


class Engine : public IEngine
{
private:

    friend class Car;
    FuelTank *fuel_tank;

    Engine(FuelTank *_fuel_tank) : fuel_tank(_fuel_tank) { isRunning = false; }

    virtual void Consume(double liters)
    {
        if(isRunning)
        {
            fuel_tank->Consume(liters);
            if(fuel_tank->fillLevel <= 0.0)
                Stop();
        }
    }

    virtual void Start()
    {
        if(fuel_tank->fillLevel > 0.0)
            isRunning = true;
    }

    virtual void Stop()  { isRunning = false; }
};



class Car : public ICar
{
public:

    Car() : engine(new Engine(&fuel_tank)) { }
    Car(double fuel_level) : fuel_tank(fuel_level), engine(new Engine(&fuel_tank)) { }

    virtual void EngineStart()
    {
        engine->Start();

        ++seconds_consumed;
    }

    virtual void EngineStop()
    {
        engine->Stop();

        ++seconds_consumed;
    }

    virtual void Refuel(double liters)
    {
        cout << "Car.Refuel() with: " << liters << " L.\n";
        fuel_tank.Refuel(liters);

        ++seconds_consumed;
    }

    virtual void RunningIdle()
    {   /* The fuel consumption in running idle is 0.0003 liter/second. */
        engine->Consume(0.0003);
    }

    virtual bool getEngineIsRunning() { return engine->isRunning; }

    virtual bool Check_if_is_On_Reserve() { return fuel_tank.fillLevel <= 5.0; }


    FuelTank fuel_tank;
    std::unique_ptr<Engine> engine;
    std::unique_ptr<FuelTankDisplay> fuelTankDisplay = std::make_unique<FuelTankDisplay>(&fuel_tank);

    double seconds_consumed = 0;
};
