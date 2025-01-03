/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef FILE_H
#define FILE_H

#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace ncpp {

class File
{
public:
    explicit File(std::string path);

    void read();
    bool exist();
    std::string_view getPath() noexcept;
    // akhir dari access modifiers public

private:
    std::string pth;
    std::variant<std::vector<char>, std::string, std::vector<std::string>> ctn;
    // akhir dari access modifiers private

protected:
    std::variant<std::vector<char>, std::string, std::vector<std::string>>& gtEdtCtn() noexcept;
    // akhir dari access modifiers protected

}; // class File

} // namespace ncpp

#endif