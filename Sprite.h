#pragma once
#include "SpriteCommon.h"
#include <DirectXMath.h>

// �X�v���C�g
class Sprite
{
private:
	// �萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial
	{
		DirectX::XMFLOAT4 color; // �F(RGBA)
	};

	// �萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
	struct ConstBufferDataTransform {
		DirectX::XMMATRIX mat;	//	3D�ϊ��s��
	};

	// ���_�f�[�^�\����
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;	//	xyz���W
		DirectX::XMFLOAT2 uv;	//	uv���W
	};

	// �\����
public:
	enum VertexNumber {
		LB,	//	�E��
		LT,	//	�E��
		RB,	//	����
		RT,	//	����
	};

public:	// �����o�֐�

	// ������
	void Initialize(SpriteCommon* spriteCommon_, uint32_t textureIndex = UINT32_MAX);

	// �X�V
	void Update();

	// �`��
	void Draw();

	// Getter 
	const DirectX::XMFLOAT4 GetColor() const { return color_; }
	const uint32_t GetTextureIndex() { return textureIndex_; }
	const DirectX::XMFLOAT2 GetSize() const { return size; }
	const float GetRotationZ() const { return rotationZ; }
	const DirectX::XMFLOAT2 GetPosition() const { return position; }
	const DirectX::XMFLOAT2 GetAnchorPoint() const { return anchorPoint_; }
	const DirectX::XMFLOAT2 GetTextureLeftTop() const { return textureLeftTop_; }
	const DirectX::XMFLOAT2 GetTextureSize() const { return textureSize_; }
	const bool& GetFlipX() const { return IsFlipX; }
	const bool& GetFlipY() const { return IsFlipY; }
	const bool& GetIsInvisible() const { return IsInvisible; }

	// Setter
	void SetColor(DirectX::XMFLOAT4 color_) { this->color_ = color_; }
	void SetTextureIndex(uint32_t index) { this->textureIndex_ = index; }
	void SetSize(const DirectX::XMFLOAT2& size) { this->size = size; }
	void SetRotationZ(const float& rotationZ) { this->rotationZ = rotationZ; }
	void SetPosition(const DirectX::XMFLOAT2& position) { this->position = position; }
	void SetAnchorPoint(const DirectX::XMFLOAT2& anchorPoint_) { this->anchorPoint_ = anchorPoint_; }
	void SetTextureLeftTop(const DirectX::XMFLOAT2& leftTop_) { this->textureLeftTop_ = leftTop_; }
	void SetTextureSize(const DirectX::XMFLOAT2& size_) { this->textureSize_ = size_; }
	void SetIsFlipX(const bool& IsFlipX) { this->IsFlipX = IsFlipX; }
	void SetIsFlipY(const bool& IsFlipY) { this->IsFlipY = IsFlipY; }
	void SetIsInvisible(const bool& IsInvisible) { this->IsInvisible = IsInvisible; }

private:
	// �e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
	void AdjustTextureSize();

private:
	// �X�v���C�g���ʕ���
	SpriteCommon* spriteCommon = nullptr;

	// �e�N�X�`���ԍ�
	uint32_t textureIndex_ = 0;

	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	DirectX::XMFLOAT2 size = { 100.0f,100.0f };
	float rotationZ = 0.0f;
	DirectX::XMFLOAT2 position = { 0.0f,0.0f };
	DirectX::XMFLOAT2 anchorPoint_ = { 0.0f,0.0f };

	// �e�N�X�`��������W
	DirectX::XMFLOAT2 textureLeftTop_ = { 0.0f,0.0f };
	// �e�N�X�`���؂�o���T�C�Y
	DirectX::XMFLOAT2 textureSize_ = { 100.0f,100.0f };

	bool IsFlipX = false;
	bool IsFlipY = false;

	bool IsInvisible = false;

	// ���_�f�[�^
	Vertex vertices[4];

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};


