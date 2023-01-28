#pragma once
#include "SpriteCommon.h"
#include <DirectXMath.h>

// �X�v���C�g
class Sprite
{
private:
	const int window_width = 1280;
	const int window_height = 1280;

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

public:	// �����o�֐�

	// ������
	void Initialize(SpriteCommon* spriteCommon_);

	// �`��
	void Draw();

private:
	// �X�v���C�g���ʕ���
	SpriteCommon* spriteCommon = nullptr;

	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};

