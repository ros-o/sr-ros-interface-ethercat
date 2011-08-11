/**
 * @file   sr_math_utils.hpp
 * @author Ugo Cupcic <ugo@shadowrobot.com>, Contact <contact@shadowrobot.com>
 * @date   Mon Jun 20 10:20:27 2011
 *
* Copyright 2011 Shadow Robot Company Ltd.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 2 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/>.
*
 * @brief This is a header library used to implement some useful math
 * functions. It is used in our different packages.
 *
 *
 */

#ifndef _SR_MATH_UTILS_HPP_
#define _SR_MATH_UTILS_HPP_

namespace sr_math_utils
{
  /**
   * Convert an angle in degrees to an angle in radians.
   *
   * @param degrees the value in degrees
   *
   * @return the value in radians.
   */
  static inline double to_rad(double degrees)
  {
    return degrees * 0.017453292519943295;
  }

  /**
   * Convert an angle in degrees to an angle in degrees.
   *
   * @param degrees the value in radians.
   *
   * @return the value in degrees.
   */
  static inline double to_degrees(double rad)
  {
    return rad * 57.295779513082323;
  }

  static inline int ipow(int base, int exp)
  {
    int result = 1;
    while (exp)
    {
      if (exp & 1)
        result *= base;
      exp >>= 1;
      base *= base;
    }

    return result;
  }

  static inline bool is_bit_mask_index_true(int bit_mask, int index)
  {
    if ( bit_mask & (1<<index) )
      return true;
    else
      return false;
  }

  static inline bool is_bit_mask_index_false(int bit_mask, int index)
  {
    return !(is_bit_mask_index_true(bit_mask, index));
  }

  /**
   * Increment a counter given a value which can overflow.
   *
   * WARNING: only works if called often enough: if new_value > last_value but
   * overflowed between the 2 calls, then we're not able to detect the overflow.
   *
   * @param full_value the full value (with no overflow)
   * @param last_value the value we received last time, between 0 and max_value.
   * @param new_value the new value we received, between 0 and max_value.
   * @param max_value the maximum value (max_value +1 = 0), typically 65535 for a 16bit number.
   *
   * @return a
   */
  static inline int counter_with_overflow(int full_value, int last_value, int new_value, int max_value = 65535)
  {
    int value_to_add = 0;

    if( new_value < last_value) // overflowing
      value_to_add = (max_value + 1 - last_value) + new_value;
    else // not overflowing
      value_to_add = new_value - last_value;

    return full_value + value_to_add;
  }
}

/* For the emacs weenies in the crowd.
Local Variables:
   c-basic-offset: 2
End:
*/

#endif
