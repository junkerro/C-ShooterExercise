#include "Initpacket.h"


InitPacket::InitPacket(const int sizeX, const int sizeY)
{
    sizeX_ = sizeX;
    sizeY_ = sizeY;
}

InitPacket *InitPacket::ParsePacket(vector<uint8_t> *data)
{
    auto pkg = new InitPacket();
    pkg->byteBuffer_ = data;

    if(pkg->ReadDataFromBuffer(0,7) != PACKET_TYPE)
        return nullptr;

    pkg->sizeX_ = pkg->ReadDataFromBuffer(8,39);
    pkg->sizeY_ = pkg->ReadDataFromBuffer(40,71);

    return pkg;
}

int InitPacket::GetSizeX()
{
    return sizeX_;
}

int InitPacket::GetSizeY()
{
    return sizeY_;
}

vector<uint8_t> *InitPacket::Build()
{
    CreateByteBuffer(9);
    WriteDataToBuffer(PACKET_TYPE,0,7);
    WriteDataToBuffer(sizeX_,8,39);
    WriteDataToBuffer(sizeY_,40,71);
    return byteBuffer_;
}


