
## 概要 
このプログラムはシンプルなasciiポモドーロです。
このプログラムは、latest_versionまでは、日本語話者によってc言語で書かれました。
このプログラムは、aura_versionは、c++ 言語によって日本語話者によって書かれました。
アスキーアートが好きなので練習がてら、copilotとvscodeでポモドーロタイマーを作ってみました！
- v1.7が現在の安定版です。

## "v1.7"での挙動
"Work Time"これは作業時間のことを指します。
"Short Break Time"これは小休憩のことを指します。
"Long Break Time"これは長休憩のことを指します。
"Sessions"これは、トータルでの、セッション数を指します。
"Long Interval spacing" これは何回に一回長休憩を取るか、を指します。通常のポモドーロでは4セッションだと思いますが、このプログラムでは、現段階で、整数128まで対応しています。
"Reminder interval" これは、何分間に一回、動画再生と、メモ帳をポップアップ表示するか。

## "v1.8"での挙動"
"v1.8"以降では、"Additional Break Time"が加わりました。
"Additional break time"とは、"Work Time"とは、セッション中に強制的に入ることができる休憩です。時間指定できます。

## 動作環境 
- このプログラムはLinuxでの運用を想定しています。

## 開発環境
- Linux mint 22.3 mate. 

## コンパイルと実行
- 対象のバージョンのフォルダに移動し、./mainを実行して下さい。
- 不安な人は、"g++ main.cpp -o main"を実行したあとに、上記のコマンドを実行して下さい。
- 
## 展望
- もっと速くて軽いプログラムを作ります。

## 注意点
できるだけファイル、フォルダ構造は変更しないでください。
変更する場合は自己責任で、パスやソースコード、ファイル名の設定を各自行ってください。

## License
詳細は、LISENCEを参照してください。

## Overview 
This programme is a simple Ascii art Pomodoro timer.
Up to version ‘latest_version’, this programme was written in C by a Japanese speaker.
From version ‘aura_version’ onwards, this programme was written in C++ by a Japanese speaker.
As I’m a fan of ASCII art, I decided to try my hand at creating a Pomodoro timer using Copilot and VS Code!
Although it behaves as in versions prior to v1.3, please refer to the image.

## Behaviour in "v1.7"
"work time" refers to the working time.
"short break time" refers to a short break.
"long break time" refers to a long break.
"sessions" refers to the total number of sessions.
"Long interval spacing" refers to how often a long break is taken. In a standard Pomodoro session, this would typically be every 4 sessions, but at present, this program supports values up to 128.
"Reminder interval" refers to how many minutes elapse before a video plays and a notepad pops up.
"Additional break time" is a break that can be forcibly initiated during a session. You can specify the duration.

## Behavior in v1.8
"Additional Break Time" has been added in v1.8 and later versions.
"Additional Break Time" refers to a break that can be forcibly taken during a session, distinct from standard "Work Time." You can specify the duration.

## System Requirements 
This program is designed to run on Linux.

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

## LISENCE
Please refer to the file for details.
