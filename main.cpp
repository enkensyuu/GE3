#include "Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Sprite.h"
#include "SpriteCommon.h"
#include "Object3d.h"
#include "Model.h"

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

	SpriteCommon* spriteCommon = nullptr;
	// スプライト共通部の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	spriteCommon->LoadTexture(0, "texture.png");
	spriteCommon->LoadTexture(1, "reimu.png");

#pragma endregion

#pragma region 最初のシーンの初期化

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	Sprite* sprite = nullptr;
	sprite = new Sprite();
	sprite->Initialize(spriteCommon,1);

	// OBJからモデルデータを読み込む
	Model* model1_ = Model::LoadFromOBJ("triangle_mat");
	Model* model2_ = Model::LoadFromOBJ("triangle_mat2");
	
	// 3Dオブジェクト生成
	Object3d* object3d1_ = Object3d::Create();
	Object3d* object3d2_ = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	object3d1_->SetModel(model1_);
	object3d2_->SetModel(model2_);
	// 3Dオブジェクトの位置を指定
	object3d2_->SetPosition({ -5,-5,-5 });


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

		// 3Dオブジェクト更新
		object3d1_->Update();
		object3d2_->Update();

		/*DirectX::XMFLOAT2 size = sprite->GetSize();
		size.y += 0.1f;
		sprite->SetSize(size);
		sprite->Update();*/

#pragma endregion

		// 描画前処理
		dxCommon->PreDraw();

#pragma region 最初のシーンの描画

		// 3Dオブジェクト描画前処理
		Object3d::PreDraw(dxCommon->GetCommandList());

		// 3Dオブジェクトの描画
		object3d1_->Draw();
		object3d2_->Draw();

		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// </summary>
		
		// 3Dオブジェクト描画後処理
		Object3d::PostDraw();

		// スプライト描画開始
		spriteCommon->PreDraw();
		//sprite->Draw();
		// スプライト描画終了
		spriteCommon->PostDraw();
#pragma endregion

		// 描画後処理
		dxCommon->PostDraw();

		if (input->TriggerKey(DIK_ESCAPE))
		{
			break;
		}
	}

#pragma endregion

#pragma region 最初のシーンの終了

	// 3Dモデル解放
	delete model1_;
	delete model2_;

	// 3Dオブジェクト解放
	delete object3d1_;
	delete object3d2_;

	// スプライト解放
	delete sprite;
	
#pragma endregion

#pragma region 基盤システムの終了

	// 入力解放
	delete input;

	// DirectX解放
	delete dxCommon;

	delete spriteCommon;

	// WindowsAPIの終了処理
	winApp->Finalize();

	// WindowsAPI解放
	delete winApp;


#pragma endregion

	return 0;
}
