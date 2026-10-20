# Pomodoro

> 集中すると寿命縮むよ。

## 概要
ただの、アスキーアートのポモドーロタイマーです。
C と Python と C++ で、少しずつ書いてきました。

- いまの安定版は v2.1 です。
- `src/` の下には、過去のものが眠っています。もう使わないけれど、消せずに残しています。

## v1.9 での挙動
- **Work Time** — 作業の時間。
- **Short Break Time** — 短い休憩。息をひとつ吐くくらいの。
- **Long Break Time** — 長い休憩。
- **Sessions** — 全部で、何回くりかえすか。
- **Long Interval spacing** — 何回に一度、長く休むか。ふつうは 4 回ですが、ここでは 128 まで数えられます。
- **Reminder interval** — 何分ごとに動画が流れて、メモ帳が開くか。忘れてしまわないように。

## v1.8 での挙動
v1.7 までは、ふつうのポモドーロと同じように時間が流れます。
v1.8 から、**Additional Break Time** が加わりました。
作業の途中でも、立ち止まっていい時間です。長さは自分で決められます。

## 動作環境
Linux で動くことだけを想定しています。

## 開発環境
Linux Mint 22.3 MATE

## コンパイルと実行
使いたいバージョンのフォルダへ移動して:

```
g++ main.cpp -o main
./main
```

## おねがい
ファイルやフォルダの並びは、できるだけそのままにしておいてください。
動かすなら、パスもソースもファイル名も、あなたの手で合わせてください。その先は、自己責任で。

## License
LICENSE を見てください。

---

# Pomodoro

> Time slips away before you notice.
> So at least the pauses, I leave here.

## Overview
If you do not die fast, do not focusing too much.

- v2.1 is the current stable version.
- Older versions sleep under `src/`. No longer used, but I couldn't bring myself to delete them.

## Behavior in v1.9
- **Work Time** — the time you spend working.
- **Short Break Time** — a short rest. About as long as one breath.
- **Long Break Time** — a longer rest.
- **Sessions** — how many times it all repeats.
- **Long Interval spacing** — how often the long rest comes. Usually every 4 sessions; here it can count up to 128.
- **Reminder interval** — how many minutes between each time a video plays and a notepad opens. So you don't forget.

## Behavior in v1.8
Up to v1.7, time flows just like an ordinary Pomodoro timer.
From v1.8, **Additional Break Time** was added —
a moment you're allowed to stop, even in the middle of work. You choose how long it lasts.

## System Requirements
Made with only Linux in mind.

## Development Environment
Linux Mint 22.3 MATE

## Compilation and Execution
Move into the folder of the version you want, then:

```
g++ main.cpp -o main
./main
```

## What Comes Next
- Faster. Lighter.
- For now, you can only move between Additional Break Time and Work Time. Someday, I hope it can return to the other times too.

## A Small Request
Please leave the files and folders as they are, as much as you can.
If you move them, the paths, the source, and the filenames are yours to set right. What happens after that is your own.

## License
See LICENSE.