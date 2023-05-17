/**
 * URL Proccess
 */
function getHashTag() {
  return location.hash.substring(1);
}

function setHashTag(tag) {
  const nextURL = "#" + tag;
  const nextTitle = document.title;
  const nextState = {};

  // This will create a new entry in the browser's history, without reloading
  window.history.pushState(nextState, nextTitle, nextURL);
}

/**
 * Board View
 */
const startupBoard = $("#startup-board");
const coverBoard = $("#cover-board");
const menuBoard = $("#menu-board");
const gameBoard = $("#game-board");
const customBoard = $("#custom-board");
const drawBoard = $("#draw-board");
const winBoard = $("#win-board");
const timeoutBoard = $("#timeout-board");

function hideAllBoard() {
  startupBoard.hide();
  coverBoard.hide();
  menuBoard.hide();
  gameBoard.hide();
  customBoard.hide();
  drawBoard.hide();
  winBoard.hide();
  timeoutBoard.hide();
}

function loadStartupView() {
  hideAllBoard();
  startupBoard
    .delay(1000)
    .fadeIn(1000)
    .delay(5000)
    .fadeOut(1000, function () {
      moveToBoardView("cover");
    });
}

function loadCoverView() {
  stopAllSound();
  hideAllBoard();
  coverBoard.fadeIn(1000);
}

function loadMenuView() {
  hideAllBoard();
  menuBoard.show();
  playBGM();
}

function loadGameView() {
  hideAllBoard();
  gameBoard.show();
  loadGame();
  updateGame();
}

function loadCustomView() {
  hideAllBoard();
  customBoard.show();
}

function loadWinView() {
  hideAllBoard();
  winBoard.show();
}

function unloadStartupView() {}

function unloadCoverView() {}

function unloadMenuView() {}

function unloadGameView() {
  stopGame();
}

function unloadCustomView() {}

let lastHashTag = undefined;
function updateBoardView() {
  // Load View
  switch (getHashTag()) {
    case "startup":
      loadStartupView();
      break;
    case "cover":
      loadCoverView();
      break;
    case "menu":
      loadMenuView();
      break;
    case "game":
      loadGameView();
      break;
    case "custom":
      loadCustomView();
      break;
    case "win":
      loadWinView();
      break;
    default:
      moveToBoardView("startup");
      break;
  }
  // Unload View
  if (lastHashTag != getHashTag()) {
    switch (lastHashTag) {
      case "startup":
        unloadStartupView();
        break;
      case "cover":
        unloadCoverView();
        break;
      case "menu":
        unloadMenuView();
        break;
      case "game":
        unloadGameView();
        break;
      case "custom":
        unloadCustomView();
        break;
    }
  }
  if (lastHashTag != getHashTag()) {
    lastHashTag = getHashTag();
  }
}

function moveToBoardView(tag) {
  setHashTag(tag);
  updateBoardView();
}

/**
 * Cover Functions
 */
function coverPress() {
  moveToBoardView("menu");
}

/**
 * Menu Functions
 */
function start() {
  startGame();
  moveToBoardView("game");
}

function custom() {
  moveToBoardView("custom");
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
  moveToBoardView("cover");
}

/**
 * Menu Functions
 */
function menu() {
  moveToBoardView("menu");
}

/**
 * Window Event
 */
$(window).on("hashchange", function () {
  updateBoardView();
});

/**
 * Document Event
 */
$(document).on("click", "body button, a, input", function () {
  playClickSound();
});

$(document).ready(function () {
  updateBoardView();
});
