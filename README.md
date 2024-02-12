# Deskripsi Singkat
Program ini adalah sebuah program yang terinspirasi dari mekanik minigame *Breach Protocol* di game _Cyberpunk 2077_. Program ini akan mencari solusi buffer paling optimal dari beberapa sequence yang disertai dengan reward. Solusi yang paling optimal yang dimaksud adalah buffer yang menghasilkan poin tertinggi dengan panjang buffer terpendek.

Program ini memiliki dua fitur utama, yaitu input melalui file.txt dan *randomly generated matrix and sequences* (input manual yang menghasilkan matriks dan sequence secara acak).

# Requirements
1. MinGW-w64 (untuk kompilasi program)
2. Terminal/Powershell/Command Prompt
3. Text editor (untuk membuat input baru dan melihat isi output file)

# Cara Mengompilasi Program
1. Buka Terminal/Powershell/Command Prompt di folder src repository ini.
2. Jika Anda membuka Terminal/Powershell/Command Prompt bukan di folder src repository ini, salin direktori folder src repository ini dari file explorer dan ketik ``` cd "salin direktori folder src di sini" ``` pada Terminal/Powershell/Command Prompt. ***CATATAN: Tanda petik dua wajib diketik di sebelah kiri dan sebelah kanan direktori folder src yang Anda salin***
3. Ketik ```g++ -o (nama file.exe disini, tanpa kurung) main.cpp helper.cpp gamematrix.cpp sequence.cpp token.cpp``` di Terminal/Powershell/Command Prompt.
4. Tunggu sampai program selesai terkompilasi dan file.exe akan muncul di folder src.
# Cara Menggunakan Program
1. Jika Anda melakukan kompilasi program terlebih dahulu, pindahkan file.exe yang sudah dibuat ke folder bin.
2. Jika Anda menggunakan program yang sudah dibuat di dalam folder bin sebelumnya, lompat ke langkah 3.
3. Buka Terminal/Powershell/Command Prompt di folder bin
4. Ketik ```./(nama file.exe yang ada di folder bin di sini)``` di Terminal/Powershell/Command Prompt.
5. Untuk input file, **PASTIKAN FILE WAJIB BEREKSTENSI .txt dan WAJIB disimpan di folder ```test``` di repositori ini.**
6. Untuk input manual melalui CLI (Random Generation), ketik semua hal yang diminta oleh program di Terminal/Powershell/Command Prompt.
7. Ikuti alur input yang diminta oleh program.
8. Ketik "Y" atau "y" untuk menyimpan output yang dikeluarkan oleh program
# Tentang Pembuat Program
| Nama          | NIM    | Kelas Strategi Algoritma|
| --------------|--------| ----|
|Akbar Al Fattah|13522036| K-02|
