#include "MProjectServer.h"

#include "Core/MLogger.h"
#include "Manager/MThreadManager.h"
#include "Manager/UserManager.h"
#include "Manager/WorldManager.h"

#include "Network/HeadServer.h"

#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>

#include <boost/asio.hpp>

QListWidget* MProjectServer::List_Widget = nullptr;

MProjectServer::MProjectServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    OnInitialize();
}

void MProjectServer::OnInitialize() {
    Initailize_Manager();
    Initailize_UI();
    Initailize_Bind();
}

//! Initailize

void MProjectServer::Initailize_Manager()
{
    MLogger::GetMutableInstance().Create("MProjectServer-logs", "MProjectServer", 65'536, 1000);

    MThreadManager::GetConstInstance();
    UserManager::GetConstInstance();
    WorldManager::GetConstInstance();
	
}

void MProjectServer::Initailize_UI()
{
    using udp = boost::asio::ip::udp;
    boost::asio::io_service netService;
    udp::resolver   resolver(netService);
    udp::resolver::query query(udp::v4(), "google.com", "");
    udp::resolver::iterator endpoints = resolver.resolve(query);
    udp::endpoint ep = *endpoints;
    udp::socket socket(netService);
    socket.connect(ep);
    boost::asio::ip::address addr = socket.local_endpoint().address();
    boost::asio::ip::address addr2 = socket.remote_endpoint().address();

    QString qstring(std::format("Public IP={}", addr.to_string()).c_str());
    ui.private_ip_title_label->setText(qstring);

    ui.server_push_btn->setText(QString("Start"));
}

void MProjectServer::Initailize_Bind()
{
    // 테스트용
    MProjectServer::List_Widget = ui.test_list;
    MLogger::GetMutableInstance().AddDelegate([]() {
        std::string msg = MLogger::GetMutableInstance().GetMutableInstance().PopMessage();
        if (true == msg.empty()) {
            return;
        }
        MProjectServer::List_Widget->addItem(QString::fromLocal8Bit(msg.c_str()));
    });


    QObject::connect(ui.server_push_btn, &QPushButton::clicked, this, &MProjectServer::OnClick);
    MThreadManager::GetMutableInstance().AddCompleteDelegate([&] {
        ui.server_push_btn->setText(QString("Connected"));
    });
}


void MProjectServer::OnClick(bool checked) {
    if (true == MThreadManager::GetConstInstance().Stopped()) {
		MThreadManager::GetMutableInstance().OnStart();
    } else {
        MThreadManager::GetMutableInstance().AllStop();
        ui.server_push_btn->setText(QString("Start"));
    }
}

