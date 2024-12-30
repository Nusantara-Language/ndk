/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef FILE_TXT_H
#define FILE_TXT_H

#include "file.h"
#include <vector>

namespace ncpp {

class FileTxt : public File
{
public:
    explicit FileTxt(std::string path);

    std::string_view getContent();
    std::string_view getContentInLine(const size_t& row);
    std::string& getEditableContent();
    const std::vector<std::string>& getContentWithLine();
    // akhir dari access modifiers public

private:
    // String
    bool ctnIsStr();
    void ctnToStr();
    std::string_view gtCtnStr();
    // String Split
    bool ctnIsSpltStr();
    void spltCtnStr();
    std::vector<std::string>& gtEdtSpltCtnStr();
    // akhir dari access modifiers private

protected:
    // akhir dari access modifiers protected

}; // class File

} // namespace ncpp

#endif