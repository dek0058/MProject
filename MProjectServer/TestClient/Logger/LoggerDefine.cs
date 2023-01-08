/*****************************************************************//**
 * \file   LoggerDefine.h
 * \brief  Log define header
 * 
 * \author dek0058
 * \date   2023-01-07
 *********************************************************************/
using System;
using System.Runtime.Serialization;

namespace mproject.logger {

    [DataContract]
    public enum ELogLevel : Byte {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Critical,
    }
}
