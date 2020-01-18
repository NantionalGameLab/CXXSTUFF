// statepattern.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "MusicPlayer.h"

int main()
{

	MusicPlayer player;

	player.Play();
	player.Pause();
	player.Stop();


	system("pause");
	return 0;
}

