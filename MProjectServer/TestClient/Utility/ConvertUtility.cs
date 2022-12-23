using System;
using System.Runtime.InteropServices;

namespace mproject {
    namespace utility {

        public static class ConvertUtility {

            public static T ToObject<T> ( byte[] _buffer, GCHandleType _type = GCHandleType.Pinned ) where T : struct {
                GCHandle gc = GCHandle.Alloc ( _buffer, _type );
                var result = Marshal.PtrToStructure ( gc.AddrOfPinnedObject ( ), typeof ( T ) );
                gc.Free ( );

                if(result != null) {
                    return (T)result;
                } else {
                    throw new InvalidCastException ( new string ( "Failed to convert buffer to object." ) );
                }
            }

            public static byte[] ToBytes<T> ( T _object, GCHandleType _type = GCHandleType.Pinned ) where T : struct {
                int size = Marshal.SizeOf ( _object );
                byte[] buffer = new byte[size];
                GCHandle gc = GCHandle.Alloc ( buffer, _type );
                Marshal.StructureToPtr ( _object, gc.AddrOfPinnedObject ( ), false );
                gc.Free ( );

                return buffer;
            }


        }

    }   // utility
}       // mproject
