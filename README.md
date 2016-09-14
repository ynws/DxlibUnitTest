# DxlibUnitTest

Dxlibで作成したゲームの大規模リファクタリングを行うため、事前にテストを作成する。  
これはその前調査用のDxlibアプリのユニットテストのサンプル。

当初はVisualStudio付属のテストツールを使用する予定だったが、  
Community版ではカバレッジが測定できないため中断。  
GoogleTest + OpenCppCoverage に方向転換。

以下を実施予定

1. ~~Dxlibサンプルプログラム作成~~  
1. ~~GoogleTest導入~~ 
1. ~~Dxlibのラッパークラスを作成~~  
1. ~~Jenkins導入~~  
1. ~~ビルド後にテスト 結果をJenkinsに表示~~  
1. ~~カバレッジ計測 結果をJenkinsに表示~~  
1. ~~ステップ数カウントをJenkinsに表示~~  
1. ~~TODOをJenkinsに表示~~  
1. ~~カバレッジ計測をgcovで行う~~  

## Dxlibサンプルプログラム作成
[公式](http://dxlib.o.oo7.jp/use/dxuse_vscom2015.html)の手順に従いセットアップ

## GoogleTest導入
テスト用コンソールアプリプロジェクトを作成し、以下の手順でGoogleTestを環境設定。  
http://dr-yellow.hatenablog.com/entry/2015/11/26/225259  
ただし、DropBox容量の関係でincludeとlibは各プロジェクトにコピーせず、  
使いまわすことにした。以下の手順だけ修正。

#### INCLUDEディレクトリの追加
G:\Dropbox\Sourcecode\googletest-release-1.8.0\googletest\include

#### libファイルのリンク設定
G:\Dropbox\Sourcecode\googletest-release-1.8.0\googletest\msvc\gtest\$(Configuration)

### VisualStudioのGoogleaTestプラグイン導入
GoogleTest Runner for Visual Studio 2015  
https://visualstudiogallery.msdn.microsoft.com/cbd1a9b2-790b-4d49-905f-d128ca21d3fb  
拡張機能からインストール

### main program修正
テスト全実行のたびにメインプログラムも動いてしまうので、  
以下のifdefを追加  
http://d.hatena.ne.jp/ar_night/20140106/1389037118

```c
#ifndef _ROGEBREAZ_TEST
int WINAPI WinMain(...){
...
}
#endif
```

## Dxlibのラッパークラスを作成
テストのたびにGUI Window出すわけにもいかないので、テスト用のラッパークラスを作成する。  
その後、Google MockでMock作成  
http://www.naturalsoftware.jp/entry/20100723/1279810738  
http://opencv.jp/googlemockdocs/fordummies.html

とりあえず自分がよく使う関数だけ作る。  

以下のようにテストで書くイメージ

```cpp
MockDxlib mockDxlib;
EXPECT_CALL(mockDxlib, DrawString(0, 0, "test", COL_BLACK)).Times(1);

Game* game = new Game(&mockDxlib);
EXPECT_TRUE(game->print());

```

モック入れた後のビルドでリンクエラーが出て詰まったのでメモ。  
GoogleTestの導入と同じように、追加の依存ファイル(gmock.lib)の設定が必要だった。  
以下をソースに書けば回避可能だが、せっかくなので設定に追加。

```c
#pragma comment( lib, "gmock.lib" )
```

とりあえずDrawStringの呼び出しテストがかけた。  
あとは単純作業で他関数に展開するだけなのでスキップ。

## Jenkins導入
http://futurismo.biz/archives/299

2.7.3をインストール。以前入れた時よりだいぶ進化していて戸惑う。

#### VSプロジェクトの登録
http://unicus.jp/skmk/archives/515

MSBuildの設定はシステムの設定ではなくGlobal Tool Configurationにあった。
C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe を追加。    

また、ビルドファイルのパスは以下。  
C:\Program Files (x86)\Jenkins\workspace\DxlibUnitTest\DxlibUnitTest.sln

#### コンパイルエラー
fatal error C1083: Cannot open include file: 'DxLib.h': No such file or directory  
-> x64でビルドされているが、追加のinclude設定していなかった。  
x64の設定すれば通りそうだが、メインはx86なのでビルドオプションで切り替える。

参考サイトの記述に加え、MSBuildの引数に以下を追加  
 /p:Platform=x86

 また、カバレッジ測定のためデバッグモードでビルド。最終的はビルド引数は以下

 ```
 /t:Rebuild /p:Configuration=Debug /p:Platform=x86
 ```

 -> ビルドOK

## ビルド後にテスト 結果をJenkinsに表示  
http://futurismo.biz/archives/475

ビルド手順最後に以下のWindowsバッチ追加  

```
@echo off
echo ################################################################################
echo ## GOOGLE TEST
echo ################################################################################
Debug\GTest.exe --gtest_output="xml:test_result.xml"
```

ビルド後の処理で集計

## カバレッジ計測 結果をJenkinsに表示  

OpenCppCoverage  
http://opencppcoverage.codeplex.com/  
https://opencppcoverage.codeplex.com/wikipage?title=Jenkins

jenkinsにCoberturaプラグイン導入
-> 可視化OK

```
@echo off
echo ################################################################################
echo ## OpenCppCoverage
echo ################################################################################
fullpath\OpenCppCoverage.exe --source MainLib --export_type=cobertura -- Debug\GTest.exe
```

NOTE: テストが一切なく、かすりもしなかったソースはそもそも表示対象外になる模様。

## ステップ数カウントをJenkinsに表示
http://futurismo.biz/archives/629  
プラグインはJenkinsから直接インストール可能

設定値の"ファイルの種類"は集計の表示単位なので、MAIN, LIB, TESTに分けた

ERROR: null といメッセージが表示されてエラー。  
http://d.hatena.ne.jp/takuma02141978/20111225/1324778439  
Jenkinsの管理 -> システムの設定 を開いて一度保存すると次回以降OK

## TODOをJenkinsに表示
ソース中のTODOコメントを抽出  
http://futurismo.biz/archives/559  
Task Scanner Plugin

ビルド後処理に"未解決タスクの集計"を追加  
ただし、VisualStudioが作成するファイルを無視したいので、`**/stdafx*` を無視リストに追加

日本語文字化けの際は、"高度な設定"からエンコーディングを指定。  
未指定の場合システムのデフォルトになる。

## カバレッジ計測をgcovで行う
OpenCppCoverageでは分岐のカバレッジがうまく出ない。  
gcovを利用する方向で考える。

#### ビルドマシン追加(不要だった)
メインマシンがWindowsだが、gcovはlinuxマシン上でテストをビルドする必要あり。  
https://www.infoq.com/jp/articles/jenkins_20111012  
を参考にビルドマシン追加・・・  
SSHポート変更は"高度な設定"から。  

#### Bash on Windows(不要だった)
と思ったが、Bash on Ubuntu on Windowsでできるのでは？  
インストール  
http://qiita.com/Aruneko/items/c79810b0b015bebf30bb  
jenkins経由でコマンド実行できない？  
本質でないのでパス。素直に別マシンでビルドする

ビルドマシン追加ではなく、SSHプラグインで実施。

#### gcov参考サイト  
http://futurismo.biz/archives/485  
http://qiita.com/kuchida1981/items/9bb8fa4cc04635e7e909  

### linux上でビルドする際の問題
テスト用ソースの以下が邪魔
* #include <SDKDDKVer.h>
* #include <tchar.h>
* includeの相対パスで￥を使っているとlinuxで読めない。  
windowsはlinuxの形式でも読めるので、そっちに倒す

### カバレッジデータの転送
作成したカバレッジデータはsambaでWindowsPCに共有。  
-> Jenkinsのbat処理からネットワークドライブにアクセスできない  
http://futurismo.biz/archives/331  
Windowsサービスで立ち上げるとネットに接続できないらしい。  
コマンドプロンプトから立ち上げることにした。  
これにより、従来のjob設定ファイルやプラグインを  
`User\hoge\.jenkins`に移動。  
ビルド設定に一部workspaceの絶対パスが書いてあったため一時動かなかった。  
よほどのことがない限りジョブ設定は相対パスと環境変数で書くこと！ 

### gcovカバレッジデータをjenkinsで表示
で、ようやくgcovデータをjenkinsで表示できた  
問題点が2点。

+ googletestのソースもカバレッジに出てしまう
+ 結果の参照先ソースファイルパスがlinux上のパスなので、jenkinsでソースが表示できない

-> gcovrの`-r`オプションで解決。ROOTの指定。

最終的なSSHコマンドは以下  
(要MakeFile化)
```bash
cd ~/jenkins
rm -r DxlibUnitTest
git clone https://github.com/ynws/DxlibUnitTest.git
mkdir DxlibUnitTest/build
cd DxlibUnitTest/build

export GTEST=~/googletest-master
export GTLIB=${GTEST}/build/gtest
export GMLIB=${GTEST}/build/googlemock

g++ -c ../MainLib/*.cpp -DLINUX -fprofile-arcs -ftest-coverage
ar r libstatic.a *.o
g++ -W -Wall ../GTest/*.cpp -DLINUX -I${GTEST}/googletest/include -I${GTEST}/googlemock/include ${GTLIB}/libgtest.a ${GTLIB}/libgtest_main.a ${GMLIB}/libgmock.a ${GMLIB}/libgmock_main.a libstatic.a -lpthread -fprofile-arcs -ftest-coverage -o test

./test

gcovr -r ~/jenkins/DxlibUnitTest --xml --output=GTestCoverage.xml .

cp GTestCoverage.xml /home/samba/jenkins/
```

上記コマンドの後、sambaのファイルをcopy
