#include <Windows.h>
#include <mmsystem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")

#define SOUND "LowBatteryAlarm"	//��

char operation;	//����
int time;		//�^�C���A�E�g����

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	char* p = NULL;		//�|�C���^
	char* np = NULL;	//���̃|�C���^

	//1�ڂ̈������擾
	p = strtok_s(lpC, " ", &np);

	//�Ȃ������特��炵�ďI��
	if (p == NULL) {
		PlaySound(SOUND, NULL, SND_ALIAS | SND_SYNC | SND_NODEFAULT);
		return 0;
	}

	//������擾
	operation = p[0];
	if (operation >= L'A' && operation <= L'Z') operation += 0x20;
	if (operation != L's' && operation != L'h') return 1;

	//2�ڂ̈������擾
	p = strtok_s(NULL, " ", &np);
	if (p == NULL) return 1;

	//�^�C���A�E�g���Ԃ��擾
	time = atoi(p);
	if (time < 0) return 1;

	//����炷
	PlaySound(SOUND, NULL, SND_ALIAS | SND_ASYNC | SND_NODEFAULT);

	//�^�C���A�E�g���ԑ҂�
	DWORD ms = (DWORD)time * 1000;
	Sleep(ms);

	//����̕�������쐬
	char buf[256];
	sprintf_s(buf, sizeof(buf), "shutdown %s", (operation == 's') ? "/s /t 0" : "/h");

	//����̎��s
	system(buf);

	return 0;
}