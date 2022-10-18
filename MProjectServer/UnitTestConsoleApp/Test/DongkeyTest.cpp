#include "DongkeyTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include "GlobalDefine.h"

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

UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	TUnitTest_AddTest(suite, DongkeyTest, TestCast);
	return suite;
}

