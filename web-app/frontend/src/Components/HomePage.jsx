import { requestLEDAction } from "../../api-utils";
export const HomePage = () => {
  const handleButtonClick = (action) => {
    requestLEDAction({ action: action });
  };
  return (
    <div className="main-content">
      <div className="button-container">
        <h1>Wireless Lightswitch</h1>
        <div className="button-container">
          <button
            onClick={() => handleButtonClick("activate")}
            className="button"
          >
            Turn On
          </button>
          <button
            onClick={() => handleButtonClick("deactivate")}
            className="button"
          >
            Turn Off
          </button>
          <button onClick={() => handleButtonClick("blink")} className="button">
            Blink
          </button>
          <button
            onClick={() => handleButtonClick("toggle")}
            className="button"
          >
            Toggle
          </button>
          <button
            onClick={() => handleButtonClick("flashing")}
            className="button"
          >
            Flashing
          </button>
        </div>
      </div>
    </div>
  );
};
