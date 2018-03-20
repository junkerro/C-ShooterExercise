#ifndef CHARBUFFER_H
#define CHARBUFFER_H

#include "Network/ServerEngine.h"

class CharBuffer
{
public:
    CharBuffer(ServerEngine * const server,int const sizeX, int const sizeY);
    CharBuffer(ServerEngine * const server,int const sizeX, int const sizeY, char const defaultChar);
    CharBuffer();


	void SetCharAt(int const positionX, int const postitionY, char const data);
	char GetCharAt(int const positionX, int const positionY);

	void ResetBufferToDefault();
	void ResetBufferToDefault(char const newDefaultChar);

	void SetDefaultChar(char const newDefaultChar);
	char GetDefaultChar();

	void Render();

	int GetSizeX();
	int GetSizeY();

    void SetData(vector<uint8_t>* data);
    void SetSize(int const sizeX, int const sizeY);

private:
    char* data_ = nullptr;
	char defaultChar_ = ' ';
    int sizeX_ = -1;
    int sizeY_ = -1;
    ServerEngine* server_ = nullptr;

	void ClearBufferData();
	void CreateBufferData();
	void InitializeBufferData();
    void SendDataToServer();
    void SetBorder();

};

#endif // CHARBUFFER_H
