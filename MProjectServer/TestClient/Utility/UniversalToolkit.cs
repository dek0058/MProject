using System;
using System.Collections.Generic;
using System.Text;

namespace TestClient.Utility {
    public class UniversalToolkit {

        static public string Digest2Hex(byte[] _data) {
            StringBuilder sb = new StringBuilder();
            foreach (byte b in _data) {
                sb.Append(b.ToString("x2"));
            }
            return sb.ToString();
        }

    }
}
