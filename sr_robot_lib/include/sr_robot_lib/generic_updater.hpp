/**
 * @file   generic_updater.hpp
 * @author toni <toni@shadowrobot.com>
 * @date   20 Oct 2011
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
*
 * @brief This is a generic robot library for Shadow Robot's Hardware.
 *
 *
 */

#ifndef GENERIC_UPDATER_HPP_
#define GENERIC_UPDATER_HPP_

#include <ros/ros.h>
#include <vector>
#include <list>
#include <queue>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <sr_external_dependencies/types_for_external.h>
extern "C"
{
  #include <sr_external_dependencies/external/0220_palm_edc/0220_palm_edc_ethercat_protocol.h>
}

namespace operation_mode
{
  namespace device_update_state
  {
    enum DeviceUpdateState
    {
      INITIALIZATION,
      OPERATION
    };
  }
}

namespace generic_updater
{
  struct UpdateConfig
  {
    int32u what_to_update;
    double when_to_update;
  };

  /**
   * The Generic Updater builds the next command we want to send to the hand.
   * We can ask for different types of data at different rates. The data and
   * their rates are defined in the sr_robot_lib/config/xxxxxx.yaml
   * The important data are refreshed as often as possible (they have a -1. refresh
   * rate in the config file).
   *
   * The unimportant data are refreshed at their given rate (the value is defined in
   * the config in seconds).
   */
  class GenericUpdater
  {
  public:
    GenericUpdater(std::vector<UpdateConfig> update_configs_vector, operation_mode::device_update_state::DeviceUpdateState update_state);
    ~GenericUpdater();

    /**
     * Building the motor command. This function is called at each packCommand() call.
     * If an unimportant data is waiting then we send it, otherwise, we send the next
     * important data.
     *
     * @param command The command which will be sent to the motor.
     */
    virtual void build_command(ETHERCAT_DATA_STRUCTURE_0200_PALM_EDC_COMMAND* command)=0;

    /**
     * A timer callback for the unimportant data. The frequency of this callback
     * is defined in the config file.
     *
     * @param event
     * @param data_type The unimportant data type we want to ask for.
     */
    void timer_callback(const ros::TimerEvent& event, FROM_MOTOR_DATA_TYPE data_type);

    operation_mode::device_update_state::DeviceUpdateState update_state;
    ///Contains all the initialization data types.
    std::vector<UpdateConfig> initialization_configs_vector;

  protected:
    ros::NodeHandle nh_tilde;

    ///Contains all the important data types.
    std::vector<UpdateConfig> important_update_configs_vector;
    ///iterate through the important or initialization data types.
    int which_data_to_request;

    ///All the timers for the unimportant data types.
    std::vector<ros::Timer> timers;
    ///A queue containing the unimportant data types we want to ask for next time (empty most of the time).
    std::queue<int32u, std::list<int32u> > unimportant_data_queue;

    boost::shared_ptr<boost::mutex> mutex;
  };
}




/* For the emacs weenies in the crowd.
Local Variables:
   c-basic-offset: 2
End:
*/

#endif /* GENERIC_UPDATER_HPP_ */
