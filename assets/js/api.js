function apiGetBoard() {
  let r = {
    width: 8,
    height: 8,
    board: [
      [
        { type: "rook", owner: "black", movable: false },
        { type: "knight", owner: "black", movable: false },
        { type: "bishop", owner: "black", movable: false },
        { type: "king", owner: "black", movable: false },
        { type: "queen", owner: "black", movable: false },
        { type: "bishop", owner: "black", movable: false },
        { type: "knight", owner: "black", movable: false },
        { type: "rook", owner: "black", movable: false },
      ],
      [
        { type: "pawn", owner: "black", movable: true },
        { type: "pawn", owner: "black", movable: true },
        { type: "pawn", owner: "black", movable: true },
        { type: "pawn", owner: "black", movable: true },
        { type: "pawn", owner: "black", movable: true },
        { type: "pawn", owner: "black", movable: true },
        { type: "pawn", owner: "black", movable: true },
        { type: "pawn", owner: "black", movable: true },
      ],
      [
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
      ],
      [
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
      ],
      [
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
      ],
      [
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
      ],
      [
        { type: "pawn", owner: "white", movable: true },
        { type: "pawn", owner: "white", movable: true },
        { type: "pawn", owner: "white", movable: true },
        { type: "pawn", owner: "white", movable: true },
        { type: "pawn", owner: "white", movable: true },
        { type: "pawn", owner: "white", movable: true },
        { type: "pawn", owner: "white", movable: true },
        { type: "pawn", owner: "white", movable: true },
      ],
      [
        { type: "rook", owner: "white", movable: false },
        { type: "knight", owner: "white", movable: false },
        { type: "bishop", owner: "white", movable: false },
        { type: "king", owner: "white", movable: false },
        { type: "queen", owner: "white", movable: false },
        { type: "bishop", owner: "white", movable: false },
        { type: "knight", owner: "white", movable: false },
        { type: "rook", owner: "white", movable: false },
      ],
    ],
  };
  return r;
}

function apiGetBoardPieceMovablePos(x, y) {
  let r = [
    { x: 1, y: 4 },
    { x: 1, y: 5 },
  ];
  return r;
}
