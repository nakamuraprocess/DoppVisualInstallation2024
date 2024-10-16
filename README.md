# DoppVisualInstallation2024

### Raspberry Pi 4 OS (legacy, 32-bit)でコンパイルする方法 ###
```bash
sudo apt-get clean
```
```bash
sudo apt-get update
```
```bash
sudo apt-get upgrade
```
※v0.11.2を使用（v0.12.0はコンパイルできるが、GLのWindowが開かない）
```bash
wget https://github.com/openframeworks/openFrameworks/releases/download/0.11.2/of_v0.11.2_linuxarmv6l_release.tar.gz
```
```bash
mkdir openFrameworks
```
```bash
tar vxfz of_v0.11.2_linuxarmv6l_release.tar.gz -C openFrameworks --strip-components 1
```
```bash
sudo openFrameworks/scripts/linux/debian/install_dependencies.sh
```
```bash
make Release -C openFrameworks/libs/openFrameworksCompiled/project
```
SSHでアプリを実行するためのパス追加
```bash
nano .bash_profile
```
```bash
export DISPLAY=:0
```
試しにexampleをコンパイルする
```bash
make Release -C openFrameworks/examples/gl/textureExample
```
実行
```bash
make RunRelease -C openFrameworks/examples/gl/textureExample
```
下記のエラーが出る場合
```bash
/usr/bin/ld: cannot find -lopenmaxil
```
```bash
nano openFrameworks/libs/openFrameworksCompiled/project/linuxarmv6l/config.linuxarmv6l.default.mk
```
```bash
PLATFORM_LIBRARIES += openmaxil　←コメントアウトする　#PLATFORM_LIBRARIES += openmaxil
```
アプリのクローン
```bash
cd openFrameworks/apps/myApps
```
```bash
git clone https://github.com/nakamuraprocess/DoppVisualInstallation2024.git
```
使用アドオン
ofxShuffleText
```bash
cd openFrameworks/addons
```
```bash
git clone https://github.com/wtshm/ofxShuffleText.git
```
アプリをコンパイルする
```bash
make Release -C openFrameworks/apps/myApps/DoppVisualInstallation2024
```
実行(dataディレクトリはscpなどで転送しておく)
```bash
make RunRelease -C openFrameworks/apps/myApps/DoppVisualInstallation2024
```
### 自動起動の設定 ###
```bash
nano .bash_profile
```
bash_profileに下記のDISPLAYと実行ファイルのパスを追加する
```bash
export DISPLAY=:0
openFrameworks/apps/myApps/DoppVisualInstallation2024/bin/DoppVisualInstallation2024
```
```bash
sudo reboot
```
### ※備考 ###
新しいプロジェクトを作成する（projectGeneratorは実行できないためemptyExampleをコピー）
```bash
cp -R openFrameworks/apps/myApps/emptyExample openFrameworks/apps/myApps/MyAppProject
```