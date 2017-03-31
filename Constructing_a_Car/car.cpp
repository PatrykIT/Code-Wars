#include <memory>

/* https://www.codewars.com/kata/constructing-a-car-number-1-engine-and-fuel-tank/train/cpp */

class ICar
{
public:

    virtual void EngineStart() = 0;

    virtual void EngineStop() = 0;

    virtual void Refuel(double liters) = 0;

    virtual void RunningIdle() = 0;

protected:

    bool engineIsRunning = false;
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

    virtual bool Check_if_is_On_Reserve() = 0;

protected:

    double fillLevel = 0.0;

    bool isOnReserve = false;

    bool isComplete = false;
};

class IFuelTankDisplay
{
protected:

    double fillLevel = 0.0;

    bool isOnReserve = false;

    bool isComplete = false;
};




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
    FuelTank() { fillLevel = 20.0; isOnReserve = false; isComplete = false;}

    virtual void Consume(double liters) { }

    virtual void Refuel(double liters) { }

    virtual bool Check_if_is_On_Reserve() { return fillLevel < 5.0; }

    double maximum_size_of_tank = 60.0;
};

class FuelTankDisplay : public IFuelTankDisplay
{
    friend class Car;
};

class Car : public ICar
{
public:

    virtual void EngineStart()
    {
        engine->Start();
        engineIsRunning = true;
    }

    virtual void EngineStop()
    {
        engine->Stop();
        engineIsRunning = false;
    }

    virtual void Refuel(double liters)
    {
        fuel_tank.fillLevel += liters;
    }
    virtual void RunningIdle() { /* The fuel consumption in running idle is 0.0003 liter/second. */   }

    //Engine engine;
    std::unique_ptr<Engine> engine;

    FuelTank fuel_tank;
    FuelTankDisplay fuel_tank_display;

    double seconds_consumed = 0;
};
