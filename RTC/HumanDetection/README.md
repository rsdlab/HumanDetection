# Nuitrackを用いた骨格検出環境の構築  
**Nuitrack SDKのダウンロード** 
1. github用のディレクトリの作成  
$cd  
$mkdir github  
$cd github 

2. OpenNIのアンインストール  
$sudo apt remove openni-utils libopenni-dev  

3. git lfsのインストール  
$sudo apt install git-lfs  

4. OpenCV3.4.9のインストール  
$cd  
$cd github  
$git clone https://github.com/opencv/opencv  
$cd opencv  
$git checkout 3.4  
$mkdir build  
$cd build  
$cmake ..  
$make -j"$(nproc)"  
$sudo make install  

5. Nuitrack SDKのダウンロード&インストール  
$git clone https://github.com/3DiVi/nuitrack-sdk  
$cd nuitrack-sdk  
$git lfs install  
$git lfs pull --include "Platforms/*"  
$git lfs pull --include "Unity3D/*"  
$cd Platforms  
$sudo apt install ./nuitrack-ubuntu-amd64.deb  
$cd  
$emacs .bashrc   
export NUITRACK_HOME=/usr/etc/nuitrack  
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/etc/nuitrack/middleware:/usr/local/lib/nuitrack  
$source .bashrc  
$cd  
$cd github/nuitrack-sdk/Nuitrack/include  
$sudo mkdir /usr/local/include/nuitrack  
$sudo cp -r * /usr/local/include/nuitrack/  

6. Nuitrackの動作確認  
$nuitrack
