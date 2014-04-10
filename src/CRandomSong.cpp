#include "CRandomSong.hpp"
#include "CDirectory.hpp"
#include "CSoundMP3.hpp"
#include "CNullSong.hpp"


CRandomSong::CRandomSong():
  CSong(GetSongName()),
  mSong(CreateSong()) {

}


CSong* CRandomSong::CreateSong() const {
  std::string name = GetName();
  if(name == "")
    return new CNullSong;
  else
    return new CSoundMP3(name);
}


std::string CRandomSong::GetSongName() const {
  CDirectory dir("Music", ".mp3");
  return dir.GetNbEntries() <= 0 ? "" : dir.GetRandomNoExt();
}
