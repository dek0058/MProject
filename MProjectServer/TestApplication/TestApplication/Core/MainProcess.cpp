#include "MainProcess.h"

#include "TestApplication/Administrator.h"
#include "TestApplication/Manager/UIManager.h"

namespace mproject {

MainProcess::MainProcess(int _fps) 
	: MThread(_fps) {

}

void MainProcess::OnStart() {
	Administrator::GetMutableInstance().StartEngine();
}

void MainProcess::OnUpdate() {

}

void MainProcess::OnStop() {

}

}	// mproject

