/*
 * MusicPlayerState.h
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#ifndef MUSICPLAYERSTATE_H_
#define MUSICPLAYERSTATE_H_

#include <string>
//！
class MusicPlayer;

class MusicPlayerState {
public:
	MusicPlayerState(std::string name);
	virtual ~MusicPlayerState();
	//! 依赖关系(Dependency)(用指针形式，无需具体类定义，没有触发类的构造函数，避免头文件的相互包含)
	virtual void Play(MusicPlayer * player);
	virtual void Pause(MusicPlayer * player);
	virtual void Stop(MusicPlayer * player);

	std::string GetName() { return m_name; }

private:
	std::string   m_name;
};

#endif /* MUSICPLAYERSTATE_H_ */
