#include "pch.h"
#include "FileManager.h"


FileManager* pFileManager = nullptr;

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

FileManager * FileManager::GetInstance()
{
	if (pFileManager == nullptr)
	{
		pFileManager = new FileManager;
	}

	return pFileManager;
}

void FileManager::Release()
{
	delete pFileManager;
}

int FileManager::MakeDirectory(const char * _directory)
{
	int ret = _mkdir(_directory);
	
	if (ret == ENOENT)
	{
		cout << "[Warning] 올바르지 않은 경로입니다." << endl;
	}

	return ret;
}

void FileManager::SetDirectory(const char * _directory)
{
	int srcLen = strlen(_directory);
	int cpyLen = (srcLen < (dfMAX_DIRECTORY_LENGTH - 1)) ? srcLen : (dfMAX_DIRECTORY_LENGTH - 1);
	memset(pFileManager->directory,0,dfMAX_DIRECTORY_LENGTH);
	memcpy(pFileManager->directory, _directory, cpyLen);
}

errno_t FileManager::OpenFile(const char * _mode)
{
	return fopen_s(&pFileManager->file, pFileManager->directory, _mode);
}

void FileManager::CloseFile()
{
	if (pFileManager->file == nullptr) return;

	fclose(pFileManager->file);
	pFileManager->file = nullptr;
}

size_t FileManager::ReadFile(void * _buffer, size_t _elementSize, size_t _elementCount)
{
	return fread(_buffer, _elementSize, _elementCount, pFileManager->file);
}

size_t FileManager::WriteFile(const void * _buffer, size_t _elementSize, size_t _elementCount)
{
	return fwrite(_buffer, _elementSize, _elementCount, pFileManager->file);
}