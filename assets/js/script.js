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

function hideAllBoard() {
  startupBoard.hide();
  coverBoard.hide();
  menuBoard.hide();
  gameBoard.hide();
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
  hideAllBoard();
  coverBoard.fadeIn(1000);
}

function loadMenuView() {
  hideAllBoard();
  menuBoard.show();
}

function loadGameView() {
  hideAllBoard();
  gameBoard.show();
  updateGame();
}

function updateBoardView() {
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
    default:
      moveToBoardView("startup");
      break;
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
  moveToBoardView("game");
}

function custom() 
{
  console.log("自訂");
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
$(document).ready(function () {
  updateBoardView();
});
