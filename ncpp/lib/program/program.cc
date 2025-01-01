/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
#endif

#include "program/program.h"

namespace ncpp {

std::filesystem::path getProgramPath()
{
    static std::filesystem::path path;
    if (path.empty())
    {
#if defined(_WIN32)
        // Windows: Menggunakan GetModuleFileName
        char buffer[MAX_PATH];
        GetModuleFileName(nullptr, buffer, MAX_PATH);
        path = std::filesystem::absolute(buffer);
#elif defined(__linux__) || defined(__APPLE__)
        // Linux/MacOS: Menggunakan readlink untuk /proc/self/exe
        char buffer[1024];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (len != -1)
        {
            buffer[len] = '\0';
            path = std::filesystem::absolute(buffer);
        }
#endif
    }
    return path;
}

} // namespace ncpp