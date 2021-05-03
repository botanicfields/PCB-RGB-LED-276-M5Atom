# PCB-RGB-LED-276-M5Atom
Circle clock using 276pcs of WS2812C-2020 and an M5Atom

<img src="https://github.com/botanicfields/PCB-RGB-LED-276-M5Atom/blob/main/jpg/bf-025_example.JPG" width=300>

## 頒布

[M5Atom 用 RGB LED 276 基板](https://www.switch-science.com/catalog/7039/)

[M5Atom 用 RGB LED 276 基板（丸形）](https://botanicfields.booth.pm/items/2940057)

## 説明書

https://github.com/botanicfields/PCB-RGB-LED-276-M5Atom/blob/main/bf-025_doc.pdf

## 置時計のデモ
　置時計のデモを作成しました。以下の機能があります。

- 時・分・秒・曜日・年・月・日の表示（スクロール）
- 時・分・秒のアナログ風表示（彗星の尾）
- 文字盤背景色の変化
- デモ: 時刻表示中のデモ (DemoClock)
- デモ: カウントダウンタイマー (DemoTimeShock)
- デモ: ランプテスト表示 (DemoCyron)
- デモ: 色相環表示 (DemoHueRing)
- デモ: パーリンノイズ (DemoNoise)

　時刻表示中のデモには以下があります。

- 文字色の切替（シアン・赤・緑・青）
- フォント表示（記号・数字、英大文字、英小文字）
- テキスト表示（英大文字、英小文字混在）
- エイリアン

　動作中 M5Atom のボタンで以下を操作します。切替の状況はシリアルモニタで確認できます。

|長押し時間|表示|効果|
|:-:|:-:|:-:|
| -  |Pale|カラーパレットを切替|
|>1 秒|Next|デモを切替、【クロックデモ】デモ内容を切替（文字色、フォント）|
|>2 秒|Exit|デモを切替|
|>3 秒|Temp|色温度を切替|
|>4 秒|Corr|色補正を切替|
|>5 秒|Scal|【パーリンノイズデモ】スケール (x, y) を切替|
|>6 秒|Peri|【パーリンノイズデモ】周期 (z) を切替|
|>7 秒|Null|ボタン操作を取消|

　カウントダウンタイマー動作中、M5Atom のボタンで以下を操作します。

|長押し時間|表示|状態|効果|
|:-:|:-:|:-:|:-:|
| - | - |カウントダウン停止中|カウントダウン開始|
| - | - |カウントダウン中|クイズモードに移行、賞金額を表示|
|>1 秒|Stop| - |カウントダウンを中止、初期値に戻す|
|>2 秒|Time| - |カウントダウンを中止、初期値を変更|
|>3 秒|Pale| - |カラーパレットを変更|
|>4 秒|Exit| - |終了、デモを切替|
|>5 秒|Null| - |ボタン操作を取消|

## 解説 Explanation
"Circle LED Clock by M5Atom and FastLED" in Japanese

[M5Atom と FastLED で 円形 LED 時計を作る](https://qiita.com/BotanicFields/items/a1e182f418d5a07120ac)

<img src="https://github.com/botanicfields/PCB-RGB-LED-276-M5Atom/blob/main/jpg/bf-025_front.JPG" width=300>

<img src="https://github.com/botanicfields/PCB-RGB-LED-276-M5Atom/blob/main/jpg/bf-025_lite.JPG" width=300>

## YouTube: Clock Demonstration 

[Clock Demo on BF-025: RGB-LED 276 for M5Atom](https://youtu.be/55dffut1Fk0)

## 3D images by KiCad:

<img src="https://github.com/botanicfields/PCB-RGB-LED-276-M5Atom/blob/main/bf-025_front.png" width=300>

<img src="https://github.com/botanicfields/PCB-RGB-LED-276-M5Atom/blob/main/bf-025_back.png" width=300>

## YouTube: Examples

[ColorPalette an example from FastLED on BF-025: RGB-LED 276 for M5Atom](https://youtu.be/OUliTGfqcDM)

[DemoReel100 an example from FastLED on BF-025 RGB-LED 276 for M5Atom](https://youtu.be/VHuoHDQSU5E)

[Pacifica an example from FastLED on BF-025 RGB-LED 276 for M5Atom](https://youtu.be/MY5FGuDM8ZY)

[Pride2015 an example from FastLED on BF-025: RGB-LED 276 for M5Atom](https://youtu.be/uj7ePEQMkhk)

[TwinkleFox an exmaple from FastLED on BF025: RGB-LED 276 for M5Atom](https://youtu.be/3NwbCFiiEbc)

## Discussions

[JLCPCB official user group facebook](https://www.facebook.com/groups/JLCPCB/permalink/837468943770299/)

## Practical status of gerber, BOM, pick & place

### V02L01

- JLCPCB: OK

### V03L01

- ALLPCB: OK
- Seeed FusionPCB: OK

### V03L02

- ALLPCB: OK
- JLCPCB: OK
