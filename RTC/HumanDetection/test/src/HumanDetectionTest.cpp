// -*- C++ -*-
/*!
 * @file  HumanDetectionTest.cpp
 * @brief Human Detection RT Component 
 * @date $Date$
 *
 * $Id$
 */

#include "HumanDetectionTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* humandetection_spec[] =
  {
    "implementation_id", "HumanDetectionTest",
    "type_name",         "HumanDetectionTest",
    "description",       "Human Detection RT Component ",
    "version",           "1.0.0",
    "vendor",            "Robot System Design Laboratory, Meijo Univ.",
    "category",          "Motion Capture",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
HumanDetectionTest::HumanDetectionTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_FacePoseOut("FacePose", m_FacePose),
    m_RightHandPoseOut("RightHandPose", m_RightHandPose),
    m_LeftHandPoseOut("LeftHandPose", m_LeftHandPose),
    m_SkeltonOut("Skelton", m_Skelton)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
HumanDetectionTest::~HumanDetectionTest()
{
}



RTC::ReturnCode_t HumanDetectionTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("FacePose", m_FacePoseIn);
  addInPort("RightHandPose", m_RightHandPoseIn);
  addInPort("LeftHandPose", m_LeftHandPoseIn);
  addInPort("Skelton", m_SkeltonIn);

  // Set OutPort buffer

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanDetectionTest::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t HumanDetectionTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetectionTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t HumanDetectionTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanDetectionTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanDetectionTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t HumanDetectionTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetectionTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetectionTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetectionTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetectionTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void HumanDetectionTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(humandetection_spec);
    manager->registerFactory(profile,
                             RTC::Create<HumanDetectionTest>,
                             RTC::Delete<HumanDetectionTest>);
  }

};


