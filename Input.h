#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800  //  DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include"WinApp.h"

class Input
{
public:
	// namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp*winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="�L�[�ԍ�"></param>
	/// <returns></returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool TriggerKey(BYTE keyNumber);

// �����o�ϐ�
private:
	// �L�[�{�[�h�f�o�C�X�̐���
	ComPtr<IDirectInputDevice8> keyboard;

	BYTE key[256] = {};

	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};

	// DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput;

	// WidowsAPI
	WinApp* winApp = nullptr;
};

