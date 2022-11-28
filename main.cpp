#include "Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	HRESULT result;

#pragma region 基盤システムの初期化

	WinApp* winApp = nullptr;
	// WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	DirectXCommon* dxCommon = nullptr;
	// DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	// 入力の初期化
	input = new Input();
	input->Initialize(winApp);

#pragma endregion

#pragma region 最初のシーンの初期化

#pragma endregion

#pragma region 最初のシーン初期化

	// ゲームループ
	while (true)
	{
#pragma region 基盤システムの更新
		// Windowsのメッセージ処理
		if (winApp->ProcessMessage())
		{
			// ゲームループを抜ける
			break;
		}

		// 入力の更新
		input->Update();

#pragma endregion

#pragma region 最初のシーンの更新

#pragma endregion

		// 描画前処理
		dxCommon->PreDraw();

#pragma region 最初のシーンの描画

#pragma endregion

		// 描画後処理
		dxCommon->PostDraw();
	}

#pragma endregion

#pragma region 最初のシーンの終了

#pragma endregion

#pragma region 基盤システムの終了

	// 入力解放
	delete input;

	// DirectX解放
	delete dxCommon;

	// WindowsAPIの終了処理
	winApp->Finalize();

	// WindowsAPI解放
	delete winApp;


#pragma endregion

	return 0;
}
