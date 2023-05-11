var logoBoard = document.getElementById("logo-board");
var menuBoard = document.getElementById("menu-board");
var gameBoard = document.getElementById("game-board");

function loadMenu(){
    logoBoard.style.display = 'none';
    menuBoard.style.display = 'block';
    gameBoard.style.display = 'none';
    console.log("111");
}

function start(){
    console.log("開始遊戲");
    logoBoard.style.display = 'none';
    menuBoard.style.display = 'none';
    gameBoard.style.display = 'block';
}

function online(){
    console.log("線上模式");
}

function about(){
    console.log("關於");
}

function options(){
    console.log("其他選項");
}

function exit(){
    console.log("離開");
}
