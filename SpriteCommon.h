#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>

#include "DirectXCommon.h"

// �X�v���C�g���ʕ�
class SpriteCommon
{
public:
	// �������s�N�Z����
	const size_t textureWidth = 256;
	// �c�����s�N�Z����
	const size_t textureHeight = 256;
	// �z��̗v�f��
	const size_t imageDataCount = textureWidth * textureHeight;

public:	// �����o�֐�

	// ������
	void Initialize(DirectXCommon* dxCommon_);

	void PreDraw();

	DirectXCommon* GetDirectXCommon() { return dxCommon; }

private:
	DirectXCommon* dxCommon;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> roorSignature;

	// �摜�C���[�W�f�[�^�z��
	DirectX::XMFLOAT4* imageData;

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
};

