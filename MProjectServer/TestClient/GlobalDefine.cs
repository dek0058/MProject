using System;

namespace TestClient {
    public static class GlobalDefine {

        public static Int32 PACKET_TAG_SIZE = sizeof(UInt32);
        public static Int32 PACKET_LEGNTH_SIZE = sizeof(UInt32);
        public static Int32 PACKET_HASH_CODE_SIZE = 32;
        public static Int32 PACKET_HEADER_SIZE = PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE + PACKET_HASH_CODE_SIZE;
        public static Int32 PACKET_MAX_SIZE = 1024;

    }
}
