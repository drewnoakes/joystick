// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#ifndef __JOYSTICK_HH__
#define __JOYSTICK_HH__

#include <string>

#define JS_EVENT_BUTTON 0x01 // button pressed/released
#define JS_EVENT_AXIS   0x02 // joystick moved
#define JS_EVENT_INIT   0x80 // initial state of device

/**
 * Encapsulates all data relevant to a sampled joystick event.
 */
class JoystickEvent
{
public:
  /** Minimum value of axes range */
  static const short MIN_AXES_VALUE = -32768;

  /** Minimum value of axes range */
  static const short MAX_AXES_VALUE = 32767;
  
  /**
   * The timestamp of the event, in milliseconds.
   */
  unsigned int time;
  
  /**
   * The value associated with this joystick event.
   * For buttons this will be either 1 (down) or 0 (up).
   * For axes, this will range between MIN_AXES_VALUE and MAX_AXES_VALUE.
   */
  short value;
  
  /**
   * The event type.
   */
  unsigned char type;
  
  /**
   * The axis/button number.
   */
  unsigned char number;

  /**
   * Returns true if this event is the result of a button press.
   */
  bool isButton()
  {
    return (type & JS_EVENT_BUTTON) != 0;
  }

  /**
   * Returns true if this event is the result of an axis movement.
   */
  bool isAxis()
  {
    return (type & JS_EVENT_AXIS) != 0;
  }

  /**
   * Returns true if this event is part of the initial state obtained when
   * the joystick is first connected to.
   */
  bool isInitialState()
  {
    return (type & JS_EVENT_INIT) != 0;
  }
};

/**
 * Represents a joystick device. Allows data to be sampled from it.
 */
class Joystick
{
private:
  void openPath(std::string devicePath);
  
  int _fd;
  
public:
  ~Joystick();

  /**
   * Initialises an instance for the first joystick: /dev/input/js0
   */
  Joystick();

  /**
   * Initialises an instance for the joystick with the specified,
   * zero-indexed number.
   */
  Joystick(int joystickNumber);

  /**
   * Initialises an instance for the joystick device specified.
   */
  Joystick(std::string devicePath);
 
  /**
   * Returns true if the joystick was found and may be used, otherwise false.
   */
  bool isFound();
  
  /**
   * Attempts to populate the provided JoystickEvent instance with data
   * from the joystick. Returns true if data is available, otherwise false.
   */
  bool sample(JoystickEvent* event);
};

#endif
