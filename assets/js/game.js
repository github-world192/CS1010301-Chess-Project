function getPiecePicUrl(type, owner) {
  let url = "./image/piece/";
  url += type + "-" + owner + ".png";
  return url;
}

function updateCurrentPlayer() {
  $("#current_player").text(apiGetCurrentPlayer());
}

function updateBoard() {
  let boardData = apiGetBoard();
  let board = $("#game-board");
  let boardBody = board.find("#game-board-container");
  boardBody.empty();
  for (let i = 0; i < boardData.height; i++) {
    let tr = $(`<div class="game-board-grid-item"></div>`);
    for (let j = 0; j < boardData.width; j++) {
      let pieceData = boardData.board[i][j];

      let pieceContainer = $(
        `<div class="game-board-piece-container" piece-container></div>`
      );
      pieceContainer.attr("piece-container-x", j).attr("piece-container-y", i);

      if (pieceData.type != "null") {
        let pieceImg = $(`<img alt="">`);
        pieceImg.attr("src", getPiecePicUrl(pieceData.type, pieceData.owner));

        let piece = $(
          `<div class="game-board-piece-piece" piece-piece></div>`
        ).append(pieceImg);

        if (pieceData.movable == true) {
          piece.addClass("game-board-piece-piece-movable");
          piece.draggable({
            cursor: "grabbing",
            opacity: 0.7,
            //   helper: "clone",
            scroll: false,
            revert: true,
            zIndex: 999,
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
      }

      let td = $(`<div class="game-board-piece-spot">`).append(pieceContainer);
      tr.append(td);
    }
    boardBody.append(tr);
  }
}

function updateGame() {
  //   updateCurrentPlayer();
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
      .addClass("game-board-piece-container-droppable")
      .droppable({
        accept: "div[piece-piece]",
        hoverClass: "game-board-piece-container-droppable-hover",
        drop: function (event, ui) {
          let fromX = parseInt(ui.draggable.parent().attr("piece-container-x"));
          let fromY = parseInt(ui.draggable.parent().attr("piece-container-y"));
          let toX = parseInt($(this).attr("piece-container-x"));
          let toY = parseInt($(this).attr("piece-container-y"));
          console.log(`fromX=${fromX}, fromY=${fromY}, toX=${toX}, toY=${toY}`);
          console.log(movePiece(fromX, fromY, toX, toY));
          updateGame();
        },
      });
  });
}

function stopDragPiece() {
  $("div[piece-container]").each(function () {
    $(this).removeClass("game-board-piece-container-droppable");
  });
}
