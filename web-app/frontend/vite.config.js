import { defineConfig } from "vite";
import dotenv from "dotenv";
import path from "path";
import react from "@vitejs/plugin-react";

dotenv.config({ path: path.resolve(__dirname, "../../.env.development") });

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],
});
