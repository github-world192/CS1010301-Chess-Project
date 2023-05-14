let startupBoard = $("#startup-board");
let coverBoard = $("#cover-board");
let menuBoard = $("#menu-board");
let gameBoard = $("#game-board");

function hideAllBoard() {
  startupBoard.hide();
  coverBoard.hide();
  menuBoard.hide();
  gameBoard.hide();
}

function loadStartup() {
  hideAllBoard();
  startupBoard
    .delay(1000)
    .fadeIn(1000)
    .delay(5000)
    .fadeOut(1000, function () {
      loadCover();
    });
}

function loadCover() {
  hideAllBoard();
  coverBoard.fadeIn(1000);
}

function loadMenu() {
  hideAllBoard();
  menuBoard.show();
}

function start() {
  console.log("開始遊戲");
  startupBoard.hide();
  coverBoard.hide();
  menuBoard.hide();
  gameBoard.show();
}

function online() {
  console.log("線上模式");
}

function about() {
  console.log("關於");
}

function options() {
  console.log("其他選項");
}

function exit() {
  console.log("離開");
}

$(document).ready(function () {
  loadStartup();
  //   loadCover();
});
