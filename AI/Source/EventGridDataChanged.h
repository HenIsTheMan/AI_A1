#pragma once

#include "Event.h"

class EventGridDataChanged final: public Event{
	EventGridDataChanged() = delete;
public:
	EventGridDataChanged(const int blockRow, const int blockCol);
	~EventGridDataChanged() = default;

	///Getters
	int GetBlockRow() const;
	int GetBlockCol() const;
private:
	int im_BlockRow;
	int im_BlockCol;

	EventGridDataChanged* Clone() const override;
};