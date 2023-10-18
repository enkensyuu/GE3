#include "Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Sprite.h"
#include "SpriteCommon.h"
#include "Object3d.h"
#include "Model.h"
#include <xaudio2.h>
#include <fstream>

#pragma comment(lib,"xaudio2.lib")

// チャンクヘッダ
struct ChunkHeader
{
	char id[4];		//	チャンク毎のID
	int32_t size;	//	チャンクサイズ
};

// RIFFヘッダチャンク
struct RiffHeader
{
	ChunkHeader chunk;	//	"RIFF"
	char type[4];		//	"WAVE"
};

// FMTチャンク
struct FormatChunk
{
	ChunkHeader chunk;	//	"fmt"
	WAVEFORMATEX fmt;	//	波形フォーマット
};

// 音声データ
struct SoundData
{
	// 波形フォーマット
	WAVEFORMATEX wfex;
	// バッファの先頭アドレス
	BYTE* pBuffer;
	// バッファのサイズ
	unsigned int bufferSize;
};

SoundData SoundLoadWave(const char* filename)
{
	// ファイル入力ストリームのインスタンス
	std::ifstream file;
	// .wavファイルをパイナリモードで開く
	file.open(filename, std::ios_base::binary);
	// ファイルオープン失敗を検出する
	assert(file.is_open());

	// RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
	{
		assert(0);
	}
	// タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0)
	{
		assert(0);
	}

	// Formatチャンクの読み込み
	FormatChunk format = {};
	// チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt", 4) != 0)
	{
		assert(0);
	}

	// チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	// Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0)
	{
		// 読み取り位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		// 再読み込み
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "data", 4) != 0)
	{
		assert(0);
	}

	// Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	// Waveファイルを閉じる
	file.close();

	// returnする為の音声データ
	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	return soundData;

}

// 音声データ
void SoundUnload(SoundData* soundData)
{
	// バッファのメモリを解放
	delete[] soundData->pBuffer;

	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
	soundData->wfex = {};


}

// 音声再生
void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData)
{
	HRESULT result;

	// 波形フォーマットを元にSourceVoiceの生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	// 再生する波形データの設定


}

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

	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;

	// XAudioエンジンのインスタンスを生成
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	// マスターボイスを生成
	result = xAudio2->CreateMasteringVoice(&masterVoice);

#pragma endregion

#pragma region 最初のシーンの初期化

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	Sprite* sprite = nullptr;
	sprite = new Sprite();
	sprite->Initialize(spriteCommon, 1);

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
