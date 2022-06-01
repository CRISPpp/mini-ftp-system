首先基于c++和winsocket编写客户端，客户端通过套接字socket可向服务端传送和接收文件或者发送消息，输入1可向服务端发送消息，输入2可向服务端发送文件，输入3可向服务端请求文件。
发送消息部分，客户端发送message给服务器，服务器收到后等待客户端的消息
结果：

客户端

![image](https://crispblog.com.cn/upload/2022/06/image-f01834d3e67a4a78bc7f73938651edbf.png)

服务器

![image](https://crispblog.com.cn/upload/2022/06/image-03ede40d16634cd0b0d6e88c40b960db.png)


客户端向服务器上传文件部分：
客户端先发送一个uploadfile通知服务器要上传文件，然后会把文件名传送过去，服务器读取到文件名后开启IO流，再读入客户端的文件内容。
结果：

客户端
![image](https://crispblog.com.cn/upload/2022/06/image-b92fbafd4c2343c7b745864b2402dca0.png)
testSend.txt

![image](https://crispblog.com.cn/upload/2022/06/image-0aec8011ec514ffebe709f89280307d4.png)
服务端

![image](https://crispblog.com.cn/upload/2022/06/image-7305107c47e44daa971ca1c0532ce5b4.png)

服务器生成的文件

![image](https://crispblog.com.cn/upload/2022/06/image-fafde9da64494beca1313f03fe9bd18c.png)









客户端下载服务器的文件，客户端先发送downloadfile给服务器，然后再发送文件名给服务器，服务器读取指定的文件，如果没有指定的文件发送error给客户端，否则将文件内容传送给客户端。
结果：

客户端
![image](https://crispblog.com.cn/upload/2022/06/image-26948afa80fa481c9b8ab12aaebda0cb.png)


服务器

![image](https://crispblog.com.cn/upload/2022/06/image-6fe99e03a9944b92a0b0190ddbe3c2f7.png)





服务器文本文件

![image](https://crispblog.com.cn/upload/2022/06/image-10179fb35d7b42b48ac54189f884328d.png)

客户端文本内容

![image](https://crispblog.com.cn/upload/2022/06/image-10179fb35d7b42b48ac54189f884328d.png)





