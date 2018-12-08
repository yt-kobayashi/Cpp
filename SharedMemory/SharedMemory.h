#pragma once
/*==================================================================================================
|
|   �T�v                :       �}�b�v�h�t�@�C������p�N���X
|   �쐬��              :       ���їR��
|   �ړI                :       �}�b�v�h�t�@�C���̐�����N���X�Ƃ��Ē񋟂��邱�ƂŊȒP�Ƀ}�b�v�h
|								�t�@�C����������悤�ɂ���
|   �g�p�@              :       SharedMemory.cpp��SharedMemory.h���v���W�F�N�g�ɒǉ����Ďg�p����
|
==================================================================================================*/
#include <Windows.h>
#include <string>

class SharedMemory
{
private:
	TCHAR mappedFileName[128];			// �}�b�v�h�t�@�C����
	int mappedFileSize;					// �}�b�v�h�t�@�C���T�C�Y
	HANDLE mappedFileHandle;			// �}�b�v�h�t�@�C���p�n���h��
	intptr_t mappedFilePointer;			// �}�b�v�h�t�@�C���p�|�C���^
public:
	// �R���g���N�^
	SharedMemory();
	SharedMemory(const std::string fileName);
	SharedMemory(const int fileSize);
	SharedMemory(const std::string fileName, const int fileSize);
	// �f�X�g���N�^
	~SharedMemory();
	// �ݒ胁�\�b�h
	bool SetFileName(const std::string fileName);
	bool SetFileSize(const int fileSize);
	// �}�b�v�h�t�@�C�����䃁�\�b�h
	bool CreateMappedFile();
	bool OpenMappedFile();
	bool UnmapMappedFile();
	bool CloseMappedFile();
	// �}�b�v�h�t�@�C�����o�̓��\�b�h
	bool ReadMappedFile(void* variablePointer, const int offset, const int dataSize);
	bool WriteMappedFile(void* variablePointer, const int offset, const int dataSize);
	bool WriteFlushMappedFile(void* variablePointer, const int offset, const int dataSize, const bool flush);
	// �v���C�x�[�g�ϐ��A�N�Z�b�T
	std::string ReadFileName();
	int ReadFileSize();
	HANDLE ReadFileHandle();
	intptr_t ReadFilePointer();
};

