#include "DongkeyTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include "GlobalDefine.h"
#include <future>

DongkeyTest::DongkeyTest(std::string const& _name) : UnitTestCase(_name) {
}

DongkeyTest::~DongkeyTest() {
}


namespace {

class C;

void Print(std::shared_ptr<C> _object);

class A : public std::enable_shared_from_this<A> {
public:
	A() {
		std::cout << "Constructor A" << std::endl;
	}
	int a = 0, b = 0, c = 0;
};


class B : public A {
public:
	B() {
		std::cout << "Constructor B" << std::endl;
	}

	float d = 0.0F;
};


class C : public B {
public:
	C() {
		std::cout << "Constructor C" << std::endl;
		/* [runtime error] bad_weak_ptr allocation
		shread_ptr은 객체의 생성자 호출 성공 이후 메모리를 할당한다.
		할당 전에는 객체 주소를 가르키는 첫번 째 복사본 weak_ptr만을 가지고 있다. */
		Print(std::static_pointer_cast<C>(shared_from_this()));
	}

	void Init() {
		Print(std::static_pointer_cast<C>(shared_from_this()));
	}

	void ThisPrint() {
		std::cout << "Print C" << std::endl;
	}
	
public:
	double e = 0.0;
};


void Print(std::shared_ptr<C> _object) {
	_object->ThisPrint();
}

}

void DongkeyTest::TestCast() {
	std::cout << std::endl;
	
	std::shared_ptr<C> c = std::make_shared<C>();
	// Success!
	c->Init();
}



namespace {

class JThreadTest : public std::enable_shared_from_this<JThreadTest> {
public:

	JThreadTest() {
		std::cout << "Constructor JThreadTest" << std::endl;
	}

	~JThreadTest() {
		std::cout << "Destructor JThreadTest" << std::endl;
	}

	virtual void Start(std::stop_token _token) {
		data = std::jthread(&JThreadTest::Thread_Run, this, _token);
	}

	void Thread_Run(std::stop_token _token) {

		auto thread_id = std::this_thread::get_id();
		std::stop_callback stop_callback(_token, [this, thread_id] {
			OnStop();
		});

		//while (!_token.stop_requested()) {
			OnUpdate();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

		
		//}
		//_token.swap
	}

	virtual void OnUpdate() {
		std::cout << "OnUpdate" << std::endl;
	}

	void OnStop() {
		std::cout << "OnStop" << typeid(this).name() << std::endl;
	}

public:
	std::jthread data;
};

class JThreadA : public JThreadTest {
public:
	JThreadA() {
		std::cout << "Constructor JThreadA" << std::endl;
	}

	virtual void OnUpdate() override {
		std::cout << "OnUpdate JThreadA" << std::endl;
	}
};

class JThreadB : public JThreadTest {
public:
	JThreadB() {
		std::cout << "Constructor JThreadB" << std::endl;
	}

	virtual void Start(std::stop_token _token) override {
		a.Start(_token);
		JThreadTest::Start(_token);
	}

	virtual void OnUpdate() override {
		std::cout << "OnUpdate JThreadB" << std::endl;
	}

public:
	JThreadA a;
	
};
}


void DongkeyTest::TestJThread() {
	
	std::cout << std::endl;

	JThreadB b;

	std::stop_source stop_source;
	b.Start(stop_source.get_token());
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	//stop_source.request_stop();

	std::cout << "is_stop:" << stop_source.stop_requested() << std::endl;
	std::cout << "possible_stop:" << stop_source.stop_possible() << std::endl;
	std::cout << "stop_request:" << stop_source.get_token().stop_requested() << std::endl;

	b.data.join();
	b.a.data.join();
}



UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	//TUnitTest_AddTest(suite, DongkeyTest, TestCast);
	//TUnitTest_AddTest(suite, DongkeyTest, TestJThread);
	return suite;
}

