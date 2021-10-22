//=============================================================================
//=============================================================================
// Timer.cpp
// 
// Class for logging gametime.
//=============================================================================
//=============================================================================

// ansi
#include <time.h>
// local
#include "helpers/Timer.h"


///////////////////////////////////////////////////////////////////////////////
// Default constructor.
///////////////////////////////////////////////////////////////////////////////
Timer::Timer( void )
{
    // seed random timer for anything using rand
    srand( ( unsigned int )time( NULL ) );

    fps = 0;
    timeStart = 0.0f;
    timeDelta = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
// Default destructor.
///////////////////////////////////////////////////////////////////////////////
Timer::~Timer( void )
{
    // do nothing
}

///////////////////////////////////////////////////////////////////////////////
// Use to initialize & to start timer.
// All time calculations are calculated from game time at this point.
///////////////////////////////////////////////////////////////////////////////
void Timer::Reset( void )
{
    // locals
    LARGE_INTEGER   ticks;

    // get processor frequency
    QueryPerformanceFrequency( &tickFrequency );

    // get current tick count
    QueryPerformanceCounter( &ticks );

    // init time at start
    timeStart = ( double )ticks.QuadPart / ( double )tickFrequency.QuadPart;

    // reset frame count
    fps = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Use to update timer.
// ONLY CALL ONCE PER FRAME!!!
///////////////////////////////////////////////////////////////////////////////
void Timer::Update( void )
{
    // locals
    static double  timePrev = GetTime();
    static double  timeLastFrame = GetTime();
    static int     frames = 0;
    double          timeNow = GetTime();

    // increment frame count
    frames++;

    // log how many frames since ONE second
    if ( timeNow - timePrev > 1.0f )
    {
        fps = frames / (int)(timeNow - timePrev);
        frames = 0;
        timePrev = timeNow;
    }

    // calculate delta time
    timeDelta     = ( timeNow - timeLastFrame );
    timeLastFrame = timeNow;
}

///////////////////////////////////////////////////////////////////////////////
// Returns ( in seconds ) the amount of time from last Reset call.
///////////////////////////////////////////////////////////////////////////////
double Timer::GetTime( void )
{
    // locals
    LARGE_INTEGER   ticks;
    double          time;

    // get current tick count
    QueryPerformanceCounter( &ticks );

    // get current time ( since computer turned on )
    time = ( double )ticks.QuadPart / ( double )tickFrequency.QuadPart;

    // calculate time since reset
    return ( time - timeStart );
}

///////////////////////////////////////////////////////////////////////////////
// Returns ( in seconds ) the amount of time from last frame.
///////////////////////////////////////////////////////////////////////////////
double Timer::GetDeltaTime( void )
{
    return timeDelta;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the current number of FRAMES PER SECOND.
///////////////////////////////////////////////////////////////////////////////
int Timer::GetFPS( void )
{
    return fps;
}



