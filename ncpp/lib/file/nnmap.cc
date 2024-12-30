/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <stdexcept>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <unistd.h>
#endif

#include "file/nnmap.h"

namespace ncpp {

/**
 * @brief Memetakan file ke dalam memori dan mengembalikan isinya sebagai std::vector<char>.
 *
 * Fungsi ini membuka file yang ditentukan, memetakannya ke dalam memori,
 * dan mengembalikan konten file sebagai vector karakter. Fungsi ini
 * mendukung platform Windows dan Unix-like (Linux/MacOS).
 *
 * @param filename Nama file yang akan dipetakan.
 * @return std::vector<char> Vector yang berisi konten file.
 *
 * @throws std::runtime_error Jika terjadi kesalahan saat membuka file,
 *         mendapatkan ukuran file, atau memetakan file ke dalam memori.
 *
 * @note
 * - Pada Windows, fungsi ini menggunakan API Windows untuk membuka file,
 *   membuat pemetaan file, dan memetakan tampilan file.
 * - Pada Linux/MacOS, fungsi ini menggunakan sistem panggilan POSIX untuk
 *   membuka file, mendapatkan ukuran file dengan lseek, dan memetakan
 *   file menggunakan mmap.
 */
std::vector<char> nnmap(const std::string& filename)
{
    std::vector<char> buffer;

#ifdef _WIN32
    // Windows-specific code
    HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        throw std::runtime_error("Gagal untuk membuka file: " + filename);
    }

    // Mendapatkan ukuran file
    DWORD fileSize = GetFileSize(hFile, nullptr);
    if (fileSize == INVALID_FILE_SIZE)
    {
        CloseHandle(hFile);
        throw std::runtime_error("Gagal untuk mendapatkan ukuran file: " + filename);
    }

    // Jika ukuran file 0, lempar pengecualian
    if (fileSize == 0)
    {
        CloseHandle(hFile);
        throw std::runtime_error("File kosong: " + filename);
    }

    // Membuat pemetaan file
    HANDLE hMap = CreateFileMappingA(hFile, nullptr, PAGE_READONLY, 0, fileSize, nullptr);
    if (hMap == nullptr)
    {
        CloseHandle(hFile);
        throw std::runtime_error("Gagal untuk membuat file mapping: " + filename);
    }

    // Memetakan tampilan file ke dalam memori
    char* data = static_cast<char*>(MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, fileSize));
    if (data == nullptr)
    {
        CloseHandle(hMap);
        CloseHandle(hFile);
        throw std::runtime_error("Gagal memetakan tampilan file: " + filename);
    }

    // Menyalin data dari mapped view ke buffer
    buffer.assign(data, data + fileSize);

    // Clean up
    UnmapViewOfFile(data); // Menghapus pemetaan tampilan
    CloseHandle(hMap);     // Menutup handle pemetaan
    CloseHandle(hFile);    // Menutup handle file
#else
    // Linux/MacOS-specific code
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1)
    {
        throw std::runtime_error("Gagal untuk membuka file: " + filename);
    }

    // Mendapatkan ukuran file dengan lseek
    off_t fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize == -1)
    {
        close(fd);
        throw std::runtime_error("Gagal mendapatkan ukuran file: " + filename);
    }

    // Jika ukuran file 0, lempar pengecualian
    if (fileSize == 0)
    {
        close(fd);
        throw std::runtime_error("File kosong: " + filename);
    }

    lseek(fd, 0, SEEK_SET); // Reset pointer ke awal

    // Memetakan file ke dalam memori
    char* data = static_cast<char*>(mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));
    if (data == MAP_FAILED)
    {
        close(fd);
        throw std::runtime_error("Gagal memetakan file: " + filename);
    }

    // Menyalin data dari mapped view ke buffer
    buffer.assign(data, data + fileSize);

    // Clean up
    munmap(data, fileSize); // Menghapus pemetaan
    close(fd);              // Menutup descriptor file
#endif

    return buffer; // Mengembalikan konten yang dipetakan sebagai vector karakter
}

} // namespace ncpp