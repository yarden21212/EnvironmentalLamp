#pragma once

#include <string>

class Music {

private:
	std::string path;
	bool isPlaying = false;
public:
	Music();

	void setSoundPath(const std::string& soundPath);
	void playMusic();
	void stopMusic();
	void setPlayStatus(bool newStatus);
	bool getPlayStatus();
};