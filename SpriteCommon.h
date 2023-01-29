#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <array>
#include <string>

#include "DirectXCommon.h"

// スプライト共通部
class SpriteCommon
{

public:	// メンバ関数

	// 初期化
	void Initialize(DirectXCommon* dxCommon_);

	void PreDraw();

	void PostDraw();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="index">テクスチャ番号</param>
	void LoadTexture(uint32_t index, const std::string& fileName);

	/// <summary>
	/// 描画用テクスチャコマンドの発行
	/// </summary>
	/// <param name="index">テクスチャ番号</param>
	void SetTextureCommands(uint32_t index);

	DirectXCommon* GetDirectXCommon() { return dxCommon; }
	ID3D12Resource* GetTextureBuffer(uint32_t index) { return texBuff[index].Get(); }

private: //	静的メンバ変数

	// SRVの最大個数
	static const size_t kMaxSRVCount = 2056;

	// デフォルトテクスチャ格納ディレクトリ
	static std::string kDfautTextureDirectoryPath;

private:
	DirectXCommon* dxCommon;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> roorSignature;

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kMaxSRVCount> texBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
};

