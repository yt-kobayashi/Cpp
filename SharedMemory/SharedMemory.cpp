//#include "stdafx.h"
#include "pch.h"
#include <Windows.h>
#include <string>
#include <atlstr.h>
#include <tchar.h>
#include "SharedMemory.h"

using namespace std;

/***************************************************
*	�R���g���N�^
*	�I�[�o�[���[�h 4
*	�I�u�W�F�N�g��錾�������_�Ŏ��s�����
***************************************************/
//>>>>>>>>>>>>>>>>>>>> �f�t�H���g <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory()
{
	SetFileName("sharedMemory");
	SetFileSize(1024);
}
//>>>>>>>>>>>>>>>>>>>> �t�@�C�����w�� <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory(const string fileName)
{
	SetFileName(fileName);
	SetFileSize(1024);
}
//>>>>>>>>>>>>>>>>>>>> �t�@�C���T�C�Y�w�� <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory(const int fileSize)
{
	SetFileName("DefaultName");
	SetFileSize(fileSize);
}
//>>>>>>>>>>>>>>>>>>>> �t�@�C����,�T�C�Y�w�� <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory(const string fileName, const int fileSize)
{
	SetFileName(fileName);
	SetFileSize(fileSize);
}

/***************************************************
*	�f�X�g���N�^
***************************************************/
SharedMemory::~SharedMemory()
{
}

