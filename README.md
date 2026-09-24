
## 概要 ## 
このプログラムはシンプルなポモドーロです。
このプログラムは、latest_versionまでは、日本語話者によってc言語で書かれました。
このプログラムは、aura_versionは、c++ 言語によって日本語話者によって書かれました。
アスキーアートが好きなので練習がてら、copilotとvscodeでポモドーロタイマーを作ってみました！

## "v1.3"での挙動
"work time"これは作業時間のことを指します。
"short break time"これは小休憩のことを指します。
"long break time"これは長休憩のことを指します。
"sessions"これは、トータルでの、（休憩は小、長とも含まない。)を指します。
"Long inter val spacing" これは何回に一回小休憩を取るか、を指します。通常のポモドーロでは4セッションだと思いますが、このプログラムでは自由です。
"Reminder interval" これは、何分間に一回、動画再生と、メモ帳をポップアップ表示するか。
です。ソースコードはライセンスにもあるように改変自由なので、各自行ってください。

## 動作環境 
このプログラムはLinuxでの運用を想定しています。

## 開発環境
Linux mint 22.3 mate. 
## コンパイルと実行
"pomo"は、単体で動きます。src/"任意のバージョン"に移動し、"g++ main.cpp -o main"のあと、"./main"で実行してください。
"v1.3"は、できるだけフォルダ構造を変更しないでください。変更する場合はソースコードを書き換えて使用してください。"g++ main.cpp -o main"のあと、"./main"で実行してください。

## 展望
v1.4以降では、もっと速くて軽いプログラムを作ります。
よろしくおねがいします。

## 注意点
できるだけファイル、フォルダ構造は変更しないでください。
変更する場合は自己責任で、パスやソースコード、ファイル名の設定を各自行ってください。

## License
詳細は、LISENCEを参照してください。

## Overview ##
This program is a simple Pomodoro timer.
Versions up to "latest_version" were written in C by a Japanese speaker.
The "aura_version" was written in C++ by a Japanese speaker.
I enjoy ASCII art, so I decided to create a Pomodoro timer using VS Code and Copilot as a practice project!

## Behavior in "v1.3"
"work time": Refers to the duration of the work session.
"short break time": Refers to the duration of a short break.
"long break time": Refers to the duration of a long break.
"sessions": Refers to the total number of work sessions (excluding both short and long breaks).
"Long interval spacing": Determines how often a long break occurs (i.e., after how many short break cycles). While the standard Pomodoro technique uses 4 sessions, this program allows you to set this freely.
"Reminder interval": Determines how often (in minutes) a video plays and a Notepad window pops up.
As indicated in the license, you are free to modify the source code; please make any necessary adjustments yourself.

## Operating Environment
This program is designed to run on Linux.

## Development Environment
Linux Mint 22.3 MATE.

## Compilation and Execution
"pomo" runs as a standalone program. Navigate to the `src/"version_name"` directory, run `g++ main.cpp -o main`, and then execute it with `./main`.
For "v1.3", please avoid changing the folder structure as much as possible. If you do modify it, please update the source code accordingly. Run `g++ main.cpp -o main` followed by `./main` to execute.

## Future Plans
For v1.4 and beyond, I plan to create a faster and more lightweight program.
Thank you.

## Important Notes
Please avoid changing the file and folder structure as much as possible.
If you do make changes, please do so at your own risk and update the paths, source code, and file name settings yourself.

## License
Please refer to the LICENSE file for details.

