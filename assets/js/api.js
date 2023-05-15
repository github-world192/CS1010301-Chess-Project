function apiGetBoard() {
  let r = {
    width: 8,
    height: 8,
    board: [
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
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
        { type: "null", owner: "null", movable: false },
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
