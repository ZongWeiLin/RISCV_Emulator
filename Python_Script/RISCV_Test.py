import os
import tkinter as tk
from tkinter import filedialog, messagebox


def run_aliss(folder_name, pattern_list_file, debug_folder):
    # 確保輸出資料夾存在
    os.makedirs(debug_folder, exist_ok=True)

    # 讀取模式清單檔案
    try:
        with open(pattern_list_file, 'r') as file:
            patterns = [line.strip() for line in file.readlines()]
    except FileNotFoundError:
        messagebox.showerror("Error", f"Pattern list file '{pattern_list_file}' not found.")
        return

    # 確認資料夾存在
    if not os.path.exists(folder_name):
        messagebox.showerror("Error", f"Folder '{folder_name}' not found.")
        return

    # 執行 ALISS 命令
    for pattern in patterns:
        aliss_command = f"./build/ALISS -e {folder_name}/{pattern}"
        print(f"Executing: {aliss_command}")
        run_code = os.system(aliss_command)

        # 若命令執行失敗，啟用除錯模式
        if run_code != 0:
            print(f"Command failed. Retrying with debug mode for '{pattern}'...")
            debug_command = f"./build/ALISS -e {folder_name}/{pattern} -d > {debug_folder}/{pattern}.log"
            print(f"Executing: {debug_command}")
            os.system(debug_command)

    messagebox.showinfo("Info", "Process completed successfully!")


def open_file_dialog(entry_field):
    """Open a file dialog and update the entry field with the selected file path."""
    file_path = filedialog.askopenfilename()
    if file_path:
        entry_field.delete(0, tk.END)
        entry_field.insert(0, file_path)


def open_folder_dialog(entry_field):
    """Open a folder dialog and update the entry field with the selected folder path."""
    folder_path = filedialog.askdirectory()
    if folder_path:
        entry_field.delete(0, tk.END)
        entry_field.insert(0, folder_path)


def start_process(folder_entry, pattern_file_entry, debug_folder_entry):
    folder_name = folder_entry.get().strip()
    pattern_list_file = pattern_file_entry.get().strip()
    debug_folder = debug_folder_entry.get().strip()

    if not folder_name or not pattern_list_file or not debug_folder:
        messagebox.showerror("Error", "All fields must be filled!")
        return

    run_aliss(folder_name, pattern_list_file, debug_folder)


def main():
    # Initialize the GUI window
    root = tk.Tk()
    root.title("ALISS Runner")
    
    # Folder name input
    tk.Label(root, text="Folder Name:").grid(row=0, column=0, padx=10, pady=5, sticky="e")
    folder_entry = tk.Entry(root, width=50)
    folder_entry.grid(row=0, column=1, padx=10, pady=5)
    tk.Button(root, text="Browse", command=lambda: open_folder_dialog(folder_entry)).grid(row=0, column=2, padx=10, pady=5)

    # Pattern list file input
    tk.Label(root, text="Pattern List File:").grid(row=1, column=0, padx=10, pady=5, sticky="e")
    pattern_file_entry = tk.Entry(root, width=50)
    pattern_file_entry.grid(row=1, column=1, padx=10, pady=5)
    tk.Button(root, text="Browse", command=lambda: open_file_dialog(pattern_file_entry)).grid(row=1, column=2, padx=10, pady=5)

    # Debug folder input
    tk.Label(root, text="Debug Folder:").grid(row=2, column=0, padx=10, pady=5, sticky="e")
    debug_folder_entry = tk.Entry(root, width=50)
    debug_folder_entry.grid(row=2, column=1, padx=10, pady=5)
    tk.Button(root, text="Browse", command=lambda: open_folder_dialog(debug_folder_entry)).grid(row=2, column=2, padx=10, pady=5)

    # Start button
    tk.Button(root, text="Run ALISS", command=lambda: start_process(folder_entry, pattern_file_entry, debug_folder_entry)).grid(row=3, column=1, pady=20)

    root.mainloop()


if __name__ == "__main__":
    main()

