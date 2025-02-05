

#include <udpserver.h>
#include <udpclient.h>
//#include <cstdio>
//#include <thread>
#include <cstdio>
#include <string>
#include <iostream>
#include <thread>


long fileSize(FILE* fp)
{

    std::fseek(fp, 0, SEEK_END);
    auto sz = std::ftell(fp);
    std::fseek(fp, 0, SEEK_SET);
    return sz;

}

void Client(const char* filename, const char* ifaceOrIp, const char* port){

    Services::UDPClient client;

    std::string directory_path{TESTFILES_DIR};
    const auto chunkbit     = 10;
    const auto chunksize    = 1 << 10;
    auto filePath           = directory_path + std::string{"/"} + std::string{filename};
    auto pFile              = std::fopen(filePath.data(), "r");
    auto fileSz             = fileSize(pFile);
    auto fileChunks         = static_cast<long>(fileSz >> chunkbit);
    auto fileTail           = fileSz % chunksize;

    for (auto fileChunksLeft = fileChunks + 1, bytesSent = 0L; fileChunksLeft > 0; --fileChunksLeft) {


        bool isLastChunk = fileChunksLeft == 1;
        bool hasNonMultipleTail = fileTail > 0;

        auto bytesToSend = isLastChunk and hasNonMultipleTail ? fileTail : (isLastChunk ? 0 : chunksize);
        if (!bytesToSend) continue;

        bytesSent += bytesToSend;

        std::cout << "Sending: " << bytesToSend << " bytes. Sent so far: " << bytesSent << std::endl;

    }

    std::fclose(pFile);

}
std::thread Server(const char* ifaceName, const char* port){

    Services::UDPServer server(port, ifaceName);
    return std::thread([&](){
        server.RunService();
    });

}

int main (int argc, char ** argv){

	//1. open an UDP socket server. Thread it.
	//2. open a client socket server. 
	//3. Send Data.
	//4. MD5 it

	//UDPServer udpServer(0x3f78);


	/*std::thread t([&](){
		udpServer.RunService();
	});
    */

	auto tServer = Server(argv[1], argv[2]);
	Client(argv[3], argv[1], argv[2]);
    tServer.join();



    return 0;


	



}