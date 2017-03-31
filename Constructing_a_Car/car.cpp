#include <memory>


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
    virtual void Consume(double liters) { }

    virtual void Start() { }

    virtual void Stop()  { }
};

class FuelTank : public IFuelTank
{
    virtual void Consume(double liters) { }

    virtual void Refuel(double liters) { }
};

class FuelTankDisplay : public IFuelTankDisplay
{

};

class Car : public ICar
{
public:

    virtual void EngineStart()
    {
        engine->Start();
        engineIsRunning = true;
    }

    virtual void EngineStop() { engineIsRunning = false; }
    virtual void Refuel(double liters) { }
    virtual void RunningIdle() { /* The fuel consumption in running idle is 0.0003 liter/second. */ }

    //Engine engine;
    std::unique_ptr<Engine> engine;

    FuelTank fuel_tank;
    FuelTankDisplay fuel_tank_display;
};
