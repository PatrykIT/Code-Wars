

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
        if(fillLevel >= 0.0 && fillLevel <= maximum_size_of_tank)
            fillLevel = fuel_level;
    }

    virtual void Consume(double liters) { fillLevel -= liters; if(fillLevel < 0.0) fillLevel = 0.0; }

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
        //return fuel_tank->fillLevel;  //The fuel tank display shows the level as rounded for 2 decimal places
         return std::floor(fuel_tank->fillLevel * std::pow(10, 1)) / std::pow(10, 1);
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
    friend class Car;
    FuelTank *fuel_tank;


    Engine(FuelTank *_fuel_tank) : fuel_tank(_fuel_tank) { isRunning = false; }

    virtual void Consume(double liters)
    {
        fuel_tank->fillLevel -= liters;
        if(fuel_tank->fillLevel <= 0)
        {
            Stop();
        }
        fuel_tank->fillLevel = 0;
    }

    virtual void Start() { isRunning = true; }

    virtual void Stop()  { isRunning = false; }
};



class Car : public ICar
{
public:

    Car() : fuelTankDisplay(new FuelTankDisplay(&fuel_tank)), engine(new Engine(&fuel_tank)) { }
    Car(double fuel_level) : fuel_tank(fuel_level), fuelTankDisplay(new FuelTankDisplay(&fuel_tank)), engine(new Engine(&fuel_tank)) { }

    virtual void EngineStart()
    {
        if(fuel_tank.fillLevel > 0)
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
        fuel_tank.Refuel(liters);

        ++seconds_consumed;
    }

    virtual void RunningIdle()
    {   /* The fuel consumption in running idle is 0.0003 liter/second. */
        engine->Consume(0.0003);
    }

    virtual bool getEngineIsRunning() { return engine->isRunning; }

    virtual bool Check_if_is_On_Reserve() { return fuel_tank.fillLevel < 5.0; }


    std::unique_ptr<Engine> engine;

    FuelTank fuel_tank;
    FuelTankDisplay *fuelTankDisplay; //Change to shared pointer

    double seconds_consumed = 0;
};
