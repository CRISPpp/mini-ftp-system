#include <WINSOCK2.H>
#include <STDIO.H>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#pragma warning(disable : 4996)

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        return 0;
    }
    while (true)
    {
        SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sclient == INVALID_SOCKET)
        {
            printf("invalid socket!");
            return 0;
        }

        sockaddr_in serAddr;
        serAddr.sin_family = AF_INET;
        serAddr.sin_port = htons(13000);
        serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
        if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
        { //连接失败
            printf("connect error !");
            closesocket(sclient);
            return 0;
        }
        cout << "发送消息请输入1，发送文件请输入2，接收文件请输入3\n";
        int tmpNum;
        cin >> tmpNum;
        if (tmpNum == 1)
        {
            string data;
            data = "message";

            const char *sendData;
            sendData = data.c_str();
            // string转const char*
            send(sclient, sendData, strlen(sendData), 0);
            cout << "请输入要发送的消息：";

            cin >> data;
            data += '\n';
            sendData = data.c_str();
            // string转const char*
            send(sclient, sendData, strlen(sendData), 0);
            // send()用来将数据由指定的socket传给对方主机
            // int send(int s, const void * msg, int len, unsigned int flags)
            // s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
            //成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error

            char recData[4096];
            int ret = recv(sclient, recData, 4096, 0);
            if (ret > 0)
            {
                recData[ret] = 0x00;
                printf(recData);
                cout << endl;
            }
            closesocket(sclient);
        }
        else if (tmpNum == 2)
        {

            string data;

            data = "uploadfile";
            const char *sendData;
            sendData = data.c_str();
            // string转const char*
            send(sclient, sendData, strlen(sendData), 0);

            string fileName;
            cout << "请输入要发送的文件名：";
            cin >> fileName;
            ifstream ifs;
            ifs.open(fileName, ios::in);
            if (!ifs.is_open())
            {
                cout << "文件打开失败" << endl;
                continue;
            }

            sendData = fileName.c_str();
            send(sclient, sendData, strlen(sendData), 0);

            data.clear();
            string buff;
            while (ifs >> buff)
                data += buff, data += " ";
            ifs.close();
            sendData = data.c_str();
            // string转const char*
            send(sclient, sendData, strlen(sendData), 0);

            char recData[4096];
            int ret = recv(sclient, recData, 4096, 0);
            if (ret > 0)
            {
                recData[ret] = 0x00;
                printf(recData);
                cout << endl;
            }
            closesocket(sclient);
        }
        else if (tmpNum == 3)
        {

            string data;

            data = "downloadfile";
            const char *sendData;
            sendData = data.c_str();
            // string转const char*
            send(sclient, sendData, strlen(sendData), 0);

            string fileName;
            cout << "请输入要获取的文件名：";
            cin >> fileName;

            sendData = fileName.c_str();
            // string转const char*
            send(sclient, sendData, strlen(sendData), 0);
            char recData[4096];
            int ret = recv(sclient, recData, 4096, 0);
            if (ret > 0)
            {
                recData[ret] = 0x00;
                printf(recData);
                cout << endl;
            }

            string content(recData);
            if (content == "error")
            {
                cout << "接收错误\n";
                continue;
            }
            cout << "接收成功\n";

            ofstream ofs;
            ofs.open(fileName, ios::out);
            ofs << content;
            ofs.close();

            ret = recv(sclient, recData, 4096, 0);
            if (ret > 0)
            {
                recData[ret] = 0x00;
                printf(recData);
            }
        }
        else
        {
            cout << "输入错误，请重新输入\n";
        }
    }

    WSACleanup();
    return 0;
}
