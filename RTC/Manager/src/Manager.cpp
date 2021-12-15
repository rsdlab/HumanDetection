// -*- C++ -*-
/*!
 * @file  Manager.cpp
 * @brief Manager
 * @date $Date$
 *
 * $Id$
 */

#include "Manager.h"

// Module specification
// <rtc-template block="module_spec">
static const char* manager_spec[] =
  {
    "implementation_id", "Manager",
    "type_name",         "Manager",
    "description",       "Manager",
    "version",           "1.0.0",
    "vendor",            "rsdlab",
    "category",          "Manager",
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
Manager::Manager(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_safetyIn("safety", m_safety),
    m_end_moveIn("end_move", m_end_move),
    m_end_manipIn("end_manip", m_end_manip),
    m_stopOut("stop", m_stop),
    m_start_moveOut("start_move", m_start_move),
    m_ManipulatorCommonInterface_CommonPort("ManipulatorCommonInterface_Common"),
    m_ManipulatorCommonInterface_MiddlePort("ManipulatorCommonInterface_Middle")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Manager::~Manager()
{
}



RTC::ReturnCode_t Manager::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("safety", m_safetyIn);
  addInPort("end_move", m_end_moveIn);
  addInPort("end_manip", m_end_manipIn);

  // Set OutPort buffer
  addOutPort("stop", m_stopOut);
  addOutPort("start_move", m_start_moveOut);

  // Set service provider to Ports

  // Set service consumers to Ports
  m_ManipulatorCommonInterface_CommonPort.registerConsumer("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_ManipulatorCommonInterface_Common);
  m_ManipulatorCommonInterface_MiddlePort.registerConsumer("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_ManipulatorCommonInterface_Middle);

  // Set CORBA Service Ports
  addPort(m_ManipulatorCommonInterface_CommonPort);
  addPort(m_ManipulatorCommonInterface_MiddlePort);

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}



/*
RTC::ReturnCode_t Manager::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Manager::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Manager::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Manager::onActivated(RTC::UniqueId ec_id)
{
   //プロバイダより遅くActivateするため
  sleep(1);

  m_start_move.data = "front";
  std::cout << "移動開始します" << std::endl;
  std::cout << "goal_:" << goal_ <<std::endl;

  // JARA_ARM::JointPos jointPoint;
  // jointPoint.length(6);
  // jointPoint[0] = -0.390;
  // jointPoint[1] = 0.054;
  // jointPoint[2] = 0.485;
  // jointPoint[3] = 0.037;
  // jointPoint[4] = 1.200;
  // jointPoint[5] = -0.457;

  // jointPoint.length(6);

  // std::vector<JARA_ARM::JointPos> joint_info;

  // joint情報 ファイル読み込み

  // for(int i = 0; i < jointPoint.length(6), i++)
  // {
  //   // ファイル読み込んで、
  //   //file joint info value
  //   joint_info.push_back();
  //   //jointPoint[i] = joint_info[i];
  // }

  // 対象物まで移動
  // Pick
  // side move
  // Place
  // home

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Manager::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



RTC::ReturnCode_t Manager::onExecute(RTC::UniqueId ec_id)
{
   if(goal_ == "not")
  {
    // 移動開始
    std::cout << "start_move:" << m_start_move.data <<std::endl;
    m_start_moveOut.write();

    // printf("m_end_moveIn.isNew():=%3d",m_end_moveIn.isNew());

    if(m_end_moveIn.isNew())
    {
      std::cout << "移動終了しました" << std::endl;

      // ROS側から到着命令受信
      m_end_moveIn.read();
      goal_ = m_end_move.data;
      printf("goal_:=%3s", goal_.c_str());
      
      if(goal_ == "end_move" && count == 1)
      {
        m_start_move.data = "front";
        m_start_moveOut.write();
        goal_ = "not";
        count = 0;
      }
    }
    else
      printf("まだもらっていません。\n");
  }

  // std::cout << "goal_1:=" << goal_ << std::endl;

  //safetyにデータが入ってきているかチェック
  if(m_safetyIn.isNew() && goal_ == "end_move")
  {

    //データがあれば下記関数で変数にデータを読み込む
    m_safetyIn.read();

    //safetyのデータが0であれば，関節角度を送信
    if(m_safety.data == 0)
    {
      //joint ros send １回だけ呼ぶこと
      if(count == 0)
      {
          JARA_ARM::JointPos jointPoint;
          JARA_ARM::JointPos setPoint, initPoint;
          jointPoint.length(6);
          jointPoint[0] = -0.390;
          jointPoint[1] = 0.054;
          jointPoint[2] = 0.485;
          jointPoint[3] = 0.037;
          jointPoint[4] = 1.200;
          jointPoint[5] = -0.457;

          setPoint.length(6);
          setPoint[0] = 1.57;
          setPoint[1] = 0.131;
          setPoint[2] = -0.265;
          setPoint[3] = 0;
          setPoint[4] = 1.453;
          setPoint[5] = 0;

          initPoint.length(6);
          initPoint[0] = 0;
          initPoint[1] = 0;
          initPoint[2] = 0;
          initPoint[3] = 0;
          initPoint[4] = 0;
          initPoint[5] = 0;
          
          hogehoge = 0;

         // 次のjoint情報を格納
         if(hoge == 1)
         {
           for(int i = 0; i < 6; i++)
          {
           jointPoint[i] = setPoint[i];
          }
         }
         if(hoge == 2)
         {
           for(int i = 0; i < 6; i++)
          {
           jointPoint[i] = initPoint[i];
          }
          hogehoge = 1;
          hoge = 0;           
         }

        std::cout << "jointPoint[0]:=" << jointPoint[0] << std::endl;
        std::cout << "hoge:=" << hoge << std::endl;
        m_ManipulatorCommonInterface_Middle->movePTPJointAbs(jointPoint);

        count++;
      }

    }
    else
    {
      // ros send
      m_stop.data = "1";

      m_stopOut.write();
    }

    std::cout << "m_end_manipIn.isNew:=" << m_end_manipIn.isNew() << std::endl;

    // Manipが終了したかチェック
    if(m_end_manipIn.isNew() && goal_ == "end_move")
    {
      m_end_manipIn.read();
      manip_end = m_end_manip.data;
      // std::cout << "m_end_manip.data_before:=" << m_end_manip.data << std::endl;
      // std::cout << "m_manipend:=" << manipend << std::endl;

      if(manip_end == "end_manip")
      {
        std::cout << "m_end_manip.data_after:=" << m_end_manip.data << std::endl;


        

        // pick and place処理を一通り終了した場合、移動backに入る
        m_start_move.data = "back";
        goal_ = "not";
        std::cout << "m_start_move.data:=" << m_start_move.data << std::endl;
        std::cout << "goal_:=" << goal_ << std::endl;
        count = 1;
        if(hogehoge == 0){
          hoge++;
        }
        for(int i = 0; i < 10; i++)
        {
          m_start_moveOut.write();
        }
      }
    }
    else  
      std::cout << "Manipulation動作中" << std::endl;
  }
  else
    std::cout << "safetyからのデータを受信していません" << std::endl;

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Manager::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Manager::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Manager::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Manager::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Manager::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void ManagerInit(RTC::Manager* manager)
  {
    coil::Properties profile(manager_spec);
    manager->registerFactory(profile,
                             RTC::Create<Manager>,
                             RTC::Delete<Manager>);
  }

};


