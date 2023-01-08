/*****************************************************************/
/**
* \file   ILogger.h
* \brief  Logger interface
* 
* \author dek0058
* \date   2023-01-07
*********************************************************************/
using System;
using System.Collections.Generic;

namespace mproject.logger {
    public class ConsoleLogger : ILogger {

        private List<Tuple<ELogLevel, String>> logs;

        public ConsoleLogger() {
            Logs = new List<Tuple<ELogLevel, string>>();
        }

        public List<Tuple<ELogLevel, String>> Logs {
            get {
                List<Tuple<ELogLevel, String>> Result = new List<Tuple<ELogLevel, string>>(logs);
                logs.Clear();
                return Result;
            }
            private set => logs = value;
        }

        public void WriteLog(ELogLevel _level, String _msg) {
            String msg = "";
            switch ( _level ) {
                case ELogLevel.Trace:       msg += "[Trace]";       break;
                case ELogLevel.Debug:       msg += "[Debug]";       break;
                case ELogLevel.Info:        msg += "[Info]";        break;
                case ELogLevel.Warning:     msg += "[Warning]";     break;
                case ELogLevel.Error:       msg += "[Error]";       break;
                case ELogLevel.Critical:    msg += "[Critical]";    break;
                default:                    msg += "[off]";         break;
            }
            msg += _msg;
            Console.WriteLine(msg);
            Logs.Add(new (_level, msg));
        }
    }
}
