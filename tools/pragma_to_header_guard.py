import os

def convert_pragma_to_header_guard(file_path):
    """
    Mengganti #pragma once dengan header guard dalam file .hpp atau .hpp.template.
    
    Args:
        file_path (str): Path ke file .hpp atau .hpp.template.
    """
    # Pastikan file memiliki ekstensi .hpp atau .hpp.template
    if not (file_path.endswith('.hpp') or file_path.endswith('.hpp.template')):
        print(f"File {file_path} bukan file .hpp atau .hpp.template!")
        return

    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
    except Exception as e:
        print(f"Error membaca file {file_path}: {e}")
        return

    # Cek apakah ada #pragma once
    if "#pragma once" not in "".join(lines):
        print(f"Tidak ada '#pragma once' dalam file {file_path}.")
        return

    # Membuat nama header guard
    file_name = os.path.basename(file_path)
    guard_name = file_name.replace('.', '_').upper()

    # Membuat header guard
    header_guard_start = f"#ifndef {guard_name}\n#define {guard_name}\n"
    header_guard_end = f"\n#endif\n"

    # Ganti #pragma once dengan header guard
    new_lines = []
    for line in lines:
        if line.strip() == "#pragma once":
            new_lines.append(header_guard_start)
        else:
            new_lines.append(line)

    # Tambahkan header guard di akhir file
    if not new_lines[-1].endswith("\n"):
        new_lines[-1] += "\n"  # Tambah newline jika tidak ada
    new_lines.append(header_guard_end)

    # Simpan perubahan
    try:
        with open(file_path, 'w') as file:
            file.writelines(new_lines)
        print(f"File {file_path} berhasil diubah dengan header guard.")
    except Exception as e:
        print(f"Error menyimpan file {file_path}: {e}")

def get_hpp_files(folder_path):
    """
    Mengambil semua path file .hpp dan .hpp.template secara rekursif dari folder yang diberikan.
    
    Args:
        folder_path (str): Path ke folder utama.
    
    Returns:
        list: Kumpulan path file .hpp dan .hpp.template.
    """
    hpp_files = []

    for root, _, files in os.walk(folder_path):
        for file in files:
            if file.endswith('.hpp') or file.endswith('.hpp.template'):
                # Gabungkan root path dengan nama file untuk mendapatkan full path
                full_path = os.path.join(root, file)
                hpp_files.append(full_path)

    return hpp_files

# Path folder utama
folder_a = "nusantara"
hpp_files = get_hpp_files(folder_a)

# Proses setiap file .hpp dan .hpp.template
for file in hpp_files:
    convert_pragma_to_header_guard(file)