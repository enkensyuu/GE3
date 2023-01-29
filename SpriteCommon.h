#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <array>
#include <string>

#include "DirectXCommon.h"

// �X�v���C�g���ʕ�
class SpriteCommon
{

public:	// �����o�֐�

	// ������
	void Initialize(DirectXCommon* dxCommon_);

	void PreDraw();

	void PostDraw();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="index">�e�N�X�`���ԍ�</param>
	void LoadTexture(uint32_t index, const std::string& fileName);

	/// <summary>
	/// �`��p�e�N�X�`���R�}���h�̔��s
	/// </summary>
	/// <param name="index">�e�N�X�`���ԍ�</param>
	void SetTextureCommands(uint32_t index);

	DirectXCommon* GetDirectXCommon() { return dxCommon; }
	ID3D12Resource* GetTextureBuffer(uint32_t index) { return texBuff[index].Get(); }

private: //	�ÓI�����o�ϐ�

	// SRV�̍ő��
	static const size_t kMaxSRVCount = 2056;

	// �f�t�H���g�e�N�X�`���i�[�f�B���N�g��
	static std::string kDfautTextureDirectoryPath;

private:
	DirectXCommon* dxCommon;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> roorSignature;

	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kMaxSRVCount> texBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
};

