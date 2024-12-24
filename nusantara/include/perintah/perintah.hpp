/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */


// Blokir pengulangan header
#pragma once


#include <functional>
#include <cstddef>
#include <string>
#include <vector>
#include <regex>


namespace nusantara {

  /**
   * Foward deklarasi EksekusiPerintah.
   * Méérekankan bahwa kelas EksekusiPerintah đã di deklarasikan, sehingga dapat digunakan sebagai referensi dalam perancangan kelas Perintah.
   */
  class EksekusiPerintah;

  /**
   * Class Perintah: Representasi untuk perintah Nusantara Language.
   */
  class Perintah {
    public:
    /**
     * Konstruktor Perintah.
     * @param nama Nama perintah.
     * @param deskripsi Deskripsi perintah.
     * @param intruksi Instruksi yang akan dieksekusi ketika perintah dipanggil.
     * @param tanpaArgumen Flag untuk menentukan apakah perintah memiliki argumen.
     */
    Perintah(
      std::string nama,
      std::string deskripsi,
      std::function<void(EksekusiPerintah &, size_t &, std::vector<std::string> &)> intruksi,
      const bool &tanpaArgumen
    );

    /**
     * Konstruktor Perintah yang menggunakan regex.
     * @param regex Regex untuk menentukan-pattern perintah.
     * @param nama Nama perintah.
     * @param deskripsi Deskripsi perintah.
     * @param intruksi Instruksi yang akan dieksekusi ketika perintah dipanggil.
     * @param tanpaArgumen Flag untuk menentukan apakah perintah memiliki argumen.
     */
    Perintah(
      std::regex regex,
      std::string name,
      std::string description,
      std::function<void(EksekusiPerintah &, size_t &, std::vector<std::string> &)> intruksi,
      const bool &tanpaArgumen
    );

    /**
     * Methode untuk mengembalikan nama perintah.
     * @return nama perintah.
     */
    [[nodiscard]] const std::string& ambilNama() const;

    /**
     * Methode untuk mengembalikan deskripsi perintah.
     * @return deskripsi perintah.
     */
    [[nodiscard]] const std::string& ambilDeskripsi() const;

    /**
     * Methode untuk mengembalikan regex perintah.
     * @return regex perintah.
     */
    [[nodiscard]] const std::regex& ambilRegex() const;

    /**
     * Methode untuk mengubah perintah ke dalam string.
     * @return string perintah.
     */
    [[nodiscard]] std::string ubahKeString() const;

    /**
     * Methode untuk mengeksekusi perintah.
     * @param eksekusiPerintah Instance dari kelas EksekusiPerintah.
     * @param indeksSaatIni Indeks saat ini.
     * @param argumen Argumen untuk perintah.
     */
    void eksekusi(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &argumen);

    /**
     * Methode untuk membandingkan dua perintah.
     * @param other Perintah lain.
     * @return Benar jika dua perintah sama.
     */
    bool operator==(const Perintah& other);

  private:

    /**
     * Flag untuk menentukan apakah perintah memiliki argumen.
     */
    bool tanpaArgumen;

    /**
     * Instruksi yang akan dieksekusi ketika perintah dipanggil.
     */
    std::function<void(EksekusiPerintah &, size_t &, std::vector<std::string> &)> intruksi;

    /**
     * Nama perintah.
     */
    std::string nama;

    /**
     * Deskripsi perintah.
     */
    std::string deskripsi;

    /**
     * Regex perintah.
     */
    std::regex regex;
  };

  /**
   * Class EksekusiPerintah: Representasi untuk instance eksekusi perintah Nusantara Language.
   *
   * @note Kode ini mengimplementasikan instance eksekusi perintah Nusantara Language.
   */
  class EksekusiPerintah {
    public:

    /**
     * Konstruktor default.
     *
     * @note Konstruktor ini digunakan untuk membuat instance EksekusiPerintah tanpa parameter.
     */
    EksekusiPerintah() = default;


    /**
     * Methode tambahPerintah.
     * Menambahkan perintah ke dalam kumpulan perintah.
     *
     * @param argumen Perintah yang akan ditambahkan.
     *
     * @note Methode ini digunakan untuk menambahkan perintah ke dalam kumpulan perintah.
     */
    auto tambah(Perintah argumen) -> void;


    /**
     * Methode ambilKumpulanPerintah.
     * Mengembalikan kumpulan perintah.
     *
     * @return Kumpulan perintah.
     *
     * @note Methode ini digunakan untuk mengembalikan kumpulan perintah.
     */
    auto ambilKumpulanPerintah() -> const std::vector<Perintah>&;


    /**
     * Methode eksekusi.
     * Eksekusi perintah dengan menggunakan argumen.
     *
     * @param argumen Argumen untuk perintah.
     *
     * @note Methode ini digunakan untuk eksekusi perintah dengan menggunakan argumen.
     */
    auto eksekusi(std::vector<std::string> argumen) -> void;

    private:
      /**
      * Variabel kumpulanPerintah.
      * Kumpulan perintah yang diajukan.
      *
      * @note Variabel ini digunakan untuk menyimpan kumpulan perintah.
      */
      std::vector<Perintah> kumpulanPerintah;
  };

} // nusantara