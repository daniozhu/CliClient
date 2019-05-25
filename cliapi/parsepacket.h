#ifndef PARSE_PACKET_H
#define PARSE_PACKET_H


class ISocketHandler
{
public:

	virtual ~ISocketHandler() {}
	
	// 协议定界函数
	// 收到的网络包buffer
	// 网络包长度
	// return >0表示完整包长度，0表示不完整，-1表示错误包
	virtual INT32 OnParsePacket(const char* buf, UINT32 len) = 0;
};
#endif