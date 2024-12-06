import csv
import serial

csv_file_path = "workout_data.csv"
serial_port = "/dev/ttyUSB0"
baud_rate = 9600

def send_lateral_raise_data():
    lateral_raise_data = []
    with open(csv_file_path, mode="r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            if row["Exercise"].strip().lower() == "lateral raise":
                lateral_raise_data.append({
                    "Set": int(row["Set"]),
                    "Reps": int(row["Reps"]),
                    "RPE": int(row["RPE"])
                })

    if not lateral_raise_data:
        print("No lateral raise data found in the CSV.")
        return

    total_sets = len(lateral_raise_data)
    reps = [entry["Reps"] for entry in lateral_raise_data]
    rpe = [entry["RPE"] for entry in lateral_raise_data]

    data = [total_sets] + reps + rpe

    try:
        with serial.Serial(serial_port, baud_rate, timeout=1) as ser:
            ser.write(bytearray(data))
            print(f"Data sent to Arduino: {data}")
    except serial.SerialException as e:
        print(f"Error communicating with the serial port: {e}")

if __name__ == "__main__":
    send_lateral_raise_data()

