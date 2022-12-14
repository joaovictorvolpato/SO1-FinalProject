#ifndef traits_h
#define traits_h

//Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU;
class Debug;

class Thread;

class System;

class SpaceShooter;

class Lists;

class Semaphore;

class PlayerShip;

class Keyboard;

class Window;

class PurpleEnemy;

class PurpleEnemiesControl;


template<typename T>
struct Traits {
    static const bool debugged = false;
};

template<> struct Traits<CPU>
{
    static const int STACK_SIZE = 64000;
    static const bool debugged = true;
};

template<> struct Traits<Debug>: public Traits<void>
{
 static const bool error = true;
 static const bool warning = false;
 static const bool info = false;
 static const bool trace = false;
};

template<> struct Traits<System> : public Traits<void>
{
 static const bool debugged = true;
};

template<> struct Traits<Thread> : public Traits<void>
{
 static const bool debugged = true;
};

template<> struct Traits<Lists> : public Traits<void>
{
 static const bool debugged = false;
};

template<> struct Traits<Semaphore> : public Traits<void>
{
 static const bool debugged = true;
};

__END_API

#endif
