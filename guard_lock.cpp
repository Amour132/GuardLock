#include <iostream>
#include <mutex> 
#include <thread>

template<class Mutex>
class GuardLock
{
public:
	GuardLock(Mutex& mtx) :_mtx(mtx)
	{
		_mtx.lock();

	}

	~GuardLock()
	{
		_mtx.unlock();
	}

	GuardLock(const GuardLock<Mutex>&) = delete;
private:
	Mutex& _mtx;
};

std::mutex mtx;
static int n = 0;

void Func()
{
	for (size_t i = 0; i < 100000; i++)
	{
		GuardLock<std::mutex> mylock(mtx);
		n++;
	}

}

int main()
{
	int begin = clock();
	std::thread t1(Func);
	std::thread t2(Func);

	t1.join();
	t2.join();

	int end = clock();
	std::cout << n << std::endl;
	std::cout << end - begin << std::endl;
}