#pragma once

class State final{
public:
	State();
	State(void (* const enter)(), void (* const update)(const double dt), void (* const exit)());
	~State() = default;

	///Setters
	void SetEnter(void (* const enter)());
	void SetUpdate(void (* const update)(const double dt));
	void SetExit(void (* const exit)());
private:
	void (*im_Enter)();
	void (*im_Update)(const double dt);
	void (*im_Exit)();

	void Enter();
	void Update(const double dt);
	void Exit();
};