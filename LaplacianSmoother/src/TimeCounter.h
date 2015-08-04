//! TimeCounter class.
/*!
\file       TimeCounter.h
\author     Tody
\date       2015/03/17
*/


#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H

#include <time.h>
#include <ostream>
#include <string>

//! TimeCounter implementation.
class TimeCounter
{
public:
    //! Constructor.
    TimeCounter ( const std::string& name )
        : last_start ( 0 ), running ( false ), elapsed ( 0 ), name ( name )
    {
        start();
    }

    //! Destructor.
    virtual ~TimeCounter() {}

    //! Set the name of the counter.
    void setName ( const std::string& name );

    //! Return the name of the counter.
    const std::string& getName() const;

    //! Get elapsed time.
    double getElapsedTime();

    //! Return if the counter is running or not.
    bool isRunning();

    //! Start the counter.
    void start();

    //! Stop without reseting
    double pause();

    //! Rest the counter.
    /*!
        \return elapsed time before reset.
    */
    double reset();

    //! Output string for the counter.
    /*!
        Output will be "name: ...[sec]"
    */
    friend std::ostream& operator<< ( std::ostream& out, TimeCounter& counter );

private:
    //! Name of the counter.
    std::string name;

    //! Time elapsed in seconds.
    double elapsed;

    //! Return if the counter is started or not.
    bool running;

    //! Clock value at start.
    long last_start;

};


#endif