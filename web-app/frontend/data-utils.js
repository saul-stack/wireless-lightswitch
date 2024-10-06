const getBoardName = () => {
  const boardName = import.meta.env.VITE_BOARD_HOSTNAME || "";
  return boardName;
};

export { getBoardName };
