![logo](https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/21264d81-8ee4-4832-9c59-d5f5c8828827)
# CS1010301-Chess-Project
111.2 CS1010301 物件導向程式設計實習 西洋棋遊戲  
An original chess game.  
Written in C++ with web technology based GUI.  
<img width="1572" alt="截圖 2023-05-20 上午4 31 10" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/9f584c02-a28c-4877-9fad-29d8938364bc">
<img width="1572" alt="截圖 2023-05-20 上午4 40 23" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/542c06ae-e7ec-4694-9846-f0cbd348aabf">
<img width="1572" alt="截圖 2023-05-20 上午4 32 39" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/c603796f-463f-42c9-bdfc-c914c72957c4">
<img width="1572" alt="截圖 2023-05-20 上午4 39 40" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/884e04ba-b04a-4f21-89ca-20ae33d67334">

## Support Platforms
 - Windows MSVC
 - MacOS AppleClang
 - Linux GCC/Clang
 > ⚠️ Apple Silicon (arm64) is not currently supported.

## Build
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## Run
### Launch Arguments
 - `--window` Launch in window mode
 - `--skip-intro` Launch skip intro animation and cover

## Known Issues
 - On windows platform, if the screen ratio is not set to 100%, it may cause window size problems. If you encounter this situation, it is recommended to use `--window` to run in windowed mode.
 - The sound may play 2 times per click, or not when clicked, which appears to be caused by the HTML renderer UltraLight, and we have not yet found a solution to this problem.
## Features
> ✋ Because of the limited time of the development team,  
>    we haven't finished all the features yet, we always welcome pull request or issue.  

|      | Name          | Description                                    |
| ---- | ------------- | ---------------------------------------------- |
| ✅    | Move Piece    | Move piece on the board                        |
| ✅    | Special Case  | Promoting/Castle/En Passant                    |
| ❎    | Undo/Redo     |                                                |
| ✅    | Show Result   | Win/Lose/Checkmate                             |
| ✅    | Menu          |                                                |
| ✅    | Resign        |                                                |
| ✅    | Timeout       | When the player's time is up, the player loses |
| ✅    | Display Clock | Display player's clock                         |
| ✅    | Who First     | Set custom first player in custom mode         |
| ❎    | FEN Standard  | Load custom game with FEN standard             |
| ❎    | Online Mode   | Multiplayer online games                       |

## Design
Beautiful and aesthetically pleasing user interface.  
All original materials are created by our designers.  
[Figma Design Project](https://www.figma.com/file/upeASWAWHpmBMB9tXlhOBT/chess-project?type=design&node-id=0%3A1&t=PiioRERyi1d0lOvg-1)
<img width="903" alt="截圖 2023-05-20 上午4 54 54" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/a376a8a0-e5a7-4826-874e-4291dc596908">
<img width="1515" alt="截圖 2023-05-20 上午4 55 41" src="https://github.com/CRT-HAO/CS1010301-Chess-Project/assets/31580253/5a1916e0-e5d9-4062-af2a-f888ac107134">

### Assets Reference
| Type             | Name                      | Source                                                |
| ---------------- | ------------------------- | ----------------------------------------------------- |
| Background Music | Japanese Cute Vibes       | https://www.youtube.com/watch?v=nzO90ZYKUAQ           |
| Font             | Frostbite Boss Fight Font | https://fontmeme.com/fonts/frostbite-boss-fight-font/ |
