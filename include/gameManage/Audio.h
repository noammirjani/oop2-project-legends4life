#pragma once
#include "macros.h"

class Audio
{
public:
	//get to the data 
	static Audio& getInstance();

	//D-tor
	~Audio();

	//set
	void         setMode(const bool);
	void         setVolume(const int);
	//get
	bool         getMode(const bool) const;
	int          getVolume() const;
	//play
	void         playSoundEffect(const int);
	void         playMusic(const int);


private:
	std::vector <sf::SoundBuffer>   m_soundBuffer;
	bool                            m_soundPlaying;
	bool                            m_musicPlaying;
	sf::Sound                       m_soundEffect;
	sf::Sound                       m_music;
	int                             m_musicVolume;
	int                             m_soundEffectVolume;

	//PRIVATE
	//c-tor, copy-c-tor, operator=
	Audio();
	Audio(const Audio&) = default;
	Audio& operator=(const Audio&) = default;

	//set functions

	void setSound();

};