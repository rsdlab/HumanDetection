# 人検知モジュールを用いた人協働ロボットシステム  

# 概要
**Nuitrackライブラリを用いた人検出コンポーネント**  
* このコンポーネントではRealSenseなどのRGB-Dカメラを用いて、人の手や、骨格、顔のトラッキングが可能になります。（骨格と顔は対応中）
   
**このコンポーネントの応用として、昨年度のRTMコンテストで発表された「RTMとROSを用いた物体操作システム」の再利用を通じた、人協働マニピュレーションシステムにおける安全機能を実現** 
* このロボットシステムは，ROSで動作するROBOTIS社のMikataArmの動作を人検出モジュールからの情報で制御する例を公開しています。（資料準備中）  

# 仕様
**人検知コンポーネント**  
* 開発言語:C++  
* OS:Linux(Ubuntu18.04)  
* ミドルウェア:OpenRTM-1.2.2 

**アーム制御コンポーネント**  

**共通**
* OS:Ubuntu20.04  

**RTM側**
* 開発言語:C++
* ミドルウェア:OpenRTM-2.0.0  

**ROS側**
* 開発言語:C++
* ミドルウェア:ROS Noetic

# 開発したコンポーネント
* [HumanDetection](https://github.com/rsdlab/HumanDetection/tree/master/RTC/HumanDetection)
* [HumanProtection](https://github.com/rsdlab/HumanDetection/tree/master/RTC/HumanProtection)  

# ドキュメント
**マニュアル**
* 人検知モジュールを用いた人協働ロボットシステムマニュアル・・・準備中

**仕様書**
* [HumanDetection仕様書](https://github.com/rsdlab/HumanDetection/blob/master/Documents/HumanDetectionSpecification.pdf)
* [HumanProtection仕様書](https://github.com/rsdlab/HumanDetection/blob/master/Documents/HumanProtectionSpecification.pdf)

**その他**
* プレゼンテーション動画・・・準備中
* RTMコンテストプレゼン資料・・・準備中
