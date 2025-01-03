#!/bin/sh

# Fungsi untuk menampilkan pesan error dan keluar
error_exit() {
    echo "Error: $1"
    exit 1
}

# Cek apakah JAVA_HOME sudah diatur
[ -z "$JAVA_HOME" ] && error_exit "JAVA_HOME tidak diatur. Harap atur JAVA_HOME dan coba lagi."

# Cek apakah Java dapat ditemukan
[ ! -x "$JAVA_HOME/bin/java" ] && error_exit "Java tidak ditemukan di $JAVA_HOME/bin/java. Harap periksa instalasi Java Anda."

# Dapatkan direktori skrip saat ini
DIRNAME=$(dirname "$0")

# Path JAR ANTLR
JAR_PATH="$DIRNAME/antlr/antlr-4.13.2-complete.jar"
[ ! -f "$JAR_PATH" ] && error_exit "File JAR ANTLR tidak ditemukan di $JAR_PATH. Harap periksa path Anda."

# Path folder grammar dan file grammar
SRC_FOLDER_PATH="$DIRNAME/../src"
GRAMMAR_FOLDER_PATH="$DIRNAME/../grammar"
GRAMMAR_PARSER_FILE="$GRAMMAR_FOLDER_PATH/NGParser.g4"
GRAMMAR_LEXER_FILE="$GRAMMAR_FOLDER_PATH/NGLexer.g4"

# Cek apakah folder grammar ada
[ ! -d "$GRAMMAR_FOLDER_PATH" ] && error_exit "Folder grammar tidak ditemukan di $GRAMMAR_FOLDER_PATH. Harap periksa path Anda."

# Cek apakah file grammar ada
[ ! -f "$GRAMMAR_PARSER_FILE" ] && error_exit "File Parser.g4 tidak ditemukan di $GRAMMAR_PARSER_FILE. Harap periksa file grammar Anda."
[ ! -f "$GRAMMAR_LEXER_FILE" ] && error_exit "File Lexer.g4 tidak ditemukan di $GRAMMAR_LEXER_FILE. Harap periksa file grammar Anda."

# Cek apakah folder output ada atau buat jika belum ada
if [ ! -d "$SRC_FOLDER_PATH" ]; then
    echo "Folder output tidak ditemukan. Membuat folder di $SRC_FOLDER_PATH."
    mkdir -p "$SRC_FOLDER_PATH" || error_exit "Gagal membuat folder output di $SRC_FOLDER_PATH."
fi

# Jalankan ANTLR untuk menghasilkan file C++
echo "Menjalankan ANTLR untuk menghasilkan file C++..."
"$JAVA_HOME/bin/java" -jar "$JAR_PATH" -Dlanguage=Cpp -package ngrammar -visitor -listener -o "$SRC_FOLDER_PATH" "$GRAMMAR_LEXER_FILE" "$GRAMMAR_PARSER_FILE"

# Validasi output
if [ $? -ne 0 ]; then
    error_exit "Proses ANTLR gagal. Periksa file antlr_output.log untuk detail."
fi

# Cek apakah file output berhasil dihasilkan
OUTPUT_FILES=$(find "$SRC_FOLDER_PATH" -type f -name "*.cpp" -o -name "*.h")
if [ -z "$OUTPUT_FILES" ]; then
    error_exit "Tidak ada file output yang dihasilkan oleh ANTLR. Periksa konfigurasi grammar Anda."
else
    echo "File output berhasil dihasilkan di $SRC_FOLDER_PATH:"
    echo "$OUTPUT_FILES"
fi

echo "Proses selesai tanpa error."