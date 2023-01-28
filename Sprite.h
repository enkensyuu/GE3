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

	// ���_�f�[�^�\����
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;	//	xyz���W
		DirectX::XMFLOAT2 uv;	//	uv���W
	};

public:	// �����o�֐�

	// ������
	void Initialize(SpriteCommon* spriteCommon_);

	// �`��
	void Draw();

private:
	// �X�v���C�g���ʕ���
	SpriteCommon* spriteCommon = nullptr;

	DirectX::XMFLOAT4 color_ = { 1.0f,0.0f,0.0f,0.5f };

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;
};

