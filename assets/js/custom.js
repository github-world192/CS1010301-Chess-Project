function startCustomGame() {
  let playeVal = $("#custom-first-player").val();
  let player = parseInt(playeVal == "white" ? 0 : 1);
  let customTime = parseInt($("#custom-time").val());
  startGameCustom(player, customTime);
  moveToBoardView("game");
}
