#include "MProjectServer.h"
#include "Manager/MThreadManager.h"
#include "Network/HeadServer.h"

#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>

#include <boost/asio.hpp>

MProjectServer::MProjectServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    OnInitialize();
}

void MProjectServer::OnInitialize() {
    // Manager Initailize...
    MThreadManager::GetMutableInstance();


    //QObject::connect(server_push_btn, &QPushButton::clicked, server_push_btn, qOverload<>(&QPushButton::click));

    QObject::connect(ui.server_push_btn, &QPushButton::clicked, this, &MProjectServer::OnClick);

	
    /*using udp = boost::asio::ip::udp;
    boost::asio::io_service netService;
    udp::resolver   resolver(netService);
    udp::resolver::query query(udp::v4(), "google.com", "");
    udp::resolver::iterator endpoints = resolver.resolve(query);
    udp::endpoint ep = *endpoints;
    udp::socket socket(netService);
    socket.connect(ep);
    boost::asio::ip::address addr = socket.local_endpoint().address();
    boost::asio::ip::address addr2 = socket.remote_endpoint().address();

    ui.test_list->addItem(QString(addr.to_string().c_str()));
    ui.test_list->addItem(QString(addr2.to_string().c_str()));*/

    //QString qstring(std::format("Public IP={}", addr.to_string()).c_str());
    //ui.public_ip_title_label->setText(qstring);

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

