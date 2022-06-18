#include "Config.h"

#include <fstream>
#include <stdexcept>
#include <Windows.h>

BOOL FileExists(LPCSTR szPath)
{
  DWORD dwAttrib = GetFileAttributesA(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool IsFileExist(const std::string &x) {
	return TRUE == ::FileExists(x.c_str());
}

Config::Config(const std::string& configpath) {
    std::fstream in(configpath);
    in >> logpath_;
    in >> mappath_;
    if (!IsFileExist(mappath_)) {
	//if (!std::filesystem::exists(mappath_)) {
        throw std::runtime_error("Config::Config - file " + mappath_ + " doesn't exists");
    }
    size_t cnt_players;
    in >> cnt_players;
    player_programs_.resize(cnt_players);
    for (size_t i = 0; i < cnt_players; ++i) {
        in >> player_programs_[i];
        if (!IsFileExist(player_programs_[i])) {
            throw std::runtime_error("Config::Config - file \"" + player_programs_[i] +
                                     "\" doesn't exists");
        }
    }
}

std::string Config::GetLogpath() const {
    return logpath_;
}

std::string Config::GetMappath() const {
    return mappath_;
}

Config::TContainer Config::GetPlayerPrograms() const {
    return player_programs_;
}