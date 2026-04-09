import csv
import serial
from datetime import datetime

PORT = "COM3"       # Change to your serial port
BAUD = 115200
OUTPUT_FILE = "runtime_log.csv"

def main():
    ser = serial.Serial(PORT, BAUD, timeout=1)
    with open(OUTPUT_FILE, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["timestamp", "raw_line"])
        print(f"Logging UART data from {PORT} to {OUTPUT_FILE}...")

        try:
            while True:
                line = ser.readline().decode("utf-8", errors="ignore").strip()
                if line:
                    print(line)
                    writer.writerow([datetime.now().isoformat(), line])
        except KeyboardInterrupt:
            print("Logging stopped.")
        finally:
            ser.close()

if __name__ == "__main__":
    main()
