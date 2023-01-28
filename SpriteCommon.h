#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>

#include "DirectXCommon.h"

// スプライト共通部
class SpriteCommon
{
public:
	// 横方向ピクセル数
	const size_t textureWidth = 256;
	// 縦方向ピクセル数
	const size_t textureHeight = 256;
	// 配列の要素数
	const size_t imageDataCount = textureWidth * textureHeight;

public:	// メンバ関数

	// 初期化
	void Initialize(DirectXCommon* dxCommon_);

	void PreDraw();

	DirectXCommon* GetDirectXCommon() { return dxCommon; }

private:
	DirectXCommon* dxCommon;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> roorSignature;

	// 画像イメージデータ配列
	DirectX::XMFLOAT4* imageData;

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
};

