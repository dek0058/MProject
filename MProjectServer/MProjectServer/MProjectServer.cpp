#include "MProjectServer.h"

#include "Core/MLogger.h"
#include "Manager/MThreadManager.h"
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
	// Core initailize...
    MLogger::GetMutableInstance().Create("MProjectServer-logs", "MProjectServer", 65'536, 1000);
    MLogger::GetMutableInstance().AddDelegate([]() {
        std::string msg = MLogger::GetMutableInstance().GetMutableInstance().PopMessage();
        if (true == msg.empty()) {
            return;
        }
        MProjectServer::List_Widget->addItem(QString::fromLocal8Bit(msg.c_str()));
    });

    // Manager Initailize...
    MThreadManager::GetConstInstance();


    //QObject::connect(server_push_btn, &QPushButton::clicked, server_push_btn, qOverload<>(&QPushButton::click));

    QObject::connect(ui.server_push_btn, &QPushButton::clicked, this, &MProjectServer::OnClick);

    MProjectServer::List_Widget = ui.test_list;
	
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

}

void MProjectServer::OnClick(bool checked) {
    static bool test_check = false;
    if (test_check) {
        return;
    }
    test_check = true;

    ui.test_list->addItem(QString("Server Start"));
    MThreadManager::GetMutableInstance().OnStart();

    // 성공되면 교체 필요할듯한데?
    ui.server_push_btn->setText(QString("Connecting..."));
}


// 테스트용
void MProjectServer::AddTestLog(std::string const& str) {
    MProjectServer::List_Widget->addItem(QString(str.c_str()));
}