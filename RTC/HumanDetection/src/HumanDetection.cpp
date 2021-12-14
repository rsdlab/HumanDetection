// -*- C++ -*-
/*!
 * @file  HumanDetection.cpp
 * @brief Human Detection RT Component 
 * @date $Date$
 *
 * $Id$
 */

#include "HumanDetection.h"

// Module specification
// <rtc-template block="module_spec">
static const char* humandetection_spec[] =
  {
    "implementation_id", "HumanDetection",
    "type_name",         "HumanDetection",
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

std::vector<tdv::nuitrack::UserHands> userHands;
 
///////////////////////////////////////////////////////////////////////////////
//Callback functions for Nuitrack
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
//Callback function For hand detection
//=============================================================================
void onHandUpdate(tdv::nuitrack::HandTrackerData::Ptr handData)
{
  if (!handData)
  {
      // No hand data
      std::printf("No hand data\n");
      return;
  }

  userHands = handData->getUsersHands();

}

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
HumanDetection::HumanDetection(RTC::Manager* manager)
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
HumanDetection::~HumanDetection()
{
}



RTC::ReturnCode_t HumanDetection::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers

  // Set OutPort buffer
  addOutPort("FacePose", m_FacePoseOut);
  addOutPort("RightHandPose", m_RightHandPoseOut);
  addOutPort("LeftHandPose", m_LeftHandPoseOut);
  addOutPort("Skelton", m_SkeltonOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  tdv::nuitrack::Nuitrack::init("");

  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanDetection::onFinalize()
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t HumanDetection::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetection::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t HumanDetection::onActivated(RTC::UniqueId ec_id)
{
  handTracker = tdv::nuitrack::HandTracker::create();
  handTracker->connectOnUpdate(std::bind(onHandUpdate, std::placeholders::_1));
  tdv::nuitrack::Nuitrack::run();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanDetection::onDeactivated(RTC::UniqueId ec_id)
{
  tdv::nuitrack::Nuitrack::release();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t HumanDetection::onExecute(RTC::UniqueId ec_id)
{
  tdv::nuitrack::Nuitrack::waitUpdate(handTracker);
  
  if(userHands.empty())
  {
    std::printf("No user hands \n");
    return RTC::RTC_OK;
  }

  //In current version, the components just can detect the hand for 1 person
  // auto cnt = userHands.size();
  
  auto rightHand = userHands[0].rightHand;
  auto leftHand = userHands[0].leftHand;

  if (!rightHand)
  {
    // No right hand
    std::printf("Right hand of the first user is not found\n");
    RTC::RTC_OK;
  }
  else
  {
    std::printf("Right hand position: x = %.0f, y = %.0f, z = %.0f\n", rightHand->xReal, rightHand->yReal, rightHand->zReal);

    m_RightHandPose.pose_q.p3D.x = rightHand->xReal;
    m_RightHandPose.pose_q.p3D.y = rightHand->yReal;
    m_RightHandPose.pose_q.p3D.z = rightHand->zReal;  

    m_RightHandPoseOut.write();

  }

  if (!leftHand)
  {
    // No right hand
    std::printf("Left hand of the first user is not found\n");
    RTC::RTC_OK;
  }
  else
  {
    std::printf("Light hand position: x = %.0f, y = %.0f, z = %.0f\n", leftHand->xReal, leftHand->yReal, leftHand->zReal);

    m_LeftHandPose.pose_q.p3D.x = leftHand->xReal;
    m_LeftHandPose.pose_q.p3D.y = leftHand->yReal;
    m_LeftHandPose.pose_q.p3D.z = leftHand->zReal; 


    m_LeftHandPoseOut.write();
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t HumanDetection::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetection::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetection::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetection::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t HumanDetection::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void HumanDetectionInit(RTC::Manager* manager)
  {
    coil::Properties profile(humandetection_spec);
    manager->registerFactory(profile,
                             RTC::Create<HumanDetection>,
                             RTC::Delete<HumanDetection>);
  }

};


