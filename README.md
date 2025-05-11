# IF1210-Tubes-01

<h2 id="description">Deskripsi</h2>
Tugas besar ini meminta untuk mencakup program rumah sakit digital dengan penerapan implementasi ADT untuk masing-masing fiturnya. 

<h2 id="table-of-contents">Daftar Isi</h2>
- <a href="#description">Deskripsi</a><br/>
- <a href="#table-of-contents">Daftar Isi</a><br/>
- <a href="#member">Anggota Kelompok</a><br/>
- <a href="#how-to-run">Cara Menjalankan Program</a><br/>
- <a href="#command">Daftar Command</a><br/>

<h2 id="member">Anggota Kelompok</h2>
Berikut adalah daftar anggota kami:<br/>
1. Ishak Palentino Napitupulu NIM. 13524022<br/>
2. Josh Reinhart Zidik NIM. 13524048<br/>
3. Syaqina Octavia Rizha NIM. 13524088<br/>
4. Jennifer Khang NIM. 13524110<br/>
5. Leonardus Brain Fatolosja NIM. 13524146<br/>

<h2 id="how-to-run">Cara Menjalankan Program</h2>
Program dijalankan menggunakan wsl di root folder. Pastikan gcc dan makefile sudah terinstall.

### Compile (Jalankan di folder yang memiliki makefile)
```bash
make
```

### Run Program
```bash
cd build
./hospital_app
```

<h2 id="command">Daftar Command</h2>
Berikut merupakan command yang tersedia untuk fitur-fitur Rumah Sakit Digital.  <br/>
* Command LOGIN berfungsi untuk login akun.  <br/>
* Command REGISTER berfungsi untuk mendaftar akun baru.  <br/>
* Command LOGOUT berfungsi untuk keluar dari akun.  <br/>
* Command LUPA_PASSWORD berfungsi untuk mengganti password.  <br/>
* Command HELP untuk menampilkan layar menu bantuan.  <br/>
* Command LIHAT_DENAH untuk melihat denah rumah sakit.  <br/>
* Command LIHAT_RUANGAN [IDRuangan] untuk melihat kapasitas, jumlah pasien, dan dokter pada IDRuangan.  <br/>
* Command SAVE untuk menyimpan pada folder data dengan nama tertentu.  <br/>
* Command TAMBAH_DOKTER untuk menambahkan jumlah dokter pada rumah sakit.<br/>
* Command ASSIGN_DOKTER untuk melakukan assign ruangan ke dokter tertentu yang belum mempunyai ruangan.<br/>
* Command EXIT memberi opsi kepada pengguna untuk menyimpan file atau tidak dan keluar dari program.  <br/>
