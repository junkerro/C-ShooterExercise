#include "Datapacket.h"

DataPacket::DataPacket(vector<uint8_t> *data)
{
    payload_ = data;
}

DataPacket::~DataPacket()
{
    if(payload_ != nullptr)
    {
        delete payload_;
        payload_ = nullptr;
    }
}

vector<uint8_t> *DataPacket::Build()
{
    int length = payload_->size() + HEADER_SIZE_BYTE;

    CreateByteBuffer(length);

    WriteDataToBuffer(PACKET_TYPE,0,7);
    WriteDataToBuffer(length,8,39);

    int position = 40;

    for(int i = 0; i < payload_->size(); i++)
    {
        WriteDataToBuffer(payload_->data()[i],position,position + 7);
        position += 8;
    }

    return byteBuffer_;
}

DataPacket *DataPacket::ParsePacket(vector<uint8_t> *data)
{
    auto pkg = new DataPacket();
    pkg->byteBuffer_ = data;

    if(pkg->ReadDataFromBuffer(0,7) != PACKET_TYPE)
        return nullptr;

    int dataLength = pkg->ReadDataFromBuffer(8,39) - HEADER_SIZE_BYTE;

    int position = 40;

    pkg->payload_ = new vector<uint8_t>();

    for(int i = 0; i < dataLength; i++)
    {
        pkg->payload_->push_back(pkg->ReadDataFromBuffer(position,position +7));
        position += 8;
    }

    return pkg;
}

vector<uint8_t> *DataPacket::GetPayload()
{
    return payload_;
}

DataPacket::DataPacket()
{

}

















































