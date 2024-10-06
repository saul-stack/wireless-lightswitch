import axios from "axios";
import { getBoardName } from "./data-utils";

const requestLEDAction = async (request) => {
  try {
    const boardName = await getBoardName();
    await axios.post(`http://${boardName}/LED`, request, {
      headers: {
        "Content-Type": "application/json",
      },
    });
  } catch (error) {
    console.error("Error making HTTP request:", error);
  }
};

export { requestLEDAction };
