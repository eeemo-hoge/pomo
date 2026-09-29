
## 概要 
このプログラムはシンプルなポモドーロです。
このプログラムは、latest_versionまでは、日本語話者によってc言語で書かれました。
このプログラムは、aura_versionは、c++ 言語によって日本語話者によって書かれました。
アスキーアートが好きなので練習がてら、copilotとvscodeでポモドーロタイマーを作ってみました！
v1.3以前の挙動にはなるのですが、imageを参考にして下さい。

## "v1.6"での挙動
"work time"これは作業時間のことを指します。
"short break time"これは小休憩のことを指します。
"long break time"これは長休憩のことを指します。
"sessions"これは、トータルでの、セッション数を指します。
"Long interval spacing" これは何回に一回長休憩を取るか、を指します。通常のポモドーロでは4セッションだと思いますが、このプログラムでは、現段階で、整数128まで対応しています。。
"Reminder interval" これは、何分間に一回、動画再生と、メモ帳をポップアップ表示するか。

## 動作環境 
このプログラムはLinuxでの運用を想定しています。

## 開発環境
Linux mint 22.3 mate. 

## コンパイルと実行
-対象のバージョンのフォルダに移動し、./mainを実行して下さい。
-不安な人は、"g++ main.cpp -o main"を実行したあとに、上記のコマンドを実行して下さい。
## 展望
もっと速くて軽いプログラムを作ります。

## 注意点
できるだけファイル、フォルダ構造は変更しないでください。
変更する場合は自己責任で、パスやソースコード、ファイル名の設定を各自行ってください。

## License
詳細は、LISENCEを参照してください。

## Overview 
This programme is a simple Pomodoro timer.
Up to version ‘latest_version’, this programme was written in C by a Japanese speaker.
From version ‘aura_version’ onwards, this programme was written in C++ by a Japanese speaker.
As I’m a fan of ASCII art, I decided to try my hand at creating a Pomodoro timer using Copilot and VS Code!
Although it behaves as in versions prior to v1.3, please refer to the image.

## Behaviour in "v1.6"
"work time" refers to the working time.
"short break time" refers to a short break.
"long break time" refers to a long break.
"sessions" refers to the total number of sessions.
"Long interval spacing" refers to how often a long break is taken. In a standard Pomodoro session, this would typically be every 4 sessions, but at present, this programme supports values up to 128.
"Reminder interval" refers to how many minutes elapse before a video plays and a notepad pops up.

## System Requirements 
This programme is designed to run on Linux.

## Development Environment
Linux Mint 22.3 MATE. 

## Compilation and Execution
- Navigate to the folder for the relevant version and run `./main`.
- If you are unsure, run `g++ main.cpp -o main` first, followed by the command above.
## Future Plans
I intend to create a faster and lighter programme.

## Important Notes
Please avoid changing the file and folder structure as much as possible.
If you do make changes, please do so at your own risk and configure the paths, source code and filenames yourself.

## Licence
Please refer to the LICENCE file for details.
