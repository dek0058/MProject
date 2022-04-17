#include "MainThread.h"
#include "Network/HeadServer.h"
#include "Network/NetworkDefine.h"

MainThread::MainThread() : MThread(L"Main", 10) {
	
}

MainThread::~MainThread() {
	
}

void MainThread::OnStart() {
	MThread::OnStart();
	
	// 현재 세션 서버가 존재하지 않음으로 빈 데이터를 보낸다.
	std::vector<FAcceptInfo> accept_info_vector;
	std::vector<FConnectInfo> connect_info_vector;

	HeadServer::GetMutableInstance().Start(accept_info_vector, connect_info_vector);


}

void MainThread::OnUpdate() {
	HeadServer::GetMutableInstance().Loop();
}

void MainThread::OnStop() {
	MThread::OnStop();
	HeadServer::GetMutableInstance().Stop();
}
