#pragma once
//�̰��� ���� ���Ǵ� STL�� ����� ��Ƴ���
#include <Windows.h>
#include <assert.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#include <functional>
#include <filesystem>
#include "uginaMath.h"

#pragma comment(lib,"Msimg32.lib")
//Windows ��Ƽ�̵�� API(Multimedia API), �����, midi,Ÿ�̸�,���̽�ƽ
#include <mmsystem.h>
//mmsystem.h�� ����ϱ����� ���̺귯��
#pragma comment(lib, "winmm.lib")

#include <dinput.h>

//��� �׷���ó���� ���� api���
#include <gdiplus.h>
//gdiplus.h�� ����ϱ����� ���̺귯��
#pragma comment(lib,"gdiplus.lib")

#include "uginaEnums.h"