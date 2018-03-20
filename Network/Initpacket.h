#ifndef INITPACKET_H
#define INITPACKET_H

#include "PacketStructure.h"

class InitPacket : public PacketStructure
{
public:

    InitPacket(int const sizeX, int const sizeY);
    virtual ~InitPacket(){}
    static InitPacket* ParsePacket(vector<uint8_t>* data);

    int GetSizeX();
    int GetSizeY();
    virtual vector<uint8_t>* Build() override;

private:
    InitPacket(){}
    int sizeX_;
    int sizeY_;
    static const uint8_t PACKET_TYPE = 0;

};

#endif // INITPACKET_H
