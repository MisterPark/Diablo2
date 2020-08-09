#pragma once

#define dfMAX_DIRECTORY_LENGTH 128

class FileManager
{
private:
	FileManager();
	~FileManager();

public:
	static FileManager* GetInstance();
	static void Release();
	static int MakeDirectory(const char* _directory);
	static void SetDirectory(const char* _directory);
	static errno_t OpenFile(const char* _mode);
	static void CloseFile();
	static size_t ReadFile(void* _buffer, size_t _elementSize, size_t _elementCount);
	static size_t WriteFile(const void* _buffer, size_t _elementSize, size_t _elementCount);
	


private:
	FILE* file = nullptr;
	char directory[dfMAX_DIRECTORY_LENGTH] = { 0, };
};

