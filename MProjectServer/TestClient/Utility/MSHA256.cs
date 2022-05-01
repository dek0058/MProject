using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;

namespace TestClient.Utility {
    public class MSHA256 {

        static public byte[] GenerateHashcode(string _value) {
            System.Security.Cryptography.SHA256Managed crypt = new System.Security.Cryptography.SHA256Managed();
            System.Text.StringBuilder hash = new System.Text.StringBuilder();
            byte[] crypto = crypt.ComputeHash(Encoding.UTF8.GetBytes(_value));
            foreach (byte theByte in crypto) {
                hash.Append(theByte.ToString("x2"));
            }
            return crypto;
        }

    }
}
