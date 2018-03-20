#ifndef DATAPACKET_H
#define DATAPACKET_H

#include "PacketStructure.h"
#include <vector>

class DataPacket : public PacketStructure
{
public:
    explicit DataPacket(vector<uint8_t>* data);
    virtual ~DataPacket();

    vector<uint8_t>* Build() override;
    static DataPacket* ParsePacket(vector<uint8_t>* data);
    vector<uint8_t>* GetPayload();


private:
    DataPacket();
    static const int HEADER_SIZE_BYTE = 5;
    static const uint8_t PACKET_TYPE = 1;
    vector<uint8_t>* payload_ = nullptr;
};

#endif // DATAPACKET_H
