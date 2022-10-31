#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800  //  DirectInputのバージョン指定
#include <dinput.h>
#include"WinApp.h"

class Input
{
public:
	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp*winApp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 入力
	/// </summary>
	/// <param name="キー番号"></param>
	/// <returns></returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool TriggerKey(BYTE keyNumber);

// メンバ変数
private:
	// キーボードデバイスの生成
	ComPtr<IDirectInputDevice8> keyboard;

	BYTE key[256] = {};

	// 前回の全キーの状態
	BYTE keyPre[256] = {};

	// DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;

	// WidowsAPI
	WinApp* winApp = nullptr;
};

