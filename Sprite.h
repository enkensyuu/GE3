#pragma once
#include "SpriteCommon.h"
#include <DirectXMath.h>

// スプライト
class Sprite
{
private:
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

	// 構造体
public:
	enum VertexNumber {
		LB,	//	右下
		LT,	//	右上
		RB,	//	左下
		RT,	//	左上
	};

public:	// メンバ関数

	// 初期化
	void Initialize(SpriteCommon* spriteCommon_);

	// 更新
	void Update();

	// 描画
	void Draw();

	// Getter 
	const DirectX::XMFLOAT4 GetColor() const { return color_; }
	const DirectX::XMFLOAT2 GetSize() const { return size; }
	const float GetRotationZ() const { return rotationZ; }
	const DirectX::XMFLOAT2 GetPosition() const { return position; }
	const DirectX::XMFLOAT2 GetAnchorPoint() const { return anchorPoint_; }
	const bool& GetFlipX() const { return IsFlipX; }
	const bool& GetFlipY() const { return IsFlipY; }
	const bool& GetIsInvisible() const { return IsInvisible; }

	// Setter
	void SetColor(DirectX::XMFLOAT4 color_) { this->color_ = color_; }
	void SetSize(const DirectX::XMFLOAT2& size) { this->size = size; }
	void SetRotationZ(const float& rotationZ) { this->rotationZ = rotationZ; }
	void SetPosition(const DirectX::XMFLOAT2& position) { this->position = position; }
	void SetAnchorPoint(const DirectX::XMFLOAT2& anchorPoint_) { this->anchorPoint_ = anchorPoint_; }
	void SetIsFlipX(const bool& IsFlipX) { this->IsFlipX = IsFlipX; }
	void SetIsFlipY(const bool& IsFlipY) { this->IsFlipY = IsFlipY; }
	void SetIsInvisible(const bool& IsInvisible) { this->IsInvisible = IsInvisible; }

private:
	// スプライト共通部分
	SpriteCommon* spriteCommon = nullptr;

	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	DirectX::XMFLOAT2 size = { 100.0f,100.0f };
	float rotationZ = 0.0f;
	DirectX::XMFLOAT2 position = { 100.0f,100.0f };
	DirectX::XMFLOAT2 anchorPoint_ = { 0.0f,0.0f };


	bool IsFlipX = false;
	bool IsFlipY = false;

	bool IsInvisible = false;

	// 頂点データ
	Vertex vertices[4];

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};


