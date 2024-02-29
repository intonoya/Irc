#include "Bot.hpp"

Bot::Bot(std::string host, int port, std::string psw, std::string nick) : _Host(host), _Port(port), _Psw(psw), _Nick(nick)
{
    if (InitTheBot() == -1) 
        return ; 
    RunTheBot();
}

Bot::~Bot()
{

}

int Bot::ConnectTheBot()
{
    if (connect(_Socket, (struct sockaddr *)&_Address, sizeof(_Address)) < 0)
    {
        std::cout << "Error: Connection failed!" << std::endl;
        return -1;
    }
    std::cout<<"Connected successfully!\n";
    return 0;
}

int Bot::InitTheBot()
{
    _BytesRead = 0;
    _BytesWritten = 0;
    if ((_Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout<<"Error: Socket failed!"<<std::endl;
        return -1;
    }
    _Address.sin_family = AF_INET;
    _Address.sin_port = htons(_Port);
    std::cout<<"Connecting to the server..." <<std::endl;
    

    if(inet_pton(AF_INET, _Host.c_str(), &_Address.sin_addr) <= 0) 
    { 
        std::cout<<"Error: Invalid address!\n";
        return -1;
    }
    return 0;
}

void Bot::SendMsg(std::string const &msg)
{
    std::string buffer = msg + "\r\n";
    _BytesWritten += send(_Socket, buffer.c_str(), strlen(buffer.c_str()), 0);
}

void Bot::RunTheBot()
{

    char buffer[5000];
    std::string data;
    gettimeofday(&_Start, NULL);

    
    while (1)
    {
        gettimeofday(&_End, NULL);
        if (_End.tv_sec - _Start.tv_sec > 10)
        {
            std::cout<<"Error: Couldn't connect to the server!"<<std::endl;
            break;
        }
        if (connect(_Socket, (struct sockaddr *)&_Address, sizeof(_Address)) != -1)
        {
            fcntl(_Socket, F_SETFL, O_NONBLOCK);
            SendMsg("PASS " + _Psw);
            SendMsg("USER " + _Nick + " " + ToString(_Port) + " " + _Host + " :Noname");
            SendMsg("NICK " + _Nick);
            
            std::cout<<"Hello, my name is "<< _Nick <<std::endl;
            std::cout<<"Please, choose one of the commands above and type it in the User chat"<<std::endl;
            std::cout<<"Commands: SAYHELLO, PYTHON, TRANSFER, HELP, EXIT"<<std::endl;
            while (1)
            {

                memset(&buffer, 0, sizeof(buffer));
                int value = recv(_Socket, (char*)&buffer, sizeof(buffer), 0);
                if (value == 0)
                    break; 
                _BytesRead += value;
                data = "";
                data.append(buffer);
                if (!data.empty())
                {
                    if (Handle(buffer))
                        break;
                }
            }
            break;
        }
    }
    close(_Socket);
    std::cout<<"The session was done :("<<std::endl;
}

std::string Bot::Parsing(std::string &data, std::string *msg)
{
    _BUser = "";
    if (data.find("PRIVMSG") > data.size())
        return "";
    _BUser = data.substr(1, data.find("!") - 1);
    std::string tmp = data.substr(data.find(":", 1) + 1, data.size());
    std::string command = tmp;
    tmp = tmp.substr(tmp.find(":", 0) + 1, tmp.size());
    
    if (tmp.size() < command.size())
        command = command.substr(0, command.size() - tmp.size());
    else
        tmp = "";
    tmp = trim(tmp, " :\r\n\t");
    command = trim(command," :\r\n");
    *msg = tmp;
    return command;
}

std::string Bot::Hello()
{
    return "Hello, my name is " + _Nick + "\r\n";
}

void Bot::Transfer(std::vector<std::string> obj)
{
    std::string input = obj[0];

    for (size_t i = 1; i < obj.size(); i++)
        input += " " + obj[i];

    std::fstream file;
    file.open(input);
    if (!file.is_open())
    {
        return ;
    }
    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::ofstream transfer;
    transfer.open("transfer.txt");
    transfer << fileContent;
    transfer.close();
}

std::string Bot::Help()
{
    return "Type one of these commands in the chat: SAYHELLO, EXIT, PYTHON, TRANSFER\r\n";
}

std::string Bot::PythonTheCat()
{
    std::ofstream file;
    file.open("PythonTheCat.txt");
    file << "meow" << std::endl;
    file <<  "  |\\__/,|   (`\\" << std::endl;
    file << "_.|o o  |_   ) )"<< std::endl;
    file << "-(((---(((--------"<< std::endl;
    file.close();
    return "Python is ready to see you, check the file PythonTheCat.txt\r\n";
}

int Bot::Handle(std::string msg)
{
    std::string text;
    std::string command = Parsing(msg, &text);

    if (_BUser.empty() || command.empty())
        return 0;
    else if (command == "SAYHELLO")
        text = Hello();
    else if (command == "HELP")
        text = Help();
    else if (command == "PYTHON")
        text = PythonTheCat();
    else if (command == "EXIT")
        return 1;
    else if(command.substr(0, 8) == "TRANSFER")
    {   
        text = command.substr(9, std::string::npos);
        std::vector<std::string> obj;
        obj.push_back(text);
        Transfer(obj);
    }
    else
        text = "Error: Wrong Input\r\n";
    if (!text.empty())
        SendMsg("PRIVMSG " + _BUser + " " + text);
    return 0;
}
