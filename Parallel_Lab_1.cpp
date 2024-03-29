﻿#include <iostream>
#include <thread>
#include <chrono>

void FirstThread(std::string &message)
{
	std::cout << "Thread ID\t" << std::this_thread::get_id() << "\tThis it FirstThread\t" << std::endl;
	message = "Hello, SecondThread!";
	std::cout << "Message changed" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::cout << "FirstThread has closed" << std::endl;
}

void SecondThread(const std::string &message)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "Thread ID\t" << std::this_thread::get_id() << "\tThis it SecondThread\t" << std::endl;
	while(true)		//Busy waiting
	{
		if (!message.empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Message recieved, message is " << "\"" << message << "\"" << std::endl;
			break;
		}	
	}
	std::cout << "SecondThread has closed" << std::endl;
}

int main()
{
	std::string message;
	std::thread firstThread(FirstThread, std::ref(message));
	std::thread secondThread(SecondThread, std::ref(message));
	firstThread.join();
	secondThread.join();
}