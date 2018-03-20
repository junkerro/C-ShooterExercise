
#include "charbuffer.h"
#include <iostream>

using namespace std;

CharBuffer::CharBuffer(ServerEngine * const server,const int sizeX, const int sizeY)
    : CharBuffer(server,sizeX, sizeY, ' ')
{
}

CharBuffer::CharBuffer(ServerEngine * const server,const int sizeX, const int sizeY, const char defaultChar)
{
    sizeX_ = sizeX;
    sizeY_ = sizeY;
    server_ = server;

    SetDefaultChar(defaultChar);

    ClearBufferData();
    CreateBufferData();
    InitializeBufferData();
    SetBorder();
}

CharBuffer::CharBuffer()
{
}

void CharBuffer::SetDefaultChar(const char newDefaultChar)
{
    defaultChar_ = newDefaultChar;
}

char CharBuffer::GetDefaultChar() {
    return defaultChar_;
}

void CharBuffer::ClearBufferData() {
    if (data_ == nullptr)
        return;

    delete[] data_;

    data_ = nullptr;
}

void CharBuffer::CreateBufferData()
{
    data_ = new char[sizeX_*sizeY_];
}

void CharBuffer::InitializeBufferData()
{
    for (int x = 0; x < sizeX_ * sizeY_; x++)
    {
        data_[x] = defaultChar_;
    }
}

void CharBuffer::SendDataToServer()
{
    if(server_ == nullptr)
        return;

    server_->BroadcastMessage(data_,sizeX_*sizeY_);

}

void CharBuffer::SetBorder()
{
    for(int x = 0; x < sizeX_; x++)
    {
        for(int y = 0; y < sizeY_; y++)
        {
            if(x == 0 || y == 0 || x == sizeX_ - 1 || y == sizeY_ -1)
                SetCharAt(x,y,'#');
        }
    }
}

char CharBuffer::GetCharAt(const int positionX, const int positionY)
{
    return data_[positionY * sizeX_ + positionX];
}

void CharBuffer::SetCharAt(const int positionX, const int positionY, const char data)
{
    data_[positionY * sizeX_ + positionX] = data;
}

void CharBuffer::ResetBufferToDefault()
{
    ClearBufferData();
    CreateBufferData();
    InitializeBufferData();
}

void CharBuffer::ResetBufferToDefault(const char newDefaultChar)
{
    SetDefaultChar(newDefaultChar);
    ResetBufferToDefault();
}


void CharBuffer::Render()
{
    system("cls");

    for (int y = 0; y < sizeY_; y++)
    {
        for (int x = 0; x < sizeX_; x++)
        {
            cout << data_[y * sizeX_ + x];
        }
        cout << endl;
    }
    cout << endl;

    SendDataToServer();
}

int CharBuffer::GetSizeX(){
    return sizeX_;
}

int CharBuffer::GetSizeY() {
    return sizeY_;
}

void CharBuffer::SetSize(const int sizeX, const int sizeY)
{
    sizeX_ = sizeX;
    sizeY_ = sizeY;
}

void CharBuffer::SetData(vector<uint8_t> *data)
{
    ClearBufferData();

    data_ = new char[data->size()];
    std::copy(data->begin(),data->end(),data_);
}




































