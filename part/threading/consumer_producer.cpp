#include <chrono>  // std::chrono::miliseconds
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std::this_thread;

using std::cout;
using std::mutex;
using std::thread;
using std::queue;
using std::vector;
using std::string;
using std::chrono::milliseconds;
using std::to_string;
using std::condition_variable;
using std::unique_lock;

void producer(queue<string>* downloaded_pages, mutex* m, int index, condition_variable* cv)
{
    for (int i = 0; i < 5; i++) {
        // 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
        // 각 쓰레드 별로 다운로드 하는데 걸리는 시간이 다르다.
        sleep_for(milliseconds(100 * index));
        string content = "웹사이트 : " + to_string(i) + " from thread(" + to_string(index) + ")\n";

        // data 는 쓰레드 사이에서 공유되므로 critical section 에 넣어야 한다.
        {
            m->lock();
            downloaded_pages->push(content);
            m->unlock();
        }

        // 하나의 consumer에게 content가 준비되었음을 통지
        cv->notify_one();
    }
}

void consumer(queue<string>* downloaded_pages, mutex* m, int* num_processed, condition_variable* cv)
{
    // 전체 처리하는 페이지 개수가 5 * 5 = 25 개.
    while (*num_processed < 25) {

        // 1) without condition_var
        {
//            m->lock();
//            // 만일 현재 다운로드한 페이지가 없다면 다시 대기.
//            if (downloaded_pages->empty()) {
//                m->unlock();  // (Quiz) 여기서 unlock 을 안한다면 어떻게 될까요?
//
//                // 10 밀리초 뒤에 다시 확인한다.
//                sleep_for(milliseconds(10));
//                continue;
//            }
        }

        // 2) with condition_var
        {
            unique_lock<mutex> lock(*m);

            // wait: 해당 조건이 true가 될 때까지 현재 쓰레드 대기
            // wait_for: wait + duration 을 입력받아, 해당 기간내에 통지가 없으면 timeout 발생시키고 쓰레드 wait 중단
            // wait_until: wait + time-point 를 입력받아, 특정 시점까지 통지가 없으면 timeout 발생시키고 쓰레드 wait 중단
            cv->wait(lock, [&] { return !downloaded_pages->empty() || *num_processed == 25; });

            if (*num_processed == 25) {
                lock.unlock();
                return;
            }
        }

        // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
        string content = downloaded_pages->front();
        downloaded_pages->pop();

        (*num_processed)++;
        m->unlock();

        // content 를 처리한다.
        cout << content;
        sleep_for(milliseconds(80));
    }
}

int consumer_producer()
{
    queue<string> downloaded_pages; // 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
    mutex m;
    condition_variable cv; // producer - consumer 간의 notify 통지를 하기 위함

    vector<thread> producers;
    for (int i = 0; i < 5; i++) {
        producers.push_back(thread(producer, &downloaded_pages, &m, i + 1, &cv));
    }

    int num_processed = 0;
    vector<thread> consumers;
    for (int i = 0; i < 3; i++) {
        consumers.push_back(thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
    }

    for (int i = 0; i < 5; i++) {
        producers[i].join();
    }

    // 나머지 자고 있는 쓰레드들을 모두 깨운다.
    cv.notify_all();

    for (int i = 0; i < 3; i++) {
        consumers[i].join();
    }

    return 0;
}
