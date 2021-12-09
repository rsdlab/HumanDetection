# Nuitrackを用いた骨格検出環境の構築  
## Nuitrack SDKのダウンロード
### Nuitrack SDKをgithubからダウンロードして環境構築を行う．
1. github用のディレクトリの作成  
$cd  
$mkdir github  
$cd github 

2. OpenNIのアンインストール  
-Nuitrackをインストールする際にOpenNIとバッティングするので，一旦アンインストール  
$sudo apt remove openni-utils libopenni-dev  

3. git lfsのインストール  
-通常のgitコマンドでは，ダウンロードできるファイルサイズに制限があるので，git lfsを導入する  
$sudo apt install git-lfs  

4. OpenCV3.4.9のインストール  
-画面表示などにOpenCV3.4.9を用いているようで，OpenCV3.4.9のDynamic Link Libraryが求められるので，これをインストール  
(ここでは最小限のものしか入れないので，必要があれば細かく指定すること)    
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
-「nuitrack」コマンドを動作させるためには，環境変数を登録する必要がある．  
$cd  
$emacs .bashrc   
-一番下に以下のように環境変数を追加する．  
export NUITRACK_HOME=/usr/etc/nuitrack  
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/etc/nuitrack/middleware:/usr/local/lib/nuitrack  
-追加したら，以下のようにして設定を反映させる．  
$source .bashrc  
-ライブラリ関係は環境変数にも設定したように，/usr以下にコピーされるが，includeディレクトリの中身までコピーされていないため，手動でコピーを行う．  
$cd  
$cd github/nuitrack-sdk/Nuitrack/include  
$sudo mkdir /usr/local/include/nuitrack  
$sudo cp -r * /usr/local/include/nuitrack/  

6. Nuitrackの動作確認  
-Nuitrackの環境構築が完了したので，これからNuitrackの動作検証を行う．
以下のコマンドでnuitrackのサンプルプログラムの起動を行う．
$nuitrack  
-最初に，Realsenseを接続する．
-なお，接続するRealsenseがすでにActivateがすんでいるものの場合，対応するActivationKeyを準備すること  
-ActivationKeyを準備した状態で，「1. Choose a 3D sensor and activate it」の「Select 3D Sensor」で接続したRealsenseを選択する．  
-続いて，「Enter Activation Key」のところで，準備したActivation Keyを入力する．  
-サンプルの動作確認として，Skeltal Trackingにチェックをいれて，「Try Nuitrack!」ボタンを押す．<ｂｒ>  
-正しく，画面が出てスケルトントラッキングができていればnuitrackのランタイムの導入が完了．  
