/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

/**
 * @brief Label Keluaran
 * 
 * @details Label keluaran adalah penanda yang muncul ketika program
 * mengeluarkan pesan di konsol, seperti pesan kesalahan atau informasi lainnya. 
 * Fungsi utama label ini adalah untuk menunjukkan dari mana pesan keluaran tersebut berasal, 
 * sehingga memudahkan dalam menganalisis program.
 */

/**
 * @brief Label keluaran pemecah sintaks/tokenizer/lexer
 * 
 */
#define __NK__LABEL_KELUARAN_TS__ "[TS] "

/**
 * @brief Label keluaran analisis semantik/penganalisa semantik/semantic analyzer
 * 
 */
#define __NK__LABEL_KELUARAN_AS__ "[AS] "

/**
 * @brief Label keluaran pengurai sintaks/parser
 * 
 */
#define __NK__LABEL_KELUARAN_PS__ "[PS] "

/**
 * @brief Label keluaran penafsir/intepreter
 * 
 */
#define __NK__LABEL_KELUARAN_P__ "[P] "

/**
 * @brief Label keluaran lingkungan eksekusi/runtime
 * 
 */
#define __NK__LABEL_KELUARAN_LE__ "[LE] "

/**
 * @brief Label keluaran custom
 * 
 */
#define __NK__LABEL_KELUARAN_CUSTOM__(LABEL) "[" LABEL "] "