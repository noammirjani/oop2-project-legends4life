#include "gameManage/Audio.h"

//-------------------------constructor------------------------------
Audio::Audio() : m_soundPlaying(true), m_musicPlaying(true), m_musicVolume(25), m_soundEffectVolume(25)
{
	m_music.setVolume(m_musicVolume);
	m_soundEffect.setVolume(m_soundEffectVolume);
	setSound();
}


//------------------------------------------------------------------
//d_tor
Audio::~Audio() {}


//------------------------------------------------------------------
void Audio::setMode(const bool type)
{
	if (type)
	{
		m_musicPlaying = !m_musicPlaying;
		(m_musicPlaying) ? m_music.play() : m_music.pause();
	}

	else m_soundPlaying = !m_soundPlaying;
}


//------------------------------------------------------------------
bool Audio::getMode(const bool type) const
{
	if (type) return m_musicPlaying;

	//else
	return m_soundPlaying;
}


//------------------------------------------------------------------
//the static function 
Audio& Audio::getInstance()
{
	static Audio instane;
	return instane;
}


//--------------------------- Set Sound -----------------------------
void Audio::setSound()
{
	auto soundBuffer = sf::SoundBuffer();
	for (auto& soundEffect : soundFilesName)
	{
		soundBuffer.loadFromFile(soundEffect);
		m_soundBuffer.push_back(soundBuffer);
	}
}


//----------------------------play Sound-----------------------------
void Audio::playSoundEffect(int enumSound)
{
	if (!m_soundPlaying) return;

	m_soundEffect.setBuffer(m_soundBuffer[enumSound]);
	m_soundEffect.play();
}


//----------------------------play Music ----------------------------
void Audio::playMusic(int enumSound)
{
	//if (enumSound > 3) enumSound % 3 + 1;

	if (!m_musicPlaying) return;

	m_music.setBuffer(m_soundBuffer[enumSound]);
	m_music.setLoop(true);
	m_music.play();
}


//----------------------------set Volume ---------------------------
void  Audio::setVolume(const int val)
{
	 m_musicVolume += val;
	 m_soundEffectVolume += val;

	// set limits 
	if (m_soundEffectVolume > 100) m_soundEffectVolume = 100;
	if (m_soundEffectVolume < 0)   m_soundEffectVolume = 0;

	if (m_musicVolume < 0)		   m_musicVolume = 0;
	if (m_musicVolume > 100)	   m_musicVolume = 100;

	m_music.setVolume(m_musicVolume);
	m_soundEffect.setVolume(m_soundEffectVolume);
}


//----------------------------get Volume ---------------------------
int Audio::getVolume()const
{
	return m_soundEffectVolume;
}