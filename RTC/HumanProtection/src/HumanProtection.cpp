// -*- C++ -*-
/*!
 * @file  HumanProtection.cpp
 * @brief Human Protection RT Component 
 * @date $Date$
 *
 * $Id$
 */

#include "HumanProtection.h"

// Module specification
// <rtc-template block="module_spec">
static const char* humanprotection_spec[] =
  {
    "implementation_id", "HumanProtection",
    "type_name",         "HumanProtection",
    "description",       "Human Protection RT Component ",
    "version",           "1.0.0",
    "vendor",            "Robot System Design Laboratory, Meijo Univ.",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.judge_parameter", "1500",

    // Widget
    "conf.__widget__.judge_parameter", "text",
    // Constraints

    "conf.__type__.judge_parameter", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
HumanProtection::HumanProtection(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_human_poseIn("HumanPose", m_human_pose),
    m_stop_comOut("StopCommand", m_stop_com)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
HumanProtection::~HumanProtection()
{
}



RTC::ReturnCode_t HumanProtection::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("HumanPose", m_human_poseIn);

  // Set OutPort buffer
  addOutPort("StopCommand", m_stop_comOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("judge_parameter", m_judge_parameter, "1500");
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t HumanProtection::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanProtection::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanProtection::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t HumanProtection::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanProtection::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanProtection::onExecute(RTC::UniqueId ec_id)
{

  std::cout << "z:= " << m_human_pose.pose_q.p3D.z << std::endl;

  if (m_human_poseIn.isNew())
  {
    m_human_poseIn.read();

    if (m_human_pose.pose_q.p3D.x == 0 && m_human_pose.pose_q.p3D.y == 0 && m_human_pose.pose_q.p3D.z == 0)
      return RTC::RTC_OK; 
    else if ( 0 < m_human_pose.pose_q.p3D.z && m_human_pose.pose_q.p3D.z <= m_judge_parameter)
    {
      m_stop_com.data = 1;
      printf("stop_com=%d\r\n", m_stop_com.data);
    }
    else
    {
      m_stop_com.data = 0;
      printf("stop_com=%d\r\n", m_stop_com.data);
    }
    
    m_stop_comOut.write();
  }
  else  
  {
    m_stop_com.data = 0;
    printf("Init stop_com=%d\r\n", m_stop_com.data);
    m_stop_comOut.write();
  }
    

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t HumanProtection::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanProtection::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanProtection::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanProtection::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanProtection::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void HumanProtectionInit(RTC::Manager* manager)
  {
    coil::Properties profile(humanprotection_spec);
    manager->registerFactory(profile,
                             RTC::Create<HumanProtection>,
                             RTC::Delete<HumanProtection>);
  }

};


