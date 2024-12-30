option(NUSANTARA_PROJECT_BUILD "Opsi untuk memilih sub proyek nusantara mana yang akan di build")

# Sub folder proyek
foreach(PROJECT ${NUSANTARA_PROJECT_BUILD})
  add_subdirectory(${PROJECT})
endforeach()