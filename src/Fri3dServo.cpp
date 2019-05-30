/*
Copyright (c) 2017 John K. Bennett. All right reserved.
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
* Notes on the implementation:
* The ESP32 supports 16 hardware LED PWM channels that are intended
* to be used for LED brightness control. The low level ESP32 code
* (esp32-hal-ledc.*) allows us to set the PWM frequency and bit-depth,
* and then manipulate them by setting bits in the relevant control
* registers.
*
* Different servos require different pulse widths to vary servo angle, but the range is
* an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
* sweep 180 degrees, so the lowest number in the published range for a particular servo
* represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
* of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
* 1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 180
* degrees. We vary pulse width (recall that the pulse period is already set to 20ms) as follows:
*
* The ESP32 PWM timers allow us to set the timer width (max 20 bits). Thus
* the timer "tick" length is (pulse_period/2**timer_width), and the equation for pulse_high_width
* (the portion of the 20ms cycle that the signal is high) becomes:
*
*                  pulse_high_width  = count * tick_length
*                                    = count * (pulse_period/2**timer_width)
*
*            and   count = (pulse_high_width / (pulse_period/2**timer_width))
*
* So, for example, if I want a 1500us pulse_high_width, I set pulse_period to 20ms (20000us)
* (this value is set in the ledcSetup call), and count (used in the ledcWrite call) to
* 1500/(20000/65536), or 4924. This is the value we write to the timer in the ledcWrite call.
* If we increase the timer_width, the timer_count values need to be adjusted.
*
* The servo signal pins connect to any available GPIO pins on the ESP32, but not all pins are
* GPIO pins.
*
* The ESP32 is a 32 bit processor that includes FP support; this code reflects that fact.
*/

#include "Fri3dServo.h"
#include "esp32-hal-ledc.h"
#include "Arduino.h"

Fri3dServo::Fri3dServo()
{      
    // initialize this channel with plausible values, except pin # (we set pin # when attached)
    this->ticks = DEFAULT_PULSE_WIDTH_TICKS;   
    this->timer_width = DEFAULT_TIMER_WIDTH;
    this->timer_width_ticks = pow(2,this->timer_width);
}

int Fri3dServo::attach(int channel)
{
    return (this->attach(channel, DEFAULT_uS_LOW, DEFAULT_uS_HIGH));
}

int Fri3dServo::attach(int channel, int min, int max)
{    
    if (channel > MAX_SERVOS || channel < 0) return 1;

    this->servoChannel = channel;
    this->pinNumber = this->servo_pins[channel];

    // min/max checks 
    if (min < MIN_PULSE_WIDTH)          // ensure pulse width is valid
        min = MIN_PULSE_WIDTH;
    if (max > MAX_PULSE_WIDTH)
        max = MAX_PULSE_WIDTH;

    this->min = min;     //store this value in uS
    this->max = max;    //store this value in uS
    
    // Set up this channel
    // if you want anything other than default timer width, you must call setTimerWidth() before attach
    ledcSetup(1 + this->servoChannel, REFRESH_CPS, this->timer_width); // channel #, 50 Hz, timer width
    ledcAttachPin(this->pinNumber, this->servoChannel);   // GPIO pin assigned to channel        

    return 0;
}

void Fri3dServo::detach()
{
    if (this->attached()) {
        ledcDetachPin(this->pinNumber);
        this->pinNumber = -1;
    }
}

void Fri3dServo::setBoundaries(int min, int max)
{
    int val = this->read();

    this->min = min;
    this->max = max;

    this->write(val);
}

void Fri3dServo::write(int value)
{
    // treat values less than MIN_PULSE_WIDTH (500) as angles in degrees (valid values in microseconds are handled as microseconds)
    if (value < MIN_PULSE_WIDTH)
    {
        if (value < 0)
            value = 0;
        else if (value > 180)
            value = 180;

        value = map(value, 0, 180, this->min, this->max);
    }
    this->writeMicroseconds(value);
}

void Fri3dServo::writeMicroseconds(int value)
{
    // calculate and store the values for the given channel
    if ((this->servoChannel <= MAX_SERVOS) && (this->attached()))   // ensure channel is valid
    {
        if (value < this->min)          // ensure pulse width is valid
            value = this->min;
        else if (value > this->max)
            value = this->max;

        value = usToTicks(value);  // convert to ticks
        this->ticks = value;
        // do the actual write
        ledcWrite(this->servoChannel, this->ticks);
    }
}

int Fri3dServo::read() // return the value as degrees
{
    return (map(readMicroseconds()+1, this->min, this->max, 0, 180));
}

int Fri3dServo::readMicroseconds()
{
    int pulsewidthUsec;
    if ((this->servoChannel <= MAX_SERVOS) && (this->attached()))
    { 
        pulsewidthUsec = ticksToUs(this->ticks);
    }
    else
    {
        pulsewidthUsec = 0;
    }

    return (pulsewidthUsec);
}

bool Fri3dServo::attached()
{
    return this->pinNumber != -1;
}

void Fri3dServo::setTimerWidth(int value)
{
    // only allow values between 16 and 20
    if (value < 16)
        value = 16;
    else if (value > 20)
        value = 20;
        
    // Fix the current ticks value after timer width change
    // The user can reset the tick value with a write() or writeUs()
    int widthDifference = this->timer_width - value;
    // if positive multiply by diff; if neg, divide
    if (widthDifference > 0)
    {
        this->ticks =this->ticks << widthDifference;
    }
    else
    {
        this->ticks =this->ticks >> widthDifference;
    }
    
    this->timer_width = value;
    this->timer_width_ticks = pow(2,this->timer_width);
    
    // If this is an attached servo, clean up
    if ((this->servoChannel <= MAX_SERVOS) && (this->attached()))
    {
        // detach, setup and attach again to reflect new timer width
        ledcDetachPin(this->pinNumber);
        ledcSetup(1 + this->servoChannel, REFRESH_CPS, this->timer_width);
        ledcAttachPin(this->pinNumber, this->servoChannel);
    }        
}

int Fri3dServo::readTimerWidth()
{
    return (this->timer_width);
}

int Fri3dServo::usToTicks(int usec)
{
    return (int)((float)usec / ((float)REFRESH_USEC / (float)this->timer_width_ticks));   
}

int Fri3dServo::ticksToUs(int ticks)
{
    return (int)((float)ticks * ((float)REFRESH_USEC / (float)this->timer_width_ticks)); 
}
