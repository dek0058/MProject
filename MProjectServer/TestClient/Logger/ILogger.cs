/*****************************************************************//**
 * \file   ILogger.h
 * \brief  Logger interface
 * 
 * \author dek0058
 * \date   2023-01-07
 *********************************************************************/
using System;
using System.Collections.Generic;

namespace mproject.logger {
    
    public interface ILogger {
        public List<Tuple<ELogLevel, String>> Logs { get; }
        public bool Empty { get => Logs.Count == 0; }
        public void WriteLog(ELogLevel _level, String _msg);
    }
}
