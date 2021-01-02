#include <Windows.h>
#include <mmsystem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")

#define SOUND "LowBatteryAlarm"	//音

char operation;	//操作
int time;		//タイムアウト期間

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	char* p = NULL;		//ポインタ
	char* np = NULL;	//次のポインタ

	//1つ目の引数を取得
	p = strtok_s(lpC, " ", &np);

	//なかったら音を鳴らして終了
	if (p == NULL) {
		PlaySound(SOUND, NULL, SND_ALIAS | SND_SYNC | SND_NODEFAULT);
		return 0;
	}

	//操作を取得
	operation = p[0];
	if (operation >= L'A' && operation <= L'Z') operation += 0x20;
	if (operation != L's' && operation != L'h') return 1;

	//2つ目の引数を取得
	p = strtok_s(NULL, " ", &np);
	if (p == NULL) return 1;

	//タイムアウト期間を取得
	time = atoi(p);
	if (time < 0) return 1;

	//音を鳴らす
	PlaySound(SOUND, NULL, SND_ALIAS | SND_ASYNC | SND_NODEFAULT);

	//タイムアウト期間待つ
	DWORD ms = (DWORD)time * 1000;
	Sleep(ms);

	//操作の文字列を作成
	char buf[256];
	sprintf_s(buf, sizeof(buf), "shutdown %s", (operation == 's') ? "/s /t 0" : "/h");

	//操作の実行
	system(buf);

	return 0;
}