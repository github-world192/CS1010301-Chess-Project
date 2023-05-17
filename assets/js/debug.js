function updateCurrentPlayer() {
  $("#current_player").text(apiGetCurrentPlayer());
}

function updateBoard() {
  let boardData = apiGetBoard();
  let board = $("#board");
  let boardBody = board.find("tbody");
  boardBody.empty();
  for (let i = 0; i < boardData.height; i++) {
    let tr = $("<tr></tr>");
    for (let j = 0; j < boardData.width; j++) {
      let pieceContainer = $(
        `<div class="piece-container" piece-container></div>`
      );
      pieceContainer.attr("piece-container-x", j).attr("piece-container-y", i);
      let piece = $(`<div class="piece-piece" piece-piece></div>`).text(
        `${boardData.board[i][j].type}(${boardData.board[i][j].owner})`
      );
      if (boardData.board[i][j].movable == true) {
        piece.addClass("piece-piece-movable");
        piece.draggable({
          cursor: "grabbing",
          opacity: 0.7,
          helper: "clone",
          revert: true,
          start: function () {
            let x = j;
            let y = i;
            startDragPiece(x, y);
          },
          stop: function () {
            stopDragPiece();
          },
        });
      }
      pieceContainer.append(piece);
      let td = $("<td></td>").append(pieceContainer);
      tr.append(td);
    }
    boardBody.append(tr);
  }
}

function update() {
  updateCurrentPlayer();
  updateBoard();
}

function movePiece(fromX, fromY, toX, toY) {
  return apiBoardMovePiece(fromX, fromY, toX, toY);
}

function startDragPiece(x, y) {
  let movablePos = apiGetBoardPieceMovablePos(x, y);
  if (movablePos === undefined) return;

  console.log(movablePos);

  movablePos.forEach(function (e) {
    $(
      `div[piece-container][piece-container-x=${e.x}][piece-container-y=${e.y}]`
    )
      .addClass("piece-container-movable")
      .droppable({
        accept: "div[piece-piece]",
        hoverClass: "piece-container-movable-hover",
        drop: function (event, ui) {
          let fromX = parseInt(ui.draggable.parent().attr("piece-container-x"));
          let fromY = parseInt(ui.draggable.parent().attr("piece-container-y"));
          let toX = parseInt($(this).attr("piece-container-x"));
          let toY = parseInt($(this).attr("piece-container-y"));
          console.log(`fromX=${fromX}, fromY=${fromY}, toX=${toX}, toY=${toY}`);
          console.log(movePiece(fromX, fromY, toX, toY));
          update();
        },
      });
  });
}

function stopDragPiece() {
  $("div[piece-container]").each(function () {
    $(this).removeClass("piece-container-movable");
  });
}

function test() {
  update();
}

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
