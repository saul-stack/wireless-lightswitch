const getBoardName = async () => {
  const rawData = await fetch("/common-config.json");
  const config = await rawData.json();
  const { boardName } = config;
  return boardName;
};

export { getBoardName };
