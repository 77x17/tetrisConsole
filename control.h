#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <conio.h>
#include <Windows.h>
// using namespace std;


int nonBlockingGetChar();
int nonBlockingGetCharTask();

//This should be atomic. but I'm skipping it right here'
static bool getCharAlive{ false };

int get_char_from_key()
{
    static const long long TIMEOUT{10};

    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();
    long long elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::future<int> getCharHandle{ std::async(std::launch::async, nonBlockingGetCharTask) };
    do {
        //Other code here
        endTime = std::chrono::high_resolution_clock::now();
        elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (elapsedMilliseconds >= TIMEOUT) {
            //If the timer hit a certain amount, cancel the getChar task
            getCharAlive = false;
            while (getCharHandle.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
                //Wait for getCharAlive to exit
            }
            // std::cout << "User did not enter anything in the alotted time" << std::endl;
            return -1;
            break; //Move on to next step
        } else {
            //Otherwise, check if the getCharTask returned anything
            if (getCharHandle.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                int userInput{ getCharHandle.get() };
                if (userInput == -1) {
                    return -1;
                    // std::cout << "User did not enter anything in the alotted time" << std::endl;
                } else {
                    return userInput;
                    // std::cout << "User entered keycode " << userInput << std::endl;
                    //Do whatever with the user input
                }
                break; //Move on to next step
            }
        }
    } while (true);
}

int nonBlockingGetChar()
{
    if (_kbhit()) {
        return _getch();
    } else {
        return -1;
    }
}

int nonBlockingGetCharTask()
{
    getCharAlive = true;
    do {
        int returnValue{ nonBlockingGetChar() };
        if (returnValue != -1) {
            return returnValue;
        }
    } while (getCharAlive);
    return -1;
}