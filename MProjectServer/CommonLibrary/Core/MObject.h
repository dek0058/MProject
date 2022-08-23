#pragma once

class MObject {
public:
	MObject();
	~MObject();
	
public:
	bool IsInitialize() const {
		return is_initialize;
	}
	bool IsDestroy() const {
		return is_destroy;
	}

protected:
	size_t GetID() const {
		return id;
	}
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};

private:
	void Initialize() {
		is_initialize = true;
		OnInitialize();
	}
	void Destroy() {
		is_destroy = true;
		OnDestroy();
	}

private:
	size_t id;
	bool is_initialize = false;
	bool is_destroy = false;
};
