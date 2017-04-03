

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

class Engine : public IEngine
{
    friend class Car;

    Engine() { isRunning = false; }
    virtual void Consume(double liters) { }

    virtual void Start() { isRunning = true; }

    virtual void Stop()  { isRunning = false; }
};

class FuelTank : public IFuelTank
{
    friend class Car;
    friend class FuelTankDisplay;

    double maximum_size_of_tank = 60.0;
    double reserve_limit = 5.0;

public:

    FuelTank() { fillLevel = 20.0; }
    FuelTank(double fuel_level) { fillLevel = fuel_level; }

    virtual void Consume(double liters) { fillLevel -= liters; }

    virtual void Refuel(double liters) { }
};


class FuelTankDisplay : public IFuelTankDisplay
{
    friend class Car;
    FuelTank *fuel_tank;

public:
    FuelTankDisplay(FuelTank *fuel) : fuel_tank(fuel) { }

    virtual double getFillLevel() { return fuel_tank->fillLevel; }

    virtual bool getIsComplete()
    {
        return fuel_tank->fillLevel == fuel_tank->maximum_size_of_tank;
    }

    virtual bool getIsOnReserve()
    {
        return fuel_tank->fillLevel <= fuel_tank->reserve_limit;
    }
};






class Car : public ICar
{
public:

    Car() : engine(new Engine), fuelTankDisplay(new FuelTankDisplay(&fuel_tank)) { }
    Car(double fuel_level) : engine(new Engine), fuel_tank(fuel_level), fuelTankDisplay(new FuelTankDisplay(&fuel_tank)) { }

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
        fuel_tank.fillLevel += liters;

        ++seconds_consumed;
    }

    virtual void RunningIdle()
    {   /* The fuel consumption in running idle is 0.0003 liter/second. */
        fuel_tank.Consume(0.0003);
    }

    virtual bool getEngineIsRunning() { return engine->isRunning; }

    virtual bool Check_if_is_On_Reserve() { return fuel_tank.fillLevel < 5.0; }


    //Engine engine;
    std::unique_ptr<Engine> engine;

    FuelTank fuel_tank;
    //FuelTankDisplay fuelTankDisplay;
    FuelTankDisplay *fuelTankDisplay; //Change to shared pointer

    double seconds_consumed = 0;
};