/***************************************************
*	�����o���\�b�h
***************************************************/
//>>>>>>>>>>>>>>>>>>>> �t�@�C�����̎w�� <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::SetFileName(const string fileName) {
	bool state;		// �����E���s����

	// �t�@�C�����̒����`�F�b�N
	if (128 < fileName.length()) {
		// ��������
		printf_s("�}�b�v�h�t�@�C�������������܂�\n");
		printf_s("�}�b�v�h�t�@�C������128�����ȓ��Ő錾���Ă�������\n");
		// ���s����
		state = false;
	}
	else {
		// �����K��
		// �t�@�C������NULL����
		memset(mappedFileName, NULL, 128);
		// CString�^��String�^��Ԋ�
		CString tempString = fileName.c_str();
		// TCHAR�^�Ƀt�@�C�������R�s�[
		_tcscpy_s(mappedFileName, tempString);
		// ��������
		state = true;
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �t�@�C���T�C�Y�̎w�� <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::SetFileSize(const int fileSize) {
	bool state;		// �����E���s����

	// �t�@�C���T�C�Y�̃`�F�b�N
	if (2000000000 < fileSize) {
		// �T�C�Y����
		printf_s("�}�b�v�h�t�@�C���T�C�Y���傫�����܂�\n");
		printf_s("�}�b�v�h�t�@�C���T�C�Y��2GB�ȉ��Ő錾���Ă�������\n");
		// ���s����
		state = false;
	}
	else {
		// �T�C�Y�K��
		mappedFileSize = fileSize;
		// ��������
		state = true;
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C���̍쐬 <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::CreateMappedFile() {
	// �쐬���\�b�h�̎��s�̃A�i�E���X
	printf_s("Run at Create MappedFile\n");
	bool state;		// �����E���s����

	// �}�b�v�h�t�@�C���̍쐬
	mappedFileHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mappedFileSize, mappedFileName);
	// �}�b�v�h�t�@�C���̍쐬�̐����E���s����
	// ���s���ɂ̓n���h����NULL���Ԃ�
	if (mappedFileHandle == NULL) {
		// ���s��
		printf_s("Create MappedFile : Fail|���s\n");
		// ���s����
		state = false;
	}
	else {
		// ������
		// �����A�i�E���X
		printf_s("Create MappedFile : Success|����\n");
		// �}�b�v�h�t�@�C���̃r���[�̎擾(�������A�h���X�̐ݒ�)
		mappedFilePointer = (intptr_t)MapViewOfFile(mappedFileHandle, FILE_MAP_ALL_ACCESS, 0, 0, mappedFileSize);
		// �r���[�̎擾�̐����E���s����
		// ���s���ɂ�NULL�|�C���^���Ԃ�(�k���|�E�b�K�I)
		if (mappedFilePointer == NULL) {
			// ���s��
			// ���s�A�i�E���X
			printf_s("Get Pointer for MappedFile : Fail|���s\n");
			// ���s����
			state = false;
		}
		else {
			// ������
			// �����A�i�E���X
			printf_s("Get Pointer for MappedFile : Success|����\n");
			// ��������
			state = true;
		}
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C���̃I�[�v�� <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::OpenMappedFile() {
	// �I�[�v�����\�b�h�̎��s�̃A�i�E���X
	printf_s("Run at Open MappedFile\n");
	bool state;		// �����E���s����

	// �}�b�v�h�t�@�C���̃I�[�v��
	mappedFileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, mappedFileName);
	// �}�b�v�h�t�@�C���̃I�[�v���̐����E���s����
	// ���s���ɂ̓n���h����NULL���Ԃ�
	if (mappedFileHandle == NULL) {
		// ���s��
		printf_s("Open MappedFile : Fail|���s\n");
		// ���s����
		state = false;
	}
	else {
		// ������
		// �����A�i�E���X
		printf_s("Open MappedFile : Success|����\n");
		// �}�b�v�h�t�@�C���̃r���[�̎擾(�������A�h���X�̐ݒ�)
		mappedFilePointer = (intptr_t)MapViewOfFile(mappedFileHandle, FILE_MAP_ALL_ACCESS, 0, 0, mappedFileSize);
		// �r���[�̎擾�̐����E���s����
		// ���s���ɂ�NULL�|�C���^���Ԃ�(�k���|�E�b�K�I)
		if (mappedFilePointer == NULL) {
			// ���s��
			// ���s�A�i�E���X
			printf_s("Get Pointer for MappedFile : Fail|���s\n");
			// ���s����
			state = false;
		}
		else {
			// ������
			// �����A�i�E���X
			printf_s("Get Pointer for MappedFile : Success|����\n");
			// ��������
			state = true;
		}
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C���̃r���[�̃A���}�b�v <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::UnmapMappedFile() {
	// �A���}�b�v���\�b�h�̃A�i�E���X
	printf_s("Run at Unmap MappedFile\n");
	bool state;		// �����E���s����

	// �}�b�v�h�t�@�C���̃r���[�̃`�F�b�N
	if (mappedFilePointer == NULL) {
		// ���s��(�r���[�̎擾�����Ă��Ȃ�)
		// ���s�A�i�E���X
		printf_s("Get Pointer for MappedFile : Fail|���s\n");
		// ���s����
		state = false;
	}
	else {
		// ������
		// �����A�i�E���X
		printf_s("Get Pointer for MappedFile : Success|����\n");
		// �r���[�̃A���}�b�v�̐����E���s����
		if (!UnmapViewOfFile((LPCVOID)mappedFilePointer)) {
			// ���s��
			// ���s�A�i�E���X
			printf_s("Unmap View of File : Fail|���s\n");
			// ���s����
			state = false;
		}
		else {
			// ������
			// �����A�i�E���X
			printf_s("Unmap View of File : Success|����\n");
			// ��������
			state = true;
		}
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C���̏I�� <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::CloseMappedFile() {
	bool state;		// �����E���s����
	// �I�����\�b�h�̃A�i�E���X
	printf_s("Run at CloseMappedFile\n");
	// �n���h�������
	CloseHandle(mappedFileHandle);
	// ��������
	state = true;
	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C������f�[�^�̓ǂݎ�� <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::ReadMappedFile(void* variablePointer, const int offset, const int dataSize) {
	bool state;		// �����E���s����

	// �}�b�v�h�t�@�C���̃`�F�b�N
	if (mappedFileHandle == NULL || mappedFilePointer == NULL) {
		// ���s��
		// ���s�A�i�E���X
		printf_s("���L���������쐬���邩,�I�[�v�����Ă�������\n");
		// ���s����
		state = false;
	}
	else {
		// ������
		// �I�[�o�[�A�N�Z�X�̃`�F�b�N
		if (mappedFileSize < offset + dataSize) {
			// ���s��
			// ���s�A�i�E���X
			printf_s("�ǂݍ��ݐ悪�}�b�v�h�t�@�C���̃T�C�Y���I�[�o�[���Ă��܂�\n");
			printf_s("�I�[�o�[���Ȃ��͈͂œǂݍ��݂��s���Ă�������\n");
			// ���s����
			state = false;
		}
		else {
			// ������
			// �}�b�v�h�t�@�C������f�[�^��ǂݎ��
			CopyMemory(variablePointer, (PVOID)(mappedFilePointer + offset), dataSize);
			// ��������
			state = true;
		}
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C������f�[�^�̏������� <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::WriteMappedFile(void* variablePointer, const int offset, const int dataSize) {
	bool state;		// �����E���s����

	// �}�b�v�h�t�@�C���̃`�F�b�N
	if (mappedFileHandle == NULL || mappedFilePointer == NULL) {
		// ���s��
		// ���s�A�i�E���X
		printf_s("���L���������쐬���邩,�I�[�v�����Ă�������\n");
		// ���s����
		state = false;
	}
	else {
		// ������
		// �I�[�o�[�A�N�Z�X�̃`�F�b�N
		if (mappedFileSize < offset + dataSize) {
			// ���s��
			// ���s�A�i�E���X
			printf_s("�������ݐ悪�}�b�v�h�t�@�C���̃T�C�Y���I�[�o�[���Ă��܂�\n");
			printf_s("�I�[�o�[���Ȃ��͈͂ŏ������݂��s���Ă�������\n");
			// ���s����
			state = false;
		}
		else {
			// ������
			// �}�b�v�h�t�@�C���փf�[�^���o�͂���
			CopyMemory((PVOID)(mappedFilePointer + offset), variablePointer, dataSize);
			// ��������
			state = true;
		}
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C������f�[�^�̑����������� <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::WriteFlushMappedFile(void* variablePointer, const int offset, const int dataSize, const bool flush) {
	bool state;		// �����E���s����

	// �������݂̐����E���s����
	if (!WriteMappedFile(variablePointer, offset, dataSize)) {
		// ���s��
		// ���s����
		state = false;
	}
	else {
		// ������
		// ������������
		if (!flush) {
			// ���s��
			// ���s����
			state = false;
		}
		else {
			// ������
			// ������������
			if (!FlushViewOfFile((LPCVOID)mappedFilePointer, mappedFileSize)) {
				// ���s����
				state = false;
			}
			else {
				// ��������
				state = true;
			}
		}
	}

	// �����Ԃ�
	return state;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C������Ԃ� <<<<<<<<<<<<<<<<<<<<<//
string SharedMemory::ReadFileName(){
	// �}�b�v�h�t�@�C������TCHAR����CStringA�ɕϊ�����
	CStringA tempString = mappedFileName;
	// CStringA����string�ɕϊ�����
	string fileName = tempString.GetBuffer(0);
	// �t�@�C������Ԃ�
	return fileName;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C���T�C�Y��Ԃ� <<<<<<<<<<<<<<<<<<<<<//
int SharedMemory::ReadFileSize(){
	return mappedFileSize;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C���n���h����Ԃ� <<<<<<<<<<<<<<<<<<<<<//
HANDLE SharedMemory::ReadFileHandle(){
	return mappedFileHandle;
}
//>>>>>>>>>>>>>>>>>>>> �}�b�v�h�t�@�C���̃r���[��Ԃ� <<<<<<<<<<<<<<<<<<<<<//
intptr_t SharedMemory::ReadFilePointer(){
	return mappedFilePointer;
}