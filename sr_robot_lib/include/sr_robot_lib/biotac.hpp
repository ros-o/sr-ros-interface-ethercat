/**
 * @file   biotac.hpp
 * @author Ugo Cupcic <ugo@shadowrobot.com>
 * @date   Th Oct 20 10:06:14 2011
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
 * @brief This is a class for accessing the data from the
 *        Biotac tactiles.
 *
 *
 */

#ifndef _BIOTAC_HPP_
#define _BIOTAC_HPP_

#include <vector>
#include <sr_robot_msgs/BiotacAll.h>
#include <sr_robot_msgs/Biotac.h>
#include <realtime_tools/realtime_publisher.h>

#include "sr_robot_lib/generic_tactiles.hpp"
#include "sr_robot_lib/generic_updater.hpp"

namespace tactiles
{
  class Biotac :
    public GenericTactiles
  {
  public:
    Biotac(std::vector<generic_updater::UpdateConfig> update_configs_vector, operation_mode::device_update_state::DeviceUpdateState update_state);
    ~Biotac() {};

    /**
     * This function is called each time a new etherCAT message
     * is received in the sr06.cpp driver. It  updates the tactile
     * sensors values contained in tactiles_vector.
     *
     * @param status_data the received etherCAT message
     */
    virtual void update(ETHERCAT_DATA_STRUCTURE_0200_PALM_EDC_STATUS* status_data);

    /**
     * Publish the information to a ROS topic.
     *
     */
    virtual void publish();

    /**
     * This function adds the diagnostics for the tactiles to the
     * multi diagnostic status published by the hand.
     */
    virtual void add_diagnostics(std::vector<diagnostic_msgs::DiagnosticStatus> &vec,
                                 diagnostic_updater::DiagnosticStatusWrapper &d);

  protected:
    /// the vector containing the data for the tactiles.
    boost::shared_ptr< std::vector<BiotacData> > tactiles_vector;

    // Tactile sensor real time publisher
    boost::shared_ptr<realtime_tools::RealtimePublisher<sr_robot_msgs::BiotacAll> > tactile_publisher;
  };//end class
}//end namespace

/* For the emacs weenies in the crowd.
Local Variables:
   c-basic-offset: 2
End:
*/

#endif /* _SHADOW_PSTS_HPP_ */
