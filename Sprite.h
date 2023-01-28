#pragma once
#include "SpriteCommon.h"
#include <DirectXMath.h>

// スプライト
class Sprite
{
private:
	const int window_width = 1280;
	const int window_height = 1280;

	// 定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial
	{
		DirectX::XMFLOAT4 color; // 色(RGBA)
	};

	// 定数バッファ用データ構造体(3D変換行列)
	struct ConstBufferDataTransform {
		DirectX::XMMATRIX mat;	//	3D変換行列
	};

	// 頂点データ構造体
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;	//	xyz座標
		DirectX::XMFLOAT2 uv;	//	uv座標
	};

public:	// メンバ関数

	// 初期化
	void Initialize(SpriteCommon* spriteCommon_);

	// 描画
	void Draw();

private:
	// スプライト共通部分
	SpriteCommon* spriteCommon = nullptr;

	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};

