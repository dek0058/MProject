#include "NetworkToolkit.h"
#include "BaseProtocol.h"

std::vector<byte> NetworkToolkit::GetPacketData(std::unique_ptr<FPacket> _packet) {
    std::vector<byte> result(PACKET_HEADER_SIZE + _packet->length);
    std::memcpy(result.data(), &_packet->tag, PACKET_TAG_SIZE);
    std::memcpy(result.data() + PACKET_TAG_SIZE, &_packet->length, PACKET_LEGNTH_SIZE);
    std::memcpy(result.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE, &_packet->hash_code, PACKET_HASH_CODE_SIZE);
    std::memcpy(result.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE + PACKET_HASH_CODE_SIZE, _packet->data.data(), _packet->length);
    return result;
}
