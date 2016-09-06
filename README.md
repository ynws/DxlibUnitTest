# DxlibUnitTest

Dxlibで作成したゲームの大規模リファクタリングを行うため、事前にテストを作成したい。  
Dxlibを使用したWindowsアプリのユニットテストの経験がないため、サンプルテストを作成する。

当初はVisualStudio付属のテストツールを使用する予定だったが、  
Community版ではカバレッジが測定できないため中断。  
GoogleTest + gcov に方向転換。

以下を実施予定

1. ~~Dxlibサンプルプログラム作成~~  
1. ~~GoogleTest導入~~ 
1. ~~Dxlibのラッパークラスを作成~~  
1. Jenkins導入  
1. コミットをフックしてビルド  
1. コミットをフックしてテスト  
1. テスト結果をJenkinsに表示  
1. gcovでカバレッジ計測  
1. カバレッジ結果をJenkinsに表示  

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

## コミットをフックしてビルド

## コミットをフックしてテスト

## テスト結果をJenkinsに表示

## gcovでカバレッジ計測

## カバレッジ結果をJenkinsに表示

