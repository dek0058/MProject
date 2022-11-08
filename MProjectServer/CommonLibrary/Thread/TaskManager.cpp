#include "TaskManager.h"
#include "GuardDefine.h"


struct FEvent {
private:
	DELETE_REFERENCE_CREATOR(FEvent)

public:
	class Awaiter {
		friend struct FEvent;
	public:
		using handler_type = std::coroutine_handle<>;

	public:
		Awaiter(FEvent const& _e) : e(_e) {}

		bool await_ready() const {
			if (e.awaiter.load() != nullptr) {
				throw std::runtime_error("Event already awaited!");
			}
			return e.is_notified;
		}

		bool await_suspend(handler_type _handler) noexcept {
			handler = _handler;
			if (e.is_notified) {
				return false;
			}
			e.awaiter.store(this);
			return true;
		}
		void await_resume() const noexcept {
		}

	private:
		FEvent const& e;
		handler_type handler;
	};

public:
	FEvent() = default;
	virtual ~FEvent() = default;

	Awaiter operator co_await() const noexcept {
		return Awaiter(*this);
	}

public:

	void Notify() noexcept {
		is_notified = true;
		auto* wait_awaiter = static_cast<Awaiter*>(awaiter.load());
		if (wait_awaiter != nullptr) {
			wait_awaiter->handler.resume();
		}
	}

private:
	friend class Awaiter;
	mutable std::atomic<void*> awaiter;
	mutable std::atomic_bool is_notified = false;
};

struct FTask {
	struct promise_type {
		promise_type() = default;
		~promise_type() = default;

		auto initial_suspend() {
			return std::suspend_never();
		}

		auto final_suspend() noexcept {
			return std::suspend_never();
		}

		void unhandled_exception() {
			std::terminate();
		}

		auto get_return_object() {
			return FTask{};
		}

		void return_void() {
		}
	};
};

namespace {
FTask TaskExecute(std::reference_wrapper<FEvent> _e, std::function<void()> _func) {
	co_await _e.get();
	if (_func) {
		_func();
	}
}
}

TaskManager::TaskManager() {
	events.reserve(32);
}

void TaskManager::Request(std::function<void()> _callback) {
	std::shared_ptr<FEvent> e = std::make_shared<FEvent>();
	try {
		TaskExecute(std::ref(*e.get()), _callback);
	}
	catch (std::exception const& e) {
		throw e;
	}
	events.emplace_back(std::ref(e));
}

void TaskManager::Execute() {
	if (events.empty()) {
		return;
	}
	
	for (auto& e : events) {
		if (e) {
			e->Notify();
		}
	}
	events.clear();
}

