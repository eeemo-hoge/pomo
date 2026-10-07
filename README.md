
## 概要 
シンプルなアスキーアートポモドーロタイマーです。
cとc++言語によって書かれました。
- v2.1が現在の安定版です。
(*src/以下にあるものは過去の作品ですが、一応残してあります。)


## "v1.9"での挙動
"Work Time"これは作業時間のことを指します。
"Short Break Time"これは小休憩のことを指します。
"Long Break Time"これは長休憩のことを指します。
"Sessions"これは、トータルでの、セッション数を指します。
"Long Interval spacing" これは何回に一回長休憩を取るか、を指します。通常のポモドーロでは4セッションだと思いますが、このプログラムでは、現段階で、整数128まで対応しています。
"Reminder interval" これは、何分間に一回、動画再生と、メモ帳をポップアップ表示するかを指します、

## "v1.8"での挙動"
"v1.7までは、普通のポモドーロと同じ挙動をします。"
"v1.8"以降では、"Additional Break Time"が加わりました。
"Additional break time"とは、"Work Time"とは、セッション中に強制的に入ることができる休憩です。時間指定できます。

## 動作環境 
- このプログラムはLinuxでの運用を想定しています。

## 開発環境
- Linux mint 22.3 mate. 

## コンパイルと実行
- 対象のバージョンのフォルダに移動し、"g++ main.cpp -o main"を実行したあとに、"./main"を実行。

## 改善点
- もっと速くて軽いプログラムを作ります。
- additionalとwork timeしか行き来できないの修正します。

## 注意点
できるだけファイル、フォルダ構造は変更しないでください。
変更する場合は自己責任で、パスやソースコード、ファイル名の設定を各自行ってください。

## License
詳細は、LISENCEを参照してください。

## Overview
A simple ASCII art Pomodoro timer.
Written in C and C++.
- v2.1 is the current stable version.
(*Files under `src/` are from previous versions but have been retained for reference.)


## Behavior in "v1.9"
"Work Time": Refers to the duration of the work period.
"Short Break Time": Refers to the duration of a short break.
"Long Break Time": Refers to the duration of a long break.
"Sessions": Refers to the total number of sessions.
"Long Interval spacing": Specifies how often a long break is taken. While a standard Pomodoro cycle typically involves 4 sessions, this program currently supports values ​​up to 128.
"Reminder interval": Specifies the frequency (in minutes) at which a video plays and a Notepad window pops up.

## Behavior in "v1.8"
Up to version v1.7, the program operates exactly like a standard Pomodoro timer. "
"Additional Break Time" has been added starting with version 1.8.
"Additional Break Time" refers to a break that can be forcibly initiated during a session, distinct from "Work Time." You can specify the duration.

## System Requirements
- This program is designed to run on Linux.

## Development Environment
- Linux Mint 22.3 MATE.

## Compilation and Execution
- Navigate to the folder for the relevant version, run "g++ main.cpp -o main", and then run "./main".

## Planned Improvements
- Create a faster and more lightweight program.
- Fix the issue where it is only possible to toggle between "Additional Break Time" and "Work Time."

## Important Notes
- Please avoid changing the file and folder structure as much as possible.
- If you do make changes, you do so at your own risk and are responsible for updating paths, source code, and filenames accordingly.
