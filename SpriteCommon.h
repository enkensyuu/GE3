#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>

#include "DirectXCommon.h"

// �X�v���C�g���ʕ�
class SpriteCommon
{

public:	// �����o�֐�

	// ������
	void Initialize(DirectXCommon* dxCommon_);

	void PreDraw();

	DirectXCommon* GetDirectXCommon() { return dxCommon; }

private:
	DirectXCommon* dxCommon;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> roorSignature;

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
};

