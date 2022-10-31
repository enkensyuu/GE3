#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



void Input::Initialize(WinApp* winApp)
{
	// �؂�Ă���WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;

	HRESULT result;

	// DirectInput�̏�����
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));


	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	// ���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	assert(SUCCEEDED(result));
	// �r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update()
{
	// �L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();

	// �O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));

	// �S�L�[�̓��͏�Ԃ��擾����
	keyboard->GetDeviceState(sizeof(key), key);

}

bool Input::PushKey(BYTE keyNumber)
{
	// �w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber])
	{
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber] && !keyPre[keyNumber])
	{
		return true;
	}
	return false;
}
