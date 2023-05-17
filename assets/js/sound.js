let soundBGM = new Audio("./sound/bgm.mp3");
let soundClick = new Audio("./sound/click.mp3");
let soundMove = new Audio("./sound/move.mp3");

function stopAllSound() {
  soundBGM.pause();
  soundBGM.currentTime = 0;
}

function playBGM() {
  soundBGM.currentTime = 0;
  soundBGM.loop = true;
  soundBGM.play();
}

function playClickSound() {
  soundClick.currentTime = 0;
  soundClick.play();
}

function playMoveSound() {
  soundMove.currentTime = 0;
  soundMove.play();
}
