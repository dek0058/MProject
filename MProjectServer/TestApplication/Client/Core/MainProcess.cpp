#include "MainProcess.h"

#include "MProjectLogger/Core/ILogger.h"

#include "Client/Administrator.h"
#include "Client/Manager/UIManager.h"


namespace mproject {

MainProcess::MainProcess(int _fps) 
	: MThread(_fps) {

}

void MainProcess::OnStart() {
	if (auto logger = Administrator::GetMutableInstance().GetLogger();  false == logger.expired()) {
		logger.lock()->WriteLog(logger::ELogLevel::Info, FString(pTEXT("MainProcess Start!")));
	}
}

void MainProcess::OnUpdate() {
	

}

void MainProcess::OnStop() {

}

}	// mproject

