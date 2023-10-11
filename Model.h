#pragma once
#include <DirectXMath.h>
#include <vector>
#include <string>
#include <d3d12.h>
#include <d3dx12.h>
#include <wrl.h>

class Model
{

public: // �T�u�N���X

	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos; // xyz���W
		DirectX::XMFLOAT3 normal; // �@���x�N�g��
		DirectX::XMFLOAT2 uv;  // uv���W
	};

	// �}�e���A��
	struct Material
	{
		std::string name; // �}�e���A����
		XMFLOAT3 ambient; // �A���r�G���g�e���x
		XMFLOAT3 diffuse; // �f�B�t�F�[�Y�e���x
		XMFLOAT3 specular;// �X�y�L�����[�e���x
		float alpha;      // �A���t�@
		std::string textureFilename; // �e�N�X�`���t�@�C����
		// �R���X�g���N�^
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

public: // �ÓI�����o�֐�

	// OBJ�t�@�C������3D
	static Model* LoadFromOBJ();

	static void SetDevice(ID3D12Device* device) { Model::device_ = device; }

public: // �����o�֐�

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);
	
	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);

private: // �ÓI�����o�ϐ�

	static ID3D12Device* device_;

private: // �����o�ϐ�
	
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	// �}�e���A��
	Material material;
	// �e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff;
	// �f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;

private: // ����J�̃����o�֐�
	// OBJ�t�@�C������3D���f����ǂݍ���(����J)
	void LoadFromOBJInternal();

};

