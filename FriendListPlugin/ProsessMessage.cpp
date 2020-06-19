#include "stdafx.h"
#include "NetProtocConfig.pb.h"
#include "ProsessMessage.h"
#include "FriendList.h"


extern FriendList* g_FriendList;
ProsessMessage::ProsessMessage(AbstractNetWork::ProtoType Type, QHostAddress addr, int port, QObject* parent /*= 0*/) : AbstractNetWork(Type, addr, port, parent)
{

}

int ProsessMessage::RecvMessage()
{
	int size = 0;
	QTcpSocket* tcp = (QTcpSocket*)ReturnCurrentTargetSocket();
	if (tcp->bytesAvailable()) {
		QByteArray buf;
		buf.resize(tcp->bytesAvailable());
		size = tcp->read(buf.data(), buf.size());
		AnalysisProtocol(buf);
		//protobuf解析协议，把解析出来的协议内容显示到界面中
	}
	return size;
}

void ProsessMessage::AnalysisProtocol(QByteArray& proto)
{
	protocolType protocol;
	if (protocol.ParseFromString(proto.toStdString())) {
		switch (protocol.type()) {
		case protocolType_Type_ftp:
			break;
		case protocolType_Type_http:
			break;
		case protocolType_Type_smtp:
			break;
		case protocolType_Type_tcp:
			switch (protocol.chatcontent(0).type())
			{
			case ChatRecord_contenttype::ChatRecord_contenttype_file:
				break;
			case ChatRecord_contenttype::ChatRecord_contenttype_image:
				break;
			case ChatRecord_contenttype::ChatRecord_contenttype_text:
				protocol.chatcontent(0).targetnumber();
				QString::fromStdString(protocol.chatcontent(0).content());
				break;
			default:
				break;
			}
			break;
		case protocolType_Type_udp:
			break;
		}
	}
}

ProsessMessage::~ProsessMessage()
{

}
